#include "gameselect.h"
#include <QPushButton>
#include <QIcon>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QTextEdit>      // 添加缺失的头文件
#include <QTextStream>    // 添加缺失的头文件
#include <QFile>          // 添加缺失的头文件
#include "gamehall.h"
#include "gameroom.h"

GameSelect::GameSelect(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(800, 480);  // 修改为800*480
    this->setWindowIcon(QIcon(":res/ico.png"));
    this->setWindowTitle("游戏关卡选择");

    // 返回按钮
    QPushButton* backBtn = new QPushButton("返回游戏大厅", this);
    backBtn->move(600, 420);
    backBtn->setFixedSize(150, 40);

    QFont font("华文行楷", 16);
    backBtn->setFont(font);
    backBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #607D8B;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 8px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #546E7A;"
        "}"
    );

    connect(backBtn, &QPushButton::clicked, [=](){
        this->close();
        // 获取父窗口（GameHall）并显示
        if (QWidget* parent = this->parentWidget()) {
            parent->show();
        } else {
            // 如果没有父窗口，创建新的GameHall
            GameHall* gameHall = new GameHall;
            gameHall->show();
        }
    });

    QFont buttonFont("华文行楷", 18);  // 字体调小

    // 创建游戏房间（保持一个实例）
    static GameRoom* gameRoom = nullptr;
    if (!gameRoom) {
        gameRoom = new GameRoom;
        gameRoom->setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);
    }

    QPushButton* simpleBtn = new QPushButton(this);
    simpleBtn->move(300, 150);  // 调整位置
    simpleBtn->setFixedSize(200, 60);
    simpleBtn->setText("简单模式");
    simpleBtn->setFont(buttonFont);
    simpleBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 10px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}"
    );

    connect(simpleBtn, &QPushButton::clicked, [=]()
    {
        this->hide();
        gameRoom->setGeometry(this->geometry());
        gameRoom->show();
        gameRoom->setTimeout(300);
    });

    QPushButton* normalBtn = new QPushButton(this);
    normalBtn->move(300, 220);
    normalBtn->setFixedSize(200, 60);
    normalBtn->setText("普通模式");
    normalBtn->setFont(buttonFont);
    normalBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #2196F3;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 10px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #1976D2;"
        "}"
    );

    connect(normalBtn, &QPushButton::clicked, [=]()
    {
        this->hide();
        gameRoom->setGeometry(this->geometry());
        gameRoom->show();
        gameRoom->setTimeout(200);
    });

    QPushButton* hardBtn = new QPushButton(this);
    hardBtn->move(300, 290);
    hardBtn->setFixedSize(200, 60);
    hardBtn->setText("困难模式");
    hardBtn->setFont(buttonFont);
    hardBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #f44336;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 10px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d32f2f;"
        "}"
    );

    connect(hardBtn, &QPushButton::clicked, [=]()
    {
        this->hide();
        gameRoom->setGeometry(this->geometry());
        gameRoom->show();
        gameRoom->setTimeout(100);
    });

    QPushButton* history = new QPushButton("历史战绩", this);
    history->move(300, 360);
    history->setFixedSize(200, 60);
    history->setFont(buttonFont);
    history->setStyleSheet(
        "QPushButton {"
        "   background-color: #FF9800;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 10px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #F57C00;"
        "}"
    );

    connect(history, &QPushButton::clicked, [=]()
    {
        QWidget* widget = new QWidget;
        widget->setWindowTitle("历史战绩");
        widget->setFixedSize(500, 300);

        QTextEdit *edit = new QTextEdit(widget);
        QFont editFont("华文行楷", 14);
        edit->setFont(editFont);
        edit->setFixedSize(500, 300);

        QFile file("C:/Users/zzc/Desktop/1.txt");
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream in(&file);
            int data = in.readLine().toInt();
            edit->append("历史最高得分：");
            edit->append(QString::number(data));
            file.close();
        }
        else
        {
            edit->append("暂无历史战绩");
        }

        widget->show();
    });
}

void GameSelect::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 绘制背景 - 游戏区域600*480，控制区域200*480
    QPixmap pix;
    pix.load(":res/simple_room.png");
    painter.drawPixmap(0, 0, 600, 480, pix);  // 游戏区域

    pix.load(":res/right_area.png");
    painter.drawPixmap(600, 0, 200, 480, pix);  // 控制区域

    // 尝试加载背景图片
    if (pix.load(":res/game_select.png")) {
        painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    } else {
        // 如果图片加载失败，使用纯色背景
        painter.fillRect(this->rect(), QColor(30, 144, 255));  // 使用道奇蓝作为背景
        painter.setPen(Qt::white);
        painter.setFont(QFont("宋体", 28));
        painter.drawText(this->rect(), Qt::AlignCenter, "游戏关卡选择");
    }
}
