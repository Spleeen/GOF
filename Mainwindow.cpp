#include "Mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow), _grid (500,500), _scene()
{
    _ui->setupUi(this);

    _ui->graphicsView->setMinimumSize (502,502);
    _ui->graphicsView->setContentsMargins (QMargins());

    _grid.generateRandomGrid (0.5);

    _ui->pushButton->setObjectName("myButton");
   QMetaObject::connectSlotsByName(this);
}


void MainWindow::updateScene(){

        QImage image(500, 500, QImage::Format_Indexed8);
        QRgb noir = qRgb(0, 0, 0); // 0xff7aa327
        QRgb blanc = qRgb(255, 255, 255); // 0xff7aa327

        image.setColor(0, noir);
        image.setColor(1, blanc);

        for (int i = 0; i < _grid.getColumns (); ++i) {
            for (int j = 0; j < _grid.getLines (); ++j) {
                if (_grid.getState (i,j) == ALIVE)
                    image.setPixel (i,j,0);
                else
                    image.setPixel (i,j,1);
            }
        }

        QPixmap monPixmap;
        monPixmap = QPixmap::fromImage(image);

        _scene.addPixmap (monPixmap);

        _ui->graphicsView->setScene (&_scene);

        _ui->graphicsView->show ();
        _grid.nextGeneration ();

}

void MainWindow::on_myButton_clicked(){

    updateScene ();
}

MainWindow::~MainWindow()
{
    delete _ui;
}
