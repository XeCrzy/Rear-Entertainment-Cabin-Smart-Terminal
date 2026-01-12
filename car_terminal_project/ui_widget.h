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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_5;
    QFrame *frame_header;
    QHBoxLayout *horizontalLayout;
    QLabel *label_title;
    QLabel *label_weather;
    QLabel *label_temperature;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_time;
    QFrame *frame_mid_part;
    QHBoxLayout *horizontalLayout_8;
    QFrame *frame_game;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *btn_snake;
    QPushButton *btn_plane;
    QPushButton *btn_more_game;
    QFrame *frame_music;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_2;
    QLabel *label_3;
    QSlider *horizontalSlider;
    QWidget *widget_music_btn;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_music_pre;
    QPushButton *btn_music_play;
    QPushButton *btn_music_next;
    QFrame *frame_fun;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit;
    QPushButton *btn_send;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btn_beijing;
    QPushButton *btn_guangzhou;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_6;
    QPushButton *btn_camera;
    QFrame *frame_talk;
    QLabel *label_7;
    QPushButton *btn_talk1;
    QFrame *frame_bottom;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_led;
    QPushButton *btn_led_switch;
    QPushButton *btn_talk;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btn_wind_small;
    QPushButton *btn_fan;
    QPushButton *btn_wind_big;
    QLabel *label_buzzer;
    QPushButton *btn_buzzer_switch;
    QPushButton *btn_help;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 480);
        Widget->setMinimumSize(QSize(800, 480));
        Widget->setMaximumSize(QSize(800, 480));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(240, 242, 245, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush3(QColor(0, 0, 0, 128));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush4(QColor(255, 255, 255, 128));
        brush4.setStyle(Qt::SolidPattern);
        Widget->setPalette(palette);
        Widget->setStyleSheet(QString::fromUtf8("/* ===================== \345\205\250\345\261\200\346\240\271\345\256\271\345\231\250 \345\205\250\345\261\200\346\240\267\345\274\217\343\200\220\344\270\245\346\240\274\344\270\215\344\277\256\346\224\271\345\270\203\345\261\200/\345\260\272\345\257\270\343\200\221 ===================== */\n"
"/* \346\225\264\344\270\252\344\270\273\347\252\227\344\275\223\350\203\214\346\231\257\357\274\214\345\217\202\350\200\203\345\233\276\347\232\204\346\265\205\347\201\260\345\272\225\350\211\262\357\274\214\344\270\215\345\275\261\345\223\215\344\273\273\344\275\225\345\255\220\346\216\247\344\273\266\345\244\247\345\260\217\344\275\215\347\275\256 */\n"
"QWidget#Widget {\n"
"    background-color: #F0F2F5;\n"
"}\n"
"\n"
"/* ===================== \345\244\264\351\203\250\345\214\272\345\237\237 - frame_header \345\217\212\345\206\205\351\203\250\346\211\200\346\234\211\346\216\247\344\273\266 \343\200\220\344\270\245\346\240\274\345\216\237\345\270\203\345\261\200\343\200\221 ===================== */\n"
"/* \345\244\264"
                        "\351\203\250\346\200\273\346\241\206\346\236\266\350\203\214\346\231\257+\350\276\271\346\241\206\357\274\232\347\272\257\347\231\275\345\272\225\350\211\262+\347\273\206\347\201\260\350\276\271\346\241\206\357\274\214\345\217\202\350\200\203\345\233\276\345\244\264\351\203\250\346\240\267\345\274\217 */\n"
"QFrame#frame_header {\n"
"    background-color: #FFFFFF;\n"
"    border: 1px solid #E4E7ED;\n"
"    border-radius: 4px;\n"
"	box-shadow: 0px 0px 6px 1px #20000000;\n"
"}\n"
"/* \345\244\264\351\203\250\346\240\207\351\242\230-\350\275\246\350\275\275\346\231\272\350\203\275\347\273\210\347\253\257 \346\226\207\345\255\227\346\240\267\345\274\217 */\n"
"QLabel#label_title {\n"
"    color: #1E293B;/* \346\267\261\347\201\260\344\270\273\346\226\207\345\255\227\350\211\262 */\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    border: none;/* \346\270\205\351\231\244\345\216\237\351\273\230\350\256\244\350\276\271\346\241\206\357\274\214\350\277\230\345\216\237\346\270\205\347\210\275\346\240\267\345\274"
                        "\217 */\n"
"}\n"
"/* \345\244\264\351\203\250\345\244\251\346\260\224\346\240\207\347\255\276 \346\226\207\345\255\227\346\240\267\345\274\217 */\n"
"QLabel#label_weather {\n"
"    color: #334155;/* \344\270\255\347\201\260\346\226\207\345\255\227\350\211\262 */\n"
"    font-size: 13px;\n"
"    font-weight: normal;\n"
"    border: none;/* \346\270\205\351\231\244\345\216\237\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"}\n"
"/* \345\244\264\351\203\250\346\270\251\345\272\246\346\240\207\347\255\276 \346\226\207\345\255\227\346\240\267\345\274\217 */\n"
"QLabel#label_temperature {\n"
"    color: #334155;/* \344\270\255\347\201\260\346\226\207\345\255\227\350\211\262 */\n"
"    font-size: 13px;\n"
"    font-weight: normal;\n"
"    border: none;/* \346\270\205\351\231\244\345\216\237\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"}\n"
"/* \345\244\264\351\203\250\346\227\266\351\227\264\346\240\207\347\255\276 \346\226\207\345\255\227\346\240\267\345\274\217 */\n"
"QLabel#label_time {\n"
"    c"
                        "olor: #1E293B;/* \346\267\261\347\201\260\344\270\273\346\226\207\345\255\227\350\211\262 */\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"    border: none;/* \346\270\205\351\231\244\345\216\237\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"    qproperty-alignment: AlignCenter;/* \346\226\207\345\255\227\345\261\205\344\270\255\357\274\214\344\270\215\344\277\256\346\224\271\346\216\247\344\273\266\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"/* ===================== \344\270\255\351\203\250\346\240\270\345\277\203\345\214\272\345\237\237 - frame_mid_part \345\217\212\345\206\205\351\203\2504\344\270\252\345\212\237\350\203\275\345\215\241\347\211\207 \343\200\220\344\270\245\346\240\274\345\216\237\345\270\203\345\261\200/\345\216\237\351\227\264\350\267\235\343\200\221 ===================== */\n"
"/* \344\270\255\351\203\250\346\200\273\346\241\206\346\236\266\346\240\267\345\274\217\357\274\232\351\200\217\346\230\216\350\203\214\346\231\257\357\274\214\344\270\215\351\201\256\346\214\241\345"
                        "\272\225\345\261\202\345\272\225\350\211\262\357\274\214\344\270\215\344\277\256\346\224\271\344\273\273\344\275\225\345\270\203\345\261\200 */\n"
"QFrame#frame_mid_part {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}\n"
"/* \346\270\270\346\210\217\345\214\272\345\215\241\347\211\207 - frame_game \346\225\264\344\275\223\346\240\267\345\274\217\343\200\220\345\216\237\345\244\247\345\260\217/\345\216\237\344\275\215\347\275\256/\345\216\237\345\206\205\350\276\271\350\267\235\343\200\221 */\n"
"QFrame#frame_game {\n"
"    background-color: #FFFFFF;/* \345\215\241\347\211\207\347\272\257\347\231\275\350\203\214\346\231\257 */\n"
"    border: 1px solid #E4E7ED;/* \345\215\241\347\211\207\347\273\206\347\201\260\350\276\271\346\241\206 */\n"
"    border-radius: 6px;/* \345\215\241\347\211\207\345\234\206\350\247\222\357\274\214\345\217\202\350\200\203\345\233\276\346\225\210\346\236\234 */\n"
"}\n"
"/* \351\237\263\344\271\220\345\214\272\345\215\241\347\211\207 - frame_music \346\225\264\344"
                        "\275\223\346\240\267\345\274\217\343\200\220\345\216\237\345\244\247\345\260\217/\345\216\237\344\275\215\347\275\256/\345\216\237\345\206\205\350\276\271\350\267\235\343\200\221 */\n"
"QFrame#frame_music {\n"
"    background-color: #FFFFFF;/* \345\215\241\347\211\207\347\272\257\347\231\275\350\203\214\346\231\257 */\n"
"    border: 1px solid #E4E7ED;/* \345\215\241\347\211\207\347\273\206\347\201\260\350\276\271\346\241\206 */\n"
"    border-radius: 6px;/* \345\215\241\347\211\207\345\234\206\350\247\222\357\274\214\345\217\202\350\200\203\345\233\276\346\225\210\346\236\234 */\n"
"}\n"
"/* \345\244\251\346\260\224+\350\247\206\351\242\221\345\214\272\345\215\241\347\211\207 - frame_fun \346\225\264\344\275\223\346\240\267\345\274\217\343\200\220\345\216\237\345\244\247\345\260\217/\345\216\237\344\275\215\347\275\256/\345\216\237\345\206\205\350\276\271\350\267\235\343\200\221 */\n"
"QFrame#frame_fun {\n"
"    background-color: #FFFFFF;/* \345\215\241\347\211\207\347\272\257\347\231\275\350\203\214\346\231\257"
                        " */\n"
"    border: 1px solid #E4E7ED;/* \345\215\241\347\211\207\347\273\206\347\201\260\350\276\271\346\241\206 */\n"
"    border-radius: 6px;/* \345\215\241\347\211\207\345\234\206\350\247\222\357\274\214\345\217\202\350\200\203\345\233\276\346\225\210\346\236\234 */\n"
"}\n"
"/* \346\231\272\350\203\275\350\257\255\351\237\263\345\214\272\345\215\241\347\211\207 - frame_talk \346\225\264\344\275\223\346\240\267\345\274\217\343\200\220\345\216\237\345\244\247\345\260\217/\345\216\237\344\275\215\347\275\256/\345\216\237\345\206\205\350\276\271\350\267\235\343\200\221 */\n"
"QFrame#frame_talk {\n"
"    background-color: #FFFFFF;/* \345\215\241\347\211\207\347\272\257\347\231\275\350\203\214\346\231\257 */\n"
"    border: 1px solid #E4E7ED;/* \345\215\241\347\211\207\347\273\206\347\201\260\350\276\271\346\241\206 */\n"
"    border-radius: 6px;/* \345\215\241\347\211\207\345\234\206\350\247\222\357\274\214\345\217\202\350\200\203\345\233\276\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"/* -------------------- \344"
                        "\270\255\351\203\250\346\211\200\346\234\211\345\212\237\350\203\275\345\214\272 \346\240\207\351\242\230\346\240\207\347\255\276 \347\273\237\344\270\200\346\240\267\345\274\217 \343\200\220\346\270\270\346\210\217\345\214\272/\351\237\263\344\271\220\346\222\255\346\224\276\345\214\272\347\255\211\343\200\221 -------------------- */\n"
"QLabel#label { /* \346\270\270\346\210\217\345\214\272\346\240\207\351\242\230 */\n"
"    color: #1E293B;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    border: none;/* \346\270\205\351\231\244\345\216\237\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"}\n"
"QLabel#label_2 { /* \351\237\263\344\271\220\346\222\255\346\224\276\345\214\272\346\240\207\351\242\230 */\n"
"    color: #1E293B;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    border: none;/* \346\270\205\351\231\244\345\216\237\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"}\n"
"QLabel#label_5 { /* \350\216\267\345\217\226\345\237\216\345\270\202\345\244\251\346\260\224\346\240"
                        "\207\351\242\230 */\n"
