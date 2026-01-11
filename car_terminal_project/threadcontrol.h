// threadcontrol.h
#ifndef THREADCONTROL_H
#define THREADCONTROL_H

#include <QThread>
#include <QMutex>

// 硬件控制宏定义
#define LED_ON   1
#define LED_OFF  0
#define BUZZER_ON  0
#define BUZZER_OFF 1

extern "C" {
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
}

class ThreadControl : public QThread
{
    Q_OBJECT

public:
    ThreadControl(QObject *parent = nullptr);
    ~ThreadControl();

    // 初始化硬件
    bool initHardware();

    // 设置LED状态
    void setLedState(bool on);

    // 设置蜂鸣器状态
    void setBuzzerState(bool on);

    // 获取当前状态
    bool getLedState() const { return m_ledOn; }
    bool getBuzzerState() const { return m_buzzerOn; }

protected:
    void run() override;

signals:
    // 状态变化信号
    void ledStateChanged(bool state);
    void buzzerStateChanged(bool state);

private:
    // 硬件文件描述符
    int m_ledFd;
    int m_buzzerFd;

    // 状态变量
    bool m_ledOn;
    bool m_buzzerOn;

    // 互斥锁保护状态
    mutable QMutex m_mutex;  // 添加 mutable 以在 const 函数中使用

    // 实际控制硬件的函数
    void controlLed(bool on);
    void controlBuzzer(bool on);
};

#endif // THREADCONTROL_H
