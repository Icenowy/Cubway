#include <cstdlib>
#include <QApplication>
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

