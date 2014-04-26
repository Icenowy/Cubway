TEMPLATE = lib
TARGET = Notification
DEPENDPATH += .
INCLUDEPATH += .

HEADERS += Notification.h
SOURCES += Notification.cpp

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libnotify
