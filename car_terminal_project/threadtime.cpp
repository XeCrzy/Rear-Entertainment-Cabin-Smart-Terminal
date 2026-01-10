#include "threadtime.h"


// 时间同步回调函数
static void onTimeSyncCallback(const char* time_str, time_t timestamp) {
    qDebug() << "NTP时间同步回调: " << time_str << ", 时间戳: " << timestamp;
}

ThreadTime::ThreadTime(QObject *parent)
    : QThread(parent)
    , m_timer(nullptr)
    , m_running(false)
    , m_ntpSynced(false)
{
    // 初始化时间管理器（只需一次）
    time_manager_init();
}

ThreadTime::~ThreadTime()
{
    stopTimeThread();
}

void ThreadTime::startTimeThread()
{
    if (!m_running) {
        m_running = true;
        start();  // 启动线程
    }
}

void ThreadTime::stopTimeThread()
{
    {
        QMutexLocker locker(&m_mutex);
        m_running = false;
    }

    if (m_timer) {
        m_timer->stop();
        delete m_timer;
        m_timer = nullptr;
    }

    wait();  // 等待线程结束
}

void ThreadTime::syncNtpTime(const QString &ntpServer)
{
    // 使用QMutex保护对C函数的调用
    QMutexLocker locker(&m_mutex);

    qDebug() << "开始同步NTP时间，服务器: " << ntpServer;

    // 同步NTP时间
    int result = sync_ntp_time(ntpServer.toUtf8().constData(), onTimeSyncCallback);

    if (result == 0) {
        m_ntpSynced = true;
        qDebug() << "NTP时间同步成功";

        // 获取时间戳和时间字符串进行验证
        time_t timestamp = get_current_timestamp();
        const char* timeStr = get_current_time_str();

        qDebug() << "获取的时间戳:" << timestamp;
        qDebug() << "时间字符串:" << timeStr;

        emit ntpSyncFinished(true, QString::fromUtf8(timeStr));
    } else {
        m_ntpSynced = false;
        qDebug() << "NTP时间同步失败，将使用系统时间";

        // 同步失败时，至少使用当前系统时间
        updateTime();

        emit ntpSyncFinished(false, QString());
    }
}
void ThreadTime::run()
{
    qDebug() << "时间线程开始运行";

       // 在子线程中创建定时器
       m_timer = new QTimer();
       m_timer->setInterval(1000);  // 1秒更新一次

       // 连接定时器信号到槽函数
       connect(m_timer, &QTimer::timeout, this, &ThreadTime::updateTime);

       // 启动定时器
       m_timer->start();

       qDebug() << "定时器已启动，间隔:" << m_timer->interval() << "ms";

       // 立即同步一次NTP时间（可以尝试不同的服务器）
       QTimer::singleShot(1000, this, [this]() {
           syncNtpTime("182.92.12.11");  // 中国NTP服务器
       });

       // 首次更新时间
       updateTime();

       // 执行事件循环
       exec();

       qDebug() << "时间线程结束运行";

       // 清理
       if (m_timer) {
           m_timer->stop();
           delete m_timer;
           m_timer = nullptr;
       }
}

void ThreadTime::updateTime()
{
    // 更新本地时间（调用C函数）
    update_local_time();

    // 获取当前时间字符串
    const char* timeStr = get_current_time_str();

    if (timeStr) {
        // 发射信号，更新UI
        emit timeUpdated(QString::fromUtf8(timeStr));

        // 添加调试输出（每10秒输出一次，避免太多输出）
        static int counter = 0;
        if (++counter % 10 == 0) {
//            qDebug() << "更新时间:" << QString::fromUtf8(timeStr);
        }
    } else {
        qDebug() << "获取时间字符串失败";
    }
}
