#include "widget.h"
#include "ui_widget.h"
#include "camerawidget.h"
#include <QImage>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
#include <QMapIterator>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    camera = new CameraWidget();
    // 使用单例模式获取输入法实例
    eInput = easyInput::Instance(this);

    // 确保输入法面板初始隐藏
    if (eInput) {
        eInput->hide();
    }

    // 初始化语音线程
    voiceThread = new VoiceThread(this);
    connect(voiceThread, &VoiceThread::voiceCommand, this, &Widget::onVoiceCommandReceived);
    connect(voiceThread, &VoiceThread::statusChanged, this, &Widget::onVoiceStatusChanged);
    connect(voiceThread, &VoiceThread::voiceRecordingFinished, this, &Widget::onVoiceRecordingFinished);

    // 连接两个语音按钮
    connect(ui->btn_talk, &QPushButton::clicked, this, &Widget::onVoiceButtonClicked);
    connect(ui->btn_talk1, &QPushButton::clicked, this, &Widget::onVoiceButtonClicked);

    // 初始化时间线程
    timeThread = new ThreadTime(this);

    // 连接时间信号与槽
    connect(timeThread, &ThreadTime::timeUpdated, this, &Widget::onTimeUpdated);
    connect(timeThread, &ThreadTime::ntpSyncFinished, this, &Widget::onNtpSyncFinished);


    // 启动时间线程
    timeThread->startTimeThread();


    // 初始化LED开关标志位为关闭
    isLedOn = false;
    // 设置label_led默认显示关闭图片
    ui->label_led->setStyleSheet("border-image: url(:/image/led_off.png);");
    // 1. 打开led驱动
    ledFd = ::open("/dev/led_drv", O_RDWR);
    if(ledFd == -1){
        perror("open led error");
    }
    currentLed = 7;
    // 初始化led定时器并设置信号连接
    ledTimer = new QTimer(this);
    connect(ledTimer, &QTimer::timeout, [=](){
        char buf[2];
        // 熄灭当前的灯
        buf[0] = 0;
        buf[1] = currentLed;
        ::write(ledFd, buf, 2);

        // 移动到下一个 (7->8->9->10->7)
        currentLed++;
        if (currentLed > 10) currentLed = 7;

        // 点亮新的灯
        buf[0] = 1;
        buf[1] = currentLed;
        ::write(ledFd, buf, 2);
    });

    // 2. 打开蜂鸣器驱动
    beepFd = ::open("/dev/beep", O_RDWR);
    if(beepFd == -1)
    {
        perror("open buzzer failed");
    }
    // 初始化蜂鸣器变量
    beepStatus = false;
    // 初始化buzzer定时器并设置信号连接
    beepTimer = new QTimer(this);
    connect(beepTimer, &QTimer::timeout, [=](){
        if(beepStatus) {
            ::ioctl(beepFd, BEEP_OFF, 1); // 关
            beepStatus = false;
        } else {
            ::ioctl(beepFd, BEEP_ON, 1);  // 开
            beepStatus = true;
        }
    });
    // 初始化音乐相关变量
    currentMusicIndex = 0;  // 默认播放1.mp3
    isMusicPlaying = false;
    isMusicPaused = false;
    musicStartTime = 0;
    musicPausedTime = 0;
    musicProgress = 0;
    totalDuration = 240 * 1000;  // 240秒转换为毫秒
    progressUpdateInterval = 500;  // 500ms更新一次

    // 设置进度条范围
    ui->horizontalSlider->setRange(0, 100);

    // 创建音乐定时器
    musicTimer = new QTimer(this);
    connect(musicTimer, &QTimer::timeout, this, &Widget::updateMusicProgress);

    // 初始化天气图标映射
    initWeatherIconMap();

    // 初始化客户端B线程（使用C语言TCP实现）
    clientBThread = new ClientBThread(this);

    // 禁止自动连接
    clientBThread->setAutoConnect(false);

    // 连接客户端B信号
    connect(clientBThread, &ClientBThread::weatherDataReceived,
            this, &Widget::onWeatherDataReceived);
    connect(clientBThread, &ClientBThread::commandReceived,
            this, &Widget::onCommandReceived);
    connect(clientBThread, &ClientBThread::connectedToServer,
            this, &Widget::onClientBConnected);
    connect(clientBThread, &ClientBThread::disconnectedFromServer,
            this, &Widget::onClientBDisconnected);
    connect(clientBThread, &ClientBThread::connectionError,
            this, &Widget::onClientBConnectionError);
    connect(clientBThread, &ClientBThread::cityNameSent,
            this, &Widget::onClientBCityNameSent);
    connect(clientBThread, &ClientBThread::debugMessage,
            this, &Widget::onClientBDebugMessage);
    connect(clientBThread, &ClientBThread::manualConnectionCompleted,
            this, &Widget::onManualConnectionCompleted);

    // 启动时只请求一次天气（显示上一次的天气） - 使用手动连接
    QTimer::singleShot(2000, this, [=]() {
        qDebug() << "Requesting initial weather data...";
        requestWeather("广州");
    });

    mainWindowInit();
}


