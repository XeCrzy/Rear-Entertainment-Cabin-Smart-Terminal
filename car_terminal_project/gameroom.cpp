#include "gameroom.h"
#include "gameselect.h"
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QTimer>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>

GameRoom::GameRoom(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(800, 480);  // 修改为800*480
    this->setWindowIcon(QIcon(":res/ico.png"));
    this->setWindowTitle("游戏房间");

    // 初始化贪吃蛇
    snakeList.push_back(QRectF(400, 240, KSnakeNodeWidth, KSnakeNodeHeight));

    // 添加初始长度
    moveUp();
    moveUp();

    // 创建食物
    createNewFood();

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [=]()
    {
        int cnt = 1;
        if(snakeList.front().intersects(foodRect))
        {
            createNewFood();
            ++cnt;
            // 移除音频播放
        }

        while(cnt--)
        {
            switch(moveDirect)
            {
                case SnakeDirect::UP:
                    moveUp();
                    break;
                case SnakeDirect::DOWN:
                    moveDwn();
                    break;
                case SnakeDirect::LEFT:
                    moveLeft();
                    break;
                case SnakeDirect::RIGHT:
                    moveRight();
                    break;
                default:
                    qDebug() << "非法移动方向";
                    break;
            }
        }
        snakeList.pop_back();  // 删除最后一个节点
        update();
    });

    // 开始游戏按钮
    QPushButton* strBtn = new QPushButton(this);
    QPushButton* stopBtn = new QPushButton(this);

    strBtn->move(620, 100);   // 调整位置
    stopBtn->move(620, 150);

    strBtn->setText("开始");
    stopBtn->setText("暂停");

    QFont font("楷体", 14);  // 字体调小
    strBtn->setFont(font);
    stopBtn->setFont(font);

    connect(strBtn, &QPushButton::clicked, [=]()
    {
        isGameStart = true;
        timer->start(moveTimeout);
        // 移除音频播放
    });

    connect(stopBtn, &QPushButton::clicked, [=]()
    {
        isGameStart = false;
        timer->stop();
        // 移除音频停止
    });

    // 方向控制按钮
    QPushButton* up = new QPushButton(this);
    QPushButton* down = new QPushButton(this);
    QPushButton* left = new QPushButton(this);
    QPushButton* right = new QPushButton(this);

    up->move(660, 250);
    down->move(660, 310);
    left->move(620, 280);
    right->move(700, 280);

    up->setText("↑");
    down->setText("↓");
    left->setText("←");
    right->setText("→");

    up->setStyleSheet("QPushButton{border:0px; font-size: 20px;}");
    down->setStyleSheet("QPushButton{border:0px; font-size: 20px;}");
    left->setStyleSheet("QPushButton{border:0px; font-size: 20px;}");
    right->setStyleSheet("QPushButton{border:0px; font-size: 20px;}");

    QFont ft("宋体", 18);
    up->setFont(ft);
    down->setFont(ft);
    left->setFont(ft);
    right->setFont(ft);

    connect(up, &QPushButton::clicked, [=]()
    {
        if(moveDirect != SnakeDirect::DOWN)
            moveDirect = SnakeDirect::UP;
    });

    connect(down, &QPushButton::clicked, [=]()
    {
        if(moveDirect != SnakeDirect::UP)
            moveDirect = SnakeDirect::DOWN;
    });

    connect(left, &QPushButton::clicked, [=]()
    {
        if(moveDirect != SnakeDirect::RIGHT)
            moveDirect = SnakeDirect::LEFT;
    });

    connect(right, &QPushButton::clicked, [=]()
    {
        if(moveDirect != SnakeDirect::LEFT)
            moveDirect = SnakeDirect::RIGHT;
    });

    // 返回主界面按钮
    QPushButton* returnBtn = new QPushButton(this);
    returnBtn->move(620, 380);
    returnBtn->setText("返回主界面");
    returnBtn->setFont(font);
    returnBtn->setStyleSheet("QPushButton{padding: 8px;}");

    connect(returnBtn, &QPushButton::clicked, [=]()
    {
        // 停止游戏
        isGameStart = false;
        if(timer) timer->stop();

        // 发送返回信号
        emit returnToMain();
        this->close();
    });

    // 退出游戏按钮
    QPushButton* ExitBtn = new QPushButton(this);
    ExitBtn->move(620, 430);
    ExitBtn->setText("退出游戏");
    ExitBtn->setFont(font);
    ExitBtn->setStyleSheet("QPushButton{padding: 8px;}");

    connect(ExitBtn, &QPushButton::clicked, [=]()
    {
        // 移除音频播放
        this->close();
    });
}

