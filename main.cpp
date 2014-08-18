#include <QApplication>
#include <QDesktopWidget>

#include <QWebInspector>

#include "Controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Subway::Cubway::Controller w;
    return a.exec();
}
