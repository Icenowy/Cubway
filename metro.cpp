#include "metro.h"
#include <QtGui/QApplication>
#include <QtGui/QDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QProcess>
#include <QtGui/QKeyEvent>


Metro::Metro(QWidget *parent)
: QWebView(parent)
{
  QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
  setWindowFlags(Qt::WindowStaysOnBottomHint | Qt::FramelessWindowHint);
  if(QApplication::arguments().length() <= 1)
  //load(QUrl("https://metro-subway.rhcloud.com/MT.php"));
    loadFile("html/index.html");
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

void Metro::loadFile(const QString &fileName)
{
  setUrl(QUrl(fileName));
}


QString adjustPath(const QString &path){
/*
#ifdef Q_OS_UNIX
#ifdef Q_OS_MAC
   if (!QDir::isAbsolutePath(path))
     return QCoreApplication::applicationDirPath()
               + QLatin1String("/../Resources/") + path;
#else
   const QString pathInInstallDir = QCoreApplication::applicationDirPath()
                + QLatin1String("/../") + path;
   if (pathInInstallDir.contains(QLatin1String("opt"))
       && pathInInstallDir.contains(QLatin1String("bin"))
       && QFileInfo(pathInInstallDir).exists()) {
     return pathInInstallDir;
   }
#endif
#endif
        return path;
        */
}
