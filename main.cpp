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

	initRandomEngine();

    w.show();
    return a.exec();

}
