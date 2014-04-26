#ifndef MODULELOADER_H
#define MODULELOADER_H

#include <QObject>
#include <QDir>
#include <QString>

class ModuleLoader : public QObject
{
    Q_OBJECT
public:
    ModuleLoader()
      : _dirModule(QDir::current().filePath("Modules"))
    {}
    Q_INVOKABLE QObject* LoadModule(QString name);
private:
    QDir _dirModule;
    QString getModulePath(QString name);
    bool isBuiltin(QString name);
    QObject* getBuiltin(QString name);
};


#endif
