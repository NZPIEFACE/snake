#include <stdlib.h>
#include <stdio.h>

#include "grid.h"
#include "cell.h"

Grid* initGrid(Cell** cell, int height, int width)
{
    Grid* grid = malloc(sizeof(Grid));

    grid->height = height;
    grid->width = width;

    grid->cells = cell;

    return grid;
}

void freeGrid(Grid** grid)
{
    (*grid)->cells = NULL;

    free(*grid);
    *grid = NULL;
}

void printGridInfo(Grid* grid)
{
    for (; *(grid->cells); ++(grid->cells)) printCellInfo(*(grid->cells));
}

void printGrid(Grid* grid)
{
    int h = grid->height;
    int w = grid->width;
    int index;
    int len = (w + 1) * 2;

    char* wall = malloc(sizeof(char) * len + 1);
    for (int i = 0; i < len; i++)
    {
        wall[i] = '#';
    }
    wall[len] = '\0';
    
    printf("%s\n", wall);

    for (int i = 0; i < h; i++)
    {
        printf("#");
        for (int j = 0; j < w; j++)
        {   
            index = i * w + j;
            printCell(grid->cells[index]);
        }
        printf("#\n");
    }

    printf("%s\n", wall);

    free(wall);

    return;
}