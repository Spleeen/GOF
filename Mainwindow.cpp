#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include <iostream>
#include "Utilities.h"

using namespace std;
bool running = false;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	_ui(new Ui::MainWindow),
	_delay (this),
	_aliveColor(255, 255, 255),
	_deadColor(0,0,0),
	_render(1500, 1500, QImage::Format_Indexed8),
	_nbCellLabel (new QLabel("Nb de cellules en vie :")),
	_nbGenerationLabel (new QLabel("Nb de générations :"))
{
	_ui->setupUi(this);
	this->setWindowTitle("Simulation du jeu de la vie");
	this->setWindowIcon (QIcon(QString("./icon.icns")));

	_grid = new Grid (1500,1500);

	_render.setColor(ALIVE, _aliveColor.rgb ());
	_render.setColor(DEAD, _deadColor.rgb ());

	_grid->generateRandomGrid(_ui->randomDoubleSpin->value());

	_delay.setInterval(1);

	connect (_ui->startStopButton, SIGNAL(clicked()),this, SLOT(startStopAnimation()));
	connect (&_delay, SIGNAL(timeout()), this, SLOT(updateScene()));
	connect (_ui->speedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeDelay(int)));
	connect (_ui->reinitButton, SIGNAL(clicked()), this, SLOT(changeRandom()));
	connect (_ui->sceneGV, SIGNAL(), this, SLOT(lol()));

	updateScene ();
}


void MainWindow::updateScene(){

	for (int i = 0; i < _grid->getColumns (); ++i) {
		for (int j = 0; j < _grid->getLines (); ++j) {
			if (_grid->getState (i,j) == ALIVE)
				_render.setPixel (i,j,ALIVE);
			else
				_render.setPixel (i,j,DEAD);
		}
	}

	_monPixmap = QPixmap::fromImage(_render);

	_scene.clear ();
	_scene.addPixmap (_monPixmap);

	_ui->sceneGV->setScene (&_scene);

	_ui->statusBar->addWidget(_nbCellLabel);
	_ui->statusBar->addWidget(_nbGenerationLabel);
	_ui->sceneGV->show ();
	_grid->nextGeneration ();
	_nbCellLabel->setText("Nb de cellules en vie : " + QString::number(_grid->getNbCellAlive()));
	_nbGenerationLabel->setText("Nb de générations : " + QString::number(_grid->getNbGenerations ()));

}

void MainWindow::changeDelay (int newDelay){
	_delay.setInterval (991-(newDelay*10));

}

void MainWindow::startStopAnimation(){

	if (running){
		_delay.stop ();
		_ui->startStopButton->setText ("Démarrer la simulation");
		_ui->actionStartStop->setText ("Démarrer la simulation");
	}
	else {
		_delay.start ();
		_ui->startStopButton->setText ("Stopper la simulation");
		_ui->actionStartStop->setText ("Stopper la simulation");
	}
	running = !running;
}



void MainWindow::changeRandom(){

	_grid->generateRandomGrid(_ui->randomDoubleSpin->value());
	updateScene ();
}

MainWindow::~MainWindow()
{
	delete _ui;
}