// 实现音乐播放按钮点击槽函数
void Widget::on_btn_music_play_clicked()
{
    qDebug() << "Music play button clicked";
    qDebug() << "Current state - Playing:" << isMusicPlaying << ", Paused:" << isMusicPaused;

    if (!isMusicPlaying) {
        // 如果音乐没有播放，开始播放
        qDebug() << "Starting music playback";
        startMusic();
    } else if (isMusicPaused) {
        // 如果音乐暂停了，恢复播放
        qDebug() << "Resuming music playback";
        resumeMusic();
    } else {
        // 如果音乐正在播放，暂停它
        qDebug() << "Pausing music playback";
        pauseMusic();
    }
}


// 上一首按钮槽函数
void Widget::on_btn_music_pre_clicked()
{
    playPreviousMusic();
}

// 下一首按钮槽函数
void Widget::on_btn_music_next_clicked()
{
    playNextMusic();
}


void Widget::updateMusicProgress()
{
    if (!isMusicPlaying) {
        return;
    }

    // 计算已播放的时间
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 elapsedTime = currentTime - musicStartTime;

    // 计算进度百分比
    int progress = (elapsedTime * 100) / totalDuration;

    // 限制进度在0-100之间
    if (progress < 0) progress = 0;
    if (progress > 100) progress = 100;

    // 更新进度
    musicProgress = progress;
    ui->horizontalSlider->setValue(musicProgress);

    // 检查是否播放完成
    if (progress >= 100) {
        qDebug() << "Music playback complete, resetting...";
        // 播放完成，切换到下一首
        playNextMusic();
    }
}


// 添加时间更新槽函数实现
void Widget::onTimeUpdated(const QString &timeStr)
{
    // 将时间显示到label_time
    ui->label_time->setText(timeStr);
}

void Widget::onNtpSyncFinished(bool success, const QString &timeStr)
{
    if (success) {
        qDebug() << "NTP synchronization complete. Current time: " << timeStr;
        // 可以在这里显示同步成功的提示
    } else {
        qDebug() << "NTP synchronization failed.";
        // 可以在这里显示同步失败的提示
    }
}




void Widget::mainWindowInit()
{
    //this->setWindowFlags(Qt::FramelessWindowHint); // 设置无边框
    this->installEventFilter(this);   // 安装事件过滤器

    eInput = new easyInput(this);      //输入法实例化

    eInput->installEventFilter(this);  //安装事件过滤器
    inputFlag = true;
    this->setFocus();   // 界面初始化时，先把焦点在menu处，否则输入法会先出现
}



bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this){
        static QPoint point;
        switch (event->type()) {
        case QEvent::MouseButtonPress:
            point.setY(cursor().pos().y());     // 记录按下点的y坐标
            eInput->hide();
            break;
        default:
            break;
        }
    }
    if(watched == eInput)
        switch (event->type()) {
        case QEvent::Hide:
            break;
        case QEvent::Show:
        {
            if(inputFlag == false){
                eInput->hide();
                return false;
            }
            //ui->textEdit->moveCursor(QTextCursor::End);//自动滑动到最后一行
        }
            break;
        default:
            break;
        }
    return QWidget::eventFilter(watched,event);//将事件传递给父类
}


// 初始化天气图标映射
void Widget::initWeatherIconMap()
{
    weatherIconMap.clear();
    weatherIconMap["晴"] = "sunny.png";
    weatherIconMap["多云"] = "cloud.png";
    weatherIconMap["阴"] = "cloud.png";
    weatherIconMap["少云"] = "cloud.png";

    weatherIconMap["小雨"] = "rain.png";
    weatherIconMap["中雨"] = "rain.png";
    weatherIconMap["大雨"] = "rain.png";
    weatherIconMap["暴雨"] = "rain.png";
    weatherIconMap["阵雨"] = "rain.png";
    weatherIconMap["雷阵雨"] = "rain.png";

    weatherIconMap["小雪"] = "snow.png";
    weatherIconMap["中雪"] = "snow.png";
    weatherIconMap["大雪"] = "snow.png";
    weatherIconMap["暴雪"] = "snow.png";

    weatherIconMap["雾"] = "Fog.png";
    weatherIconMap["霾"] = "Fog.png";
    weatherIconMap["扬沙"] = "Fog.png";
    weatherIconMap["沙尘暴"] = "Fog.png";
}


void Widget::slotHideInput()
{
    eInput->hide();
}

void Widget::exitWindow()
{
    this->close();
}






void Widget::on_btn_led_switch_clicked()
{
    // 1. 切换LED开关状态
    isLedOn = !isLedOn;

    // 2. 更新label_led的显示图片
    if (isLedOn) {
        // 开启状态：显示on图片 + 启动流水灯定时器
        ui->label_led->setStyleSheet("border-image: url(:/image/led_on.png);");
        // 启动LED定时器（流水灯）
        ledTimer->start(500); // 500ms切换一次灯，可根据需求调整时间
    } else {
        // 关闭状态：显示off图片 + 停止流水灯定时器 + 熄灭所有灯
        ui->label_led->setStyleSheet("border-image: url(:/image/led_off.png);");
        ledTimer->stop();

        // 关闭时熄灭当前点亮的LED灯（避免灯一直亮）
        if (ledFd != -1) {
            char buf[2];
            buf[0] = 0;       // 熄灭指令
            buf[1] = currentLed; // 当前点亮的灯
            ::write(ledFd, buf, 2);
        }
    }
}

void Widget::on_btn_buzzer_switch_clicked()
{
    // 切换状态标志位
    beepStatus = !beepStatus;

    // 根据状态控制蜂鸣器硬件
    if (beepFd >= 0) {
        int ret = ::ioctl(beepFd, beepStatus ? BEEP_ON : BEEP_OFF,1);
        if (ret < 0) {
            qDebug() << "Buzzer control failed:" << strerror(errno);
        }
    } else {
        qDebug() << "The buzzer device is not turned on; only the interface status is changed.";
    }

    // 更新按钮图标样式
    if (beepStatus) {
        ui->label_buzzer->setStyleSheet("border-image: url(:/image/buzzer_on.png);");
    } else {
        ui->label_buzzer->setStyleSheet("border-image: url(:/image/buzzer_off.png);");
    }

    qDebug() << "Buzzer status:" << (beepStatus ? "开启" : "关闭");
}

void Widget::on_btn_camera_clicked()
{

    camera->show();
}

