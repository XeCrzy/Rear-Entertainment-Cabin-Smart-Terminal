/********************************************************************************
** Form generated from reading UI file 'camerawidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAWIDGET_H
#define UI_CAMERAWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraWidget
{
public:
    QLabel *label_video;
    QPushButton *btn_start;
    QPushButton *btn_stop;
    QPushButton *btn_capture;
    QPushButton *btn_show;
    QPushButton *btn_return;

    void setupUi(QWidget *CameraWidget)
    {
        if (CameraWidget->objectName().isEmpty())
            CameraWidget->setObjectName(QStringLiteral("CameraWidget"));
        CameraWidget->resize(800, 480);
        label_video = new QLabel(CameraWidget);
        label_video->setObjectName(QStringLiteral("label_video"));
        label_video->setGeometry(QRect(0, 0, 640, 480));
        label_video->setStyleSheet(QStringLiteral("background-color: rgb(158, 158, 158);"));
        btn_start = new QPushButton(CameraWidget);
        btn_start->setObjectName(QStringLiteral("btn_start"));
        btn_start->setGeometry(QRect(660, 10, 111, 61));
        btn_stop = new QPushButton(CameraWidget);
        btn_stop->setObjectName(QStringLiteral("btn_stop"));
        btn_stop->setGeometry(QRect(660, 90, 111, 61));
        btn_capture = new QPushButton(CameraWidget);
        btn_capture->setObjectName(QStringLiteral("btn_capture"));
        btn_capture->setGeometry(QRect(660, 170, 111, 61));
        btn_show = new QPushButton(CameraWidget);
        btn_show->setObjectName(QStringLiteral("btn_show"));
        btn_show->setGeometry(QRect(660, 260, 111, 61));
        btn_return = new QPushButton(CameraWidget);
        btn_return->setObjectName(QStringLiteral("btn_return"));
        btn_return->setGeometry(QRect(660, 350, 111, 61));

        retranslateUi(CameraWidget);

        QMetaObject::connectSlotsByName(CameraWidget);
    } // setupUi

    void retranslateUi(QWidget *CameraWidget)
    {
        CameraWidget->setWindowTitle(QApplication::translate("CameraWidget", "Widget", 0));
        label_video->setText(QString());
        btn_start->setText(QApplication::translate("CameraWidget", "\345\274\200\345\220\257", 0));
        btn_stop->setText(QApplication::translate("CameraWidget", "\345\201\234\346\255\242", 0));
        btn_capture->setText(QApplication::translate("CameraWidget", "\346\212\223\346\213\215", 0));
        btn_show->setText(QApplication::translate("CameraWidget", "\346\265\217\350\247\210", 0));
        btn_return->setText(QApplication::translate("CameraWidget", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", 0));
    } // retranslateUi

};

namespace Ui {
    class CameraWidget: public Ui_CameraWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAWIDGET_H
