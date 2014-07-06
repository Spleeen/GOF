#include "Grid.h"
#include "Utilities.h"
#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <Utilities.h>
#include <String>
using namespace std;

string LIB = "OPENMP";
#define N_THREADS 8

typedef struct Portion_grid {
	int borne_a;
	int borne_b;
	int nbCols;
	Grid* grid;
	int nbTemp;
} Portion_grid;

 void* grid_compute_thread (void* t) {   

	Portion_grid* portion = (Portion_grid*)t;

	for (int y = portion->borne_a; y < portion->borne_b; ++y)
	{
		for (int x = 0; x < portion->nbCols; ++x)
		{
			if (portion->grid->getState (x,y) == ALIVE) portion->nbTemp++;
			int count = portion->grid->arroundCell (x,y);
			if ((count == 2 || count == 3) && portion->grid->getState (x,y) == ALIVE )
				portion->grid->setNextState (x,y, ALIVE);
			else if ( count == 3 && portion->grid->getState (x,y) == DEAD)
				portion->grid->setNextState (x,y, ALIVE);
			else
				portion->grid->setNextState (x,y, DEAD);
		}
	}
        
	return NULL;
}

Grid::Grid(const int dimx, const int dimy): _nbCells(0)
{

	if(dimx > 0 && dimy > 0)
	{
		_columns = dimx;
		_lines = dimy;
		_previousPopulation = new Population(dimx, dimy);
		_currentPopulation = new Population(dimx, dimy);
		_nextPopulation = new Population(dimx, dimy);
	}
	else
	{
		_columns = 0;
		_lines = 0;
		_previousPopulation = NULL;
		_currentPopulation = NULL;
		_nextPopulation = NULL;

	}
	_algoUsed = CONWAY;
}

State Grid::getState(const int x, const int y)
{
	return _currentPopulation->at(x,y);
}

void Grid::setNextState(const int x, const int y, State state)
{
	_nextPopulation->set(x,y, state);
}

void Grid::nextGeneration()
{
	_nbGenerations++;
	_nbCells = 0;

	if (LIB == "OPENMP")
	{

		#ifdef _OPENMP
			#pragma omp parallel
			{
				int nbTemp =  0;

				#pragma omp for
				for (int y = 0; y < getLines (); ++y)
				{
					for (int x = 0; x < getColumns (); ++x)
					{
						if (getState (x,y) == ALIVE){
							nbTemp++;
						}
						int count = arroundCell (x,y);
						if ((count == 2 || count == 3) && getState (x,y) == ALIVE )
							setNextState (x,y, ALIVE);
						else if ( count == 3 && getState (x,y) == DEAD)
							setNextState (x,y, ALIVE);
						else
							setNextState (x,y, DEAD);
					}
				}

				#pragma omp atomic
				_nbCells += nbTemp;
			}
		#endif //_OPENMP
	}
	else {
		int nbTemp = 0;
		pthread_t threads [N_THREADS];
		Portion_grid portion[N_THREADS];

		//Lancement des threads
		for (int j=0; j<N_THREADS; ++j){
			//Obligation de réserver pour chacun des threads une variable de type struct. Sinon, elle pointerait sur la même variable en mémoire.
			Portion_grid tmp = {getLines ()*j / N_THREADS, getLines ()*(j + 1) / N_THREADS, getColumns (), this, nbTemp};
			portion[j] = tmp;

			if (pthread_create (&threads[j], NULL, grid_compute_thread, (void*)&portion[j]) != 0){
				perror ("Erreur dans la création du thread\n");
				exit(EXIT_FAILURE);
			}
		}

		//Attente du résultat
		for (int j=0; j<N_THREADS; ++j){
			pthread_join (threads[j],NULL);
			nbTemp += portion[j].nbTemp;
		}

		_nbCells = nbTemp;
	}

	swapGrid ();
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
	if(_previousPopulation != NULL)
		delete _nextPopulation;

	if(_currentPopulation != NULL)
		delete _currentPopulation;

	if(_nextPopulation != NULL)
		delete _nextPopulation;
}

void Grid::swapGrid()
{
	swap (_currentPopulation, _nextPopulation);
	swap (_previousPopulation, _nextPopulation);
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
