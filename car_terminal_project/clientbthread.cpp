#include "clientbthread.h"
#include <QDebug>
#include <QTimer>
#include <QCoreApplication>
#include <QStringList>
#include <QElapsedTimer>
#include <QRegularExpression>

ClientBThread::ClientBThread(QObject *parent)
    : QThread(parent)
    , thread_running(true)
    , serverHost("192.168.16.181")
    , serverPort(60000)
{
    // Initialize C language TCP client structure
    memset(&tcp_client, 0, sizeof(TCPClient));
    tcp_client.socket_fd = -1;
    tcp_client.connected = false;
    tcp_client.running = false;
    strncpy(tcp_client.server_ip, "192.168.16.181", sizeof(tcp_client.server_ip) - 1);
    tcp_client.server_port = 60000;
    pthread_mutex_init(&tcp_client.socket_mutex, NULL);
}

ClientBThread::~ClientBThread()
{
    stopThread();
    wait(1000);

    // Destroy mutex
    pthread_mutex_destroy(&tcp_client.socket_mutex);
}

bool ClientBThread::connectToServer(const QString &host, quint16 port)
{
    serverHost = host;
    serverPort = port;

    // If already running, return directly
    if (isRunning() && isConnected()) {
        emit debugMessage("Already connected to server");
        return true;
    }

    // Start thread if not running
    if (!isRunning()) {
        start();
    }

    return true;
}

void ClientBThread::disconnectFromServer()
{
    c_tcp_disconnect();
}

bool ClientBThread::isConnected() const
{
    return c_tcp_is_connected();
}

void ClientBThread::stopThread()
{
    thread_mutex.lock();
    thread_running = false;
    thread_cond.wakeAll();
    thread_mutex.unlock();

    // Disconnect TCP
    c_tcp_disconnect();

    quit();
    wait(500);
}

void ClientBThread::run()
{
    qDebug() << "ClientBThread: C TCP client thread started";

    // Set thread running flag
    thread_mutex.lock();
    tcp_client.running = true;
    thread_mutex.unlock();

    // Connect to server
    QByteArray hostBytes = serverHost.toUtf8();
    const char* host = hostBytes.constData();

    if (!c_tcp_connect(host, serverPort)) {
        emit connectionError("Failed to connect to server");
        emit debugMessage("Failed to connect to server");

        thread_mutex.lock();
        tcp_client.running = false;
        thread_mutex.unlock();
        return;
    }

    emit connectedToServer();
    emit debugMessage("Connected to server");

    // Send identity
    sendIdentity();

    // Main receive loop
    char buffer[BUFFER_SIZE];
    int consecutive_timeouts = 0;
    const int MAX_TIMEOUTS = 10; // 连续超时10次才认为是连接问题

    while (thread_running) {
        // Check if need to exit
        thread_mutex.lock();
        bool running = thread_running && tcp_client.running;
        thread_mutex.unlock();

        if (!running) {
            break;
        }

        // Check connection status
        if (!c_tcp_is_connected()) {
            emitDebug("Connection lost, attempting to reconnect...");

            // Try to reconnect
            if (c_tcp_connect(host, serverPort)) {
                sendIdentity();
                emit connectedToServer();
                emitDebug("Reconnected to server");
                consecutive_timeouts = 0; // 重置超时计数
            } else {
                msleep(5000); // Wait 5 seconds before retry
                continue;
            }
        }

        // Receive data with timeout
        int bytes_received = c_tcp_receive(buffer, BUFFER_SIZE - 1, 500); // 500ms超时

        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            QString message = QString::fromUtf8(buffer).trimmed();

            // 防止重复处理相同的消息
            static QString lastMessage;
            if (message == lastMessage && !message.isEmpty()) {
                continue;
            }
            lastMessage = message;

            // 只有在真正有数据时才打印调试信息
            if (message.length() > 0) {
                emitDebug("Received data: " + message);
            }

            // Process received message
            processReceivedMessage(buffer);
            consecutive_timeouts = 0; // 收到数据，重置超时计数
        }
        else if (bytes_received == 0) {
            // Connection closed
            emitDebug("Server closed connection");
            c_tcp_disconnect();
            emit disconnectedFromServer();
            break;
        }
        else if (bytes_received == -2) {
            // Timeout (这是我们在c_tcp_receive中返回的-2)
            consecutive_timeouts++;
            if (consecutive_timeouts >= MAX_TIMEOUTS) {
                // 连续超时多次，可能是连接问题
                emitDebug("Connection timeout detected, checking connection...");
                if (!c_tcp_is_connected()) {
                    c_tcp_disconnect();
                    emit disconnectedFromServer();
                    break;
                }
                consecutive_timeouts = 0;
            }
            // 超时是正常现象，不打印错误信息
        }
        else if (bytes_received < 0) {
            // 真正的错误
            if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
                // 只有当errno不是这些"非错误"时才打印
                const char* err_msg = strerror(errno);
                if (err_msg && strlen(err_msg) > 0 && strcmp(err_msg, "Success") != 0) {
                    emitDebug(QString("Receive error: %1").arg(err_msg));
                }
            }
            consecutive_timeouts++;
            if (consecutive_timeouts >= MAX_TIMEOUTS) {
                emitDebug("Too many receive errors, reconnecting...");
                c_tcp_disconnect();
                msleep(1000);
                continue;
            }
        }

        // Process Qt events
        QCoreApplication::processEvents();
        msleep(50);  // Reduce CPU usage
    }

    // Cleanup
    c_tcp_disconnect();

    thread_mutex.lock();
    tcp_client.running = false;
    thread_mutex.unlock();

    emit disconnectedFromServer();
    emit debugMessage("TCP client thread ended");

    qDebug() << "ClientBThread: C TCP client thread ended";
}

