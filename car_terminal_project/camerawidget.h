#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>

#include <QTimer>
#include <QTime>
#include <QDebug>
#include "v4l2api.h"
#include "picshowmainwindow.h" // 子窗口的头文件


QT_BEGIN_NAMESPACE
namespace Ui { class CameraWidget; }
QT_END_NAMESPACE

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    CameraWidget(QWidget *parent = nullptr);
    ~CameraWidget();

private slots:
    void onUpdateUIData();
    void on_btn_start_clicked();

    void on_btn_stop_clicked();

    void on_btn_capture_clicked();

    void on_btn_show_clicked();

    void on_btn_show_2_clicked();

    void on_btn_return_clicked();

private:
    Ui::CameraWidget *ui;

    V4l2Api *v4l2;//定义一个摄像头类的指针
    QTimer *m_timer;

    QImage saveImage;  //图片处理类的对象
};
#endif // CAMERAWIDGET_H
