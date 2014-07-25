#include "MFile.h"
#include <QProcess>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDebug>
//MetroFile
bool MFile::Exists(QString file)
{
  return QFile::exists(file);
}


/*
void MFile::DownLoad(QString url,QString tofile)
{
    QProcess *qp = new QProcess;
    qp->start("wget",QStringList() << url << "-O" << tofile);
}
*/


QString MFile::Read(QString file)
{
  QFile f(file);
  if (!f.open(QFile::ReadOnly | QFile::Text)){
    qDebug() << "Error: Unable to open file '" << file << "' for read";
    return "";
  }
  QTextStream in(&f);
  return in.readAll();
}


void MFile::XdgOpen(QString file)
{
  QProcess *qp = new QProcess;
  QStringList Args;
  Args << file;
  qp -> start("xdg-open", Args);
  return;
}


QStringList MFile::List(QString dir)
{
  // Mark: Need Add Arguments
  QDir directory(dir);
  return directory.entryList();
}


// 計劃中
/*
QVariantMap MFile::InfoList(QString dir)
{
  directory.entryInfoList();
}
*/