// 语音识别相关槽函数
// 添加录音完成槽函数
void Widget::onVoiceRecordingFinished()
{
    qDebug() << "Voice recording finished";
    // 可以在这里更新UI，比如显示"正在识别..."等
}
// 修改语音按钮点击处理函数
void Widget::onVoiceButtonClicked()
{
    qDebug() << "Voice button clicked";

    // 检查线程是否正在运行
    if (voiceThread && voiceThread->isRunning()) {
        qDebug() << "Voice recognition is already in progress";
        return;
    }

    // 开始语音识别
    if (voiceThread) {
        voiceThread->start();
        ui->btn_talk->setEnabled(false);
        ui->btn_talk1->setEnabled(false);
        qDebug() << "Voice recognition started";
    }
}
// 语音命令处理函数
void Widget::onVoiceCommandReceived(const QString &command)
{
    qDebug() << "Voice command received:" << command;

    // 重新启用语音按钮
    ui->btn_talk->setEnabled(true);
    ui->btn_talk1->setEnabled(true);

    // 将命令转换为小写以便比较
    QString cmd = command.trimmed().toLower();
    qDebug() << "Processing command:" << cmd;

    // 命令匹配和执行
    if (cmd == "打开相机" || cmd == "相机打开" || cmd.contains("相机")) {
        qDebug() << "Executing: Open camera";
        camera->show();
    }
    else if (cmd == "播放音乐" || cmd == "音乐播放" || cmd.contains("音乐")) {
        qDebug() << "Executing: Play music";
        if (!isMusicPlaying) {
            on_btn_music_play_clicked();
        }
    }
    else if (cmd == "停止音乐" || cmd == "音乐停止" || (cmd.contains("停止") && cmd.contains("音乐"))) {
        qDebug() << "Executing: Stop music";
        if (isMusicPlaying) {
            stopMusic();
        }
    }
    else if (cmd == "播放下一首" || cmd == "播放下一首歌" || cmd.contains("播放下一首")) {
        qDebug() << "Executing: Next music";
        playNextMusic();
    }
    else if (cmd == "播放上一首" || cmd == "播放上一首歌" || cmd.contains("播放上一首")) {
        qDebug() << "Executing: Previous music";
        playPreviousMusic();
    }
    else if (cmd == "打开灯" || cmd == "灯打开" || cmd.contains("打开灯") || cmd.contains("开灯")) {
        qDebug() << "Executing: Turn on LED";
        if (!isLedOn) {
            on_btn_led_switch_clicked();
        }
    }
    else if (cmd == "关闭灯" || cmd == "灯关闭" || cmd.contains("关闭灯") || cmd.contains("关灯")) {
        qDebug() << "Executing: Turn off LED";
        if (isLedOn) {
            on_btn_led_switch_clicked();
        }
    }
    else if (cmd == "打开蜂鸣器" || cmd == "蜂鸣器打开" || cmd.contains("蜂鸣器")) {
        qDebug() << "Executing: Turn on buzzer";
        if (!beepStatus) {
            on_btn_buzzer_switch_clicked();
        }
    }
    else if (cmd == "关闭蜂鸣器" || cmd == "蜂鸣器关闭" || cmd.contains("关闭蜂鸣器")) {
        qDebug() << "Executing: Turn off buzzer";
        if (beepStatus) {
            on_btn_buzzer_switch_clicked();
        }
    }
    // 新增天气查询命令处理 - 使用新的手动连接方式
    else if (cmd == "广州天气" || cmd == "查看广州天气") {
        qDebug() << "Executing: Query Guangzhou weather";
        requestWeather("广州");
    }
    else if (cmd == "北京天气" || cmd == "查看北京天气") {
        qDebug() << "Executing: Query Beijing weather";
        requestWeather("北京");
    }
    else if (cmd == "杭州天气" || cmd == "查看杭州天气") {
        qDebug() << "Executing: Query Hangzhou weather";
        requestWeather("杭州");
    }
    else if (cmd == "上海天气" || cmd == "查看上海天气") {
        qDebug() << "Executing: Query Shanghai weather";
        requestWeather("上海");
    }
    else if (cmd.contains("天气") && cmd.length() > 2) {
        // 通用天气查询：提取城市名
        QString city = cmd;
        city = city.replace("天气", "").replace("查看", "").trimmed();

        if (!city.isEmpty()) {
            qDebug() << "Executing: Query weather for" << city;
            requestWeather(city);
        } else {
//            QMessageBox::information(this, "Weather Query",
//                                   "Please say the city name, e.g.: Beijing weather, Guangzhou weather");
        }
    }
    else if (cmd == "帮助" || cmd.contains("帮助")) {
        qDebug() << "Executing: Show help";
        QString helpText =
            "Supported voice commands:\n\n"
            "Device Control:\n"
            "1. Open camera / Camera open\n"
            "2. Play music / Stop music\n"
            "3. Turn on LED / Turn off LED\n"
            "4. Turn on buzzer / Turn off buzzer\n\n"
            "Weather Query:\n"
            "5. Beijing weather / Guangzhou weather\n"
            "6. Hangzhou weather / Shanghai weather\n"
            "7. Other cities: Say city name + weather, e.g.: Shenzhen weather\n\n"
            "8. Help - Show this help information";

        QMessageBox::information(this, "Voice Command Help", helpText);
    }
    else {
        qDebug() << "Unrecognized command:" << command;
        QMessageBox::warning(this, "Unrecognized Command",
            QString("Unrecognized command: %1\n\nPlease say 'Help' to view available commands").arg(command));
    }
}

