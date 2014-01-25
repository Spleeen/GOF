#include "grid.h"

using namespace std;

Grid::Grid(const int wx, const int hx)
{

    if(h > 0 && h > 0)
    {
        int i;

        w = wx;
        h = hx;
        _grid = (int**)malloc(sizeof(Cell*) * hx);

        for(i=0 ; i<hx ; i++)
            _grid[i] = (int*)calloc(wx, sizeof(Cell));
    }
    else
    {
        w = 0;
        h = 0;
        _grid = NULL;
    }
}


Grid::~Grid()
{

    if(_grid != NULL)
    {
        int i;

        for(i=0 ; i<hx ; i++)
            free(_grid[i]);

        free(_grid);
    }
}
