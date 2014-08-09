#include <QApplication>
#include <QDesktopWidget>

#include <QWebInspector>

#include "metro.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Metro w;
    return a.exec();
}
