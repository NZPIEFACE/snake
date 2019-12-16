#ifndef _CELL_H
#define _CELL_H

typedef struct Coord Coord;

typedef struct Cell 
{
    Coord* coord;

    int snake;
    int food;
}
Cell;

Cell* initCell(Coord* coord);
void freeCell(Cell** cell);

void setSnake(Cell* cell, int snake);
void resetSnake(Cell* cell);
void addSnake(Cell* cell);
void setFood(Cell* cell, int food);
void resetFood(Cell* cell);

void printCellInfo(Cell* cell);
void printCell(Cell* cell);

Cell** initAllCell(Coord** coord, int height, int width);
void freeAllCell(Cell*** all);

Cell* findCell(Cell** cells, Coord* coord);

#endif
