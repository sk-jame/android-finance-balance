#-------------------------------------------------
#
# Project created by QtCreator 2018-04-05T14:04:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Balance
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += DB_FORMAT_VERSION=1

# DEFINES += NOT_DEFAULT_STYLE_ALLOWED

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    ui/mainwindow.cpp \
    ui/base/widgetforstack.cpp \
    ui/tables/qtablesortwidget.cpp \
    ui/tables/databasetablewidget.cpp \
    ui/base/amountwidget.cpp \
    data/task.cpp \
    data/databaseworker.cpp \
    data/datacontainer.cpp \
    common/logger.cpp \
    ui/base/reasonwidget.cpp \
    ui/base/filterwidget.cpp \
    ui/incomestackwidget.cpp \
    ui/stackwidget.cpp

HEADERS += \
    ui/mainwindow.h \
    ui/base/widgetforstack.h \
    ui/tables/qtablesortwidget.h \
    ui/tables/databasetablewidget.h \
    ui/base/amountwidget.h \
    data/task.h \
    data/databaseworker.h \
    data/datacontainer.h \
    common/operations.h \
    common/logger.h \
    ui/base/reasonwidget.h \
    ui/base/filterwidget.h \
    ui/incomestackwidget.h \
    ui/stackwidget.h

FORMS += \
    ui/mainwindow.ui \
    ui/base/amountwidget.ui \
    ui/base/reasonwidget.ui \
    ui/base/filterwidget.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resources.qrc

INCLUDEPATH += \
    ui/base
