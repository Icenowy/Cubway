#ifndef METRO_H
#define METRO_H

#include <iostream>
#include <QtGui/QWidget>
#include <QtWebKit/QWebSettings>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebView>
#include <QtGui/QKeyEvent>
#include <QMultiMap>
#include <QHash>
#include "moduleloader.h"
using namespace std;

class Metro : public QWebView
{
    Q_OBJECT
public:
    Metro(QWidget *parent = 0);
    ~Metro();
    static Metro *Mainview;
protected:
//    lua_State *lua;
    void keyPressEvent(QKeyEvent *ke);
    void keyReleaseEvent(QKeyEvent *ke);
    void resizeEvent(QResizeEvent * event); 
    void addObject(QString name, QObject *_object);
private:
    QMultiMap<QString, QString> MetaData;
    QString InitFunction;
    QHash<QString, QObject*> _objects;
    ModuleLoader _moduleLoader;
    QHash<QString, bool> EventsEnabled;
signals:
    void LinkFragment(QString _fragment);
public slots:
    void HandleMetaData();
    void javaScriptWindowObjectCleared();
    QString GetArg(int n);
    int GetArgsLen();
    void QtAlert(QString str);
    void Echo(QString str);
    /*
    QString System(QString str);
    QString Exec(QString str,QString args,int wait);
    void aExec(QString str);
    */
    QString OpenFile();
    QString GetColor();
    QString GetFont(QString family,int size,QString weight,QString style);
    QStringList WinSizeHint();
    void WinTitle(QString title);
    void WinResize(int w,int h);
    void WinPos(int x,int y);
    void WinFlag(QString flag);
    void WinFullScreen();
    void WinMaximize();
    void WinMinimize();
    void WinNormal();
    void LinkClicked(const QUrl &_url);
    QWebElement Element(QString selector);
    QWebElementCollection Elements(QString selector);
};

#endif //METRO_H
