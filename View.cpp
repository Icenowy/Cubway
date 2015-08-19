#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QStringList>
#include <QByteArray>
#include <QMultiMap>
#include <QUrl>
#include <QDialog>
#include <QFileDialog>
#include <QStyle>
#include <QKeyEvent>
#include <QProcess>
#include <QPluginLoader>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "View.h"
#include "moduleloader.h"

CUBWAY_NS_BEGIN

View::View(QWidget *parent)
    : QWebView(parent)
{
    this->doWebSettings();
    setWindowTitle("Cubway");
//    setWindowFlags(Qt::WindowStaysOnBottomHint | Qt::FramelessWindowHint);
    if(QApplication::arguments().length() <= 1){
      setHtml("<!DOCTYPE html><html><head></head><body></body></html>");
      show();
    }else{
      this->appFile.reset(new QFile(QApplication::arguments()[1]));
      QFileInfo file_info(*this->appFile);
      this->appDirPath = file_info.absoluteDir().path();
      load(QUrl::fromLocalFile(file_info.absoluteFilePath()));
    }

    connect(page()->mainFrame(), SIGNAL(loadFinished(bool)),
            this, SLOT(HandleMetaData()) );
    Mainview = this;
}
View * View::Mainview = NULL;


View::~View()
{
    Mainview = NULL;
}


void View::doWebSettings()
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
}

void View::HandleMetaData(){
  /* Get data */
  MetaData = page()->mainFrame()->metaData();

  /* Title */
  if(MetaData.contains("win_title"))
    setWindowTitle(MetaData.values("win_title").at(0));
  else
    setWindowTitle(page()->mainFrame()->title());
  /* Size */
  if(MetaData.contains("win_size")){
    QString tmp_size = MetaData.values("win_size").at(0);
    if(tmp_size=="auto"){
      resize(this->page()->mainFrame()->contentsSize());
    }else{
      QStringList sizeXY = tmp_size.split("x");
      if(sizeXY.size() == 2)
        resize(sizeXY[0].toInt(),sizeXY[1].toInt());
    }
  }
  if(MetaData.contains("win_fixed")){
    setFixedSize(this->size());
  }
  if(MetaData.contains("win_fullscreen")){
    showFullScreen();
  }
  /* Position */
  if(MetaData.contains("win_position")){
    QString tmp_pos = MetaData.values("win_position").at(0);
    if(tmp_pos == "center")
      winCenter();
    // elif Set by settings or last
  }
  /* Flag */
  if(MetaData.contains("win_flag")){
    QStringList tmp_flag = MetaData.values("win_flag");
    if(tmp_flag[0] == "below")
      setWindowFlags(this->windowFlags() | Qt::WindowStaysOnBottomHint);
    else if(tmp_flag[0] == "above")
      setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
  }
  /* Scrollbar */
  if(MetaData.contains("win_scrollbar")){
    QStringList tmp_scroll = MetaData.values("win_scrollbar");
    for(int i=0; i<tmp_scroll.size(); i++){
      Qt::ScrollBarPolicy val;
      if(tmp_scroll[i] == "AlwaysOn"){
	val = Qt::ScrollBarAlwaysOn;
      }else if(tmp_scroll[i] == "AlwaysOff"){
	val = Qt::ScrollBarAlwaysOff;
      }else{
	val = Qt::ScrollBarAsNeeded;
      }
      if(i == 0){
	this->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, val);
      }else{
	this->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, val);
      }
    }
  }
  /* Events */
  if(MetaData.contains("win_events")){
    QStringList tmp_events = MetaData.values("win_events").at(0).split(" ");
    for(int i=0; i<tmp_events.size(); i++)
      EventsEnabled[tmp_events[i]] = true;
  }
  /* Init Function */
  QString InitScript;
  if(MetaData.contains("init_script"))
    InitScript = MetaData.values("init_script").at(0);
  if(!InitScript.isEmpty())
    page() -> mainFrame() -> evaluateJavaScript(InitScript);

  /* Show */
  if(MetaData.contains("win_fullscreen"))
    showFullScreen();
  else
    show();
}

QString View::getArg(int n)
{
  if(n > QApplication::arguments().length()-1 || n < 0){
    page() -> mainFrame() -> evaluateJavaScript("throw \"GetArg: No such argument\"");
    return "";
  }else{
    return  QApplication::arguments()[n];
  }
}

int View::getArgsLen()
{
  return  QApplication::arguments().length();
}

void View::echo(QString str)
{
  qDebug()<<str;
}

QString View::fileDialog(QString dir, QString filters)
{
  return QFileDialog::getOpenFileName(this, tr("Open File"), dir, filters);
}

void View::winTitle(QString title)
{
    Mainview->setWindowTitle(title);
}

void View::winResize(int w,int h)
{
    Mainview->resize(w,h);
}

QVariantMap View::winSizeHint(){
  QVariantMap sizeHint;
  sizeHint["width"]=Mainview->page()->mainFrame()->contentsSize().width();
  sizeHint["height"]=Mainview->page()->mainFrame()->contentsSize().height();
  return sizeHint;
}

void View::winCenter(){
  /* https://wiki.qt.io/How_to_Center_a_Window_on_the_Screen */
  Mainview->setGeometry(
    QStyle::alignedRect(
       Qt::LeftToRight,
       Qt::AlignCenter,
       Mainview->size(),
       qApp->desktop()->availableGeometry()
    )
  );
}

void View::winPos(int x, int y)
{
  Mainview->move(x,y);
}

void View::winFullScreen()
{
    Mainview->showFullScreen();
}

void View::winMaximize()
{
    Mainview->showMaximized();
}

void View::winMinimize()
{
    Mainview->showMinimized();
}

void View::winNormal()
{
    Mainview->showNormal();
}

void View::msgbox(QString title, QString content)
{
    QMessageBox::information(this, title, content);
}


QVariantMap View::scrollBarInfo(){
  QVariantMap result, hl, vl;
  hl["width"] = Mainview->page()->mainFrame()->scrollBarGeometry(Qt::Horizontal).width();
  hl["height"] = Mainview->page()->mainFrame()->scrollBarGeometry(Qt::Horizontal).height();
  vl["width"] = Mainview->page()->mainFrame()->scrollBarGeometry(Qt::Vertical).width();
  vl["height"] = Mainview->page()->mainFrame()->scrollBarGeometry(Qt::Vertical).height();
  result["horizontal"] = hl;
  result["vertical"] = vl;
  return result;
}

// Events

void View::keyPressEvent(QKeyEvent *ke)
{
  if(EventsEnabled["onKeyPressEvent"]){
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

void View::keyReleaseEvent(QKeyEvent *ke)
{
  if(EventsEnabled["onKeyReleaseEvent"]){
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

void View::resizeEvent(QResizeEvent * event)
{
  if(EventsEnabled["onResizeEvent"]){
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


CUBWAY_NS_END
