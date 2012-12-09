#include "metro.h"
#include <QtGui/QApplication>
#include <QtGui/QDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QProcess>
#include <QtGui/QKeyEvent>
#include "lua/lua.hpp"


Metro::Metro(QWidget *parent)
    : QWebView(parent)
{
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    setWindowFlags(Qt::WindowStaysOnBottomHint | Qt::FramelessWindowHint);
    if(QApplication::arguments().length() <= 1)
        load(QUrl("https://metro-subway.rhcloud.com/MT.php"));
    else
        load(QUrl(QApplication::arguments()[1]));
    showFullScreen();
    connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(javaScriptWindowObjectCleared()));
}

Metro::~Metro()
{
}

void Metro::javaScriptWindowObjectCleared()
{
    page()->mainFrame()->addToJavaScriptWindowObject("MetroView", this);
}

void Metro::QtAlert(QString str)
{
    QMessageBox::information(this,"QtAlert",str);
}

void Metro::System(QString str)
{
    QProcess *qp = new QProcess;
    qp->start(str);
}

void Metro::keyPressEvent(QKeyEvent *ke)
{
    //if(ke->key() == Qt::Key_Super_L || ke->key() == Qt::Key_Super_R)
    //if(ke->key() == Qt::Key_Alt)
    {

    }
    //else
    {
        QWebView::keyPressEvent(ke);
    }
}

void Metro::Hide()
{
    hide();
}
