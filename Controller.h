#ifndef CUBWAY_CONTROLLER_H
#define CUBWAY_CONTROLLER_H

#include <QObject>

#include "common.h"
#include "View.h"

CUBWAY_NS_BEGIN

class Controller : public QObject
{
  Q_OBJECT
public:
  Controller ();
private:
  View m_view;
};

CUBWAY_NS_END

#endif//CUBWAY_CONTROLLER_H
