#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QStringList>

class Process : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QStringList argv READ getArgv)
  Q_PROPERTY(QString platform READ getPlatform)
  public:
    QStringList getArgv();
    QString getPlatform();
    Q_INVOKABLE QString getEnv(QString name);
    Q_INVOKABLE QObject* exec(QString cmd, QStringList args = QStringList());
    Q_INVOKABLE bool execDetached(QString cmd, QStringList args = QStringList(), QString dir = QString());
    Q_INVOKABLE void exit(int return_value);
};

#endif
