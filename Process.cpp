#include "Process.h"
#include <QApplication>

QStringList Process::getArgv()
{
  return QApplication::arguments();
}