"    color: #1E293B;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    border: none;/* \346\270\205\351\231\244\345\216\237\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"}\n"
"QLabel#label_6 { /* \350\247\206\351\242\221\346\222\255\346\224\276\346\240\207\351\242\230 */\n"
"    color: #1E293B;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    border: none;/* \346\270\205\351\231\244\345\216\237\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"}\n"
"QLabel#label_7 { /* \346\231\272\350\203\275\350\257\255\351\237\263\345\212\251\346\211\213\346\240\207\351\242\230 */\n"
"    color: #1E293B;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    border: none;/* \346\270\205\351\231\244\345\216\237\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"}\n"
"\n"
"/* -------------------- \346\270\270\346\210\217\345\214\272\345\206\205\351\203\250\346\214\211\351\222\256 \346\240\267\345\274\217\343\200\220\350\264\252\345\220\203\350\233\207/\351\243"
                        "\236\346\234\272\345\244\247\346\210\230/\346\233\264\345\244\232\346\270\270\346\210\217\357\274\214\345\216\237\345\244\247\345\260\217\344\270\215\345\217\230\343\200\221 -------------------- */\n"
"QPushButton#btn_snake {\n"
"    background-color: #2563EB;/* \350\223\235\350\211\262\346\214\211\351\222\256\357\274\214\345\217\202\350\200\203\345\233\276\351\205\215\350\211\262 */\n"
"    color: #FFFFFF;/* \347\231\275\350\211\262\346\226\207\345\255\227 */\n"
"    font-size: 13px;\n"
"    font-weight: normal;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton#btn_snake:hover {background-color: #1D4ED8;}/* \346\202\254\346\265\256\345\212\240\346\267\261\357\274\214\346\227\240\344\275\215\347\247\273 */\n"
"QPushButton#btn_snake:pressed {background-color: #1E40AF;}/* \346\214\211\344\270\213\346\233\264\346\267\261\357\274\214\346\227\240\344\275\215\347\247\273 */\n"
"\n"
"QPushButton#btn_plane {\n"
"    background-color: #DC2626;/* \347\272\242\350\211\262\346\214\211\351\222\256\357"
                        "\274\214\345\217\202\350\200\203\345\233\276\351\205\215\350\211\262 */\n"
