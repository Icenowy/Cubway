#ifndef CUBWAY_VIEW_H
#define CUBWAY_VIEW_H

#include <iostream>

// QtGui
#include <QKeyEvent>

// QtWidget
#include <QWidget>

// QtWebkit/Widget
#include <QWebSettings>
#include <QWebFrame>
#include <QWebElement>
#include <QWebView>

//QtCore
#include <QSize>
#include <QMultiMap>
#include <QVariant>
#include <QHash>
#include <QScopedPointer>

#include "common.h"
#include "moduleloader.h"

using namespace std;


class QFile;
class QDir;

CUBWAY_NS_BEGIN

class View : public QWebView
{
    Q_OBJECT
public:
    View (QWidget *parent = 0);
    ~View ();
    static View *Mainview;
    void addObject(QString name, QObject *_object);
protected:
//    lua_State *lua;
    void keyPressEvent(QKeyEvent *ke);
    void keyReleaseEvent(QKeyEvent *ke);
    void resizeEvent(QResizeEvent * event); 
    void initFolders();
    void doWebSettings();
private:
    QMultiMap<QString, QString> MetaData;
    QString InitFunction;
    QHash<QString, QObject*> _objects;
    //ModuleLoader _moduleLoader;
    QHash<QString, bool> EventsEnabled;
  QScopedPointer<QFile> appFile;
  QString appDirPath;
  QScopedPointer<QDir> userDir;
  QScopedPointer<QDir> settingsDir;
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
    QString OpenFile(QString Dir, QString Filters);
    QVariantMap GetColor(QVariantMap initial);
    QString GetFont(QString family,int size,QString weight,QString style);
    QVariantMap WinSizeHint();
    void WinTitle(QString title);
    void WinResize(int w,int h);
    void WinPos(int x,int y);
    void WinFullScreen();
    void WinMaximize();
    void WinMinimize();
    void WinNormal();
    QVariantMap ScrollBar();
    void LinkClicked(const QUrl &_url);
    QString getFileDir();
    QString getSettings(QString AppName);
    void setSettings(QString AppName, QString str);
};
CUBWAY_NS_END

#endif //CUBWAY_VIEW_H
