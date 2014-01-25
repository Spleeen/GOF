#include <QApplication>

#include "mainwindow.h"
#include "Utilities.h"
#include "Grid.h"
#include <iostream>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    initRandomEngine();

    Grid grid (30,30);

    grid.generateRandomGrid (0.5);

    t_start;
    for (int var = 0; var < 1000; ++var) {
        grid.nextGeneration ();
        grid.printMap ();
        Sleep(100);
    }
    t_end;

    t_show;
    //return a.exec();
    return EXIT_SUCCESS;
}
