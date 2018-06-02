#-------------------------------------------------
#
# Project created by QtCreator 2018-06-02T02:12:18
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = widgets
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += TEST

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    ../../src/ui/base/reasonwidget.cpp \
    ../../src/ui/base/widgetforstack.cpp

HEADERS += \
    ../../src/ui/base/reasonwidget.h \
    ../../src/ui/base/widgetforstack.h

INCLUDEPATH += \
        ../../src/ui/base/

FORMS += \
    ../../src/ui/base/reasonwidget.ui
