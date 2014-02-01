#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _grid (4000,4000),
    _scene(), _delay (this),
    _aliveColor(255, 0, 0),
    _deadColor(0,0,0),
    _render(4000, 4000, QImage::Format_Indexed8)

{
    _ui->setupUi(this);

    _ui->graphicsView->setMinimumSize (802,502);

    _render.setColor(0, _aliveColor.rgb ());
    _render.setColor(1, _deadColor.rgb ());

    _grid.generateRandomGrid (0.9);

    _delay.setInterval(0);

    connect (_ui->pushButton, SIGNAL(clicked()),&_delay, SLOT(start()));
    connect (_ui->pushButton_2, SIGNAL(clicked()), &_delay, SLOT(stop()));
    connect(&_delay, SIGNAL(timeout()), this, SLOT(updateScene()));
    connect (_ui->speedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeDelay(int)));
}


void MainWindow::updateScene(){


    for (int i = 0; i < _grid.getColumns (); ++i) {
        for (int j = 0; j < _grid.getLines (); ++j) {
            if (_grid.getState (i,j) == ALIVE)
                _render.setPixel (i,j,0);
            else
                _render.setPixel (i,j,1);
        }
    }

    QPixmap monPixmap;
    monPixmap = QPixmap::fromImage(_render);

    _scene.addPixmap (monPixmap);

    _ui->graphicsView->setScene (&_scene);
    _ui->graphicsView->show ();
    _grid.nextGeneration ();


}

void MainWindow::changeDelay (int newDelay){
    _delay.setInterval (991-(newDelay*10));

}

MainWindow::~MainWindow()
{
    delete _ui;
}
