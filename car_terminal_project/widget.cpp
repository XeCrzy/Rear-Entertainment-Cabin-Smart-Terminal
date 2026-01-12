#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QDateTime>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 使用单例模式获取输入法实例
    eInput = easyInput::Instance(this);

    // 确保输入法面板初始隐藏
    if (eInput) {
        eInput->hide();
    }

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

    mainWindowInit();
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
        qDebug() << "NTP同步完成，当前时间: " << timeStr;
        // 可以在这里显示同步成功的提示
    } else {
        qDebug() << "NTP同步失败";
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

void Widget::slotHideInput()
{
    eInput->hide();
}

void Widget::exitWindow()
{
    this->close();
}

Widget::~Widget()
{
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
    delete ui;
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
                qDebug() << "蜂鸣器控制失败:" << strerror(errno);
            }
        } else {
            qDebug() << "蜂鸣器设备未打开，仅切换界面状态";
        }

        // 更新按钮图标样式
        if (beepStatus) {
            ui->label_buzzer->setStyleSheet("border-image: url(:/image/buzzer_on.png);");
        } else {
            ui->label_buzzer->setStyleSheet("border-image: url(:/image/buzzer_off.png);");
        }

        qDebug() << "蜂鸣器状态:" << (beepStatus ? "开启" : "关闭");
}
