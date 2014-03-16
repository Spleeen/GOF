#ifndef GRID_H
#define GRID_H

typedef enum {DEAD=false,ALIVE=true} State;

class Grid
{
private:

	typedef enum Algo {
		CONWAY
	} Algo;

	State** _currentPopulation;
	State** _nextPopulation;
	Algo _algoUsed;
	int _columns, _lines;
    int _nbCells;
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

	void fillGrid (State state);

	~Grid();

private:
	void swapGrid();
	short arroundCell(const int x, const int y);

};

#endif // GRID_H
