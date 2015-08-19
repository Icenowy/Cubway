#include "Controller.h"

#include <QVariant>
#include <QDebug>

CUBWAY_NS_BEGIN

Controller::Controller ()
{
  init_view ();
}

/*
void
Controller::addObject (const QString &name, QObject *obj)
{
  setProperty (name.toLocal8Bit (), QVariant::fromValue (obj));
}
*/

void
Controller::init_view ()
{
  handle_javaScriptWindowObjectCleared();
  connect (m_view.page()->mainFrame(),
           SIGNAL (javaScriptWindowObjectCleared ()),
           this,
           SLOT (handle_javaScriptWindowObjectCleared ()));
  connect (&m_view, &QWebView::linkClicked, [this](const QUrl& url)
  {
    if (m_url_loaders.contains (url.scheme ()))
      m_url_loaders[url.scheme ()](url);
    else
      this -> view () -> load (url);
  });
}

void
Controller::handle_javaScriptWindowObjectCleared ()
{
  m_view.page () -> mainFrame ()
    -> addToJavaScriptWindowObject ("GUI", view());
  m_view.page () -> mainFrame ()
    -> addToJavaScriptWindowObject ("Modules", &m_moduleLoader);
  handle_aliases ();
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
