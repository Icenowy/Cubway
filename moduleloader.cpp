#include "moduleloader.h"
#include <QPluginLoader>

// Builtins 
#include "MFile.h"

QObject* ModuleLoader::LoadModule(QString name)
{
    if (name.endsWith(".js")) {
        return NULL;
    }
    if (isBuiltin(name)) {
        return getBuiltin(name);
    }
    QPluginLoader* pluginloader=new QPluginLoader(this);
    pluginloader->setLoadHints(QLibrary::ResolveAllSymbolsHint);
    pluginloader->setFileName(this->getModulePath(name));
    if (pluginloader->load()){
        return pluginloader->instance();
    } else {
        return NULL;
    }
}

QString ModuleLoader::getModulePath(QString mod)
{
    if (!_dirModule.exists(mod)) {
        if (QDir::current().exists(mod+".so")) {
            return QDir::current().filePath(mod+".so");
        } else {
            return NULL;
        }
    } else {
        QDir moddir(_dirModule.filePath(mod));
        if (!moddir.exists("lib"+mod+".so")) {
            return NULL;
        } else {
            return moddir.filePath("lib"+mod+".so");
        }
    }
}

bool ModuleLoader::isBuiltin(QString name)
{
    if (name=="MFile")
        return true;
    return false;
}

QObject* ModuleLoader::getBuiltin(QString name)
{
    if (name=="MFile")
        return new MFile();
    return NULL;
}
