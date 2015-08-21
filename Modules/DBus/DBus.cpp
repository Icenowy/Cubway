#include <QtPlugin>
#include <QtDBus>
#include "DBus.h"


QString DBusModule::call(QString service, QString path, QString interface, QString method, QList<QVariant> args){
	QDBusInterface iface(service, path, interface, QDBusConnection::sessionBus(), this);
	QDBusReply<QString> reply = iface.callWithArgumentList(QDBus::Block, method, args);
	if(reply.isValid()){
		return reply.value();
	}
	return reply.error().message();
}


// Q_EXPORT_PLUGIN2(DBus, DBusModule)
