#ifndef CLIENTBTHREAD_H
#define CLIENTBTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

// C language headers in extern "C"
extern "C" {
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <string.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <pthread.h>
    #include <signal.h>
}

class ClientBThread : public QThread
{
    Q_OBJECT

public:
    explicit ClientBThread(QObject *parent = nullptr);
    ~ClientBThread();

    // Send city name to server
    bool sendCityName(const QString &city, bool autoConnect = false);

    // TCP connection control
    bool connectToServer(const QString &host = "192.168.16.181", quint16 port = 60000);
    void disconnectFromServer();
    bool isConnected() const;

    // Check if we have a cached connection
    bool hasConnection() const { return connectionEstablished; }

    // Thread control
    void stopThread();

    // Set connection mode
    void setAutoConnect(bool autoConnect) { this->autoConnect = autoConnect; }

signals:
    // Weather data update signal
    void weatherDataReceived(const QString &city,
                            const QString &weather,
                            const QString &temperature,
                            const QString &humidity);

    // Command receive signal
    void commandReceived(const QString &command);

    // Connection status signals
    void connectedToServer();
    void disconnectedFromServer();
    void connectionError(const QString &error);

    // Data sending status
    void cityNameSent(const QString &city);
    void dataSendError(const QString &error);

    // Debug information
    void debugMessage(const QString &msg);

    // New signal for manual connection completed
    void manualConnectionCompleted(bool success);

protected:
    void run() override;

private slots:
    void onReconnectTimeout();

private:
    // C language TCP client data structure
    typedef struct {
        int socket_fd;
        struct sockaddr_in server_addr;
        bool connected;
        bool running;
        char server_ip[64];
        int server_port;
        pthread_mutex_t socket_mutex;
    } TCPClient;

    // TCP client instance
    TCPClient tcp_client;

    // Qt thread control
    bool thread_running;
    bool connectionEstablished;
    bool autoConnect;
    QMutex thread_mutex;
    QWaitCondition thread_cond;

    // Server information
    QString serverHost;
    quint16 serverPort;

    // Current city for sending
    QString currentCity;

    // Buffer size
    enum { BUFFER_SIZE = 4096 };

    // Message type enumeration
    enum MessageType {
        MSG_WEATHER,
        MSG_COMMAND,
        MSG_CONNECTION_NOTIFICATION,
        MSG_UNKNOWN
    };

    // C language TCP client functions
    bool c_tcp_connect(const char* host, int port);
    void c_tcp_disconnect();
    bool c_tcp_is_connected() const;
    bool c_tcp_send(const char* data, int length);
    int c_tcp_receive(char* buffer, int buffer_size, int timeout_ms = 1000);

    // Manual connection function
    bool manualConnectAndSend(const QString &city);

    // Data parsing functions
    QString parseTemperature(const QString &tempStr) const;
    void processReceivedMessage(const char* message);

    // Message classification function
    MessageType classifyMessage(const QString &message);
    // Weather data parsing function
    void parseWeatherData(const QString &msg);

    // Send identity
    void sendIdentity();

    // Thread-safe signal emission
    void emitWeatherData(const QString &city, const QString &weather,
                        const QString &temperature, const QString &humidity);
    void emitCommand(const QString &command);
    void emitDebug(const QString &msg);
};

#endif // CLIENTBTHREAD_H
