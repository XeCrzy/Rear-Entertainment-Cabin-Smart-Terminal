#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMenuBar>
#include <QTextEdit>
#include <QTimer>
#include "easyInput/easyinput.h"
#include "threadtime.h"

extern "C"
{
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define BEEP_ON  0
#define BEEP_OFF 1
}


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    void mainWindowInit();
    easyInput *eInput;
    bool   inputFlag;   //是否开启输入法标志位
    bool eventFilter(QObject *watched, QEvent *event);
    ThreadTime *timeThread;  // 添加时间线程成员

    int ledFd;
    int beepFd;
    bool beepStatus;
    int currentLed;
    QTimer *ledTimer;
    QTimer *beepTimer;
    bool isLedOn;


private slots:
    void slotHideInput();
    void exitWindow();
    // 时间更新槽函数
    void onTimeUpdated(const QString &timeStr);
    void onNtpSyncFinished(bool success, const QString &timeStr);
    //控制led灯和蜂鸣器按钮槽函数
    void on_btn_led_switch_clicked();
    void on_btn_buzzer_switch_clicked();
};
#endif // WIDGET_H
