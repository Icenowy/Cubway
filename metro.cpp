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
    QWebSettings* defaultSettings = QWebSettings::globalSettings();  
    QWebSettings::enablePersistentStorage("");  
    defaultSettings->setAttribute(QWebSettings::JavascriptEnabled, true);  
    // Plug-ins must be set to be enabled to use plug-ins.  
    defaultSettings->setAttribute(QWebSettings::PluginsEnabled,true);  
    defaultSettings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,true);  
    defaultSettings->setObjectCacheCapacities(0, 0, 0); 

    setWindowFlags(Qt::WindowStaysOnBottomHint | Qt::FramelessWindowHint);
    if(QApplication::arguments().length() <= 1)
        load(QUrl("https://metro-subway.rhcloud.com/MT.php"));
    else
        load(QUrl(QApplication::arguments()[1]));
    showFullScreen();
    connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(javaScriptWindowObjectCleared()));
    lua = luaL_newstate();
	RunLua("libmetro.lua");
}

Metro::~Metro()
{
    lua_close(lua);
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

void Metro::RunLua(QString str)
{
    luaL_loadfile(lua,str.toAscii());
    lua_pcall(lua,0,LUA_MULTRET,0);
}

void Metro::RunLuaString(QString str)
{
    luaL_loadstring(lua,str.toAscii());
    lua_pcall(lua,0,LUA_MULTRET,0);
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
