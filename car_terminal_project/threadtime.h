#ifndef THREADTIME_H
#define THREADTIME_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QDebug>
#include "time_manager.h"

class ThreadTime : public QThread
{
    Q_OBJECT
public:
    explicit ThreadTime(QObject *parent = nullptr);
    ~ThreadTime();

        // 启动时间线程
        void startTimeThread();

        // 停止时间线程
        void stopTimeThread();

        // 同步NTP时间
        void syncNtpTime(const QString &ntpServer = "182.92.12.11");

        // 添加备用服务器列表
            QStringList getNtpServers() const {
                return QStringList()
                    << "182.92.12.11"    // 中国NTP服务器
                    << "ntp.aliyun.com"  // 阿里云NTP
                    << "time.windows.com" // Windows时间服务器
                    << "pool.ntp.org";   // NTP池
            }

signals:
    // 时间更新信号
    void timeUpdated(const QString &timeStr);

    // NTP同步完成信号
    void ntpSyncFinished(bool success, const QString &timeStr);

protected:
    void run() override;

private slots:
    void updateTime();

private:
    QTimer *m_timer;      // 定时器，用于每秒更新时间
    bool m_running;       // 线程运行标志
    QMutex m_mutex;       // 线程同步锁
    bool m_ntpSynced;
};

#endif // THREADTIME_H
