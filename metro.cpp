#include <QDebug>
#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QStringList>
#include <QByteArray>
#include <QMultiMap>
#include <QUrl>
#include <QtGui/QDialog>
#include <QtGui/QFileDialog>
#include <QtGui/QColorDialog>
#include <QtGui/QFontDialog>
#include <QtGui/QKeyEvent>
#include <QProcess>
#include <QPluginLoader>
#include <QMessageBox>
#include <QWebElement>
#include <QWebElementCollection>
#include "metro.h"
#include "moduleloader.h"

Metro::Metro(QWidget *parent)
    : QWebView(parent)
{
    QWebSettings* defaultSettings = QWebSettings::globalSettings();  
    QWebSettings::enablePersistentStorage("");  
    // Inspect Support
    defaultSettings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    defaultSettings->setAttribute(QWebSettings::JavascriptEnabled, true);  
    // Plug-ins must be set to be enabled to use plug-ins.  
    defaultSettings->setAttribute(QWebSettings::PluginsEnabled,true);  
    defaultSettings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,true);  
    defaultSettings->setObjectCacheCapacities(0, 0, 0); 
    // Handle Links
    page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    setWindowTitle("QtMetro - Cubway");
//    setWindowFlags(Qt::WindowStaysOnBottomHint | Qt::FramelessWindowHint);
    if(QApplication::arguments().length() <= 1)
        load(QUrl("http://erhandsome.org/subway"));
    else
        load(QUrl(QApplication::arguments()[1]));
//    showFullScreen();

    connect(this, SIGNAL(loadFinished(bool)),
            this, SLOT(HandleMetaData()) );
    connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(javaScriptWindowObjectCleared()) );
    connect(this, SIGNAL(linkClicked(const QUrl &)),
            this, SLOT(LinkClicked(const QUrl &)) );
    addObject("MetroView", this);
    addObject("require",&_moduleLoader);
    Mainview = this;
}
Metro* Metro::Mainview = NULL;

Metro::~Metro()
{
    //lua_close(lua);
    Mainview = NULL;
}


void Metro::HandleMetaData(){
  /* Get data */
  MetaData = page()->mainFrame()->metaData();

  /* Title */
  if(!MetaData.values("subway_title").isEmpty())
    setWindowTitle(MetaData.values("subway_title").at(0));
  /* Size */
  if(!MetaData.values("subway_size").isEmpty()){
    QString tmp_size = MetaData.values("subway_size").at(0);
    QStringList sizeXY = tmp_size.split("x");
    if(sizeXY.size()==2)
      resize(sizeXY[0].toInt(),sizeXY[1].toInt());
  }
  /* Position */
  if(!MetaData.values("subway_position").isEmpty()){
    QString tmp_pos = MetaData.values("subway_position").at(0);
    if(tmp_pos=="center"||tmp_pos=="centre"){
      WinPos(-1,-1);
    }
    // elif Set by settings or last
  }
  /* Flag */
  //
  /* Events */
  if(!MetaData.values("subway_events").isEmpty()){
    QStringList tmp_events = MetaData.values("subway_events").at(0).split(" ");
    for(int i=0;i<tmp_events.size();i++)
      EventsEnabled[tmp_events[i]] = true;
  }
  /* Init Function */
  if(!MetaData.values("subway_init").isEmpty()){
    InitFunction = MetaData.values("subway_init").at(0);
    qDebug() << "InitFunction :" << InitFunction;
  }else{ qDebug() << "No InitFunction"; }
  if(!InitFunction.isEmpty()){
    page() -> mainFrame() -> evaluateJavaScript(InitFunction);
    qDebug() << "Evaluated InitFunction " << InitFunction;
  }

  /* Show */
  if(!MetaData.values("subway_fullscreen").isEmpty())
    showFullScreen();
  else
    show();
}


void Metro::addObject(QString name, QObject *_object){
  page() -> mainFrame() -> addToJavaScriptWindowObject(name, _object);
  _objects[name] = _object;
}


void Metro::javaScriptWindowObjectCleared()
{
  QHashIterator<QString, QObject*> i(_objects);
  while (i.hasNext()) {
    i.next();
    page() -> mainFrame() -> addToJavaScriptWindowObject(i.key(),i.value());
  }
}


QString Metro::GetArg(int n)
{
  if(n>QApplication::arguments().length()||n<0){
    return "undefined";
  }else{
    return  QApplication::arguments()[n];
  }
}

int Metro::GetArgsLen()
{
  return  QApplication::arguments().length();
}


void Metro::Echo(QString str)
{
qDebug()<<str;
}


// 執行系統指令：已廢棄
/*
QString Metro::System(QString str)
{
    QProcess *qp = new QProcess;
    qp->start(str);
    if (!qp->waitForStarted())
      return "1";
    if (!qp->waitForFinished())
      return "2";
    QByteArray result = qp->readAll();
    return QString(result);
}
QString Metro::Exec(QString str,QString args,int wait)
{
    QProcess *qp = new QProcess;
    if (!args.isNull()||!args.isEmpty()){
    QStringList Args=args.split(' ');
    qp->start(str,Args);
    }else qp->start(str);

    if (wait==0){
    if (!qp->waitForStarted())
      return "1";
    if (!qp->waitForFinished())
      return "2";
    QByteArray result = qp->readAll();
    return QString(result);
    } else return "-1";
}
void Metro::aExec(QString str)
{
    QProcess *qp = new QProcess;
    qp->start(str);
}
*/


