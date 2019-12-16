#include <stdlib.h>
#include <stdio.h>

#include "cell.h"
#include "coord.h"

Cell* initCell(Coord* coord)
{
    Cell* cell = malloc(sizeof(Cell));

    cell->coord = coord;

    cell->snake = 0;
    cell->food = 0;

    return cell;
}

void freeCell(Cell** cell)
{
    (*cell)->coord = NULL;

    free(*cell);
    *cell = NULL;

    return;
}

void setSnake(Cell* cell, int snake)
{
    cell->snake = snake;
    return;
}

void addSnake(Cell* cell)
{
    cell->snake += 1;
    return;
}

void resetSnake(Cell* cell)
{
    cell->snake = 0;
    return;
}

void setFood(Cell* cell, int food)
{
    cell->food = food;
    return;
}

void resetFood(Cell* cell)
{
    cell->food = 0;
    return;
}

void printCellInfo(Cell* cell)
{
    printCoord(cell->coord);
    printf("Snake: %8d\n", cell->snake);
    printf("Food: %9d\n", cell->food);

    return;
}

void printCell(Cell* cell)
{
    if (cell->snake)
    {
        printf("\033[47m"); // white
        printf("\033[47;1m");
    }
    else if (cell->food)
    {
        printf("\033[41m"); // red
        printf("\033[41;1m");
    }

    printf("  ");

    printf("\033[0m");
    
}

Cell** initAllCell(Coord** coord, int height, int width)
{
    Cell** all = malloc(sizeof(Cell*) * height * width);
    int index;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            index = i * width + j;
            all[index] = initCell(coord[index]);
        }
    }

    return all;
}

void freeAllCell(Cell*** all)
{
    for (; *all; ++all) freeCell(*all);
    all = NULL;
    return;
}

Cell* findCell(Cell** c, Coord* coord)
{
    for (; *c; ++c) if ((*c)->coord == coord) return *c;
    return NULL;
}
