#ifndef VOICETHREAD_H
#define VOICETHREAD_H

#include <QObject>
#include <QThread>
#include <QString>

class VoiceThread : public QThread
{
    Q_OBJECT
public:
    explicit VoiceThread(QObject *parent = nullptr);
    ~VoiceThread();

    void stopRecording();

signals:
    void voiceCommand(const QString &command);
    void statusChanged(const QString &status);
    void voiceRecordingFinished();  // 录音完成信号

protected:
    void run() override;

private:
    bool m_stopFlag;
    int m_socketFd;
    QString m_serverIp;
    int m_serverPort;

    // 私有方法
    void recordAudio();
    bool socketConnect();
    void sendAudioFile();
    QString receiveResult();
};

#endif // VOICETHREAD_H
