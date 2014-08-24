#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QStringList>
#include <QByteArray>
#include <QMultiMap>
#include <QUrl>
#include <QDialog>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QKeyEvent>
#include <QProcess>
#include <QPluginLoader>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QTextStream>

#include "View.h"
#include "moduleloader.h"

CUBWAY_NS_BEGIN

View::View(QWidget *parent)
    : QWebView(parent)
{
    this->initFolders();
    this->doWebSettings();
    setWindowTitle("Cubway");
//    setWindowFlags(Qt::WindowStaysOnBottomHint | Qt::FramelessWindowHint);
    if(QApplication::arguments().length() <= 1){
        load(QUrl("http://github.com/EasternHeart/Cubway"));
    }else{
      this->appFile.reset(new QFile(QApplication::arguments()[1]));
      QFileInfo file_info(*this->appFile);
      this->appDirPath = file_info.absoluteDir().path();
      load(QUrl::fromLocalFile(file_info.absoluteFilePath()));
    }
//    showFullScreen();

    connect(page()->mainFrame(), SIGNAL(loadFinished(bool)),
            this, SLOT(HandleMetaData()) );
//    connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
 //           this, SLOT(javaScriptWindowObjectCleared()) );
    connect(this, SIGNAL(linkClicked(const QUrl &)),
            this, SLOT(LinkClicked(const QUrl &)) );
    //addObject("MetroView", this);
    //addObject("require", &_moduleLoader);
    Mainview = this;
}
View * View::Mainview = NULL;


View::~View()
{
    Mainview = NULL;
}


void View::initFolders(){
  userDir.reset(new QDir(QDir::homePath() + "/.cubway"));
  if(!userDir->exists())
    QDir::home().mkdir(".cubway");
  settingsDir.reset(new QDir(QDir::homePath() + "/.cubway/Settings"));
  if(!settingsDir->exists())
    userDir -> mkdir("Settings");
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
    // Handle Links
    page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
 
}

