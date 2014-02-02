#-------------------------------------------------
#
# Project created by QtCreator 2012-12-01T21:27:39
#
#-------------------------------------------------

QT       += core gui
QT       += webkit

TARGET = QtMetro
TEMPLATE = app


SOURCES += main.cpp\
        metro.cpp \
    xfitman.cpp

HEADERS  += metro.h \
    xfitman.h


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += x11
