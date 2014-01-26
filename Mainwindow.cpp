#include "Mainwindow.h"
#include "GraphicsScene.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GraphicsScene scene;

    ui->graphicsView->setScene (&scene);
    ui->graphicsView->show ();
}

MainWindow::~MainWindow()
{
    delete ui;
}
