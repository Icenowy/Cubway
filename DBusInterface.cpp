#include "DBusInterface.h"
#include <QDBusConnection>
#include <QWidget>


void createInterface(QString service_name, QWidget *view){
  new Adaptor(view);
  QDBusConnection con = QDBusConnection::sessionBus();
  con.registerObject("/view", view);
  con.registerService(service_name);
}


Adaptor::Adaptor(QWidget *view): QDBusAbstractAdaptor(view) {
  this->view = view;
}


void Adaptor::toggleVisible(){
  view->setVisible(!view->isVisible());
}

