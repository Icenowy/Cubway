#include "Controller.h"

#include <QVariant>

CUBWAY_NS_BEGIN

Controller::Controller ()
{
  init_view ();
}

void
Controller::addObject (const QString &name, QObject *obj)
{
  setProperty (name.toLocal8Bit (), QVariant::fromValue (obj));
}

void
Controller::init_view ()
{
  m_view.addObject ("Cubway", this);
  this->addObject ("require", &m_moduleLoader);
}

CUBWAY_NS_END
