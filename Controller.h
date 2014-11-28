#ifndef CUBWAY_CONTROLLER_H
#define CUBWAY_CONTROLLER_H

#include <QObject>

#include <functional>

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
  void evaluateJavaScript (const QString &source);
  using url_loader_f = std::function<void (const QUrl &url)>;
protected:
  void init_view ();
  void handle_aliases ();
protected slots:
  void handle_javaScriptWindowObjectCleared ();
private:
  View m_view;
  ModuleLoader m_moduleLoader;
  QHash<QString,QString> m_aliases;
  QHash<const QString, url_loader_f> m_url_loaders;
};

CUBWAY_NS_END

#endif//CUBWAY_CONTROLLER_H
