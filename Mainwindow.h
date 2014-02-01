#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Grid.h"
#include "GraphicsScene.h"
#include <QTimer>
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    Grid _grid;
    GraphicsScene _scene;
    QTimer _delay;
    QColor _aliveColor;
    QColor _deadColor;
    QImage _render;

public slots :
    void updateScene();
    void changeDelay(int newDelay);
};

#endif // MAINWINDOW_H
