#ifndef _CUBWAY_X11_X11PLUGIN_H
#define _CUBWAY_X11_X11PLUGIN_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include "xfitman.h"

class X11Toolkit : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.subway.Cubway.X11Plugin")
private:
    Window toWindow(QString _wid);
    QString fromWindow(Window _wid);
public slots:
    QString getActiveWindow();
    void moveWindowToDesktop(QString _wid, int _display);
    int getWindowDesktop(QString _wid);
    void minimizeWindow(QString _wid);
    QVariantList getClientList();
    QString getWindowTitle(QString _wid);
    void Test();
};

#endif
