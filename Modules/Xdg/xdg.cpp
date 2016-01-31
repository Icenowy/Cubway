#include <QVariantMap>
#include <qt5xdg/XdgDirs>
#include <qt5xdg/XdgIcon>
#include <qt5xdg/XdgDesktopFile>
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


QVariantMap XdgModule::loadDesktopFile(const QString &fileName){
  QVariantMap result;

  XdgDesktopFile desktop;
  desktop.load(fileName);
  switch(desktop.type()){
  case XdgDesktopFile::UnknownType:
    result["type"] = "unknown";
    break;
  case XdgDesktopFile::ApplicationType:
    result["type"] = "application";
    break;
  case XdgDesktopFile::LinkType:
    result["type"] = "link";
    break;
  case XdgDesktopFile::DirectoryType:
    result["type"] = "directory";
  }
  result["valid"] = desktop.isValid();
  result["categories"] = desktop.categories();
  result["icon"] = desktop.icon().pixmap(icon_size, icon_size);
  result["icon_name"] = desktop.iconName();
  result["name"] = desktop.name();
  result["comment"] = desktop.comment();
  QString url = desktop.url();
  QVariant exec = desktop.value("exec");
  if(!url.isEmpty())
    result["url"] = url;
  if(exec.isValid())
    result["exec"] = exec;
  return result;
}


int XdgModule::getIconSize(){
  return icon_size;
}


void XdgModule::setIconSize(int value){
  icon_size = value;
}


QPixmap XdgModule::getIcon(const QString &name){
  return XdgIcon::fromTheme(name).pixmap(icon_size, icon_size);
}


QString XdgModule::getThemeName(){
  return XdgIcon::themeName();
}


void XdgModule::setThemeName(const QString &name){
  XdgIcon::setThemeName(name);
}
