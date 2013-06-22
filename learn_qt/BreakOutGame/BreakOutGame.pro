#-------------------------------------------------
#
# Project created by QtCreator 2013-06-20T10:17:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BreakOutGame
TEMPLATE = app


SOURCES +=\
    paddle.cpp \
    ball.cpp \
    brick.cpp \
    breakout.cpp \
    main.cpp

HEADERS  += \
    paddle.h \
    ball.h \
    brick.h \
    breakout.h

RESOURCES += \
    resource.qrc