void Widget::onVoiceStatusChanged(const QString &status)
{
    qDebug() << "Voice status:" << status;

        // 可以在这里更新UI，显示语音识别状态
        // 例如：在某个标签上显示当前状态
        // 注意：确保这个标签存在，如果不存在可以创建一个或者使用现有的
        // 例如：ui->label_status->setText(status);

        // 如果需要在状态栏显示，可以使用 QStatusBar（如果存在）
        // 或者简单地在调试信息中显示
}

QString Widget::getWeatherIconPath(const QString &weather)
{
    // 尝试完全匹配
    if (weatherIconMap.contains(weather)) {
        return weatherIconMap[weather];
    }

    // 尝试部分匹配
    QMapIterator<QString, QString> it(weatherIconMap);
    while (it.hasNext()) {
        it.next();
        if (weather.contains(it.key())) {
            return it.value();
        }
    }

    // 默认图标
    return "sunny.png";
}

// 天气数据接收槽函数
void Widget::onWeatherDataReceived(const QString &city, const QString &weather,
                                  const QString &temperature, const QString &humidity)
{
    qDebug() << "Weather data received - City:" << city << "Weather:" << weather
             << "Temperature:" << temperature << "Humidity:" << humidity;

    // 标记已收到天气数据
    if (!initialWeatherReceived) {
        initialWeatherReceived = true;
        qDebug() << "Initial weather data received";
    }

    // 显示一个短暂的提示
    QMessageBox::information(this, "天气查询结果",
        QString("%1天气:\n天气: %2\n温度: %3℃\n湿度: %4")
            .arg(city).arg(weather).arg(temperature).arg(humidity));

    // Update temperature display
    ui->label_temperature->setText(QString("温度:%1℃").arg(temperature));

    // Update weather icon
    QString iconPath = getWeatherIconPath(weather);
    ui->label_weather->setStyleSheet(
        QString("border-image: url(:/image/%1);").arg(iconPath));

    // Update city display if label_city exists
    QLabel *labelCity = findChild<QLabel*>("label_city");
    if (labelCity) {
        labelCity->setText(city);
    }
}

// 命令接收槽函数
void Widget::onCommandReceived(const QString &command)
{
    qDebug() << "Command received:" << command;

    QString cmd = command.toUpper();

    if (cmd == "LED_ON") {
        // Turn on LED
        if (!isLedOn) {
            on_btn_led_switch_clicked();
        }
        qDebug() << "Executing command: Turn on LED";
    }
    else if (cmd == "LED_OFF") {
        // Turn off LED
        if (isLedOn) {
            on_btn_led_switch_clicked();
        }
        qDebug() << "Executing command: Turn off LED";
    }
    else if (cmd == "BUZZER_ON") {
        // Turn on buzzer
        if (!beepStatus) {
            on_btn_buzzer_switch_clicked();
        }
        qDebug() << "Executing command: Turn on buzzer";
    }
    else if (cmd == "BUZZER_OFF") {
        // Turn off buzzer
        if (beepStatus) {
            on_btn_buzzer_switch_clicked();
        }
        qDebug() << "Executing command: Turn off buzzer";
    }
    else {
        qDebug() << "Unknown command:" << command;
    }
}

