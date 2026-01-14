#ifndef GAMEROOM_H
#define GAMEROOM_H

#include <QWidget>
#include <QPaintEvent>
#include <QList>

enum class SnakeDirect
{
    UP=1,
    DOWN,
    LEFT,
    RIGHT
};

class GameRoom : public QWidget
{
    Q_OBJECT
public:
    explicit GameRoom(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* event);

    void moveUp();      // 蛇向上移动
    void moveDwn();     // 蛇向下移动
    void moveLeft();    // 蛇向左移动
    void moveRight();   // 蛇向右移动

    bool checkFail();   // 判断游戏是否结束
    void createNewFood();

    void setTimeout(int timeout){ moveTimeout = timeout; }

signals:
    void returnToMain();  // 返回主界面的信号

private:
    const int KSnakeNodeWidth = 20;
    const int KSnakeNodeHeight = 20;
    const int KDefaultTimeout = 200;  // 默认速度
    QList<QRectF> snakeList;          // 表示贪吃蛇链表
    QRectF foodRect;                  // 表示食物节点

    SnakeDirect moveDirect = SnakeDirect::UP;  // 设置蛇默认移动方向为上
    QTimer* timer;                             // 定时器

    bool isGameStart = false;  // 表示是否开始游戏
    int moveTimeout = KDefaultTimeout;
};

#endif // GAMEROOM_H
