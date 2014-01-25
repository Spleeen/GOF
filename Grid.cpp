#include "Grid.h"
#include "Utilities.h"
#include <iostream>
#include <stdio.h>
#include <omp.h>
using namespace std;

Grid::Grid(const int dimx, const int dimy)
{

    if(dimx > 0 && dimy > 0)
    {
        int i;

        _columns = dimx;
        _lines = dimy;
        _currentPopulation = (State**)malloc(sizeof(State*) * dimx);
        _nextPopulation = (State**)malloc(sizeof(State*) * dimx);


        for(i=0 ; i<dimx ; i++){
            _currentPopulation[i] = (State*)calloc(dimy, sizeof(State));
            _nextPopulation[i] = (State*)calloc(dimy, sizeof(State));
        }
    }
    else
    {
        _columns = 0;
        _lines = 0;
        _currentPopulation = NULL;
        _nextPopulation = NULL;

    }
    _algoUsed = CONWAY;
}

inline State Grid::getState(const int x, const int y)
{
    return _currentPopulation[x][y];
}

inline void Grid::setNextState(const int x, const int y, State state)
{
    _nextPopulation[x][y] = state;
}

void Grid::nextGeneration()
{
    #pragma omp parallel for
    for (int y = 0; y < _lines; ++y)
    {
        for (int x = 0; x < _columns; ++x)
        {
            int count = arroundCell (x,y);
            if ((count == 2 || count == 3) && getState (x,y) == ALIVE )
                setNextState (x,y, ALIVE);
            else if ( count == 3 && getState (x,y) == DEAD)
                setNextState (x,y, ALIVE);
            else
                setNextState (x,y, DEAD);
        }
    }

    swapGrid ();
}


Grid::~Grid()
{

    if(_currentPopulation != NULL)
    {
        int i;

        for(i=0 ; i<_lines ; i++)
            free(_currentPopulation[i]);

        free(_currentPopulation);
    }
}

void Grid::swapGrid()
{

    State** vswap = _currentPopulation;
    _currentPopulation = _nextPopulation;
    _nextPopulation = vswap;
}

short Grid::arroundCell(const int x, const int y)
{
    short n = 0;

    for ( short i = -1 ; i < 2 ; i++ )
        for ( short j = -1 ; j < 2 ; j++ )
            if ( i+x >= 0 && i+x < _columns  )
                if ( j+y >= 0 && j+y < _lines  ){
                    if ( i == 0 && j == 0 )
                        continue ;
                    if ( _currentPopulation[i+x][j+y] == ALIVE)
                        n++ ;
                }

    return n;
}

void Grid::printMap() {

    for (int y = 0; y < _lines; ++y) {
        for (int x = 0; x < _columns; ++x){
            if (_currentPopulation[x][y] == ALIVE)
                cout << "*";
            else
                cout << " ";
        }
        cout <<endl;
    }
    cout <<endl;
}

void Grid::generateRandomGrid(float probAlive)
{
    for (int y = 0; y < _lines; ++y) {
        for (int x = 0; x < _columns; ++x) {
            float rand = getRand (0,1);
            setNextState (x,y,(rand < probAlive)? ALIVE:DEAD);
        }
    }
    swapGrid ();
}

void Grid::selectAlgo(Algo algo){
    _algoUsed = algo;
}
