#-------------------------------------------------
#
# Project created by QtCreator 2020-09-12T23:42:33
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BrightMail
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
    conmmunicate/Communi_Core.cpp \
    login/logindlg.cpp \
        main.cpp \
    part1_receivemail/recemail.cpp \
    part3_deliver/deliver.cpp \
    part4_deleted/deleted.cpp \
    part5_draftBox/draftbox.cpp \
    part6_friends/friends.cpp \
    part6_friends/finddialog.cpp \
    dialog.cpp \
    extra1_tcp/clientwidget.cpp \
    extra1_tcp/serverwidget.cpp \
    extra1_tcp/form.cpp \

    login/logindlg.cpp

HEADERS += \
    conmmunicate/Communi_Core.hpp \
    login/logindlg.h \
    part1_receivemail/recemail.h \
    part3_deliver/deliver.h \
    part4_deleted/deleted.h \
    part5_draftBox/draftbox.h \
    part6_friends/friends.h \
    part6_friends/finddialog.h \
    dialog.h \
    extra1_tcp/clientwidget.h \
    extra1_tcp/serverwidget.h \
    extra1_tcp/form.h \

    login/logindlg.h

FORMS += \
    extra1_tcp/clientwidget.ui \
    extra1_tcp/serverwidget.ui \
    extra1_tcp/form.ui \
    login/logindlg.ui

RESOURCES += \
    brightmail.qrc

