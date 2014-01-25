#ifndef CELL_H
#define CELL_H

class Cell
{
    bool _alive;
public:
    /* Random cell */
    Cell();
    Cell(bool alive);
    bool isAlive();
};

#endif // CELL_H
