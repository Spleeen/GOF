#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Grid.h"
#include "GOFScene.h"
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
    Ui::MainWindow* _ui;
    Grid* _grid;
    QTimer _delay;
    QColor _aliveColor;
    QColor _deadColor;
    GOFScene _scene;
    QImage _render;
    QPixmap _monPixmap;

public slots :
    void updateScene();
    void startAnimation();
    void stopAnimation();
    void changeRandom();
    void changeDelay(int newDelay);
};

#endif // MAINWINDOW_H
