#include "Grid.h"
#include "Utilities.h"
#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <Utilities.h>
using namespace std;

Grid::Grid(const int dimx, const int dimy): _nbCells(0)
{

	if(dimx > 0 && dimy > 0)
	{
		int i;

		_columns = dimx;
		_lines = dimy;
		_currentPopulation = (State**) malloc(sizeof(State*) * dimx);
		_nextPopulation = (State**) malloc(sizeof(State*) * dimx);

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

State Grid::getState(const int x, const int y)
{
	return _currentPopulation[x][y];
}

void Grid::setNextState(const int x, const int y, State state)
{
	_nextPopulation[x][y] = state;

}

void Grid::nextGeneration()
{
	_nbGenerations++;
	t_start;
	int nbTemp = 0;

#pragma omp parallel for
	for (int y = 0; y < getLines (); ++y)
	{
		for (int x = 0; x < getColumns (); ++x)
		{
			if (getState (x,y) == ALIVE) nbTemp++;
			int count = arroundCell (x,y);
			if ((count == 2 || count == 3) && getState (x,y) == ALIVE )
				setNextState (x,y, ALIVE);
			else if ( count == 3 && getState (x,y) == DEAD)
				setNextState (x,y, ALIVE);
			else
				setNextState (x,y, DEAD);
		}
	}

	_nbCells = nbTemp;

	t_end;
	swapGrid ();

	t_show;
}

int Grid::getColumns (){
	return _columns;
}

int Grid::getLines (){
	return _lines;
}

int Grid::getNbCellAlive (){
	return _nbCells;
}

int Grid::getNbCellDead (){
	return getColumns()*getLines()-_nbCells;
}

int Grid::getNbGenerations (){
	return _nbGenerations;
}

Grid::~Grid()
{
	if(_currentPopulation != NULL)
	{
		for(int i=0 ; i< getColumns (); i++)
			free(_currentPopulation[i]);
		free(_currentPopulation);
	}
	if(_nextPopulation != NULL)
	{
		for(int i=0 ; i< getColumns (); i++)
			free(_nextPopulation[i]);
		free(_nextPopulation);
	}
}

void Grid::swapGrid()
{
	swap (_currentPopulation, _nextPopulation);
}

short Grid::arroundCell(const int x, const int y)
{
	short n = 0;

	// not optimized version (borders)
	if(x <= 0 || y <= 0 || x >= _lines-1 || y >= getColumns ()-1)
	{
		for(short j = -1 ; j < 2 ; j++)
			if(j+y >= 0 && j+y < getLines ())
				for(short i = -1 ; i < 2 ; i++)
					if(i+x >= 0 && i+x < getColumns ())
						if((i != 0 || j != 0) && getState(i+x, j+y) == ALIVE)
							n++;
	}

	// optimized version
	else
	{
	if(getState(x-1, y-1) == ALIVE) n++;
		if(getState(x+0, y-1) == ALIVE) n++;
		if(getState(x+1, y-1) == ALIVE) n++;
		if(getState(x-1, y+0) == ALIVE) n++;
		if(getState(x+1, y+0) == ALIVE) n++;
		if(getState(x-1, y+1) == ALIVE) n++;
		if(getState(x+0, y+1) == ALIVE) n++;
		if(getState(x+1, y+1) == ALIVE) n++;
	}

	return n;
}

void Grid::generateRandomGrid(float probAlive)
{
	for (int y = 0; y < getLines (); ++y) {
		for (int x = 0; x < getColumns (); ++x) {
			float rand = getRand (0,1);
			setNextState (x,y,(rand > probAlive)? DEAD:ALIVE);
		}
	}
	_nbGenerations = 0;
	swapGrid ();
}

void Grid::fillGrid (State state){

	for (int y = 0; y < getLines (); ++y)
		for (int x = 0; x < getColumns (); ++x)
			setNextState (x,y, state);

	swapGrid();
}

void Grid::selectAlgo(Algo algo){
	_algoUsed = algo;
}