"    color: #FFFFFF;/* \347\231\275\350\211\262\346\226\207\345\255\227 */\n"
"    font-size: 13px;\n"
"    font-weight: normal;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton#btn_plane:hover {background-color: #B91C1C;}/* \346\202\254\346\265\256\345\212\240\346\267\261\357\274\214\346\227\240\344\275\215\347\247\273 */\n"
"QPushButton#btn_plane:pressed {background-color: #991B1B;}/* \346\214\211\344\270\213\346\233\264\346\267\261\357\274\214\346\227\240\344\275\215\347\247\273 */\n"
"\n"
"QPushButton#btn_more_game {\n"
"    background-color: #64748B;/* \347\201\260\350\211\262\346\214\211\351\222\256\357\274\214\345\217\202\350\200\203\345\233\276\351\205\215\350\211\262 */\n"
"    color: #FFFFFF;/* \347\231\275\350\211\262\346\226\207\345\255\227 */\n"
"    font-size: 13px;\n"
"    font-weight: normal;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton#btn_more_game:hover {background-col"
                        "or: #475569;}/* \346\202\254\346\265\256\345\212\240\346\267\261\357\274\214\346\227\240\344\275\215\347\247\273 */\n"
"QPushButton#btn_more_game:pressed {background-color: #334155;}/* \346\214\211\344\270\213\346\233\264\346\267\261\357\274\214\346\227\240\344\275\215\347\247\273 */\n"
"\n"
"/* -------------------- \351\237\263\344\271\220\345\214\272\345\206\205\351\203\250\346\216\247\344\273\266 \346\240\267\345\274\217\343\200\220\345\216\237\345\244\247\345\260\217/\345\216\237\344\275\215\347\275\256\344\270\215\345\217\230\343\200\221 -------------------- */\n"
"/* \351\237\263\344\271\220\345\234\206\345\275\242\345\233\276\346\240\207\345\256\271\345\231\250 - \345\217\252\345\212\240\350\276\271\346\241\206\345\222\214\345\234\206\350\247\222\357\274\214\344\275\240\345\220\216\346\234\237\345\212\240border-image\345\215\263\345\217\257\357\274\214\345\244\247\345\260\217\344\270\215\345\217\230 */\n"
"QLabel#label_3 {\n"
"    border: 1px solid #E4E7ED;\n"
"    border-radius: 70px;/* \345\256\214\347"
                        "\276\216\345\234\206\345\275\242\357\274\214\345\214\271\351\205\215\344\275\240\347\232\204140x160\345\260\272\345\257\270 */\n"
"    background-color: #F8FAFC;\n"
"    border-style: solid;\n"
"}\n"
"/* \351\237\263\344\271\220\351\237\263\351\207\217\346\273\221\345\235\227 \347\276\216\345\214\226\357\274\214\344\270\215\344\277\256\346\224\271\346\273\221\345\235\227\345\244\247\345\260\217/\344\275\215\347\275\256 */\n"
"QSlider#horizontalSlider {\n"
"    background-color: #E4E7ED;/* \346\273\221\345\235\227\345\272\225\350\211\262 */\n"
"    height: 4px;\n"
"    border-radius: 2px;\n"
"}\n"
"QSlider#horizontalSlider::handle {\n"
"    width: 12px;\n"
"    height: 12px;\n"
"    background-color: #2563EB;/* \346\273\221\345\235\227\346\214\211\351\222\256\350\223\235\350\211\262 */\n"
"    border-radius: 6px;/* \345\234\206\345\275\242\346\273\221\345\235\227 */\n"
"    margin-top: -4px;\n"
"    margin-bottom: -4px;\n"
"    border: none;\n"
"}\n"
"/* \351\237\263\344\271\220\344\270\212\344\270\200\346\233\262"
                        "/\346\222\255\346\224\276/\344\270\213\344\270\200\346\233\262\346\214\211\351\222\256 \346\240\267\345\274\217 */\n"
