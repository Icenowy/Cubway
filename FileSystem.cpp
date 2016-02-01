#include "FileSystem.h"
#include <QDir>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDebug>

bool FileSystem::exists(QString file)
{
  return QFile::exists(file);
}

QString FileSystem::read(QString file)
{
  QFile f(file);
  if (!f.open(QFile::ReadOnly | QFile::Text)){
    qDebug() << "Error: Unable to open file '" << file << "' for read";
    return "";
  }
  QTextStream in(&f);
  return in.readAll();
}

QStringList FileSystem::list(QString dir)
{
  QDir directory(dir);
  return directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);
}

