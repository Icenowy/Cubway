#include "MFile.h"
#include <QProcess>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDebug>
//MetroFile
bool MFile::exists(QString file)
{
  return QFile::exists(file);
}

QString MFile::read(QString file)
{
  QFile f(file);
  if (!f.open(QFile::ReadOnly | QFile::Text)){
    qDebug() << "Error: Unable to open file '" << file << "' for read";
    return "";
  }
  QTextStream in(&f);
  return in.readAll();
}

QStringList MFile::list(QString dir)
{
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

