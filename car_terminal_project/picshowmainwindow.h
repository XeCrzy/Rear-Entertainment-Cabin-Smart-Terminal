#ifndef PICSHOWMAINWINDOW_H
#define PICSHOWMAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDir> // Directory class header
#include <QFileInfoList> // File list header

namespace Ui {
class PicShowMainWindow;
}

class PicShowMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PicShowMainWindow(QWidget *parent = nullptr);
    ~PicShowMainWindow();

private slots:
    void on_btn_prev_clicked();
    void on_btn_next_clicked();
    void on_btn_back_clicked();

private:
    Ui::PicShowMainWindow *ui;
    QFileInfoList fileList;  // Store image file names list
    int index; // Current index

    // Add this private function declaration
    void displayImage(int idx);
};

#endif // PICSHOWMAINWINDOW_H
