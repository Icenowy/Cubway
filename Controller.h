#ifndef CUBWAY_CONTROLLER_H
#define CUBWAY_CONTROLLER_H

#include <QObject>

#include "common.h"
#include "View.h"
#include "moduleloader.h"

CUBWAY_NS_BEGIN

class Controller : public QObject
{
  Q_OBJECT
  Q_PROPERTY (View *view READ view)
public:
  Controller ();
  View * view ()
    {
      return &m_view;
    }
  void addObject (const QString &name, QObject *obj);
protected:
  void init_view ();
private:
  View m_view;
  ModuleLoader m_moduleLoader;
};

CUBWAY_NS_END

#endif//CUBWAY_CONTROLLER_H
