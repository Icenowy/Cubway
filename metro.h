#ifndef METRO_H
#define METRO_H

#include <iostream>
#include <QtGui/QWidget>
#include <QtWebKit/QWebSettings>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebView>
#include <QtGui/QKeyEvent>
#include "lua/lua.hpp"
using namespace std;

class Metro : public QWebView
{
    Q_OBJECT
public:
    Metro(QWidget *parent = 0);
    ~Metro();
    static Metro *Mainview;
protected:
    lua_State *lua;
    void keyPressEvent(QKeyEvent *ke);
public slots:
    void javaScriptWindowObjectCleared();
    void QtAlert(QString str);
    QString System(QString str);
    QString OpenFile();
    QString GetColor();
    QString GetFont(QString family,int size,QString weight,QString style);
    void WinTitle(QString title);
    void WinResize(int w,int h);
    void WinPos(int x,int y);
//    void WinFlag(QString flag);
    void WinFullScreen();
    void WinMaximize();
    void WinMinimize();
    void WinNormal();
    void RunLua(QString str);
    void RunLuaString(QString str);
    void Hide();
};

#endif // METRO_H
