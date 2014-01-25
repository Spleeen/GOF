#ifndef GRID_H
#define GRID_H
#include "cell.h"

class Grid
{
private:

    Cell** _grid;
    int w, h;
public:

    Grid(const int wx, const int hx);

    bool getState();
    void updateState();

    ~Grid();
};

#endif // GRID_H
