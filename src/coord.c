#include <stdio.h>
#include <stdlib.h>

#include "coord.h"

Coord* initCoord(int row, int col)
{
    Coord* coord = malloc(sizeof(Coord));
    coord->row = row;
    coord->col = col;
    return coord;
}

void freeCoord(Coord** coord)
{
    free(*coord);
    *coord = NULL;
    return;
}

void printCoord(Coord* coord)
{
    printf("Row: %10d, ", coord->row);
    printf("Col: %10d\n", coord->col);
    return;
}

Coord** initAllCoord(int height, int width)
{
    Coord** all = malloc(sizeof(Coord*) * height * width);
    int index;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            index = i * width + j;
            all[index] = initCoord(i, j);
        }
    }

    return all;
}

void freeAllCoord(Coord*** all)
{
    for (; *all; ++all) freeCoord(*all);
    all = NULL;
    return;
}

Coord* findCoord(Coord** coords, int row, int col)
{
    for (; *coords; ++coords)
        if ((*coords)->row == row && (*coords)->col == col)
            return *coords;

    return NULL;
}

Coord* deltaCoord(Coord** coords, Coord* coord, int drow, int dcol)
{
    int row = coord->row + drow;
    int col = coord->col + dcol;
    return findCoord(coords, row, col);
}
