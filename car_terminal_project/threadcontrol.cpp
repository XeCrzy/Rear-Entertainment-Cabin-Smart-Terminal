// threadcontrol.cpp
#include "threadcontrol.h"
#include <QDebug>
#include <cstring>
#include <cerrno>

ThreadControl::ThreadControl(QObject *parent)
    : QThread(parent)
    , m_ledFd(-1)
    , m_buzzerFd(-1)
    , m_ledOn(false)
    , m_buzzerOn(false)
{
}

ThreadControl::~ThreadControl()
{
    // 安全停止线程
    if (isRunning()) {
        quit();
        wait();
    }

    // 关闭硬件
    if (m_ledFd != -1) {
        // 关闭所有LED
        for (int i = 7; i <= 10; i++) {
            char buf[2] = {LED_OFF, static_cast<char>(i)};
            write(m_ledFd, buf, 2);
        }
        ::close(m_ledFd);
    }

    if (m_buzzerFd != -1) {
        ::ioctl(m_buzzerFd, BUZZER_OFF, 1);
        ::close(m_buzzerFd);
    }
}

bool ThreadControl::initHardware()
{
    // 打开LED驱动
    m_ledFd = ::open("/dev/led_drv", O_RDWR);
    if (m_ledFd == -1) {
        qWarning() << "打开 LED 驱动失败:" << strerror(errno);
        return false;
    }

    // 初始关闭所有LED
    for (int i = 7; i <= 10; i++) {
        char buf[2] = {LED_OFF, static_cast<char>(i)};
        ::write(m_ledFd, buf, 2);
    }

    // 打开蜂鸣器驱动
    m_buzzerFd = ::open("/dev/beep", O_RDWR);
    if (m_buzzerFd == -1) {
        qWarning() << "打开蜂鸣器驱动失败:" << strerror(errno);
        // 蜂鸣器失败不影响LED
        return false;  // 如果蜂鸣器初始化失败，返回false
    } else {
        // 初始关闭蜂鸣器
        ::ioctl(m_buzzerFd, BUZZER_OFF, 1);
    }

    return true;
}

void ThreadControl::setLedState(bool on)
{
    QMutexLocker locker(&m_mutex);
    if (m_ledOn != on) {
        m_ledOn = on;
        controlLed(on);
        emit ledStateChanged(on);
    }
}

void ThreadControl::setBuzzerState(bool on)
{
    QMutexLocker locker(&m_mutex);
    if (m_buzzerOn != on) {
        m_buzzerOn = on;
        controlBuzzer(on);
        emit buzzerStateChanged(on);
    }
}

void ThreadControl::controlLed(bool on)
{
    if (m_ledFd == -1) {
        qWarning() << "LED驱动未初始化";
        return;
    }

    if (on) {
        // 开启LED（点亮LED7）
        char buf[2] = {LED_ON, 7};
        ::write(m_ledFd, buf, 2);
        qDebug() << "控制LED: 开启";
    } else {
        // 关闭所有LED
        for (int i = 7; i <= 10; i++) {
            char buf[2] = {LED_OFF, static_cast<char>(i)};
            ::write(m_ledFd, buf, 2);
        }
        qDebug() << "控制LED: 关闭";
    }
}

void ThreadControl::controlBuzzer(bool on)
{
    if (m_buzzerFd == -1) {
        qWarning() << "蜂鸣器驱动未初始化";
        return;
    }

    if (on) {
        ::ioctl(m_buzzerFd, BUZZER_ON, 1);
        qDebug() << "控制蜂鸣器: 开启";
    } else {
        ::ioctl(m_buzzerFd, BUZZER_OFF, 1);
        qDebug() << "控制蜂鸣器: 关闭";
    }
}

void ThreadControl::run()
{
    // 初始化硬件
    if (initHardware()) {
        qDebug() << "硬件初始化成功";
    } else {
        qWarning() << "硬件初始化失败";
    }

    // 简单的事件循环
    exec();
}
