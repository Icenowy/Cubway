TARGET = X11Toolkit
TEMPLATE = lib

QT += core x11extras gui widgets

SOURCES += x11plugin.cpp xfitman.cpp
HEADERS  += x11plugin.h xfitman.h

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += x11

