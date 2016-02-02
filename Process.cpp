#include <cstdlib>
#include <QApplication>
#include <QProcess>
#include "Process.h"


QStringList Process::getArgv()
{
  return QApplication::arguments();
}


QString Process::getPlatform()
{
#ifdef Q_OS_WIN32
  return "win32";
#elif defined(Q_OS_LINUX)
  return "linux";
#elif defined(Q_OS_FREEBSD)
  return "freebsd";
#else
  return "others";
#endif
}


QString Process::getEnv(QString name)
{
  return getenv(name.toStdString().c_str());
}


QObject* Process::exec(QString cmd, QStringList args)
{
  QProcess *p = new QProcess;
  p->start(cmd, args);
  return p;
}


bool Process::execDetached(QString cmd, QStringList args)
{
  return QProcess::startDetached(cmd, args);
}
