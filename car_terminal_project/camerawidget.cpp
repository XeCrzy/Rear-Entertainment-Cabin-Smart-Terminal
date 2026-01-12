#include "camerawidget.h"
#include "ui_camerawidget.h"

#include <QImage>

CameraWidget::CameraWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CameraWidget)
{
    ui->setupUi(this);

    v4l2 = nullptr;

    // Ensure image directory exists
    QDir dir("./pic");
    if (!dir.exists()) {
        if (dir.mkpath(".")) {
            qDebug() << "Created image directory: ./pic/";
        } else {
            qDebug() << "Failed to create image directory: ./pic/";
        }
    }

    // Timer for updating video feed
    m_timer = new QTimer;
    connect(m_timer, &QTimer::timeout, this, &CameraWidget::onUpdateUIData);
}

CameraWidget::~CameraWidget()
{
    delete ui;
}

void CameraWidget::onUpdateUIData()
{
    char buffer[640*480*3] = {0};
    char rgbbuffer[640*480*3] = {0};

    // 1. Capture YUYV data
    v4l2->get_frame(buffer);

    // 2. Convert YUYV to RGB
    v4l2->yuv422torgb24((unsigned char *)buffer, (unsigned char *)rgbbuffer, 640, 480);

    // 3. Display image on UI
    QImage image = QImage((unsigned char *)rgbbuffer, 640, 480, QImage::Format_RGB888);
    QPixmap pic = QPixmap::fromImage(image);

    pic = pic.scaled(ui->label_video->size());
    ui->label_video->setPixmap(pic);

    saveImage = image;
}

// Start camera button
void CameraWidget::on_btn_start_clicked()
{
    if (v4l2 == nullptr) {
        v4l2 = new V4l2Api("/dev/video7");
    }

    v4l2->start(); // Start camera

    // Capture camera data every 100ms (10fps)
    m_timer->start(100);
}

// Stop camera button
void CameraWidget::on_btn_stop_clicked()
{
    m_timer->stop();

    if (v4l2 != nullptr) {
        v4l2->stop();
        v4l2->destory();
        delete v4l2;
        v4l2 = nullptr;
    }
}

// Capture button
void CameraWidget::on_btn_capture_clicked()
{
    // Get current time for filename
    QString curTime = QTime::currentTime().toString("hh:mm:ss");
    QString fileName = QString("./pic/%1.bmp").arg(curTime);

    // Remove colons from filename
    fileName = fileName.remove(':');
    qDebug() << "Saving image to:" << fileName;

    // Save captured image
    saveImage.save(fileName);
}

// Show gallery button
void CameraWidget::on_btn_show_clicked()
{
    // Create picture gallery window
    PicShowMainWindow *picWindow = new PicShowMainWindow(this);

    // Set auto-delete attribute
    picWindow->setAttribute(Qt::WA_DeleteOnClose);

    // Show gallery window and hide current window
    picWindow->show();
    this->hide();
}

void CameraWidget::on_btn_show_2_clicked()
{
    this->hide();
}

void CameraWidget::on_btn_return_clicked()
{
    this->hide();
}
