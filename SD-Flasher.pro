#-------------------------------------------------
#
# Project created by QtCreator 2013-06-20T17:38:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SD-Flasher
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    scan.cpp \
    fuse.cpp \
    init.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

