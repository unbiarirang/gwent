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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page2;
    QFrame *frame_mainMenu;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(894, 562);
        MainWindow->setLayoutDirection(Qt::RightToLeft);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setStyleSheet(QStringLiteral("border-image: url(:/images/images/wallpaper.jpg) 0 0 0 0 strectch stretch;"));
        stackedWidget->addWidget(page);
        page2 = new QWidget();
        page2->setObjectName(QStringLiteral("page2"));
        page2->setAutoFillBackground(false);
        page2->setStyleSheet(QLatin1String("#page2 {\n"
"border-image: url(:/images/images/ciri.jpg) 0 0 0 0 strectch stretch;\n"
"}\n"
"\n"
"#frame_mainMenu {\n"
"background-color:rgba(48, 132, 119, 100);\n"
"}\n"
"\n"
"QLabel {\n"
"font: 75 16pt \"Cambria\";\n"
"color: white;\n"
"}"));
        frame_mainMenu = new QFrame(page2);
        frame_mainMenu->setObjectName(QStringLiteral("frame_mainMenu"));
        frame_mainMenu->setGeometry(QRect(50, -2, 179, 571));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_mainMenu->sizePolicy().hasHeightForWidth());
        frame_mainMenu->setSizePolicy(sizePolicy);
        frame_mainMenu->setFrameShape(QFrame::StyledPanel);
        frame_mainMenu->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_mainMenu);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, -1);
        verticalSpacer = new QSpacerItem(20, 120, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(frame_mainMenu);
        label->setObjectName(QStringLiteral("label"));
        label->setCursor(QCursor(Qt::PointingHandCursor));
        label->setFrameShadow(QFrame::Plain);

        verticalLayout->addWidget(label);

        label_3 = new QLabel(frame_mainMenu);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(label_3);

        label_2 = new QLabel(frame_mainMenu);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(label_2);

        label_4 = new QLabel(frame_mainMenu);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(label_4);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout_3->addLayout(verticalLayout);

        stackedWidget->addWidget(page2);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Deck", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "2P PLAY", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "1P PLAY", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
