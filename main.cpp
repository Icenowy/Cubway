#include <QtGui/QApplication>
#include <QtWebKit>
#include <QtGui/QDesktopWidget>
#include "metro.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Metro w;
    
    return a.exec();
}
