#include <QApplication>

#include "Mainwindow.h"
#include "Utilities.h"
#include "Grid.h"
#include <iostream>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    initRandomEngine();
    w.updateScene ();

    return a.exec();
}
