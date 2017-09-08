/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *button_login;
    QSpacerItem *horizontalSpacer_3;
    QWidget *page2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QFrame *frame_mainMenu;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_username;
    QSpacerItem *verticalSpacer;
    QPushButton *button_deck;
    QPushButton *button_1p;
    QPushButton *button_2p;
    QPushButton *button_settings;
    QSpacerItem *verticalSpacer_4;
    QWidget *page3;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_board1;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1141, 727);
        MainWindow->setMinimumSize(QSize(1141, 727));
        MainWindow->setLayoutDirection(Qt::RightToLeft);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QLatin1String("#page {\n"
"border-image: url(:/images/images/wallpaper.jpg) 0 0 0 0 strectch stretch;\n"
"}\n"
"\n"
"#page2 {\n"
"border-image: url(:/images/images/ciri.jpg) 0 0 0 0 strectch stretch;\n"
"}\n"
"\n"
"#frame_mainMenu {\n"
"background-color:rgba(48, 132, 119, 100);\n"
"}\n"
"\n"
"#frame_board1, #frame_board2 {\n"
"border-image: url(:/images/images/board.jpg) 0 0 0 0 strectch stretch;\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        sizePolicy.setHeightForWidth(page->sizePolicy().hasHeightForWidth());
        page->setSizePolicy(sizePolicy);
        page->setStyleSheet(QLatin1String("QPushButton {\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border: 0px;\n"
"font: 75 20pt \"Cambria\";\n"
"color: rgb(220, 220, 220);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"color: white;\n"
"}"));
        horizontalLayout_4 = new QHBoxLayout(page);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 380, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        button_login = new QPushButton(page);
        button_login->setObjectName(QStringLiteral("button_login"));

        horizontalLayout_6->addWidget(button_login);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        horizontalLayout_4->addLayout(horizontalLayout_6);

        stackedWidget->addWidget(page);
        page2 = new QWidget();
        page2->setObjectName(QStringLiteral("page2"));
        sizePolicy.setHeightForWidth(page2->sizePolicy().hasHeightForWidth());
        page2->setSizePolicy(sizePolicy);
        page2->setAutoFillBackground(false);
        page2->setStyleSheet(QLatin1String("QPushButton {\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border: 0px;\n"
"font: 75 20pt \"Cambria\";\n"
"color: rgb(220, 220, 220);\n"
"text-align: left;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"color: white;\n"
"}"));
        horizontalLayout = new QHBoxLayout(page2);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(60, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        frame_mainMenu = new QFrame(page2);
        frame_mainMenu->setObjectName(QStringLiteral("frame_mainMenu"));
        sizePolicy.setHeightForWidth(frame_mainMenu->sizePolicy().hasHeightForWidth());
        frame_mainMenu->setSizePolicy(sizePolicy);
        frame_mainMenu->setMinimumSize(QSize(230, 0));
        frame_mainMenu->setMaximumSize(QSize(250, 16777215));
        frame_mainMenu->setFrameShape(QFrame::StyledPanel);
        frame_mainMenu->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_mainMenu);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, 11, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, -1);
        label_username = new QLabel(frame_mainMenu);
        label_username->setObjectName(QStringLiteral("label_username"));
        label_username->setStyleSheet(QLatin1String("font: 12pt \"Cambria\";\n"
"color: rgb(220, 220, 220);\n"
""));

        verticalLayout->addWidget(label_username);

        verticalSpacer = new QSpacerItem(20, 140, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer);

        button_deck = new QPushButton(frame_mainMenu);
        button_deck->setObjectName(QStringLiteral("button_deck"));

        verticalLayout->addWidget(button_deck);

        button_1p = new QPushButton(frame_mainMenu);
        button_1p->setObjectName(QStringLiteral("button_1p"));

        verticalLayout->addWidget(button_1p);

        button_2p = new QPushButton(frame_mainMenu);
        button_2p->setObjectName(QStringLiteral("button_2p"));

        verticalLayout->addWidget(button_2p);

        button_settings = new QPushButton(frame_mainMenu);
        button_settings->setObjectName(QStringLiteral("button_settings"));

        verticalLayout->addWidget(button_settings);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout_2->addLayout(verticalLayout);


        horizontalLayout->addWidget(frame_mainMenu);

        stackedWidget->addWidget(page2);
        page3 = new QWidget();
        page3->setObjectName(QStringLiteral("page3"));
        horizontalLayout_5 = new QHBoxLayout(page3);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(7);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        frame_board1 = new QFrame(page3);
        frame_board1->setObjectName(QStringLiteral("frame_board1"));
        frame_board1->setFrameShape(QFrame::StyledPanel);
        frame_board1->setFrameShadow(QFrame::Raised);

        horizontalLayout_3->addWidget(frame_board1);


        horizontalLayout_5->addLayout(horizontalLayout_3);

        stackedWidget->addWidget(page3);

        verticalLayout_2->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        button_login->setText(QApplication::translate("MainWindow", "Login", Q_NULLPTR));
        label_username->setText(QApplication::translate("MainWindow", "hi, username", Q_NULLPTR));
        button_deck->setText(QApplication::translate("MainWindow", "Deck", Q_NULLPTR));
        button_1p->setText(QApplication::translate("MainWindow", "1P PLAY", Q_NULLPTR));
        button_2p->setText(QApplication::translate("MainWindow", "2P PLAY", Q_NULLPTR));
        button_settings->setText(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