void View::HandleMetaData(){
  /* Get data */
  MetaData = page()->mainFrame()->metaData();

  /* Title */
  if(MetaData.contains("subway_title"))
    setWindowTitle(MetaData.values("subway_title").at(0));
  else
    setWindowTitle(page()->mainFrame()->title());
  /* Size */
  if(MetaData.contains("subway_size")){
    QString tmp_size = MetaData.values("subway_size").at(0);
    if(tmp_size=="auto"){
      resize(this->page()->mainFrame()->contentsSize());
    }else{
      QStringList sizeXY = tmp_size.split("x");
      if(sizeXY.size()==2)
        resize(sizeXY[0].toInt(),sizeXY[1].toInt());
    }
  }
  if(MetaData.contains("subway_fixed")){
    setFixedSize(this->size());
  }
  if(MetaData.contains("subway_fullscreen")){
    showFullScreen();
  }
  /* Position */
  if(MetaData.contains("subway_position")){
    QString tmp_pos = MetaData.values("subway_position").at(0);
    if(tmp_pos=="center"||tmp_pos=="centre"){
      WinPos(-1,-1);
    }
    // elif Set by settings or last
  }
  /* Flag */
  if(MetaData.contains("subway_flag")){
    QStringList tmp_flag = MetaData.values("subway_flag");
    if(tmp_flag[0] == "below")
      setWindowFlags(this->windowFlags() | Qt::WindowStaysOnBottomHint);
    else if(tmp_flag[0] == "above")
      setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
  }
  /* Scrollbar */
  if(MetaData.contains("subway_scrollbar")){
    QStringList tmp_scroll = MetaData.values("subway_scrollbar");
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
  if(MetaData.contains("subway_events")){
    QStringList tmp_events = MetaData.values("subway_events").at(0).split(" ");
    for(int i=0; i<tmp_events.size(); i++)
      EventsEnabled[tmp_events[i]] = true;
  }
  /* Init Function */
  if(MetaData.contains("subway_init")){
    InitFunction = MetaData.values("subway_init").at(0);
    qDebug() << "InitFunction :" << InitFunction;
  }else{ qDebug() << "No InitFunction"; }
  if(!InitFunction.isEmpty()){
    page() -> mainFrame() -> evaluateJavaScript(InitFunction);
    qDebug() << "Evaluated InitFunction " << InitFunction;
  }

  /* Show */
  if(MetaData.contains("subway_fullscreen"))
    showFullScreen();
  else
    show();
}


#if 0
void View::addObject(QString name, QObject *_object){
  page() -> mainFrame() -> addToJavaScriptWindowObject(name, _object);
  _objects[name] = _object;
}
void View::javaScriptWindowObjectCleared()
{
  QHashIterator<QString, QObject*> i(_objects);
  while (i.hasNext()) {
    i.next();
    page() -> mainFrame() -> addToJavaScriptWindowObject(i.key(),i.value());
  }
}
#endif


QString View::GetArg(int n)
{
  if(n > QApplication::arguments().length()-1 || n < 0){
    page() -> mainFrame() -> evaluateJavaScript("throw \"GetArg: No such argument\"");
    return "";
  }else{
    return  QApplication::arguments()[n];
  }
}

int View::GetArgsLen()
{
  return  QApplication::arguments().length();
}


void View::Echo(QString str)
{
qDebug()<<str;
}


// 執行系統指令：已廢棄
/*
QString View::System(QString str)
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
QString View::Exec(QString str,QString args,int wait)
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
void View::aExec(QString str)
{
    QProcess *qp = new QProcess;
    qp->start(str);
}
*/


QString View::OpenFile(QString Dir, QString Filters)
{
  return QFileDialog::getOpenFileName(this, tr("Open File"), Dir, Filters);
}

QVariantMap View::GetColor(QVariantMap initial)
{
  QVariantMap result;
  QColor Initial(initial["red"].toInt(), initial["green"].toInt(), initial["blue"].toInt());
  QColor color = QColorDialog::getColor(Initial, this);
  if(color.isValid()){
    result["valid"] = true;
    result["red"] = color.red();
    result["green"] = color.green();
    result["blue"] = color.blue();
  }else{
    result["valid"] = false;
  }
  return result;
}

QString View::GetFont(QString family,int size,QString weight,QString style)
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


void View::WinTitle(QString title)
{
    Mainview->setWindowTitle(title);
}

void View::WinResize(int w,int h)
{
    Mainview->resize(w,h);
}

QVariantMap View::WinSizeHint(){
  QVariantMap sizeHint;
  //SizeHint << QString::number(Mainview->page()->mainFrame()->contentsSize().width()) << QString::number(Mainview->page()->mainFrame()->contentsSize().height());
  sizeHint["width"]=Mainview->page()->mainFrame()->contentsSize().width();
  sizeHint["height"]=Mainview->page()->mainFrame()->contentsSize().height();
  return sizeHint;
}

void View::WinPos(int x,int y)
{
    QDesktopWidget *desktop = QApplication::desktop();
    if(x==-1&&y==-1){
      Mainview->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    }else{
      Mainview->move(x,y);
    }
}

void View::WinFullScreen()
{
    Mainview->showFullScreen();
}

void View::WinMaximize()
{
    Mainview->showMaximized();
}

void View::WinMinimize()
{
    Mainview->showMinimized();
}

void View::WinNormal()
{
    Mainview->showNormal();
}

void View::QtAlert(QString str)
{
    QMessageBox::information(this,"QtAlert",str);
}


QVariantMap View::ScrollBar(){
  QVariantMap result, hl, vl;
  hl["width"] = Mainview->page()->mainFrame()->scrollBarGeometry(Qt::Horizontal).width();
  hl["height"] = Mainview->page()->mainFrame()->scrollBarGeometry(Qt::Horizontal).height();
  vl["width"] = Mainview->page()->mainFrame()->scrollBarGeometry(Qt::Vertical).width();
  vl["height"] = Mainview->page()->mainFrame()->scrollBarGeometry(Qt::Vertical).height();
  result["horizontal"] = hl;
  result["vertical"] = vl;
  return result;
}


void View::LinkClicked(const QUrl &_url){
  if(_url.hasFragment())
    emit LinkFragment(_url.fragment());
}

// Events

void View::keyPressEvent(QKeyEvent *ke)
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

void View::keyReleaseEvent(QKeyEvent *ke)
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

void View::resizeEvent(QResizeEvent * event)
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


QString View::getFileDir(){
  return this->appDirPath;
}


QString View::getSettings(QString AppName){
  QString file = settingsDir->path() + "/" + AppName;
  QFile f(file);
  if(!f.exists()){
    setSettings(AppName, "");
  }
  if (!f.open(QFile::ReadOnly | QFile::Text)){
    qDebug() << "Error: Unable to open file '" << file << "' for read";
    return "";
  }
  QTextStream in(&f);
  return in.readAll();
}


void View::setSettings(QString AppName, QString str){
  QString file = settingsDir->path() + "/" + AppName;
  QFile settingsFile(file);
  if(settingsFile.open(QIODevice::ReadWrite)){
    settingsFile.resize(0);
    QTextStream stream(&settingsFile);
    stream << str;
  }else{
    qDebug() << "Error: Unable to open file '" << file << "' for write";
  }
}

CUBWAY_NS_END
