#include "picshowmainwindow.h"
#include "ui_picshowmainwindow.h"

#include <QDir>
#include <QPixmap>
#include <QFileInfo>
#include <QMessageBox>
#include <QImageReader>

PicShowMainWindow::PicShowMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PicShowMainWindow),
    index(0)
{
    ui->setupUi(this);

    // Initialize variables
    index = 0;

    // Load images from directory
    QDir dir("./pic");

    if (!dir.exists()) {
        qDebug() << "Image directory does not exist: ./pic/";
        QMessageBox::warning(this, "Warning", "Image directory does not exist!");
        return;
    }

    // Get all image files
    QStringList filters;
    filters << "*.bmp" << "*.BMP" << "*.jpg" << "*.JPG"
            << "*.jpeg" << "*.JPEG" << "*.png" << "*.PNG";

    // Sort by time (newest first)
    dir.setSorting(QDir::Time | QDir::Reversed);
    fileList = dir.entryInfoList(filters, QDir::Files, QDir::Time);

    qDebug() << "Found images:" << fileList.size();

    if (fileList.isEmpty()) {
        qDebug() << "No image files found in directory";
        QMessageBox::information(this, "Information", "No image files found!");
        ui->label->setText("No images to display");
        return;
    }

    // Display first image
    displayImage(0);
}

PicShowMainWindow::~PicShowMainWindow()
{
    delete ui;
}

void PicShowMainWindow::displayImage(int idx)
{
    // Safety boundary check
    if (fileList.isEmpty() || idx < 0 || idx >= fileList.size()) {
        qDebug() << "Invalid image index:" << idx << ", total images:" << fileList.size();

        if (fileList.isEmpty()) {
            ui->label->clear();
            ui->label->setText("No images to display");
        }
        return;
    }

    QFileInfo fileInfo = fileList.at(idx);
    QString imagePath = fileInfo.absoluteFilePath();

    qDebug() << "Loading image:" << imagePath << ", index:" << idx;

    // Check if file exists
    if (!fileInfo.exists()) {
        qDebug() << "Image file does not exist:" << imagePath;
        ui->label->setText(QString("File not found:\n%1").arg(fileInfo.fileName()));
        return;
    }

    // Check if file is readable
    if (!fileInfo.isReadable()) {
        qDebug() << "Image file is not readable:" << imagePath;
        ui->label->setText(QString("File not readable:\n%1").arg(fileInfo.fileName()));
        return;
    }

    // Load image
    QPixmap pixmap;
    if (!pixmap.load(imagePath)) {
        qDebug() << "Failed to load image:" << imagePath;

        // Try to get detailed error info
        QImageReader reader(imagePath);
        if (!reader.canRead()) {
            qDebug() << "Cannot read image format, possibly corrupted:" << reader.errorString();
        }

        ui->label->setText(QString("Load failed:\n%1").arg(fileInfo.fileName()));
        return;
    }

    // Check if image is valid
    if (pixmap.isNull()) {
        qDebug() << "Image is null:" << imagePath;
        ui->label->setText(QString("Invalid image:\n%1").arg(fileInfo.fileName()));
        return;
    }

    qDebug() << "Successfully loaded image, size:" << pixmap.size();

    // Scale and display image
    QPixmap scaledPixmap = pixmap.scaled(
        ui->label->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );

    ui->label->setPixmap(scaledPixmap);
    ui->label->setAlignment(Qt::AlignCenter);

    // Update status bar
    QString statusText = QString("Image %1/%2: %3")
                            .arg(idx + 1)
                            .arg(fileList.size())
                            .arg(fileInfo.fileName());
    statusBar()->showMessage(statusText);

    // Update current index
    index = idx;
}

void PicShowMainWindow::on_btn_prev_clicked()
{
    qDebug() << "Previous button clicked, current index:" << index;

    if (fileList.isEmpty()) {
        qDebug() << "Image list is empty, cannot navigate";
        return;
    }

    int newIndex = index - 1;
    if (newIndex < 0) {
        // Loop to last image
        newIndex = fileList.size() - 1;
    }

    qDebug() << "Switch to previous image, new index:" << newIndex;
    displayImage(newIndex);
}

void PicShowMainWindow::on_btn_next_clicked()
{
    qDebug() << "Next button clicked, current index:" << index;

    if (fileList.isEmpty()) {
        qDebug() << "Image list is empty, cannot navigate";
        return;
    }

    int newIndex = index + 1;
    if (newIndex >= fileList.size()) {
        // Loop to first image
        newIndex = 0;
    }

    qDebug() << "Switch to next image, new index:" << newIndex;
    displayImage(newIndex);
}

void PicShowMainWindow::on_btn_back_clicked()
{
    qDebug() << "Back button clicked";

    // Show parent window
    if (parentWidget()) {
        parentWidget()->show();
    }

    // Close current window
    this->close();
}