void GameRoom::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 绘制背景 - 游戏区域600*480，控制区域200*480
    QPixmap pix;
    pix.load(":res/simple_room.png");
    painter.drawPixmap(0, 0, 600, 480, pix);  // 游戏区域

    pix.load(":res/right_area.png");
    painter.drawPixmap(600, 0, 200, 480, pix);  // 控制区域

    // 绘制蛇头
    if(moveDirect == SnakeDirect::UP)
    {
        pix.load(":res/up.png");
    }
    else if(moveDirect == SnakeDirect::DOWN)
    {
        pix.load(":res/down.png");
    }
    else if(moveDirect == SnakeDirect::LEFT)
    {
        pix.load(":res/left.png");
    }
    else if(moveDirect == SnakeDirect::RIGHT)
    {
        pix.load(":res/right.png");
    }

    auto snakeHead = snakeList.front();
    painter.drawPixmap(snakeHead.x(), snakeHead.y(), snakeHead.width(), snakeHead.height(), pix);

    // 绘制蛇身
    pix.load(":res/body.png");
    for(int i = 1; i < snakeList.size() - 1; i++)
    {
        auto node = snakeList.at(i);
        painter.drawPixmap(node.x(), node.y(), node.width(), node.height(), pix);
    }

    // 绘制蛇尾巴
    auto snakeTail = snakeList.back();
    painter.drawPixmap(snakeTail.x(), snakeTail.y(), snakeTail.width(), snakeTail.height(), pix);

    // 绘制食物
    pix.load(":res/normal_food.bmp");
    painter.drawPixmap(foodRect.x(), foodRect.y(), foodRect.width(), foodRect.height(), pix);

    // 绘制分数背景
    pix.load(":res/sorce_bg.png");
    painter.drawPixmap(610, 20, 90, 40, pix);

    // 绘制分数
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    QFont font("方正舒体", 16);  // 字体调小
    painter.setFont(font);
    painter.drawText(635, 48, QString("%1").arg(snakeList.size() - 3));  // 减去初始长度3

    // 保存分数到文件
    int score = snakeList.size() - 3;  // 计算得分
    QFile file("C:/Users/zzc/Desktop/1.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << score;
        file.close();
    }

    // 绘制游戏失败效果
    if(checkFail())
    {
        pen.setColor(Qt::red);
        painter.setPen(pen);
        QFont font("方正舒体", 30);  // 字体调小
        painter.setFont(font);
        painter.drawText(200, 200, QString("游戏结束!"));
        timer->stop();
        // 移除音频播放
    }
}

void GameRoom::moveUp()
{
    QPointF leftTop;
    QPointF rightBottom;

    auto snakeNode = snakeList.front();
    int headX = snakeNode.x();
    int headY = snakeNode.y();

    if(headY < 0)  // 穿墙处理
    {
        leftTop = QPointF(headX, 480 - KSnakeNodeHeight);
    }
    else
    {
        leftTop = QPointF(headX, headY - KSnakeNodeHeight);
    }

    rightBottom = leftTop + QPoint(KSnakeNodeWidth, KSnakeNodeHeight);
    snakeList.push_front(QRectF(leftTop, rightBottom));
}

void GameRoom::moveDwn()
{
    QPointF leftTop;
    QPointF rightBottom;

    auto snakeNode = snakeList.front();
    int headX = snakeNode.x();
    int headY = snakeNode.y();

    if(headY + KSnakeNodeHeight > 480)  // 注意这里是480不是800
    {
        leftTop = QPointF(headX, 0);
    }
    else
    {
        leftTop = snakeNode.bottomLeft();
    }

    rightBottom = leftTop + QPointF(KSnakeNodeWidth, KSnakeNodeHeight);
    snakeList.push_front(QRectF(leftTop, rightBottom));
}

void GameRoom::moveLeft()
{
    QPointF leftTop;
    QPointF rightBottom;

    auto snakeNode = snakeList.front();
    int headX = snakeNode.x();
    int headY = snakeNode.y();

    if(headX < 0)
    {
        leftTop = QPointF(600 - KSnakeNodeWidth, headY);  // 游戏区域宽度为600
    }
    else
    {
        leftTop = QPointF(headX - KSnakeNodeWidth, headY);
    }

    rightBottom = leftTop + QPointF(KSnakeNodeWidth, KSnakeNodeHeight);
    snakeList.push_front(QRectF(leftTop, rightBottom));
}

void GameRoom::moveRight()
{
    QPointF leftTop;
    QPointF rightBottom;

    auto snakeNode = snakeList.front();
    int headX = snakeNode.x();
    int headY = snakeNode.y();

    if(headX + KSnakeNodeWidth > 600)  // 游戏区域宽度为600
    {
        leftTop = QPointF(0, headY);
    }
    else
    {
        leftTop = snakeNode.topRight();
    }

    rightBottom = leftTop + QPointF(KSnakeNodeWidth, KSnakeNodeHeight);
    snakeList.push_front(QRectF(leftTop, rightBottom));
}

bool GameRoom::checkFail()
{
    // 检查是否撞墙（游戏区域边界）
    auto head = snakeList.front();
    if(head.x() < 0 || head.x() >= 600 || head.y() < 0 || head.y() >= 480)
    {
        return true;
    }

    // 检查是否撞到自己
    for(int i = 1; i < snakeList.size(); i++)
    {
        if(snakeList.at(i) == snakeList.at(0))
        {
            return true;
        }
    }

    return false;
}

void GameRoom::createNewFood()
{
    // 在游戏区域内随机生成食物（600*480）
    foodRect = QRectF(qrand() % (600 / KSnakeNodeWidth) * KSnakeNodeWidth,
                      qrand() % (480 / KSnakeNodeHeight) * KSnakeNodeHeight,
                      KSnakeNodeWidth,
                      KSnakeNodeHeight);

    // 确保食物不会生成在蛇身上
    for(const auto& segment : snakeList)
    {
        if(segment.intersects(foodRect))
        {
            createNewFood();  // 重新生成
            break;
        }
    }
}
