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
    , connectionEstablished(false)
    , manualWeatherOnly(true)
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

    qDebug() << "ClientBThread: Initialized - will maintain connection for commands";
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

    qDebug() << "ClientBThread: Connecting to server..." << host << ":" << port;

    // Start thread if not running
    if (!isRunning()) {
        start();
        return true;
    }

    return true;
}

bool ClientBThread::sendCityName(const QString &city)
{
    qDebug() << "ClientBThread: Sending city name:" << city;

    if (manualWeatherOnly) {
        // Use manual connection for weather query
        return manualWeatherQuery(city);
    } else {
        // Use existing connection
        if (!c_tcp_is_connected()) {
            qDebug() << "ClientBThread: Not connected, cannot send city name";
            return false;
        }

        QByteArray cityBytes = city.toUtf8();
        const char* cityData = cityBytes.constData();

        if (c_tcp_send(cityData, strlen(cityData))) {
            emit cityNameSent(city);
            qDebug() << "ClientBThread: City name sent via existing connection:" << city;
            return true;
        } else {
            qDebug() << "ClientBThread: Failed to send city name";
            return false;
        }
    }
}

bool ClientBThread::maintainConnectionForCommands()
{
    qDebug() << "ClientBThread: Establishing persistent connection for command reception";

    // Connect to server
    QByteArray hostBytes = serverHost.toUtf8();
    const char* host = hostBytes.constData();

    if (!c_tcp_connect(host, serverPort)) {
        qDebug() << "ClientBThread: Failed to connect to server for command reception";
        emit connectionError("Connection failed for command reception");
        return false;
    }

    qDebug() << "ClientBThread: Connected to server for command reception";
    emit connectedToServer();

    // Send identity
    sendIdentity();

    // Main loop to receive commands
    char buffer[BUFFER_SIZE];

    while (thread_running && c_tcp_is_connected()) {
        memset(buffer, 0, sizeof(buffer));

        // Receive with timeout
        int bytes_received = c_tcp_receive(buffer, BUFFER_SIZE - 1, 5000);

        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            QString message = QString::fromUtf8(buffer).trimmed();

            qDebug() << "ClientBThread: Received message:" << message;

            // Process the message
            processReceivedMessage(buffer);
        } else if (bytes_received == 0) {
            qDebug() << "ClientBThread: Server closed connection";
            break;
        } else if (bytes_received == -2) {
            // Timeout, continue
            continue;
        } else {
            // Error
            qDebug() << "ClientBThread: Receive error, breaking connection";
            break;
        }

        QCoreApplication::processEvents();
    }

    // Disconnect
    c_tcp_disconnect();
    connectionEstablished = false;
    emit disconnectedFromServer();

    qDebug() << "ClientBThread: Connection lost, will attempt to reconnect";
    return false;
}

bool ClientBThread::manualWeatherQuery(const QString &city)
{
    qDebug() << "ClientBThread: Starting manual weather query for city:" << city;

    // Create a temporary connection for weather query
    QByteArray hostBytes = serverHost.toUtf8();
    const char* host = hostBytes.constData();

    int temp_socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (temp_socket < 0) {
        qDebug() << "ClientBThread: Failed to create socket for weather query";
        return false;
    }

    // Set timeout
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    setsockopt(temp_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(temp_socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    // Prepare server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(serverPort);

    if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
        qDebug() << "ClientBThread: Invalid IP address for weather query";
        ::close(temp_socket);
        return false;
    }

    // Connect
    if (::connect(temp_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        qDebug() << "ClientBThread: Connection failed for weather query:" << strerror(errno);
        ::close(temp_socket);
        return false;
    }

    qDebug() << "ClientBThread: Connected for weather query";

    // Send identity
    const char* identity = "CLIENT_B";
    if (::send(temp_socket, identity, strlen(identity), 0) < 0) {
        qDebug() << "ClientBThread: Failed to send identity for weather query";
        ::close(temp_socket);
        return false;
    }

    // Send city name
    QByteArray cityBytes = city.toUtf8();
    const char* cityData = cityBytes.constData();

    if (::send(temp_socket, cityData, strlen(cityData), 0) < 0) {
        qDebug() << "ClientBThread: Failed to send city name for weather query";
        ::close(temp_socket);
        return false;
    }

    qDebug() << "ClientBThread: City name sent for weather query:" << city;
    emit cityNameSent(city);

    // Receive weather data
    char buffer[BUFFER_SIZE];
    bool weatherReceived = false;
    QElapsedTimer timer;
    timer.start();

    while (!weatherReceived && timer.elapsed() < 10000) {
        memset(buffer, 0, sizeof(buffer));

        int bytes_received = recv(temp_socket, buffer, BUFFER_SIZE - 1, 0);

        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            QString message = QString::fromUtf8(buffer).trimmed();

            qDebug() << "ClientBThread: Received weather data:" << message;

            if (message.contains("城市:") || message.contains("天气:") ||
                message.contains("温度:") || message.contains("湿度:")) {
                processReceivedMessage(buffer);
                weatherReceived = true;
                break;
            }
        } else if (bytes_received == 0) {
            qDebug() << "ClientBThread: Server closed connection during weather query";
            break;
        } else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // Timeout, continue
                continue;
            }
            break;
        }
    }

    // Close temporary socket
    ::close(temp_socket);

    if (weatherReceived) {
        qDebug() << "ClientBThread: Weather query completed successfully";
        emit weatherQueryCompleted(true);
        return true;
    } else {
        qDebug() << "ClientBThread: Weather query failed or timed out";
        emit weatherQueryCompleted(false);
        return false;
    }
}

