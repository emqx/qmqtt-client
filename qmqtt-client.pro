#-------------------------------------------------
#
# Project created by QtCreator 2013-03-22T21:02:13
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qmqtt-client
TEMPLATE = app

DEPENDPATH += . /Users/erylee/WorkSpace/qmqtt
INCLUDEPATH +=  /Users/erylee/WorkSpace/qmqtt

LIBS+=  -L/Users/erylee/WorkSpace/qmqtt-build-debug -lqmqtt

SOURCES += main.cpp
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
