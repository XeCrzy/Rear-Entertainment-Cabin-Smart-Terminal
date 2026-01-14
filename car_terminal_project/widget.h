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
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

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
    // GIF动画对象
    QMovie *voiceGifMovie;

    //输入法相关
    void mainWindowInit();
    easyInput *eInput;
    bool   inputFlag;   //是否开启输入法标志位
    bool eventFilter(QObject *watched, QEvent *event);
    ThreadTime *timeThread;  // 添加时间线程成员

    // LED流水灯相关
    bool isLedOn;
    int currentLed;
    QTimer *ledTimer;
    int ledFd;

    // 蜂鸣器相关
    bool beepStatus;
    bool beepRunning;
    QTimer *beepTimer;
    int beepFd;

    // LED控制函数
    void startLedFlow();
    void stopLedFlow();
    void turnOnLed();
    void turnOffLed();

    // 蜂鸣器控制函数
    void startBeep();
    void stopBeep();
    void turnOnBeep();
    void turnOffBeep();

    //音乐播放相关
    QTimer *musicTimer;
    bool isMusicPlaying;     // 是否正在播放
    bool isMusicPaused;      // 是否暂停状态
    int currentMusicIndex;   // 当前播放的音乐索引 (0: 1.mp3, 1: 2.mp3)
    qint64 musicStartTime;   // 播放开始的时间戳
    qint64 musicPausedTime;  // 暂停时已播放的时间
    int musicProgress;       // 当前进度值
    int totalDuration;       // 总时长（毫秒）
    int progressUpdateInterval;

    // 音乐控制函数
    void startMusic();        // 开始播放音乐
    void stopMusic();         // 停止播放音乐
    void pauseMusic();        // 暂停播放音乐
    void resumeMusic();       // 恢复播放音乐
    void playNextMusic();     // 播放下一首
    void playPreviousMusic(); // 播放上一首
    void killMusicProcess();  // 杀死音乐进程
    bool checkMusicProcess(); // 检查是否有音乐进程在运行

    // 客户端B线程相关
    ClientBThread *clientBThread;
    bool initialWeatherReceived;  // 标记是否已收到初始天气
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

    // 上一首/下一首按钮槽函数
    void on_btn_music_pre_clicked();
    void on_btn_music_next_clicked();

    //打开相机槽函数
    void on_btn_camera_clicked();

    //语音识别槽函数
    void onVoiceCommandReceived(const QString &command);
    void onVoiceStatusChanged(const QString &status);
    void onVoiceRecordingFinished();
    void onVoiceButtonClicked();  // 统一处理两个语音按钮

    void showVoiceGif();     // 显示GIF动画
    void hideVoiceGif();     // 隐藏GIF动画
    //城市天气查询函数
    void queryWeatherByCity(const QString &city);
    void onWeatherQueryCompleted(bool success);
    // 客户端B相关槽函数
    void onWeatherDataReceived(const QString &city, const QString &weather,
                               const QString &temperature, const QString &humidity);
    void onCommandReceived(const QString &command);
    void onClientBConnected();
    void onClientBDisconnected();
    void onClientBConnectionError(const QString &error);
    void onClientBCityNameSent(const QString &city);
    void onClientBDebugMessage(const QString &msg);
    void onManualConnectionCompleted(bool success);  // 新增：手动连接完成

    // 城市名发送槽函数
    void on_btn_send_clicked();
    void on_btn_beijing_clicked();
    void on_btn_guangzhou_clicked();

    // 客户端B重连
    void reconnectClientB();
    // 手动请求天气
    void requestWeather(const QString &city);

};
#endif // WIDGET_H
