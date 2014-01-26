#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Grid.h"
#include "GraphicsScene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void updateScene();


    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    Grid _grid;
    GraphicsScene _scene;

public slots :
        void on_myButton_clicked();
};

#endif // MAINWINDOW_H
