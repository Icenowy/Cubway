#ifndef METRO_H
#define METRO_H

#include <QtGui/QWidget>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebView>
#include <QtGui/QKeyEvent>

class Metro : public QWebView
{
    Q_OBJECT
public:
    Metro(QWidget *parent = 0);
    ~Metro();
protected:
    void keyPressEvent(QKeyEvent *ke);
public slots:
    void javaScriptWindowObjectCleared();
    void QtAlert(QString str);
    void System(QString str);
    void Hide();
};

#endif // METRO_H
