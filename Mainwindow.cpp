#include "Mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow), _grid (200,200), _scene()
{
    _ui->setupUi(this);

    _ui->graphicsView->setFixedSize (200,200);
    _ui->graphicsView->setScene (&_scene);

   // _grid.generateRandomGrid (0.5);

    _ui->graphicsView->show ();

}

void MainWindow::updateScene(){

    while (1){
    }
}

MainWindow::~MainWindow()
{
    delete _ui;
}
