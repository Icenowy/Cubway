#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantMap>

class FileSystem : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE bool exists(QString file);
    Q_INVOKABLE bool isDir(QString file);
    Q_INVOKABLE QString read(QString file);
    Q_INVOKABLE QStringList list(QString dir);
};

#endif
