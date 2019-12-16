#ifndef _COORD_H
#define _COORD_H

typedef struct Coord
{
    int row;
    int col;
}
Coord;

Coord* initCoord(int row, int col);
void freeCoord(Coord** coord);

void printCoord(Coord* coord);

Coord** initAllCoord(int height, int width);
void freeAllCoord(Coord*** all);

Coord* findCoord(Coord** coords, int row, int col);
Coord* deltaCoord(Coord** coords, Coord* coord, int drow, int dcol);

#endif
