#-------------------------------------------------
#
# Project created by QtCreator 2012-12-01T21:27:39
#
#-------------------------------------------------

QT       += core gui widgets
QT       += webkit webkitwidgets

TARGET = cubway
TEMPLATE = app

DEFINES += "CUBWAY_DEBUG=1"

SOURCES += main.cpp\
        metro.cpp \
        moduleloader.cpp\
        MFile.cpp

HEADERS  += metro.h \
        moduleloader.h\
        MFile.h