// 客户端B连接状态槽函数
void Widget::onClientBConnected()
{
    qDebug() << "Client B connected to server";
    // Can update UI status here
}


void Widget::onClientBDisconnected()
{
    qDebug() << "Client B disconnected from server";
    // 只有在不是重复连接的情况下才重连
    static QElapsedTimer reconnectTimer;
    if (!reconnectTimer.isValid() || reconnectTimer.hasExpired(5000)) {
        // Try to reconnect after 5 seconds
        QTimer::singleShot(5000, this, &Widget::reconnectClientB);
        reconnectTimer.start(); // 重置计时器
    }
}

void Widget::onClientBConnectionError(const QString &error)
{
    qDebug() << "Client B connection error:" << error;

    // 只在第一次连接失败时显示弹窗，避免重复弹窗
    static bool errorShown = false;
    static QElapsedTimer errorTimer;

    if (!errorShown || errorTimer.hasExpired(10000)) { // 10秒内只显示一次
//        QMessageBox::warning(this, "连接错误",
//                            QString("客户端B连接错误:\n%1\n\n将在5秒后重试...").arg(error));
        errorShown = true;
        errorTimer.start(); // 重置计时器
    }

    // 等待5秒后重连
    QTimer::singleShot(5000, this, &Widget::reconnectClientB);
}

void Widget::onClientBCityNameSent(const QString &city)
{
    qDebug() << "City name sent:" << city;
    // Can show success message here
}

void Widget::onClientBDebugMessage(const QString &msg)
{
    qDebug() << "Client B debug:" << msg;
}

// 移除或修改自动重连逻辑
void Widget::reconnectClientB()
{
    // 现在我们不自动重连，只在需要时手动连接
    qDebug() << "Auto-reconnect disabled. Please use manual weather request.";
}

// 城市名发送槽函数
void Widget::on_btn_send_clicked()
{
    QString city = ui->lineEdit->text().trimmed();
    if (city.isEmpty()) {
//        QMessageBox::warning(this, "Input Error", "Please enter city name");
        return;
    }

    requestWeather(city);
}

void Widget::on_btn_beijing_clicked()
{
    QString city = "北京";
    ui->lineEdit->setText(city);
    requestWeather(city);
}

void Widget::on_btn_guangzhou_clicked()
{
    QString city = "广州";
    ui->lineEdit->setText(city);
    requestWeather(city);
}

// 通用城市天气查询函数
void Widget::queryWeatherByCity(const QString &city)
{
    if (city.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入城市名");
        return;
    }

    ui->lineEdit->setText(city);

    if (clientBThread && clientBThread->isConnected()) {
        clientBThread->sendCityName(city);
        QMessageBox::information(this, "天气查询", QString("正在查询%1的天气...").arg(city));
    } else {
//        QMessageBox::warning(this, "连接错误", "未连接到服务器");
        reconnectClientB();
    }
}

// 新增：手动连接完成槽函数
void Widget::onManualConnectionCompleted(bool success)
{
    qDebug() << "Manual connection completed, success:" << success;
    if (success) {
        qDebug() << "Weather data received successfully";
    } else {
        qDebug() << "Failed to get weather data";
//        QMessageBox::warning(this, "Connection Error", "Failed to get weather data. Please try again.");
    }
}

