#include "GraphicsScene.h"
#include <iostream>

GraphicsScene::GraphicsScene(QGraphicsScene *parent) :
    QGraphicsScene(parent)
{

    QRect rectangle(10, 10, 100, 100);
    std::cout <<"lol";
    QPen pen(Qt::blue, 1, Qt::SolidLine);
    std::cout <<"lol";
    setBackgroundBrush(Qt::white);
    parent->addRect (rectangle,pen);
}
