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
  this->addObject ("require", &m_moduleLoader);
#ifdef CUBWAY_DEBUG
  m_aliases ["MetroView"] = "Cubway.view";
  m_aliases ["require"] = "Cubway.require";
#endif
  handle_javaScriptWindowObjectCleared();
  connect (m_view.page()->mainFrame(),
           SIGNAL (javaScriptWindowObjectCleared ()),
           this,
           SLOT (handle_javaScriptWindowObjectCleared ()));
}

void
Controller::handle_javaScriptWindowObjectCleared ()
{
  m_view.page () -> mainFrame ()
    -> addToJavaScriptWindowObject ("Cubway", this);
  handle_aliases();
}

void
Controller::evaluateJavaScript (const QString &source)
{
  m_view.page() -> mainFrame() -> evaluateJavaScript (source);
}

void
Controller::handle_aliases ()
{
  QHash<QString, QString>::const_iterator ia = m_aliases.constBegin ();
  while (ia != m_aliases.constEnd ())
    {
      QString code("window.");
      code += ia.key() + "=";
      code += ia.value() + ";";
      evaluateJavaScript (code);
      ++ia;
    }
}

CUBWAY_NS_END