//请求天气函数
void Widget::requestWeather(const QString &city)
{
    qDebug() << "Requesting weather for:" << city;

    if (clientBThread) {
        // 使用手动连接模式发送城市名
        bool result = clientBThread->sendCityName(city, false);  // false表示手动连接

        if (!result) {
            qDebug() << "Failed to send city name:" << city;
//            QMessageBox::warning(this, "请求失败",
//                                QString("请求%1的天气失败").arg(city));
        }
    }
}


// 开始播放音乐
void Widget::startMusic()
{
    // 先杀死可能正在运行的音乐进程
    killMusicProcess();

    QString command;
    if (currentMusicIndex == 0) {
        command = "madplay /tmp/1.mp3 2>&1 &";
        qDebug() << "Starting music: 1.mp3";
    } else {
        command = "madplay /tmp/2.mp3 2>&1 &";
        qDebug() << "Starting music: 2.mp3";
    }

    // 检查音乐文件是否存在
    QString musicFile = (currentMusicIndex == 0) ? "/tmp/1.mp3" : "/tmp/2.mp3";
    if (access(musicFile.toStdString().c_str(), F_OK) == -1) {
        qDebug() << "Music file not found:" << musicFile;
        QMessageBox::warning(this, "错误", QString("音乐文件不存在: %1").arg(musicFile));
        return;
    }

    // 执行播放命令
    int ret = system(command.toStdString().c_str());
    if (ret == 0) {
        qDebug() << "Music started successfully";
    } else {
        qDebug() << "Failed to start music, return code:" << ret;
        // 尝试再次检查并杀死进程
        killMusicProcess();
        // 再次尝试播放
        system(command.toStdString().c_str());
    }

    // 更新状态
    isMusicPlaying = true;
    isMusicPaused = false;
    musicStartTime = QDateTime::currentMSecsSinceEpoch();
    musicPausedTime = 0;
    musicProgress = 0;

    // 重置进度条
    ui->horizontalSlider->setValue(0);

    // 启动定时器更新进度条
    musicTimer->start(progressUpdateInterval);

    // 更新按钮图标为播放（因为正在播放）
    ui->btn_music_play->setStyleSheet("border-image: url(:/image/music_play.png);");

    qDebug() << "Music state: Playing, Paused:" << isMusicPaused;
}

// 杀死音乐进程
void Widget::killMusicProcess()
{
    // 使用更强的kill命令，确保进程被终止
    system("pkill -9 madplay 2>/dev/null");
    // 给系统一点时间释放音频设备
    usleep(100000); // 100ms
    qDebug() << "Music process killed";
}

// 检查是否有音乐进程正在运行
bool Widget::checkMusicProcess()
{
    FILE* fp = popen("pgrep madplay", "r");
    char buffer[128];
    bool result = false;

    if (fp) {
        if (fgets(buffer, sizeof(buffer), fp) != NULL) {
            result = true;
        }
        pclose(fp);
    }

    return result;
}

// 停止播放音乐
void Widget::stopMusic()
{
    // 停止定时器
    musicTimer->stop();

    // 杀死音乐进程
    killMusicProcess();

    // 重置状态
    isMusicPlaying = false;
    isMusicPaused = false;
    musicProgress = 0;
    musicPausedTime = 0;

    // 重置进度条
    ui->horizontalSlider->setValue(0);

    // 更新按钮图标为暂停（因为停止了）
    ui->btn_music_play->setStyleSheet("border-image: url(:/image/music_pause.png);");

    qDebug() << "Music stopped";
    qDebug() << "Music state: Playing:" << isMusicPlaying << ", Paused:" << isMusicPaused;
}