void ClientBThread::disconnectFromServer()
{
    c_tcp_disconnect();
    connectionEstablished = false;
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

    qDebug() << "ClientBThread: Thread stopped";
}

void ClientBThread::run()
{
    qDebug() << "ClientBThread: Thread started - maintaining connection for commands";

    // Main loop to maintain connection
    while (thread_running) {
        if (!maintainConnectionForCommands()) {
            // Connection lost, wait and retry
            if (thread_running) {
                qDebug() << "ClientBThread: Waiting 3 seconds before reconnection...";
                for (int i = 0; i < 30 && thread_running; i++) {
                    msleep(100);
                    QCoreApplication::processEvents();
                }
            }
        }
    }

    qDebug() << "ClientBThread: Thread ended";
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
        qDebug() << "ClientBThread: Failed to create socket:" << strerror(errno);
        pthread_mutex_unlock(&tcp_client.socket_mutex);
        return false;
    }

    // Set socket options
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
        qDebug() << "ClientBThread: Invalid IP address:" << host;
        ::close(tcp_client.socket_fd);
        tcp_client.socket_fd = -1;
        pthread_mutex_unlock(&tcp_client.socket_mutex);
        return false;
    }

    // Connect to server
    if (::connect(tcp_client.socket_fd, (struct sockaddr*)&tcp_client.server_addr,
                  sizeof(tcp_client.server_addr)) < 0) {
        qDebug() << "ClientBThread: Connection failed:" << strerror(errno);
        ::close(tcp_client.socket_fd);
        tcp_client.socket_fd = -1;
        pthread_mutex_unlock(&tcp_client.socket_mutex);
        return false;
    }

    strncpy(tcp_client.server_ip, host, sizeof(tcp_client.server_ip) - 1);
    tcp_client.server_port = port;
    tcp_client.connected = true;

    pthread_mutex_unlock(&tcp_client.socket_mutex);

    qDebug() << "ClientBThread: Connected to" << host << ":" << port;
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

    qDebug() << "ClientBThread: Disconnected";
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
    struct timeval tv;
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;
    setsockopt(tcp_client.socket_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    int bytes_received = recv(tcp_client.socket_fd, buffer, buffer_size - 1, 0);

    pthread_mutex_unlock(&tcp_client.socket_mutex);

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        return bytes_received;
    } else if (bytes_received == 0) {
        // Connection closed
        return 0;
    } else {
        // Error or timeout
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return -2; // Timeout
        }
        return -1; // Other error
    }
}

// ==================== DATA PROCESSING FUNCTIONS ====================

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
    if (!c_tcp_is_connected()) {
        qDebug() << "ClientBThread: Cannot send identity, not connected";
        return;
    }

    const char* identity = "CLIENT_B";
    if (c_tcp_send(identity, strlen(identity))) {
        qDebug() << "ClientBThread: Sent identity: CLIENT_B";
    } else {
        qDebug() << "ClientBThread: Failed to send identity";
    }
}

void ClientBThread::processReceivedMessage(const char* message)
{
    QString msg = QString::fromUtf8(message).trimmed();

    if (msg.isEmpty()) {
        return;
    }

    // Use classification function to determine message type
    MessageType type = classifyMessage(msg);

    switch (type) {
    case MSG_CONNECTION_NOTIFICATION:
        qDebug() << "ClientBThread: Received connection notification:" << msg;
        return;

    case MSG_COMMAND:
        qDebug() << "ClientBThread: Received command:" << msg;
        emitCommand(msg);
        return;

    case MSG_WEATHER:
        qDebug() << "ClientBThread: Parsing weather data";
        parseWeatherData(msg);
        return;

    case MSG_UNKNOWN:
        qDebug() << "ClientBThread: Unknown message type:" << msg;
        return;
    }
}

// Weather data parsing
void ClientBThread::parseWeatherData(const QString &msg)
{
    // Robust weather data parsing
    QStringList lines = msg.split("\n");

    // Filter empty lines
    QStringList filteredLines;
    for (const QString &line : lines) {
        if (!line.trimmed().isEmpty()) {
            filteredLines.append(line);
        }
    }

    QString city, weather, temperature, humidity;

    // Use regular expressions to extract information
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

    // Validate and correct data
    if (city.isEmpty()) city = "Unknown City";
    if (weather.isEmpty()) weather = "Unknown";
    if (temperature.isEmpty()) temperature = "25"; // Default temperature
    if (humidity.isEmpty()) humidity = "N/A%";

    // Ensure temperature is pure number
    temperature = parseTemperature(temperature);

    qDebug() << "ClientBThread: Parsed weather - City:" << city
             << "Weather:" << weather << "Temp:" << temperature << "°C Humidity:" << humidity;

    emitWeatherData(city, weather, temperature, humidity);
}

QString ClientBThread::parseTemperature(const QString &tempStr) const
{
    // Extract temperature numeric part
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

    // If no numbers extracted, return default value
    if (result.isEmpty() || result == "-") {
        return "25";
    }

    // Ensure temperature value is reasonable
    bool ok;
    double temp = result.toDouble(&ok);
    if (ok && temp >= -50 && temp <= 60) {
        return QString::number(temp, 'f', 0); // Round to integer
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

void ClientBThread::onReconnectTimeout()
{
    // Not used in this implementation
}
