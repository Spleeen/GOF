#ifndef GRID_H
#define GRID_H

#include "Matrix.h"

typedef char State;
typedef Matrix<State> Population;
#define ALIVE 0
#define DEAD 1

class Grid
{
private:

	typedef enum Algo {
		CONWAY
	} Algo;
	Population* _previousPopulation;
    Population* _currentPopulation;
    Population* _nextPopulation;
	Algo _algoUsed;
	int _columns, _lines;
	int _nbCells;
	int _nbGenerations;
public:


	//Grille sans vie
	Grid(const int wx, const int hx);

    State getState(const int x, const int y);
	void setNextState(const int x, const int y, State state);

	//Avec les règles classiques du jeu de la vie de Conway
	void nextGeneration();
	void generateRandomGrid(float probAlive);

	void selectAlgo(Algo algo);
	void printMap();

    int getColumns();
    int getLines ();
    int getNbCellAlive ();
	int getNbCellDead ();
	int getNbGenerations();


	void fillGrid (State state);
	short arroundCell(const int x, const int y);

	~Grid();

private:
	void swapGrid();

};

#endif // GRID_H
