#include <OrgFreedesktopNotifications.h>

OrgFreedesktopNotificationsInterface::OrgFreedesktopNotificationsInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

OrgFreedesktopNotificationsInterface::~OrgFreedesktopNotificationsInterface()
{
}

