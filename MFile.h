#ifndef MFILE_H
#define MFILE_H

#include <QObject>
#include <QString>

class MFile : public QObject
{
    Q_OBJECT
public slots:
    bool Exists(QString file);
    void DownLoad(QString url,QString tofile);
    QString Read(QString file);
    bool CreateDir(QString path);
    int Remove(const QStringList& Files);
//    int RemoveDirs(const QStringList& Files);
    bool CopyFile(QString from,QString to);
    bool Move(QString old,QString New,bool rename);
    void XdgOpen(QString path);
    QString List(QString where);
};

#endif
