#-------------------------------------------------
#
# Project created by QtCreator 2020-05-31T10:54:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ftpdemo
TEMPLATE = app

include($$PWD/qftp/qftp.pri)

SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