"QPushButton#btn_music_pre,QPushButton#btn_music_next {\n"
"    background-color: #E2E8F0;\n"
"    color: #1E293B;\n"
"    font-size: 12px;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton#btn_music_play {\n"
"    background-color: #2563EB;\n"
"    color: #FFFFFF;\n"
"    font-size: 12px;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"/* -------------------- \345\244\251\346\260\224\345\214\272-\350\276\223\345\205\245\346\241\206+\346\214\211\351\222\256 \346\240\267\345\274\217\343\200\220\345\216\237\345\244\247\345\260\217\344\270\215\345\217\230\343\200\221 -------------------- */\n"
"QLineEdit#lineEdit {\n"
"    border:1px solid #E4E7ED;\n"
"    border-radius:4px;\n"
"    background-color:#FFFFFF;\n"
"    color:#1E293B;\n"
"    font-size:12px;\n"
"    padding-left:5px;\n"
"}\n"
"QPushButton#btn_send,QPushButton#btn_beijing,QPushButton#btn_guangzhou"
                        " {\n"
"    background-color: #E2E8F0;\n"
"    color: #1E293B;\n"
"    font-size:12px;\n"
"    border:none;\n"
"    border-radius:4px;\n"
"}\n"
"QPushButton#btn_send:hover,QPushButton#btn_beijing:hover,QPushButton#btn_guangzhou:hover {\n"
"    background-color: #CBD5E1;\n"
"}\n"
"\n"
"/* -------------------- \350\247\206\351\242\221\345\214\272 \346\240\267\345\274\217\343\200\220\345\216\237\345\244\247\345\260\217\344\270\215\345\217\230\343\200\221 -------------------- */\n"
"/* \350\247\206\351\242\221\346\222\255\346\224\276\345\256\271\345\231\250 - \344\275\240\345\220\216\346\234\237\345\212\240border-image\357\274\214\345\217\252\345\212\240\345\272\225\350\211\262\345\222\214\350\276\271\346\241\206 */\n"
"QWidget#widget {\n"
"    background-color: #1E293B;\n"
"    border:1px solid #475569;\n"
"    border-radius:4px;\n"
"}\n"
"/* \350\247\206\351\242\221\346\222\255\346\224\276/\346\232\202\345\201\234\346\214\211\351\222\256 */\n"
"QPushButton#btn_start_pause {\n"
"    background-color: #2563EB;\n"
""
                        "    color:#FFFFFF;\n"
"    font-size:12px;\n"
"    border:none;\n"
"    border-radius:4px;\n"
"}\n"
"\n"
"/* -------------------- \346\231\272\350\203\275\350\257\255\351\237\263\345\214\272 \345\234\206\345\275\242\345\256\271\345\231\250 \346\240\267\345\274\217\343\200\220\345\216\237150x150\345\244\247\345\260\217\344\270\215\345\217\230\343\200\221 -------------------- */\n"
"QLabel#label_4 {\n"
"    border: 2px solid #CBD5E1;\n"
"    border-radius:75px;/* \345\256\214\347\276\216\345\234\206\345\275\242\357\274\214\345\214\271\351\205\215\344\275\240\347\232\204150x150\345\260\272\345\257\270 */\n"
"    background-color: #F8FAFC;\n"
"    border-style: solid;\n"
"    /* \344\275\240\345\220\216\346\234\237\345\234\250\350\277\231\351\207\214\345\212\240 border-image: url(\344\275\240\347\232\204\345\233\276\347\211\207\350\267\257\345\276\204); \345\215\263\345\217\257 */\n"
"}\n"
"\n"
"/* ===================== \345\272\225\351\203\250\345\212\237\350\203\275\345\214\272 - frame_bottom \345\217\212\345\206"
                        "\205\351\203\250\346\211\200\346\234\211\346\214\211\351\222\256 \343\200\220\344\270\245\346\240\274\345\216\237\345\270\203\345\261\200/\345\216\237\345\244\247\345\260\217/\345\216\237\351\227\264\350\267\235 \345\256\214\345\205\250\344\270\215\345\217\230\343\200\221 ===================== */\n"
"/* \345\272\225\351\203\250\346\200\273\346\241\206\346\236\266\346\240\267\345\274\217\357\274\232\347\272\257\347\231\275\345\272\225\350\211\262+\347\273\206\347\201\260\350\276\271\346\241\206\357\274\214\345\217\202\350\200\203\345\233\276\345\272\225\351\203\250\346\240\267\345\274\217 */\n"
"QFrame#frame_bottom {\n"
"    background-color: #FFFFFF;\n"
"    border:1px solid #E4E7ED;\n"
"    border-radius:4px;\n"
"}\n"
"/* -------------------- \345\272\225\351\203\250\346\211\200\346\234\211\346\214\211\351\222\256 \347\273\237\344\270\200\345\237\272\347\241\200\346\240\267\345\274\217 + \344\270\252\346\200\247\351\205\215\350\211\262\343\200\220\345\205\250\351\203\250\345\216\237\345\244\247\345\260\217/\344"
                        "\275\215\347\275\256\344\270\215\345\217\230\357\274\214\346\227\240\344\273\273\344\275\225\344\275\215\347\247\273\343\200\221 -------------------- */\n"
