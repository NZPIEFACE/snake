#include <stdlib.h>

#include "world.h"

World* initWorld(Grid* grid, Snake* snake, Coord** coords)
{
    World* world = malloc(sizeof(World));

    world->grid = grid;
    world->snake = snake;
    world->coords = coords;
    world->food = NULL;

    return world;
}

void freeWorld(World** world)
{
    (*world)->grid = NULL;
    (*world)->snake = NULL;
    (*world)->coords = NULL;
    (*world)->food = NULL;

    free(*world);
    *world = NULL;

    return;
}