void ClientBThread::onReconnectTimeout()
{
    if (thread_running && !isConnected()) {
        emit debugMessage("Attempting to reconnect...");
        QByteArray hostBytes = serverHost.toUtf8();
        const char* host = hostBytes.constData();

        if (c_tcp_connect(host, serverPort)) {
            sendIdentity();
            emit connectedToServer();
            emit debugMessage("Reconnection successful");
        } else {
            // Try again after 5 seconds
            QTimer::singleShot(5000, this, SLOT(onReconnectTimeout()));
        }
    }
}

// ==================== C LANGUAGE TCP CLIENT IMPLEMENTATION ====================

bool ClientBThread::c_tcp_connect(const char* host, int port)
{
    pthread_mutex_lock(&tcp_client.socket_mutex);

    // If already connected, disconnect first
    if (tcp_client.connected && tcp_client.socket_fd >= 0) {
        ::close(tcp_client.socket_fd);
        tcp_client.socket_fd = -1;
        tcp_client.connected = false;
    }

    // Create socket
    tcp_client.socket_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_client.socket_fd < 0) {
        emitDebug(QString("Failed to create socket: %1").arg(strerror(errno)));
        pthread_mutex_unlock(&tcp_client.socket_mutex);
        return false;
    }

    // Set socket options for better stability
    int optval = 1;
    setsockopt(tcp_client.socket_fd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
    setsockopt(tcp_client.socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    // Set timeout
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    setsockopt(tcp_client.socket_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(tcp_client.socket_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    // Set server address
    memset(&tcp_client.server_addr, 0, sizeof(tcp_client.server_addr));
    tcp_client.server_addr.sin_family = AF_INET;
    tcp_client.server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &tcp_client.server_addr.sin_addr) <= 0) {
        // If IP conversion fails, try DNS resolution
        struct hostent *he = gethostbyname(host);
        if (he == NULL) {
            emitDebug(QString("DNS resolution failed: %1").arg(host));
            ::close(tcp_client.socket_fd);
            tcp_client.socket_fd = -1;
            pthread_mutex_unlock(&tcp_client.socket_mutex);
            return false;
        }
        memcpy(&tcp_client.server_addr.sin_addr, he->h_addr, he->h_length);
    }

    // Connect to server with timeout
    int connect_result = ::connect(tcp_client.socket_fd,
                                   (struct sockaddr*)&tcp_client.server_addr,
                                   sizeof(tcp_client.server_addr));

    if (connect_result < 0) {
        if (errno != EINPROGRESS) {
            emitDebug(QString("Connection failed: %1").arg(strerror(errno)));
            ::close(tcp_client.socket_fd);
            tcp_client.socket_fd = -1;
            pthread_mutex_unlock(&tcp_client.socket_mutex);
            return false;
        }

        // Use select to wait for connection completion
        fd_set writefds;
        struct timeval tv;

        FD_ZERO(&writefds);
        FD_SET(tcp_client.socket_fd, &writefds);

        tv.tv_sec = 5;  // 5 second timeout
        tv.tv_usec = 0;

        int select_result = select(tcp_client.socket_fd + 1, NULL, &writefds, NULL, &tv);

        if (select_result <= 0) {
            emitDebug("Connection timeout");
            ::close(tcp_client.socket_fd);
            tcp_client.socket_fd = -1;
            pthread_mutex_unlock(&tcp_client.socket_mutex);
            return false;
        }

        // Check socket error
        int error = 0;
        socklen_t len = sizeof(error);
        if (getsockopt(tcp_client.socket_fd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
            emitDebug(QString("Failed to get socket error: %1").arg(strerror(errno)));
            ::close(tcp_client.socket_fd);
            tcp_client.socket_fd = -1;
            pthread_mutex_unlock(&tcp_client.socket_mutex);
            return false;
        }

        if (error != 0) {
            emitDebug(QString("Connection error: %1").arg(strerror(error)));
            ::close(tcp_client.socket_fd);
            tcp_client.socket_fd = -1;
            pthread_mutex_unlock(&tcp_client.socket_mutex);
            return false;
        }
    }

    strncpy(tcp_client.server_ip, host, sizeof(tcp_client.server_ip) - 1);
    tcp_client.server_port = port;
    tcp_client.connected = true;

    pthread_mutex_unlock(&tcp_client.socket_mutex);
    return true;
}

void ClientBThread::c_tcp_disconnect()
{
    pthread_mutex_lock(&tcp_client.socket_mutex);

    if (tcp_client.socket_fd >= 0) {
        ::close(tcp_client.socket_fd);
        tcp_client.socket_fd = -1;
    }

    tcp_client.connected = false;

    pthread_mutex_unlock(&tcp_client.socket_mutex);
}

bool ClientBThread::c_tcp_is_connected() const
{
    bool connected = false;

    // Use const_cast to remove const restriction because pthread_mutex_lock is not const
    ClientBThread* self = const_cast<ClientBThread*>(this);
    pthread_mutex_lock(&self->tcp_client.socket_mutex);
    connected = tcp_client.connected && tcp_client.socket_fd >= 0;
    pthread_mutex_unlock(&self->tcp_client.socket_mutex);

    return connected;
}

bool ClientBThread::c_tcp_send(const char* data, int length)
{
    if (!c_tcp_is_connected() || data == NULL || length <= 0) {
        return false;
    }

    pthread_mutex_lock(&tcp_client.socket_mutex);

    int total_sent = 0;
    while (total_sent < length) {
        int sent = ::send(tcp_client.socket_fd, data + total_sent, length - total_sent, 0);
        if (sent <= 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
                // Buffer full or interrupted, wait a bit
                usleep(1000);
                continue;
            }

            // Send failed
            tcp_client.connected = false;
            pthread_mutex_unlock(&tcp_client.socket_mutex);
            return false;
        }
        total_sent += sent;
    }

    pthread_mutex_unlock(&tcp_client.socket_mutex);
    return true;
}

int ClientBThread::c_tcp_receive(char* buffer, int buffer_size, int timeout_ms)
{
    if (!c_tcp_is_connected() || buffer == NULL || buffer_size <= 0) {
        return -1;
    }

    pthread_mutex_lock(&tcp_client.socket_mutex);

    // Set receive timeout
    fd_set readfds;
    struct timeval tv;

    FD_ZERO(&readfds);
    FD_SET(tcp_client.socket_fd, &readfds);

    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;

    int select_result = select(tcp_client.socket_fd + 1, &readfds, NULL, NULL, &tv);

    if (select_result > 0) {
        if (FD_ISSET(tcp_client.socket_fd, &readfds)) {
            int bytes_received = recv(tcp_client.socket_fd, buffer, buffer_size - 1, 0);

            if (bytes_received == 0) {
                // Connection closed
                tcp_client.connected = false;
                pthread_mutex_unlock(&tcp_client.socket_mutex);
                return 0;
            } else if (bytes_received < 0) {
                // Receive error
                if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
                    tcp_client.connected = false;
                }
                pthread_mutex_unlock(&tcp_client.socket_mutex);
                return -1;
            }

            pthread_mutex_unlock(&tcp_client.socket_mutex);
            return bytes_received;
        }
    }

    pthread_mutex_unlock(&tcp_client.socket_mutex);

    // Timeout or error
    if (select_result == 0) {
        return -2; // 特殊值表示超时
    }
    return -1; // 其他错误
}

