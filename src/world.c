#include <stdlib.h>

#include "world.h"

World* initWorld(Grid* grid, Snake* snake)
{
    World* world = malloc(sizeof(World));

    world->grid = grid;
    world->snake = snake;

    return world;
}

void freeWorld(World** world)
{
    (*world)->grid = NULL;
    (*world)->snake = NULL;

    free(*world);
    *world = NULL;

    return;
}