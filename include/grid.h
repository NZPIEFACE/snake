#ifndef _GRID_H
#define _GRID_H

typedef struct Cell Cell;

typedef struct Grid
{
    int height;
    int width;

    Cell** cells;
}
Grid;

Grid* initGrid(Cell** cell, int height, int width);
void freeGrid(Grid** grid);

void printGridInfo(Grid* grid);
void printGrid(Grid* grid);

#endif
