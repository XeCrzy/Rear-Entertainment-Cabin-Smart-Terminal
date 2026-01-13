#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QMenuBar>
#include <QTextEdit>
#include <QTimer>
#include "easyInput/easyinput.h"
#include "camerawidget.h"
#include "threadtime.h"
#include "voicethread.h"
#include "clientbthread.h"
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
    //相机界面
    CameraWidget *camera;
    //语音线程
    VoiceThread *voiceThread;


    //输入法相关
    void mainWindowInit();
    easyInput *eInput;
    bool   inputFlag;   //是否开启输入法标志位
    bool eventFilter(QObject *watched, QEvent *event);
    ThreadTime *timeThread;  // 添加时间线程成员

    //led和蜂鸣器相关
    int ledFd;
    int beepFd;
    bool beepStatus;
    int currentLed;
    QTimer *ledTimer;
    QTimer *beepTimer;
    bool isLedOn;

    //音乐播放相关
    QTimer *musicTimer;
    bool isMusicPlaying;
    int musicProgress;  // 当前进度值
    int totalDuration;  // 总时长（毫秒）
    int progressUpdateInterval;
    qint64 musicStartTime;  // 播放开始的时间戳
    qint64 musicPausedTime; // 暂停时已播放的时间
    bool isMusicPaused;     // 是否处于暂停状态

    // 客户端B线程相关
    ClientBThread *clientBThread;
    // 天气图标映射
    QMap<QString, QString> weatherIconMap;
    // 初始化天气图标映射
    void initWeatherIconMap();
    // 根据天气获取图标路径
    QString getWeatherIconPath(const QString &weather);

private slots:
    void slotHideInput();
    void exitWindow();

    // 时间更新槽函数
    void onTimeUpdated(const QString &timeStr);
    void onNtpSyncFinished(bool success, const QString &timeStr);

    //控制led灯和蜂鸣器按钮槽函数
    void on_btn_led_switch_clicked();
    void on_btn_buzzer_switch_clicked();

    //音乐播放相关函数
    void on_btn_music_play_clicked();
    void updateMusicProgress();
    void on_btn_camera_clicked();

    // 语音识别槽函数
    void onVoiceCommandReceived(const QString &command);
    void onVoiceStatusChanged(const QString &status);
    void onVoiceRecordingFinished();
    void onVoiceButtonClicked();  // 统一处理两个语音按钮

    // 客户端B相关槽函数
    void onWeatherDataReceived(const QString &city, const QString &weather,
                               const QString &temperature, const QString &humidity);
    void onCommandReceived(const QString &command);
    void onClientBConnected();
    void onClientBDisconnected();
    void onClientBConnectionError(const QString &error);
    void onClientBCityNameSent(const QString &city);
    void onClientBDebugMessage(const QString &msg);

    // 城市名发送槽函数
    void on_btn_send_clicked();
    void on_btn_beijing_clicked();
    void on_btn_guangzhou_clicked();

    // 客户端B重连
    void reconnectClientB();

};
#endif // WIDGET_H
