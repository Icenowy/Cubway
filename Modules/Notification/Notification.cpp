#include <QtPlugin>
#include <QString>
#undef signals
#include <libnotify/notify.h>
#include "Notification.h"

void NotificationModule::Send(QString title, QString body, QString icon) 
{
  /* Code from ArchWiki */
  notify_init (QString("subway_notify_"+title).toStdString().c_str());
  NotifyNotification *Hello = notify_notification_new (title.toStdString().c_str(), body.toStdString().c_str(), icon.toStdString().c_str());
  notify_notification_show (Hello, NULL);
  g_object_unref(G_OBJECT(Hello));
  notify_uninit();
}

Q_EXPORT_PLUGIN2(Notification, NotificationModule)
