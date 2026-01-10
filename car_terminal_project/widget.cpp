#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QBrush>
#include <QDebug>
#include <QPalette>
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


    //创建背景图片控件
    QPixmap pix = QPixmap(":/image/background.png").scaled(this->size());
    //创建画板
    QPalette paletee;
    paletee.setBrush(QPalette::Background,QBrush(pix));
    this->setPalette(paletee);
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
    delete ui;
}


void Widget::on_btn_game_clicked()
{
    qDebug() << "游戏按钮";
}
