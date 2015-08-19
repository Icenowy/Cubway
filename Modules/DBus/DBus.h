#ifndef _MODULES_DBUS_H
#define _MODULES_DBUS_H

#include <QObject>
#include <QString>
#include <QList>
#include <QVariant>

class DBusModule: public QObject
{
    Q_OBJECT
public slots:
	QString call(QString service, QString path, QString interface, QString method, QList<QVariant> args);
};

#endif //_MODULES_DBUS_H
