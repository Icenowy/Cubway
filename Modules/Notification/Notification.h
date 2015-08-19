#ifndef _MODULES_NOTIFICATION_H
#define _MODULES_NOTIFICATION_H

#include <QObject>
#include <QString>

class NotificationModule: public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.subway.Cubway.Notification")
public slots:
    void send(QString title, QString body, QString icon);
};

#endif //_MODULES_NOTIFICATION_H
