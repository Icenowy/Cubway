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

class Controller;

class View : public QWebView
{
    Q_OBJECT
public:
    View (QWidget *parent = 0);
    ~View ();
    static View *Mainview;
protected:
    void keyPressEvent(QKeyEvent *ke);
    void keyReleaseEvent(QKeyEvent *ke);
    void resizeEvent(QResizeEvent *event);
    void doWebSettings();
private:
    QMultiMap<QString, QString> MetaData;
    QHash<QString, QObject*> _objects;
    QHash<QString, bool> EventsEnabled;
    QScopedPointer<QFile> appFile;
    QString appDirPath;
    QScopedPointer<QDir> userDir;
    QScopedPointer<QDir> settingsDir;
public slots:
    void HandleMetaData();
    void msgbox(QString title, QString content);
    void echo(QString str);
    QString fileDialog(QString dir, QString filters);
    QVariantMap winSizeHint();
    void winTitle(QString title);
    void winResize(int w,int h);
    void winCenter();
    void winPos(int x,int y);
    void winFullScreen();
    void winMaximize();
    void winMinimize();
    void winNormal();
    QVariantMap scrollBarInfo();
    friend class Controller;
};
CUBWAY_NS_END

#endif //CUBWAY_VIEW_H
