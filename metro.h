#ifndef METRO_H
#define METRO_H

#include <QtGui/QWidget>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebView>
#include "lua/lua.hpp"

class Metro : public QWebView
{
    Q_OBJECT
public:
    Metro(QWidget *parent = 0);
    ~Metro();
protected:
    lua_State *lua;
public slots:
    void javaScriptWindowObjectCleared();
    void QtAlert(QString str);
    void System(QString str);
    void RunLua(QString str);
    void RunLuaString(QString str);
};

#endif // METRO_H
