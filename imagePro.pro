#-------------------------------------------------
#
# Project created by QtCreator 2021-06-01T09:25:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = imagePro
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += \
D:\openCV\build\include\opencv \
D:\openCV\build\include\opencv2 \
D:\openCV\build\include

LIBS += D:\openCV\build\x64\vc14\lib\opencv_world3414d.lib
LIBS += D:\openCV\build\x64\vc14\lib\opencv_world3414.lib


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    MenuBar.cpp \
    imagewidget.cpp \
    geom.cpp \
    imagechange.cpp

HEADERS += \
        mainwindow.h \
    MenuBar.h \
    imagewidget.h \
    geom.h \
    imagechange.h

FORMS += \
        mainwindow.ui
