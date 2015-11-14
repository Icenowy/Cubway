#include <QVariantMap>
#include <qt5xdg/XdgDirs>
#include <qt5xdg/XdgIcon>
#include "xdg.h"


QVariantMap XdgModule::getUserDirs(){
  QVariantMap result;
  
  result["desktop"] = XdgDirs::userDir(XdgDirs::Desktop);
  result["download"] = XdgDirs::userDir(XdgDirs::Download);
  result["templates"] = XdgDirs::userDir(XdgDirs::Templates);
  result["publicShare"] = XdgDirs::userDir(XdgDirs::PublicShare);
  result["documents"] = XdgDirs::userDir(XdgDirs::Documents);
  result["music"] = XdgDirs::userDir(XdgDirs::Music);
  result["pictures"] = XdgDirs::userDir(XdgDirs::Pictures);
  result["videos"] = XdgDirs::userDir(XdgDirs::Videos);

  result["data"] = XdgDirs::dataHome();
  result["config"] = XdgDirs::configHome();
  result["cache"] = XdgDirs::cacheHome();
  result["autostart"] = XdgDirs::autostartHome();

  return result;
}


QPixmap XdgModule::getIcon(const QString &name, int width, int height){
  return XdgIcon::fromTheme(name).pixmap(width, height);
}


QString XdgModule::getThemeName(){
  return XdgIcon::themeName();
}


void XdgModule::setThemeName(const QString &name){
  XdgIcon::setThemeName(name);
}
