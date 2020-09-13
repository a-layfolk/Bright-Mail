#-------------------------------------------------
#
# Project created by QtCreator 2020-09-07T08:04:49
#
#-------------------------------------------------

#modules
QT       += core gui

#in order to compate QT4
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#app's name
TARGET = QT01
#decide makefile's type
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp

HEADERS  += mywidget.h
