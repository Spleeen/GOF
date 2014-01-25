#include "cell.h"
#include "Utilities.h"

Cell::Cell()
{
    _alive = (0 == rand(0,2));
}

Cell::Cell(bool alive)
{
    _alive = alive;
}

const bool Cell::isAlive()
{
    return _alive;
}