// 暂停播放音乐
void Widget::pauseMusic()
{
    if (!isMusicPlaying || isMusicPaused) {
        return;
    }

    // 检查是否有音乐进程
    if (!checkMusicProcess()) {
        qDebug() << "No music process found, cannot pause";
        isMusicPlaying = false;
        isMusicPaused = false;
        return;
    }

    // 暂停音乐进程
    int ret = system("pkill -SIGSTOP madplay");
    if (ret == 0) {
        qDebug() << "Music paused";
        isMusicPaused = true;

        // 停止定时器
        musicTimer->stop();

        // 记录暂停时已播放的时间
        musicPausedTime = QDateTime::currentMSecsSinceEpoch() - musicStartTime;

        // 更新按钮图标为暂停
        ui->btn_music_play->setStyleSheet("border-image: url(:/image/music_pause.png);");
    } else {
        qDebug() << "Failed to pause music, return code:" << ret;
        // 如果暂停失败，可能是进程已经结束
        isMusicPlaying = false;
        isMusicPaused = false;
        musicTimer->stop();
        ui->horizontalSlider->setValue(0);
        ui->btn_music_play->setStyleSheet("border-image: url(:/image/music_pause.png);");
    }

    qDebug() << "Music state: Playing:" << isMusicPlaying << ", Paused:" << isMusicPaused;
}

// 恢复播放音乐
void Widget::resumeMusic()
{
    if (!isMusicPlaying || !isMusicPaused) {
        return;
    }

    // 检查是否有音乐进程
    if (!checkMusicProcess()) {
        qDebug() << "No music process found, cannot resume";
        // 如果进程不存在，重新开始播放
        startMusic();
        return;
    }

    // 继续音乐进程
    int ret = system("pkill -SIGCONT madplay");
    if (ret == 0) {
        qDebug() << "Music resumed";
        isMusicPaused = false;

        // 更新开始时间
        musicStartTime = QDateTime::currentMSecsSinceEpoch() - musicPausedTime;

        // 启动定时器
        musicTimer->start(progressUpdateInterval);

        // 更新按钮图标为播放
        ui->btn_music_play->setStyleSheet("border-image: url(:/image/music_play.png);");
    } else {
        qDebug() << "Failed to resume music, return code:" << ret;
        // 如果恢复失败，可能是进程已经结束
        isMusicPlaying = false;
        isMusicPaused = false;
        musicTimer->stop();
        ui->horizontalSlider->setValue(0);
        ui->btn_music_play->setStyleSheet("border-image: url(:/image/music_pause.png);");
    }

    qDebug() << "Music state: Playing:" << isMusicPlaying << ", Paused:" << isMusicPaused;
}

// 播放下一首
void Widget::playNextMusic()
{
    qDebug() << "Switching to next music";

    // 切换到下一首
    currentMusicIndex = (currentMusicIndex + 1) % 2;  // 0->1, 1->0

    // 如果正在播放，则播放新歌曲
    if (isMusicPlaying) {
        startMusic();
    }
}

// 播放上一首
void Widget::playPreviousMusic()
{
    qDebug() << "Switching to previous music";

    // 切换到上一首
    currentMusicIndex = (currentMusicIndex == 0) ? 1 : 0;  // 0->1, 1->0

    // 如果正在播放，则播放新歌曲
    if (isMusicPlaying) {
        startMusic();
    }
}


Widget::~Widget()
{
    // 停止语音线程
    if (voiceThread) {
        voiceThread->stopRecording();
        if (voiceThread->isRunning()) {
            voiceThread->wait(2000);  // 等待2秒
        }
        delete voiceThread;
        voiceThread = nullptr;
    }
    // 停止音乐
    stopMusic();

    // 停止并删除音乐定时器
    if (musicTimer) {
        musicTimer->stop();
        delete musicTimer;
    }

    // 停止时间线程
    if (timeThread) {
        timeThread->stopTimeThread();
        delete timeThread;
    }
    // 停止LED定时器并熄灭灯
    if (ledTimer) {
        ledTimer->stop();
        // 熄灭最后点亮的灯
        if (ledFd != -1) {
            char buf[2];
            buf[0] = 0;
            buf[1] = currentLed;
            ::write(ledFd, buf, 2);
            ::close(ledFd); // 关闭LED驱动文件描述符
        }
        delete ledTimer;
    }

    // 关闭蜂鸣器驱动
    if (beepFd != -1) {
        ::ioctl(beepFd, BEEP_OFF, 1);
        ::close(beepFd);
    }
    delete camera;
    delete ui;
}

