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
    bool exists(QString file);
    QString read(QString file);
    QStringList list(QString dir);
};

#endif
