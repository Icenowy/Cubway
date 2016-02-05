#ifndef DBUSINTERFACE_H
#define DBUSINTERFACE_H

#include <QObject>
#include <QDBusAbstractAdaptor>


void createInterface(QString app_name, QWidget *view);


class Adaptor : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.subway.cubway")
private:
    QWidget *view;
public:
    Adaptor(QWidget *view);
public slots:
    void toggleVisible();
};


#endif