"/* \345\272\225\351\203\250\351\200\232\347\224\250\346\214\211\351\222\256\346\240\267\345\274\217\357\274\232\347\273\237\344\270\200\345\237\272\347\241\200\346\240\267\345\274\217\357\274\214hover\345\222\214pressed\346\227\240\344\275\215\347\247\273\357\274\214\345\217\252\346\224\271\351\242\234\350\211\262 */\n"
"QPushButton#btn_led,QPushButton#btn_led_switch,QPushButton#btn_talk,QPushButton#btn_wind_small,\n"
"QPushButton#btn_fan,QPushButton#btn_wind_big,QPushButton#btn_buzzer,QPushButton#btn_buzzer_switch,QPushButton#btn_help {\n"
"    font-size: 12px;\n"
"    font-weight: normal;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"}\n"
"/* LED\347\233\270\345\205\263\346\214\211\351\222\256-\346\265\205\350\223\235 */\n"
"QPushButton#btn_led {background-color: #94A3B8;color:#FFFFFF;}\n"
"QPushButton#btn_led:hover {background-color: #64748B;}\n"
""
                        "QPushButton#btn_led_switch {background-color: #38BDF8;color:#FFFFFF;}\n"
"QPushButton#btn_led_switch:hover {background-color: #0EA5E9;}\n"
"/* \350\257\255\351\237\263\346\214\211\351\222\256-\347\264\253\350\211\262 */\n"
"QPushButton#btn_talk:hover {background-color: #7E22CE;}\n"
"/* \351\243\216\346\211\207\347\233\270\345\205\263\346\214\211\351\222\256-\346\265\205\347\273\277 */\n"
"QPushButton#btn_wind_small,QPushButton#btn_wind_big {background-color: #A3E635;color:#1E293B;font-size:11px;}\n"
"QPushButton#btn_fan {background-color: #4ADE80;color:#FFFFFF;}\n"
"QPushButton#btn_fan:hover {background-color: #22C55E;}\n"
"/* \350\234\202\351\270\243\345\231\250\347\233\270\345\205\263\346\214\211\351\222\256-\346\251\231\350\211\262 */\n"
"QPushButton#btn_buzzer {background-color: #F97316;color:#FFFFFF;}\n"
"QPushButton#btn_buzzer:hover {background-color: #EA580C;}\n"
"QPushButton#btn_buzzer_switch {background-color: #FB923C;color:#FFFFFF;}\n"
"QPushButton#btn_buzzer_switch:hover {background-color: #F97316;}"
                        "\n"
"/* \345\270\256\345\212\251\346\214\211\351\222\256-\347\201\260\350\211\262 */\n"
"QPushButton#btn_help:hover {background-color: #475569;}\n"
"\n"
"/* ===================== \345\205\250\345\261\200\351\200\232\347\224\250\350\241\245\345\205\205 \351\230\262\346\240\267\345\274\217\346\272\242\345\207\272\343\200\220\346\227\240\344\273\273\344\275\225\345\270\203\345\261\200\344\277\256\346\224\271\343\200\221 ===================== */\n"
"/* \346\270\205\351\231\244\346\211\200\346\234\211QFrame\347\232\204\351\273\230\350\256\244\345\244\232\344\275\231\350\276\271\346\241\206\357\274\214\351\230\262\346\255\242\351\201\256\346\214\241 */\n"
"QFrame {border-style: none;}\n"
"/* \346\211\200\346\234\211\346\214\211\351\222\256\346\214\211\344\270\213\346\227\240\345\201\217\347\247\273\357\274\214\345\256\214\347\276\216\350\264\264\345\220\210\345\216\237\345\270\203\345\261\200 */\n"
"QPushButton {\n"
"    padding:0px;\n"
"    margin:0px;\n"
"}\n"
"\n"
"/* \346\273\221\345\235\227 - \347\273\206\346\235"
                        "\241\347\212\266 */\n"
"QSlider#horizontalSlider::handle {\n"
"    width: 2px;\n"
"    height: 12px;\n"
"    background-color: #FFFFFF;\n"
"    border: 1px solid #1E40AF;/* \346\267\261\350\223\235\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 0px;\n"
"    margin-top: -4px;\n"
"    margin-bottom: -4px;\n"
"}\n"
"\n"
"/* \345\267\262\345\241\253\345\205\205\347\232\204\350\277\233\345\272\246\351\203\250\345\210\206 */\n"
"QSlider#horizontalSlider::sub-page:horizontal {\n"
"    background-color: #2563EB;\n"
"    height: 4px;\n"
"    border-radius: 2px;\n"
"}\n"
"\n"
"/* \346\234\252\345\241\253\345\205\205\347\232\204\350\277\233\345\272\246\351\203\250\345\210\206 */\n"
"QSlider#horizontalSlider::add-page:horizontal {\n"
"    background-color: #CBD5E1;\n"
"    height: 4px;\n"
"    border-radius: 2px;\n"
"}\n"
"\n"
"/* \346\225\264\344\275\223\346\273\221\345\235\227\346\216\247\344\273\266 */\n"
"QSlider#horizontalSlider {\n"
"    /* \344\277\235\347\225\231\345\237\272\346\234\254\350\256\276\347"
                        "\275\256\357\274\214\344\275\206\350\203\214\346\231\257\350\256\276\344\270\272\351\200\217\346\230\216 */\n"