// ==================== DATA PROCESSING FUNCTIONS ====================
//消息分类
ClientBThread::MessageType ClientBThread::classifyMessage(const QString &message)
{
    if (message.contains("CLIENT_B_CONNECTED") ||
        message.contains("CLIENT_C_CONNECTED") ||
        message == "CONNECTED") {
        return MSG_CONNECTION_NOTIFICATION;
    }

    if (message.contains("LED_") ||
        message.contains("BUZZER_") ||
        message.contains("CTRL:")) {
        return MSG_COMMAND;
    }

    if (message.contains("城市:") ||
        message.contains("天气:") ||
        message.contains("温度:") ||
        message.contains("湿度:")) {
        return MSG_WEATHER;
    }

    return MSG_UNKNOWN;
}

void ClientBThread::sendIdentity()
{
    const char* identity = "CLIENT_B";
    if (c_tcp_send(identity, strlen(identity))) {
        emitDebug("Sent identity: CLIENT_B");
    } else {
        emit dataSendError("Failed to send identity");
        emitDebug("Failed to send identity");
    }
}

void ClientBThread::sendCityName(const QString &city)
{
    if (!isConnected()) {
        emit dataSendError("Not connected to server");
        emitDebug("Cannot send city name, not connected");
        return;
    }

    if (city.isEmpty()) {
        emitDebug("City name cannot be empty");
        return;
    }

    QByteArray cityBytes = city.toUtf8();
    const char* cityData = cityBytes.constData();

    if (c_tcp_send(cityData, strlen(cityData))) {
        emit cityNameSent(city);
        emitDebug("Sent city name: " + city);
    } else {
        emit dataSendError("Failed to send city name: " + city);
        emitDebug("Failed to send city name: " + city);
    }
}

