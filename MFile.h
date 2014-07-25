#ifndef MFILE_H
#define MFILE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantMap>

class MFile : public QObject
{
    Q_OBJECT
public slots:
    bool Exists(QString file);
    QString Read(QString file);
    void XdgOpen(QString file);
    QStringList List(QString dir);
};

#endif
