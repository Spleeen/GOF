#include "cell.h"
#include "Utilities.h"

Cell::Cell()
{
    _alive = (0 == rand()%2);
}

Cell::Cell(bool alive)
{
    _alive = alive;
}

bool Cell::isAlive()
{
    return _alive;
}
