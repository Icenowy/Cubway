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
    void loadFile(const QString &fileName);
protected:
    void keyPressEvent(QKeyEvent *ke);
    QString adjustPath(const QString &path);
public slots:
    void javaScriptWindowObjectCleared();
    void QtAlert(QString str);
    void System(QString str);
    void Hide();
};

#endif // METRO_H
