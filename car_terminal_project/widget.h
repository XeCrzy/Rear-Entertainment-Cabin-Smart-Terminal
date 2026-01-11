#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMenuBar>
#include <QTextEdit>
#include "easyInput/easyinput.h"
#include "threadtime.h"

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


private slots:
    void slotHideInput();
    void exitWindow();
    // 时间更新槽函数
    void onTimeUpdated(const QString &timeStr);
    void onNtpSyncFinished(bool success, const QString &timeStr);



};
#endif // WIDGET_H
