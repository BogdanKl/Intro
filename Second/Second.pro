#-------------------------------------------------
#
# Project created by QtCreator 2013-03-15T14:19:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Second
TEMPLATE = app
SOURCES += main.cpp\
        mainwindow.cpp
HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
CONFIG += extserialport
include(qextserialport/src/qextserialport.pri)
