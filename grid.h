#ifndef GRID_H
#define GRID_H

typedef enum {DEAD=false,ALIVE=true} State;

class Grid
{
private:

    State** _currentPopulation;
    State** _nextPopulation;

    int _columns, _lines;
public:

    //Grille sans vie
    Grid(const int wx, const int hx);

    State getState(const int x, const int y);
    void setNextState(const int x, const int y, State state);

    //Avec les règles classiques du jeu de la vie de Conway
    void nextGeneration();
    void generateRandomGrid(float probAlive);

    void printMap();

    ~Grid();

private:
    void swapGrid();
    short arroundCell(const int x, const int y);

};

#endif // GRID_H