void ClientBThread::processReceivedMessage(const char* message)
{
    QString msg = QString::fromUtf8(message).trimmed();

    if (msg.isEmpty()) {
        return;
    }

    // 使用分类函数确定消息类型
    MessageType type = classifyMessage(msg);

    switch (type) {
    case MSG_CONNECTION_NOTIFICATION:
        emitDebug("Received connection notification: " + msg);
        // 不处理连接通知，这些是给客户端A的
        return;

    case MSG_COMMAND:
        emitDebug("Received command: " + msg);
        emitCommand(msg);
        return;

    case MSG_WEATHER:
        emitDebug("Parsing weather data");
        parseWeatherData(msg);
        return;

    case MSG_UNKNOWN:
        emitDebug("Unknown message type: " + msg);
        return;
    }
}

//天气数据解析
void ClientBThread::parseWeatherData(const QString &msg)
{
    // 更健壮的天气数据解析
    QStringList lines = msg.split("\n");

    // 手动过滤空行
    QStringList filteredLines;
    for (const QString &line : lines) {
        if (!line.trimmed().isEmpty()) {
            filteredLines.append(line);
        }
    }

    QString city, weather, temperature, humidity;

    // 使用正则表达式提取信息
    QRegularExpression cityRegex("城市:\\s*(.+)");
    QRegularExpression weatherRegex("天气:\\s*(.+)");
    QRegularExpression tempRegex("温度:\\s*([-+]?\\d*\\.?\\d+).*");
    QRegularExpression humidityRegex("湿度:\\s*(\\d+%?)");

    for (const QString &line : filteredLines) {
        QString trimmedLine = line.trimmed();

        QRegularExpressionMatch match;

        if (city.isEmpty() && (match = cityRegex.match(trimmedLine)).hasMatch()) {
            city = match.captured(1).trimmed();
        }
        else if (weather.isEmpty() && (match = weatherRegex.match(trimmedLine)).hasMatch()) {
            weather = match.captured(1).trimmed();
        }
        else if (temperature.isEmpty() && (match = tempRegex.match(trimmedLine)).hasMatch()) {
            temperature = match.captured(1).trimmed();
        }
        else if (humidity.isEmpty() && (match = humidityRegex.match(trimmedLine)).hasMatch()) {
            humidity = match.captured(1).trimmed();
        }
    }

    // 验证并修正数据
    if (city.isEmpty()) city = "未知城市";
    if (weather.isEmpty()) weather = "未知";
    if (temperature.isEmpty()) temperature = "25"; // 默认温度
    if (humidity.isEmpty()) humidity = "N/A%";

    // 确保温度是纯数字
    temperature = parseTemperature(temperature);

    emitDebug(QString("Parsed weather - City:%1 Weather:%2 Temp:%3°C Humidity:%4")
              .arg(city).arg(weather).arg(temperature).arg(humidity));

    emitWeatherData(city, weather, temperature, humidity);
}

