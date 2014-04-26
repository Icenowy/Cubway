#include "MFile.h"
#include <QProcess>
#include <QDir>
#include <QByteArray>
#include <QMessageBox>
//MetroFile
bool MFile::Exists(QString file)
{
return QFile::exists(file);
}

void MFile::DownLoad(QString url,QString tofile)
{
    QProcess *qp = new QProcess;
    qp->start("wget",QStringList() << url << "-O" << tofile);
}

QString MFile::Read(QString file)
{
    QProcess *qp = new QProcess;
    qp->start("cat",QStringList() << file);
    if (!qp->waitForStarted())
      return "1";
    if (!qp->waitForFinished())
      return "2";
    QByteArray result = qp->readAll();
    return QString(result);
}

bool MFile::CreateDir(QString path)
{
    QDir dir; 
    return dir.mkpath(path);
}

int MFile::Remove(const QStringList& Files)
{
    QString filelist;
    QMessageBox msgBox;
    for (int i = 0; i < Files.size(); ++i)
    {
/*
      QString gate=Files.at(i);
      gate.replace( QString("\\"), QString("\\\\"));
      filelist=filelist+"\n'"+gate+"'";
*/
      filelist=filelist+"\n'"+Files.at(i)+"'";
    }
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(QString("!File Delete Confirm!"));
    msgBox.setText("Do you really want to delete the files "+filelist+" ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    int re = msgBox.exec();
    if(re==QMessageBox::Yes){
    QFile file;
    for (int i = 0; i < Files.size(); ++i)
      file.remove(Files.at(i));
    return 0;
    }else{
    return 1;
    }
}

bool MFile::CopyFile(QString from,QString to)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(QString("!File Copy Confirm!"));
    msgBox.setText("Do you really want to copy the file '"+from+"' to '"+to+"'?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    int re = msgBox.exec();
    if(re==QMessageBox::Yes){
     QFile file;
     return file.copy(from,to);
    }else{
     return false;
    }
}

bool MFile::Move(QString old,QString New,bool rename)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(QString("!File Rename Confirm!"));
    if(rename==true)
    msgBox.setText("Do you really want to rename the file '"+old+"' as '"+New+"'?");
    else
    msgBox.setText("Do you really want to move the file '"+old+"' to '"+New+"'?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    int re = msgBox.exec();
    if(re==QMessageBox::Yes){
     QFile file;
     return file.rename(old,New);
    }else{
     return false;
    }
}

void MFile::XdgOpen(QString path)
{
system((QString("xdg-open \"") + path + 
QString("\"")).toStdString().c_str());
}

QString MFile::List(QString where)
{
    QProcess *qp = new QProcess;
    QStringList Args;
    Args << where;
    qp->start("genFileList.sh",Args);
    if (!qp->waitForStarted())
      return "1";
    if (!qp->waitForFinished())
      return "2";
    QByteArray result = qp->readAll();
    return QString(result);
}


