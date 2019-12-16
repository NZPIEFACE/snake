#ifndef _WORLD_H
#define _WORLD_H

typedef struct Grid Grid;
typedef struct Snake Snake;
typedef struct Cell Cell;
typedef struct Coord Coord;

typedef struct World
{
    Grid* grid;
    Snake* snake;
    Cell* food;    // initialized to NULL
    Coord** coords;
}
World;

World* initWorld(Grid* grid, Snake* snake, Coord** coords);
void freeWorld(World** world);

#endif
