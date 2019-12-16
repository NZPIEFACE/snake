#ifndef _SNAKE_H
#define _SNAKE_H

typedef struct Coord Coord;

typedef struct Snake
{
    int length;
    Coord* head;
}
Snake;

Snake* initSnake(Coord* coord);
void freeSnake(Snake** snake);

void setSnakeHead(Snake* snake, Coord* coord);
void setSnakeLength(Snake* snake, int length);

#endif
