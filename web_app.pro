#-------------------------------------------------
#
# Project created by QtCreator 2020-06-23T11:33:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += network

TARGET = web_app
TEMPLATE = app


SOURCES += \
    main.cpp\
    mainwindow.cpp \
    net_speed.cpp \
    common.cpp \
    tcpserver.cpp

#DEPENDPATH += net_speed.cpp\
#            common.cpp

HEADERS  += mainwindow.h \
    common.h \
    packet.h \
    net_speed.h \
    tcpserver.h

FORMS    += mainwindow.ui

LIBS += -lrt
