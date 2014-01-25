#include <QApplication>

#include "mainwindow.h"
#include "Utilities.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    initRandomEngine();
    return a.exec();
}
