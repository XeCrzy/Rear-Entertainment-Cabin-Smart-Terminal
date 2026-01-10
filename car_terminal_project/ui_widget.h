/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QLabel *label_title;
    QSpacerItem *horizontalSpacer;
    QLabel *label_time;
    QFrame *frame;
    QLabel *label_weather;
    QLabel *label_temperature;
    QPushButton *btn_beijing;
    QPushButton *btn_guangzhou;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_send;
    QPushButton *btn_send;
    QFrame *frame_3;
    QPushButton *btn_game;
    QPushButton *btn_talk;
    QPushButton *btn_led;
    QPushButton *btn_buzzer;
    QPushButton *btn_music;
    QPushButton *btn_video;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 480);
        Widget->setMinimumSize(QSize(800, 480));
        Widget->setMaximumSize(QSize(800, 480));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush1(QColor(255, 255, 255, 128));
        brush1.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush2(QColor(255, 255, 255, 128));
        brush2.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        QBrush brush3(QColor(255, 255, 255, 128));
        brush3.setStyle(Qt::NoBrush);
        Widget->setPalette(palette);
        Widget->setStyleSheet(QString::fromUtf8("QWidget#Widget{\n"
"	border-image: url(:/image/background.png);\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"QPushButton {\n"
"    \n"
"	background-color: rgba(230, 230, 230, 150);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(255, 255, 255, 0.2);\n"
"}\n"
"QLabel#label_time{\n"
"	color: rgb(255, 255, 255);\n"
"	\n"
"	font: 11pt \"Arial Rounded MT Bold\";\n"
"	\n"
"}\n"
"\n"
"QLabel#label_title{\n"
"	color: rgb(255, 255, 255);\n"
"	\n"
"	font: 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"/* \346\263\250\346\204\217\357\274\232QLabel \347\232\204\347\261\273\345\220\215\345\267\262\344\277\256\346\255\243\357\274\210\345\216\237\350\257\215 QLbabel \344\270\272\347\254\224\350\257\257\357\274\211 */\n"
"QLabel#label_temperature {\n"
"    border: 1px solid white;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QLabel#label_weather {\n"
"    border: 1px solid white;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton#btn_guangzhou {\n"
""
                        "    border: 1px solid white;\n"
"    border-radius: 10px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton#btn_beijing {\n"
"    border: 1px solid white;\n"
"    border-radius: 10px;\n"
"	color: white;\n"
"	\n"
"\n"
"}\n"
"\n"
"QPushButton#btn_send {\n"
"	background-color: rgb(255, 85, 0);\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton#btn_game {\n"
"    border: 1px solid white;\n"
"    border-radius: 10px;\n"
"	color: white;\n"
"	\n"
"	border-image: url(:/image/game.png);\n"
"}\n"
"\n"
"QPushButton#btn_talk {\n"
"    border: 1px solid white;\n"
"    border-radius: 10px;\n"
"	color: white;\n"
"	\n"
"	border-image: url(:/image/talk.png);\n"
"}\n"
"\n"
"QPushButton#btn_led {\n"
"    border: 1px solid white;\n"
"    border-radius: 10px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton#btn_buzzer {\n"
"    border: 1px solid white;\n"
"    border-radius: 10px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton#btn_music {\n"
"    border: 1px solid white;\n"
"    border-radius: 10px;\n"
"	color: white;\n"
"	\n"
""
                        "	border-image: url(:/image/music.png);\n"
"}\n"
"\n"
"QPushButton#btn_video {\n"
"    border: 1px solid white;\n"
"    border-radius: 10px;\n"
"	color: white;\n"
"	\n"
"	border-image: url(:/image/video.png);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        widget_2 = new QWidget(Widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 800, 100));
        widget_2->setMinimumSize(QSize(800, 100));
        widget_2->setMaximumSize(QSize(800, 100));
        widget_2->setStyleSheet(QString::fromUtf8("background: qradialgradient(cx:0.5, cy:0.5, radius:1.2, fx:0.5, fy:0.5, \n"
"                stop:0 #2c3036, \n"
"                stop:0.6 #1a1c20, \n"
"                stop:1 #0a0b0d);\n"
"\n"
"    /* 2. \347\231\275\350\211\262\351\230\264\345\275\261\350\276\271\346\241\206\357\274\232\n"
"       \351\200\232\350\277\207\344\275\277\347\224\250 semi-transparent white (\345\215\212\351\200\217\346\230\216\347\231\275)\357\274\214\n"
"       \345\234\250\346\267\261\350\211\262\350\203\214\346\231\257\344\270\212\344\274\232\344\272\247\347\224\237\344\270\200\347\247\215\345\220\221\345\244\226\345\217\221\345\205\211\347\232\204\342\200\234\346\234\246\350\203\247\347\231\275\350\211\262\351\230\264\345\275\261\342\200\235\351\224\231\350\247\211\343\200\202*/\n"
"    border: 1px solid rgba(255, 255, 255, 40); \n"
"    border-radius: 12px;"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_title = new QLabel(widget_2);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setMinimumSize(QSize(250, 50));
        label_title->setMaximumSize(QSize(250, 50));
        label_title->setFrameShape(QFrame::Box);

        gridLayout->addWidget(label_title, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(397, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        label_time = new QLabel(widget_2);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setMinimumSize(QSize(200, 50));
        label_time->setMaximumSize(QSize(200, 50));
        label_time->setFrameShape(QFrame::Box);

        gridLayout->addWidget(label_time, 0, 2, 1, 1);

        frame = new QFrame(Widget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(20, 150, 371, 271));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        label_weather = new QLabel(frame);
        label_weather->setObjectName(QStringLiteral("label_weather"));
        label_weather->setGeometry(QRect(30, 10, 131, 81));
        label_weather->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_weather->setFrameShape(QFrame::Panel);
        label_weather->setAlignment(Qt::AlignCenter);
        label_temperature = new QLabel(frame);
        label_temperature->setObjectName(QStringLiteral("label_temperature"));
        label_temperature->setGeometry(QRect(200, 20, 131, 61));
        label_temperature->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_temperature->setFrameShape(QFrame::Panel);
        btn_beijing = new QPushButton(frame);
        btn_beijing->setObjectName(QStringLiteral("btn_beijing"));
        btn_beijing->setGeometry(QRect(30, 110, 101, 41));
        btn_guangzhou = new QPushButton(frame);
        btn_guangzhou->setObjectName(QStringLiteral("btn_guangzhou"));
        btn_guangzhou->setGeometry(QRect(210, 110, 101, 41));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 160, 351, 101));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit_send = new QLineEdit(frame_2);
        lineEdit_send->setObjectName(QStringLiteral("lineEdit_send"));

        horizontalLayout->addWidget(lineEdit_send);

        btn_send = new QPushButton(frame_2);
        btn_send->setObjectName(QStringLiteral("btn_send"));

        horizontalLayout->addWidget(btn_send);

        frame_3 = new QFrame(Widget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(430, 150, 351, 271));
        frame_3->setFrameShape(QFrame::Box);
        frame_3->setFrameShadow(QFrame::Raised);
        btn_game = new QPushButton(frame_3);
        btn_game->setObjectName(QStringLiteral("btn_game"));
        btn_game->setGeometry(QRect(50, 30, 101, 51));
        btn_talk = new QPushButton(frame_3);
        btn_talk->setObjectName(QStringLiteral("btn_talk"));
        btn_talk->setGeometry(QRect(200, 30, 101, 51));
        btn_led = new QPushButton(frame_3);
        btn_led->setObjectName(QStringLiteral("btn_led"));
        btn_led->setGeometry(QRect(50, 110, 101, 51));
        btn_buzzer = new QPushButton(frame_3);
        btn_buzzer->setObjectName(QStringLiteral("btn_buzzer"));
        btn_buzzer->setGeometry(QRect(200, 110, 101, 51));
        btn_music = new QPushButton(frame_3);
        btn_music->setObjectName(QStringLiteral("btn_music"));
        btn_music->setGeometry(QRect(50, 190, 101, 51));
        btn_video = new QPushButton(frame_3);
        btn_video->setObjectName(QStringLiteral("btn_video"));
        btn_video->setGeometry(QRect(200, 190, 101, 51));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        label_title->setText(QApplication::translate("Widget", "\350\275\246\350\275\275\346\231\272\350\203\275\347\273\210\347\253\257", 0));
        label_time->setText(QApplication::translate("Widget", "time", 0));
        label_weather->setText(QApplication::translate("Widget", "\345\244\251\346\260\224", 0));
        label_temperature->setText(QApplication::translate("Widget", "\346\270\251\345\272\246:18\342\204\203", 0));
        btn_beijing->setText(QApplication::translate("Widget", "\345\214\227\344\272\254", 0));
        btn_guangzhou->setText(QApplication::translate("Widget", "\345\271\277\345\267\236", 0));
        btn_send->setText(QApplication::translate("Widget", "\345\217\221\351\200\201", 0));
        btn_game->setText(QString());
        btn_talk->setText(QString());
        btn_led->setText(QApplication::translate("Widget", "led", 0));
        btn_buzzer->setText(QApplication::translate("Widget", "buzzer", 0));
        btn_music->setText(QString());
        btn_video->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
