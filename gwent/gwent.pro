#-------------------------------------------------
#
# Project created by QtCreator 2017-09-04T17:41:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gwent
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    logindialog.cpp \
    clabel.cpp \
    global.cpp \
    cardBase.cpp \
    card.cpp \
    game.cpp \
    skill.cpp \
    user.cpp \
    util.cpp \
    page.cpp

HEADERS += \
        mainwindow.h \
    logindialog.h \
    global.h \
    clabel.h \
    cardBase.h \
    card.h \
    enum.h \
    game.h \
    skill.h \
    user.h \
    util.h \
    page.h

FORMS += \
        mainwindow.ui \
    logindialog.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    json/json_vc71_libmtd.lib

QT += concurrent

QMAKE_LFLAGS += -static-libgcc

CONFIG += release