"    background-color: transparent;\n"
"    height: 4px;\n"
"    border-radius: 2px;\n"
"}\n"
"\n"
"\n"
""));
        verticalLayout_5 = new QVBoxLayout(Widget);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, -1, 0, -1);
        frame_header = new QFrame(Widget);
        frame_header->setObjectName(QStringLiteral("frame_header"));
        frame_header->setMinimumSize(QSize(800, 48));
        frame_header->setMaximumSize(QSize(800, 48));
        frame_header->setFrameShape(QFrame::Box);
        frame_header->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_header);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_title = new QLabel(frame_header);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setMinimumSize(QSize(250, 48));
        label_title->setMaximumSize(QSize(250, 48));
        label_title->setFrameShape(QFrame::Box);
        label_title->setFrameShadow(QFrame::Plain);
        label_title->setLineWidth(0);

        horizontalLayout->addWidget(label_title);

        label_weather = new QLabel(frame_header);
        label_weather->setObjectName(QStringLiteral("label_weather"));
        label_weather->setMinimumSize(QSize(60, 40));
        label_weather->setMaximumSize(QSize(60, 40));
        label_weather->setStyleSheet(QStringLiteral("border-image: url(:/image/sunny.png);"));
        label_weather->setFrameShape(QFrame::Panel);
        label_weather->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_weather);

        label_temperature = new QLabel(frame_header);
        label_temperature->setObjectName(QStringLiteral("label_temperature"));
        label_temperature->setMinimumSize(QSize(60, 40));
        label_temperature->setMaximumSize(QSize(60, 40));
        label_temperature->setStyleSheet(QStringLiteral(""));
        label_temperature->setFrameShape(QFrame::Panel);

        horizontalLayout->addWidget(label_temperature);

        horizontalSpacer_4 = new QSpacerItem(128, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label_time = new QLabel(frame_header);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setMinimumSize(QSize(200, 48));
        label_time->setMaximumSize(QSize(200, 48));
        label_time->setLayoutDirection(Qt::LeftToRight);
        label_time->setFrameShape(QFrame::Box);

        horizontalLayout->addWidget(label_time);


        verticalLayout_5->addWidget(frame_header);

        frame_mid_part = new QFrame(Widget);
        frame_mid_part->setObjectName(QStringLiteral("frame_mid_part"));
        frame_mid_part->setMinimumSize(QSize(800, 320));
        frame_mid_part->setMaximumSize(QSize(800, 320));
        frame_mid_part->setFrameShape(QFrame::Box);
        frame_mid_part->setFrameShadow(QFrame::Raised);
        horizontalLayout_8 = new QHBoxLayout(frame_mid_part);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        frame_game = new QFrame(frame_mid_part);
        frame_game->setObjectName(QStringLiteral("frame_game"));
        frame_game->setMinimumSize(QSize(170, 310));
        frame_game->setMaximumSize(QSize(160, 310));
        frame_game->setLayoutDirection(Qt::LeftToRight);
        frame_game->setFrameShape(QFrame::StyledPanel);
        frame_game->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_game);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(frame_game);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(140, 30));
        label->setMaximumSize(QSize(120, 30));
        label->setFrameShape(QFrame::Box);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label);

        btn_snake = new QPushButton(frame_game);
        btn_snake->setObjectName(QStringLiteral("btn_snake"));
        btn_snake->setMinimumSize(QSize(140, 70));
        btn_snake->setMaximumSize(QSize(120, 70));
        btn_snake->setStyleSheet(QStringLiteral("border-image: url(:/image/snake.jpg);"));

        verticalLayout->addWidget(btn_snake);

        btn_plane = new QPushButton(frame_game);
        btn_plane->setObjectName(QStringLiteral("btn_plane"));
        btn_plane->setMinimumSize(QSize(140, 70));
        btn_plane->setMaximumSize(QSize(120, 70));
        btn_plane->setStyleSheet(QStringLiteral("border-image: url(:/image/plane.jpg);"));

        verticalLayout->addWidget(btn_plane);

        btn_more_game = new QPushButton(frame_game);
        btn_more_game->setObjectName(QStringLiteral("btn_more_game"));
        btn_more_game->setMinimumSize(QSize(140, 70));
        btn_more_game->setMaximumSize(QSize(120, 70));
        btn_more_game->setStyleSheet(QStringLiteral("border-image: url(:/image/game.png);"));

        verticalLayout->addWidget(btn_more_game);


        horizontalLayout_8->addWidget(frame_game);

        frame_music = new QFrame(frame_mid_part);
        frame_music->setObjectName(QStringLiteral("frame_music"));
        frame_music->setMinimumSize(QSize(170, 310));
        frame_music->setMaximumSize(QSize(160, 310));
        frame_music->setFrameShape(QFrame::StyledPanel);
        frame_music->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_music);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_2 = new QLabel(frame_music);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(140, 30));
        label_2->setMaximumSize(QSize(120, 30));
        label_2->setFrameShape(QFrame::Box);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(label_2);

        label_3 = new QLabel(frame_music);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(150, 150));
        label_3->setMaximumSize(QSize(150, 150));
        label_3->setStyleSheet(QStringLiteral("border-image: url(:/image/music.jpg);"));
        label_3->setFrameShape(QFrame::Box);

        verticalLayout_6->addWidget(label_3);

        horizontalSlider = new QSlider(frame_music);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimumSize(QSize(140, 20));
        horizontalSlider->setMaximumSize(QSize(140, 20));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_6->addWidget(horizontalSlider);

        widget_music_btn = new QWidget(frame_music);
        widget_music_btn->setObjectName(QStringLiteral("widget_music_btn"));
        widget_music_btn->setMinimumSize(QSize(140, 40));
        widget_music_btn->setMaximumSize(QSize(140, 40));
        horizontalLayout_2 = new QHBoxLayout(widget_music_btn);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, 0, -1, 0);
        btn_music_pre = new QPushButton(widget_music_btn);
        btn_music_pre->setObjectName(QStringLiteral("btn_music_pre"));
        btn_music_pre->setMinimumSize(QSize(30, 30));
        btn_music_pre->setMaximumSize(QSize(30, 30));
        btn_music_pre->setStyleSheet(QStringLiteral("border-image: url(:/image/music_pre.png);"));

        horizontalLayout_2->addWidget(btn_music_pre);

        btn_music_play = new QPushButton(widget_music_btn);
        btn_music_play->setObjectName(QStringLiteral("btn_music_play"));
        btn_music_play->setMinimumSize(QSize(40, 40));
        btn_music_play->setMaximumSize(QSize(40, 40));
        btn_music_play->setStyleSheet(QStringLiteral("border-image: url(:/image/music_pause.png);"));

        horizontalLayout_2->addWidget(btn_music_play);

        btn_music_next = new QPushButton(widget_music_btn);
        btn_music_next->setObjectName(QStringLiteral("btn_music_next"));
        btn_music_next->setMinimumSize(QSize(30, 30));
        btn_music_next->setMaximumSize(QSize(30, 30));
        btn_music_next->setStyleSheet(QStringLiteral("border-image: url(:/image/music_next.png);"));

        horizontalLayout_2->addWidget(btn_music_next);


        verticalLayout_6->addWidget(widget_music_btn);


        horizontalLayout_8->addWidget(frame_music);

        frame_fun = new QFrame(frame_mid_part);
        frame_fun->setObjectName(QStringLiteral("frame_fun"));
        frame_fun->setMinimumSize(QSize(170, 310));
        frame_fun->setMaximumSize(QSize(160, 310));
        frame_fun->setLayoutDirection(Qt::LeftToRight);
        frame_fun->setFrameShape(QFrame::StyledPanel);
        frame_fun->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_fun);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        frame = new QFrame(frame_fun);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setLayoutDirection(Qt::LeftToRight);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setMidLineWidth(0);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(140, 30));
        label_5->setMaximumSize(QSize(120, 30));
        label_5->setFrameShape(QFrame::Box);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(70, 30));
        lineEdit->setMaximumSize(QSize(70, 30));

        horizontalLayout_3->addWidget(lineEdit);

        btn_send = new QPushButton(frame);
        btn_send->setObjectName(QStringLiteral("btn_send"));
        btn_send->setMinimumSize(QSize(50, 30));
        btn_send->setMaximumSize(QSize(50, 30));

        horizontalLayout_3->addWidget(btn_send);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btn_beijing = new QPushButton(frame);
        btn_beijing->setObjectName(QStringLiteral("btn_beijing"));
        btn_beijing->setMinimumSize(QSize(60, 30));
        btn_beijing->setMaximumSize(QSize(60, 30));

        horizontalLayout_4->addWidget(btn_beijing);

        btn_guangzhou = new QPushButton(frame);
        btn_guangzhou->setObjectName(QStringLiteral("btn_guangzhou"));
        btn_guangzhou->setMinimumSize(QSize(60, 30));
        btn_guangzhou->setMaximumSize(QSize(60, 30));

        horizontalLayout_4->addWidget(btn_guangzhou);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(frame);

        frame_2 = new QFrame(frame_fun);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setMinimumSize(QSize(150, 160));
        frame_2->setMaximumSize(QSize(150, 160));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(70, 30));
        label_6->setMaximumSize(QSize(70, 30));
        label_6->setFrameShape(QFrame::Box);
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_4->addWidget(label_6);

        btn_camera = new QPushButton(frame_2);
        btn_camera->setObjectName(QStringLiteral("btn_camera"));
        btn_camera->setMinimumSize(QSize(130, 100));
        btn_camera->setMaximumSize(QSize(130, 100));
        btn_camera->setStyleSheet(QStringLiteral("border-image: url(:/image/camera.png);"));

        verticalLayout_4->addWidget(btn_camera);


        verticalLayout_3->addWidget(frame_2);


        horizontalLayout_8->addWidget(frame_fun);

        frame_talk = new QFrame(frame_mid_part);
        frame_talk->setObjectName(QStringLiteral("frame_talk"));
        frame_talk->setMinimumSize(QSize(170, 310));
        frame_talk->setMaximumSize(QSize(160, 310));
        frame_talk->setFrameShape(QFrame::StyledPanel);
        frame_talk->setFrameShadow(QFrame::Raised);
        label_7 = new QLabel(frame_talk);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 20, 140, 30));
        label_7->setMinimumSize(QSize(140, 30));
        label_7->setMaximumSize(QSize(120, 30));
        label_7->setFrameShape(QFrame::Box);
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        btn_talk1 = new QPushButton(frame_talk);
        btn_talk1->setObjectName(QStringLiteral("btn_talk1"));
        btn_talk1->setGeometry(QRect(10, 90, 150, 150));
        btn_talk1->setMinimumSize(QSize(150, 150));
        btn_talk1->setMaximumSize(QSize(150, 150));
        btn_talk1->setStyleSheet(QString::fromUtf8("    border: 1px solid #E4E7ED;\n"
"    border-radius: 75px;/* \345\256\214\347\276\216\345\234\206\345\275\242\357\274\214\345\214\271\351\205\215\344\275\240\347\232\204140x160\345\260\272\345\257\270 */\n"
"    background-color: #F8FAFC;\n"
"    border-style: solid;\n"
"	border-image: url(:/image/Intelligent_voice.png);"));

        horizontalLayout_8->addWidget(frame_talk);


        verticalLayout_5->addWidget(frame_mid_part);

        frame_bottom = new QFrame(Widget);
        frame_bottom->setObjectName(QStringLiteral("frame_bottom"));
        frame_bottom->setMinimumSize(QSize(800, 74));
        frame_bottom->setMaximumSize(QSize(800, 74));
        frame_bottom->setFrameShape(QFrame::Box);
        frame_bottom->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame_bottom);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_led = new QLabel(frame_bottom);
        label_led->setObjectName(QStringLiteral("label_led"));
        label_led->setMinimumSize(QSize(70, 50));
        label_led->setMaximumSize(QSize(70, 50));
        label_led->setStyleSheet(QStringLiteral("border-image: url(:/image/led_off.png);"));

        horizontalLayout_7->addWidget(label_led);

        btn_led_switch = new QPushButton(frame_bottom);
        btn_led_switch->setObjectName(QStringLiteral("btn_led_switch"));
        btn_led_switch->setMinimumSize(QSize(70, 50));
        btn_led_switch->setMaximumSize(QSize(70, 50));

        horizontalLayout_7->addWidget(btn_led_switch);

        btn_talk = new QPushButton(frame_bottom);
        btn_talk->setObjectName(QStringLiteral("btn_talk"));
        btn_talk->setMinimumSize(QSize(70, 50));
        btn_talk->setMaximumSize(QSize(70, 50));
        btn_talk->setStyleSheet(QStringLiteral("border-image: url(:/image/talk.png);"));

        horizontalLayout_7->addWidget(btn_talk);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        btn_wind_small = new QPushButton(frame_bottom);
        btn_wind_small->setObjectName(QStringLiteral("btn_wind_small"));
        btn_wind_small->setMinimumSize(QSize(50, 30));
        btn_wind_small->setMaximumSize(QSize(50, 30));

        horizontalLayout_6->addWidget(btn_wind_small);

        btn_fan = new QPushButton(frame_bottom);
        btn_fan->setObjectName(QStringLiteral("btn_fan"));
        btn_fan->setMinimumSize(QSize(70, 50));
        btn_fan->setMaximumSize(QSize(70, 50));

        horizontalLayout_6->addWidget(btn_fan);

        btn_wind_big = new QPushButton(frame_bottom);
        btn_wind_big->setObjectName(QStringLiteral("btn_wind_big"));
        btn_wind_big->setMinimumSize(QSize(50, 30));
        btn_wind_big->setMaximumSize(QSize(50, 30));

        horizontalLayout_6->addWidget(btn_wind_big);


        horizontalLayout_7->addLayout(horizontalLayout_6);

        label_buzzer = new QLabel(frame_bottom);
        label_buzzer->setObjectName(QStringLiteral("label_buzzer"));
        label_buzzer->setMinimumSize(QSize(70, 50));
        label_buzzer->setMaximumSize(QSize(70, 50));
        label_buzzer->setStyleSheet(QStringLiteral("border-image: url(:/image/buzzer_off.png);"));

        horizontalLayout_7->addWidget(label_buzzer);

        btn_buzzer_switch = new QPushButton(frame_bottom);
        btn_buzzer_switch->setObjectName(QStringLiteral("btn_buzzer_switch"));
        btn_buzzer_switch->setMinimumSize(QSize(70, 50));
        btn_buzzer_switch->setMaximumSize(QSize(70, 50));

        horizontalLayout_7->addWidget(btn_buzzer_switch);

        btn_help = new QPushButton(frame_bottom);
        btn_help->setObjectName(QStringLiteral("btn_help"));
        btn_help->setMinimumSize(QSize(70, 50));
        btn_help->setMaximumSize(QSize(70, 50));
        btn_help->setStyleSheet(QStringLiteral("border-image: url(:/image/help.png);"));

        horizontalLayout_7->addWidget(btn_help);


        verticalLayout_5->addWidget(frame_bottom);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        label_title->setText(QApplication::translate("Widget", "\345\220\216\345\250\261\345\272\247\350\210\261\346\231\272\350\203\275\347\273\210\347\253\257", 0));
        label_weather->setText(QString());
        label_temperature->setText(QApplication::translate("Widget", "\346\270\251\345\272\246:18\342\204\203", 0));
        label_time->setText(QApplication::translate("Widget", "time", 0));
        label->setText(QApplication::translate("Widget", "\346\270\270\346\210\217\345\214\272", 0));
        btn_snake->setText(QString());
        btn_plane->setText(QString());
        btn_more_game->setText(QString());
        label_2->setText(QApplication::translate("Widget", "\351\237\263\344\271\220\346\222\255\346\224\276\345\214\272", 0));
        label_3->setText(QString());
        btn_music_pre->setText(QString());
        btn_music_play->setText(QString());
        btn_music_next->setText(QString());
        label_5->setText(QApplication::translate("Widget", "\350\216\267\345\217\226\345\237\216\345\270\202\345\244\251\346\260\224", 0));
        btn_send->setText(QApplication::translate("Widget", "\345\217\221\351\200\201\345\237\216\345\270\202", 0));
        btn_beijing->setText(QApplication::translate("Widget", "\345\214\227\344\272\254", 0));
        btn_guangzhou->setText(QApplication::translate("Widget", "\345\271\277\345\267\236", 0));
        label_6->setText(QApplication::translate("Widget", "\347\233\270\346\234\272", 0));
        btn_camera->setText(QString());
        label_7->setText(QApplication::translate("Widget", "\346\231\272\350\203\275\350\257\255\351\237\263\345\212\251\346\211\213", 0));
        btn_talk1->setText(QString());
        label_led->setText(QString());
        btn_led_switch->setText(QApplication::translate("Widget", "\347\201\257\345\274\200\345\205\263", 0));
        btn_talk->setText(QString());
        btn_wind_small->setText(QApplication::translate("Widget", "\345\260\217\351\243\216", 0));
        btn_fan->setText(QApplication::translate("Widget", "\351\243\216\346\211\207", 0));
        btn_wind_big->setText(QApplication::translate("Widget", "\345\244\247\351\243\216", 0));
        label_buzzer->setText(QString());
        btn_buzzer_switch->setText(QApplication::translate("Widget", "\350\234\202\351\270\243\345\231\250\345\274\200\345\205\263", 0));
        btn_help->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