QString Metro::OpenFile()
{
    return QFileDialog::getOpenFileName(this,tr("Open File"));
}

QString Metro::GetColor()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid()){
    int r = color.red();
    int g = color.green();
    int b = color.blue();
    return "rgb("+QString::number(r)+","+QString::number(g)+","+QString::number(b)+")";
    }else{
    return "-1";
    }
}

QString Metro::GetFont(QString family,int size,QString weight,QString style)
{
    bool ok;
    bool _style;
    QFont font;
    QString font_style;
    QString font_weight;
    QString font_family;
    if (style=="italic") _style=true; else _style=false; 
    if(weight=="bold")
    font = QFontDialog::getFont(&ok,QFont(family, size,QFont::Bold,_style),this);
    else
    font = QFontDialog::getFont(&ok,QFont(family, size,QFont::Normal,_style),this);
    if (ok) {
    font_family=font.family();
    if(font.italic()) font_style="italic"; else font_style="normal";
    if(font.bold()) font_weight="bold"; else font_weight="normal";
//    return "font-family:"+font_family.replace(QString(" "), QString("-"))+";font-size:"+QString::number(font.pointSize())+";font-style:"+font_style+";font-weight:"+font_weight+";";
//    return font_family.replace(QString(" "), QString("-"))+" "+QString::number(font.pointSize())+"px "+font_style+" "+font_weight;
    return font_style+" "+font_weight+" "+QString::number(font.pointSize())+"px "+'"'+font_family+'"';
    }else{
    return "-1";
    }
}


void Metro::WinTitle(QString title)
{
    Mainview->setWindowTitle(title);
}

void Metro::WinResize(int w,int h)
{
    Mainview->resize(w,h);
}

void Metro::WinPos(int x,int y)
{
    QDesktopWidget *desktop = QApplication::desktop();
    if(x==-1&&y==-1){
      Mainview->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    }else{
      Mainview->move(x,y);
    }
}

void Metro::WinFlag(QString flag)
{
    Qt::WindowFlags flags = 0;
    flags = Qt::Window;
    if(flag=="below") flags |= Qt::WindowStaysOnBottomHint;
    if(flag=="above") flags |= Qt::WindowStaysOnTopHint;
    Mainview->setWindowFlags(flags);
    show();
}

void Metro::WinFullScreen()
{
    Mainview->showFullScreen();
}

void Metro::WinMaximize()
{
    Mainview->showMaximized();
}

void Metro::WinMinimize()
{
    Mainview->showMinimized();
}

void Metro::WinNormal()
{
    Mainview->showNormal();
}

void Metro::QtAlert(QString str)
{
    QMessageBox::information(this,"QtAlert",str);
}


QWebElementCollection Metro::Elements(QString selector){
  return page()->mainFrame()->findAllElements(selector);
}


QWebElement Metro::Element(QString selector){
  return page()->mainFrame()->findFirstElement(selector);
}


void Metro::LinkClicked(const QUrl &_url){
  if(_url.hasFragment())
    emit LinkFragment(_url.fragment());
}

// Events

void Metro::keyPressEvent(QKeyEvent *ke)
{
  if(EventsEnabled["onKeyPressEvent"]==true){
    char *buf;
    buf = new char[snprintf(NULL,0,"onKeyPressEvent(%d)",
        ke->key())+1];
    sprintf(buf,"onKeyPressEvent(%d)",
        ke->key());
    page()->mainFrame()->evaluateJavaScript(buf);
    delete[] buf;
  }
  QWebView::keyPressEvent(ke);
}

void Metro::keyReleaseEvent(QKeyEvent *ke)
{
  if(EventsEnabled["onKeyReleaseEvent"]==true){
    char *buf;
    buf = new char[snprintf(NULL,0,"onKeyReleaseEvent(%d)",
        ke->key())+1];
    sprintf(buf,"onKeyReleaseEvent(%d)",
        ke->key());
    page()->mainFrame()->evaluateJavaScript(buf);
    delete[] buf;
  }
  QWebView::keyPressEvent(ke);
}

void Metro::resizeEvent(QResizeEvent * event)
{
  if(EventsEnabled["onResizeEvent"]==true){
	char *buf;
	buf = new char[snprintf(NULL,0,"onResizeEvent(%d,%d,%d,%d)",
		event->size().width(),event->size().height(),
        event->oldSize().width(),event->oldSize().height())+1];
	sprintf(buf,"onResizeEvent(%d,%d,%d,%d)",
		event->size().width(),event->size().height(),
		event->oldSize().width(),event->oldSize().height());
	page()->mainFrame()->evaluateJavaScript(buf);
	delete[] buf;
  }
  QWebView::resizeEvent(event);
}


