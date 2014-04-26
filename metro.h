#ifndef METRO_H
#define METRO_H

#include <iostream>
#include <QtGui/QWidget>
#include <QtWebKit/QWebSettings>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebView>
#include <QtGui/QKeyEvent>
#include <QHash>
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
    QHash<QString, QObject*> _objects;
public slots:
    void HandleMetaData();
    QObject *LoadModule(QString mod);
    void javaScriptWindowObjectCleared();
    QString GetArg(int n);
    int GetArgsLen();
    void QtAlert(QString str);
    QString System(QString str);
    void Echo(QString str);
    QString Exec(QString str,QString args,int wait);
    void aExec(QString str);
    QString OpenFile();
    QString GetColor();
    QString GetFont(QString family,int size,QString weight,QString style);
    void WinTitle(QString title);
    void WinResize(int w,int h);
    void WinPos(int x,int y);
    void WinFlag(QString flag);
    void WinFullScreen();
    void WinMaximize();
    void WinMinimize();
    void WinNormal();
    void Hide();
};

class MFile : public QObject
{
    Q_OBJECT
public slots:
    bool Exists(QString file);
    void DownLoad(QString url,QString tofile);
    QString Read(QString file);
    bool CreateDir(QString path);
    int Remove(const QStringList& Files);
//    int RemoveDirs(const QStringList& Files);
    bool CopyFile(QString from,QString to);
    bool Move(QString old,QString New,bool rename);
    void XdgOpen(QString path);
    QString List(QString where);
};

class Unix : public QObject
{
    Q_OBJECT
//public:
//    Unix(QObject *parent = 0);
//    ~Unix();
public slots:
    void SendNotify(QString str,QString icon);
};

#endif //METRO_H
