#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QStringList>

class Process : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QStringList argv READ getArgv)
  public slots:
    QStringList getArgv();
};

#endif
