#ifndef _MODULES_XDG_H
#define _MODULES_XDG_H

#include <QtCore>
#include <QPixmap>
#include <QObject>

class XdgModule: public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.subway.Cubway.Xdg")
    Q_PROPERTY(QVariantMap userDirs READ getUserDirs)
    Q_PROPERTY(QString themeName READ getThemeName WRITE setThemeName)
public:
    QVariantMap getUserDirs();
    QString getThemeName();
    void setThemeName(const QString &name);
    Q_INVOKABLE QPixmap getIcon(const QString &name, int width, int height);
};

#endif //_MODULES_XDG_H
