#ifndef _MODULES_DBUS_H
#define _MODULES_DBUS_H

#include <QtCore>
#include <QObject>
#include <QString>
#include <QList>
#include <QVariant>

class DBusModule: public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.subway.Cubway.Notification")
public slots:
	QString call(QString service, QString path, QString interface, QString method, QList<QVariant> args);
};

#endif //_MODULES_DBUS_H
