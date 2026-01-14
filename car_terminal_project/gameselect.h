#ifndef GAMESELECT_H
#define GAMESELECT_H

#include <QWidget>

class GameSelect : public QWidget
{
    Q_OBJECT
public:
    explicit GameSelect(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

signals:
    void returnToMain();  // 返回主界面的信号
};

#endif // GAMESELECT_H
