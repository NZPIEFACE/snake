#ifndef _WORLD_H
#define _WORLD_H

typedef struct Grid Grid;
typedef struct Snake Snake;

typedef struct World
{
    Grid* grid;
    Snake* snake;

}
World;

World* initWorld(Grid* grid, Snake* snake);
void freeWorld(World** world);

#endif
