/********************************************************************************
** Form generated from reading UI file 'gamehall.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEHALL_H
#define UI_GAMEHALL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameHall
{
public:

    void setupUi(QWidget *GameHall)
    {
        if (GameHall->objectName().isEmpty())
            GameHall->setObjectName(QStringLiteral("GameHall"));
        GameHall->resize(800, 480);
        GameHall->setMinimumSize(QSize(800, 480));
        GameHall->setMaximumSize(QSize(800, 480));

        retranslateUi(GameHall);

        QMetaObject::connectSlotsByName(GameHall);
    } // setupUi

    void retranslateUi(QWidget *GameHall)
    {
        GameHall->setWindowTitle(QApplication::translate("GameHall", "GameHall", 0));
    } // retranslateUi

};

namespace Ui {
    class GameHall: public Ui_GameHall {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEHALL_H
