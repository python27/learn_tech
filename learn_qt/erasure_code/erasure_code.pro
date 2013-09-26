#-------------------------------------------------
#
# Project created by QtCreator 2013-07-07T11:53:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = erasure_code
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    package.cpp \
    mathFunction.cpp \
    LT_TEXT.cpp \
    LT_BMP.cpp \
    GF2_LDPC_BMP.cpp \
    GF2_LDPC.cpp \
    bmp.cpp \
    Cascade_BMP.cpp \
    Cascade_TEXT.cpp \
    GF2_LDPC_TEXT.cpp

HEADERS  += dialog.h \
    package.h \
    mathFunction.h \
    LT_TEXT.h \
    LT_BMP.h \
    GF2_LDPC_BMP.h \
    GF2_LDPC.h \
    bmp.h \
    Cascade_BMP.h \
    Cascade_TEXT.h \
    GF2_LDPC_TEXT.h

FORMS    += dialog.ui
