#include <stdlib.h>

#include "snake.h"

Snake* initSnake(Coord* coord)
{
    Snake* snake = malloc(sizeof(Snake));

    snake->length = 1;
    snake->head = coord;

    return snake;
}

void freeSnake(Snake** snake)
{
    (*snake)->head = NULL;

    free(*snake);
    *snake = NULL;

    return;
}

void setSnakeHead(Snake* snake, Coord* coord)
{
    snake->head = coord;
    return;
}

void setSnakeLength(Snake* snake, int length)
{
    snake->length = length;
    return;
}