#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include <iostream>
#include "Utilities.h"

#define ALIVE_COLOR 0
#define DEAD_COLOR 1

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	_ui(new Ui::MainWindow),
	_delay (this),
	_aliveColor(255, 255, 255),
	_deadColor(0,0,0),
	_render(4000, 4000, QImage::Format_Indexed8),
	_nbCellLabel (new QLabel("Nb de cellules en vie :"))
{
	_ui->setupUi(this);
	this->setWindowTitle("Simulation du jeu de la vie");

	_grid = new Grid (4000,4000),

	_render.setColor(ALIVE_COLOR, _aliveColor.rgb ());
	_render.setColor(DEAD_COLOR, _deadColor.rgb ());

	_grid->generateRandomGrid(_ui->randomDoubleSpin->value());

	_delay.setInterval(1);

	connect (_ui->startButton, SIGNAL(clicked()),this, SLOT(startAnimation()));
	connect (_ui->stopButton, SIGNAL(clicked()), this, SLOT(stopAnimation()));
	connect (&_delay, SIGNAL(timeout()), this, SLOT(updateScene()));
	connect (_ui->speedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeDelay(int)));
	connect (_ui->reinitButton, SIGNAL(clicked()), this, SLOT(changeRandom()));
	connect (_ui->sceneGV, SIGNAL(), this, SLOT(lol()));

}


void MainWindow::updateScene(){

	for (int i = 0; i < _grid->getColumns (); ++i) {
		for (int j = 0; j < _grid->getLines (); ++j) {
			if (_grid->getState (i,j) == ALIVE)
				_render.setPixel (i,j,ALIVE_COLOR);
			else
				_render.setPixel (i,j,DEAD_COLOR);
		}
	}

	_monPixmap = QPixmap::fromImage(_render);

	_scene.clear ();
	_scene.addPixmap (_monPixmap);

	_ui->sceneGV->setScene (&_scene);

	_ui->statusBar->addWidget(_nbCellLabel);
	_ui->sceneGV->show ();
	_grid->nextGeneration ();
	_nbCellLabel->setText("Nb de cellules en vie : " + QString::number(_grid->getNbCellAlive()));
}

void MainWindow::changeDelay (int newDelay){
	_delay.setInterval (991-(newDelay*10));

}

void MainWindow::startAnimation(){

	_delay.start ();
	_ui->startButton->setEnabled (false);
	_ui->actionD_marrer_la_simulation->setEnabled(false);
	_ui->stopButton->setEnabled (true);
	_ui->actionStopper_la_simulation->setEnabled(true);
}

void MainWindow::stopAnimation(){

	_delay.stop ();
	_ui->startButton->setEnabled (true);
	_ui->actionD_marrer_la_simulation->setEnabled(true);
	_ui->stopButton->setEnabled (false);
	_ui->actionStopper_la_simulation->setEnabled(false);

}

void MainWindow::changeRandom(){

	_grid->generateRandomGrid(_ui->randomDoubleSpin->value());
}

MainWindow::~MainWindow()
{
	delete _ui;
}

