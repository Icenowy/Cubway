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
    Q_PROPERTY(int iconSize READ getIconSize WRITE setIconSize)
public:
    QVariantMap getUserDirs();
    Q_INVOKABLE QVariantMap loadDesktopFile(const QString &fileName);
    QString getThemeName();
    void setThemeName(const QString &name);
    int icon_size = 16;
    int getIconSize();
    void setIconSize(int value);
    Q_INVOKABLE QPixmap getIcon(const QString &name);
};


#endif //_MODULES_XDG_H