QString ClientBThread::parseTemperature(const QString &tempStr) const
{
    // 提取温度数字部分
    QString result;
    bool hasDecimal = false;

    for (int i = 0; i < tempStr.length(); ++i) {
        QChar ch = tempStr.at(i);

        if (ch.isDigit()) {
            result.append(ch);
        }
        else if (ch == '.' && !hasDecimal) {
            result.append(ch);
            hasDecimal = true;
        }
        else if (ch == '-') {
            result.append(ch);
        }
    }

    // 如果没有提取到数字，返回默认值
    if (result.isEmpty() || result == "-") {
        return "25";
    }

    // 确保温度值合理
    bool ok;
    double temp = result.toDouble(&ok);
    if (ok && temp >= -50 && temp <= 60) {
        return QString::number(temp, 'f', 0); // 取整
    }

    return "25";
}

// ==================== THREAD-SAFE SIGNAL EMISSION ====================

void ClientBThread::emitWeatherData(const QString &city, const QString &weather,
                                   const QString &temperature, const QString &humidity)
{
    // Emit signal in main thread
    QMetaObject::invokeMethod(this, "weatherDataReceived", Qt::QueuedConnection,
                              Q_ARG(QString, city),
                              Q_ARG(QString, weather),
                              Q_ARG(QString, temperature),
                              Q_ARG(QString, humidity));
}

void ClientBThread::emitCommand(const QString &command)
{
    // Emit signal in main thread
    QMetaObject::invokeMethod(this, "commandReceived", Qt::QueuedConnection,
                              Q_ARG(QString, command));
}

void ClientBThread::emitDebug(const QString &msg)
{
    // Emit signal in main thread
    QMetaObject::invokeMethod(this, "debugMessage", Qt::QueuedConnection,
                              Q_ARG(QString, msg));
}
