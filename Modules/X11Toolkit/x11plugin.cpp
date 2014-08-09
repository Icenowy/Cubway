#include <QtPlugin>
#include <QList>
#include <QProcess>
#include <QVariantList>
#include "xfitman.h"
#include "x11plugin.h"
//X11

QString X11Toolkit::getActiveWindow()
{
  return this->fromWindow(xfitMan().getActiveWindow());
}

void X11Toolkit::moveWindowToDesktop(QString _wid, int _display)
{
  xfitMan().moveWindowToDesktop(toWindow(_wid),_display);
}

void X11Toolkit::Test()
{
  QProcess *qp = new QProcess;
  qp->start("notify-send",QStringList() << "Testing X11");
}

QString X11Toolkit::fromWindow(Window _wid)
{
  return QString::number((unsigned long long)_wid,16);
}

Window X11Toolkit::toWindow(QString _wid)
{
  return (Window)_wid.toULongLong(NULL,16);
}

int X11Toolkit::getWindowDesktop(QString _wid)
{
  return xfitMan().getWindowDesktop(toWindow(_wid));
}

void X11Toolkit::minimizeWindow(QString _wid)
{
  xfitMan().minimizeWindow(toWindow(_wid));
}

QVariantList X11Toolkit::getClientList()
{
  QList<Window> wl = xfitMan().getClientList();
  QVariantList vl;
  Window w;
  foreach(w,wl)
    {
      vl.append(fromWindow(w));
    }
  return vl;
}

QString X11Toolkit::getWindowTitle(QString _wid)
{
  return xfitMan().getWindowTitle(toWindow(_wid));
}

