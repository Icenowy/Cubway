#include <QObject>
#include <QString>
#include <QVariantList>
#include "xfitman.h"

class X11 : public QObject
{
    Q_OBJECT
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
