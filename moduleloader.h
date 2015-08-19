#ifndef MODULELOADER_H
#define MODULELOADER_H

#include <QObject>
#include <QDir>
#include <QString>
#include <QHash>

class ModuleLoader : public QObject
{
    Q_OBJECT
public:
    ModuleLoader()
      : _dirModule(QDir::current().filePath("Modules"))
    {}
    Q_INVOKABLE QObject* load(QString name);
private:
    QHash<QString, QObject *> m_builtin;
    QDir _dirModule;
    QString getModulePath(QString name);
    bool isBuiltin(QString name);
    QObject* getBuiltin(QString name);
};


#endif
