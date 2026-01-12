#include "voicethread.h"
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QProcess>
#include <QtEndian>

// 使用extern "C"包裹C标准库头文件
extern "C" {
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
}

VoiceThread::VoiceThread(QObject *parent)
    : QThread(parent)
    , m_stopFlag(false)
    , m_socketFd(-1)
    , m_serverIp("192.168.16.181")
    , m_serverPort(55555)
{
    qDebug() << "VoiceThread created";
}

VoiceThread::~VoiceThread()
{
    m_stopFlag = true;
    if (isRunning()) {
        wait();
    }

    if (m_socketFd != -1) {
        ::close(m_socketFd);
    }
}

void VoiceThread::stopRecording()
{
    m_stopFlag = true;
}

void VoiceThread::run()
{
    qDebug() << "VoiceThread started";

    // Step 1: Record audio
    emit statusChanged("Recording...");
    qDebug() << "Start recording audio";

    recordAudio();
    emit voiceRecordingFinished();  // 发出录音完成信号

    if (m_stopFlag) {
        qDebug() << "Recording stopped by user";
        return;
    }

    // Step 2: Connect to server
    emit statusChanged("Connecting to server...");
    qDebug() << "Connecting to server:" << m_serverIp << ":" << m_serverPort;

    if (!socketConnect()) {
        emit statusChanged("Connection failed");
        qDebug() << "Failed to connect to server";
        return;
    }

    // Step 3: Send audio file
    emit statusChanged("Sending audio...");
    qDebug() << "Sending audio file to server";

    sendAudioFile();

    // Step 4: Receive recognition result
    emit statusChanged("Receiving result...");
    qDebug() << "Waiting for recognition result";

    QString result = receiveResult();
    qDebug() << "Received result:" << result;

    // Step 5: Emit signal with result
    if (!result.isEmpty() && !m_stopFlag) {
        emit voiceCommand(result);
        emit statusChanged("Recognition complete");
    } else {
        emit statusChanged("Recognition failed");
    }

    // Close socket
    if (m_socketFd != -1) {
        ::close(m_socketFd);
        m_socketFd = -1;
    }

    qDebug() << "VoiceThread finished";
}

void VoiceThread::recordAudio()
{
    // 使用arecord命令录音3秒
    qDebug() << "Recording audio for 3 seconds...";

    // 构建命令
    QString command = "arecord -d3 -c1 -r16000 -twav -fS16_LE /tmp/voice.wav";
    qDebug() << "Execute command:" << command;

    // 使用QProcess执行命令
    QProcess process;
    process.start(command);

    // 等待录音完成（最多等待4秒）
    if (!process.waitForFinished(4000)) {
        qDebug() << "Audio recording timeout";
        emit statusChanged("Recording timeout");
        return;
    }

    int exitCode = process.exitCode();
    if (exitCode != 0) {
        qDebug() << "Audio recording failed with code:" << exitCode;
        emit statusChanged("Recording failed");
    } else {
        qDebug() << "Audio recording completed successfully";
        emit statusChanged("Recording completed");
    }
}

bool VoiceThread::socketConnect()
{
    // Create socket
    m_socketFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (m_socketFd < 0) {
        qDebug() << "Socket creation failed:" << strerror(errno);
        return false;
    }

    // Set server address
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(m_serverPort);

    // Convert IP address
    QByteArray ipBytes = m_serverIp.toUtf8();
    if (::inet_pton(AF_INET, ipBytes.constData(), &serverAddr.sin_addr) <= 0) {
        qDebug() << "Invalid address / Address not supported";
        ::close(m_socketFd);
        m_socketFd = -1;
        return false;
    }

    // Connect to server with timeout
    struct timeval tv;
    tv.tv_sec = 5;  // 5 seconds timeout
    tv.tv_usec = 0;
    ::setsockopt(m_socketFd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&tv, sizeof(tv));
    ::setsockopt(m_socketFd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));

    // Use ::connect to avoid conflict with Qt's connect
    if (::connect(m_socketFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        qDebug() << "Connection to server failed:" << strerror(errno);
        ::close(m_socketFd);
        m_socketFd = -1;
        return false;
    }

    qDebug() << "Connected to server successfully";
    return true;
}

void VoiceThread::sendAudioFile()
{
    QFile audioFile("/tmp/voice.wav");
        if (!audioFile.open(QIODevice::ReadOnly)) {
            qDebug() << "Cannot open audio file:" << audioFile.errorString();
            return;
        }

        // Get file size
        qint64 fileSize = audioFile.size();
        qDebug() << "Audio file size:" << fileSize << "bytes";

        // Send file size (4 bytes) - 使用htonl进行字节序转换
        quint32 netSize = htonl(static_cast<quint32>(fileSize));  // 改为使用htonl
        ssize_t sent = ::send(m_socketFd, &netSize, sizeof(netSize), 0);
        if (sent != sizeof(netSize)) {
            qDebug() << "Failed to send file size:" << strerror(errno);
            audioFile.close();
            return;
        }

    // Send file data
    char buffer[1024];
    qint64 totalSent = 0;

    while (!audioFile.atEnd() && !m_stopFlag) {
        qint64 bytesRead = audioFile.read(buffer, sizeof(buffer));
        if (bytesRead > 0) {
            ssize_t bytesSent = ::send(m_socketFd, buffer, bytesRead, 0);
            if (bytesSent != bytesRead) {
                qDebug() << "Failed to send audio data:" << strerror(errno);
                break;
            }
            totalSent += bytesSent;
        }
    }

    audioFile.close();
    qDebug() << "Audio file sent:" << totalSent << "bytes";

    // 添加一个小的延迟，让服务器开始处理
    msleep(100);
}

QString VoiceThread::receiveResult()
{
    if (m_socketFd == -1) {
        qDebug() << "Socket not connected";
        return "";
    }

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    // 增加超时时间到30秒，因为语音识别需要时间
    struct timeval tv;
    tv.tv_sec = 30;  // 改为30秒
    tv.tv_usec = 0;
    ::setsockopt(m_socketFd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));

    // Receive recognition result
    ssize_t bytesReceived = ::recv(m_socketFd, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        qDebug() << "Successfully received" << bytesReceived << "bytes";
        qDebug() << "Raw data received:" << QByteArray(buffer, bytesReceived).toHex();
        return QString::fromUtf8(buffer);
    } else if (bytesReceived == 0) {
        qDebug() << "Server closed connection";
        return "";
    } else {
        qDebug() << "Failed to receive result or timeout:" << strerror(errno);
        return "";
    }
}
