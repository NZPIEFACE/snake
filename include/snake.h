#ifndef _SNAKE_H
#define _SNAKE_H

typedef struct Coord Coord;

typedef struct Snake
{
    int length;
    Coord* head;
    int direction;  // NSEW -> 1 4 2 3
}
Snake;

Snake* initSnake(Coord* coord);
void freeSnake(Snake** snake);

void setSnakeHead(Snake* snake, Coord* coord);
void setSnakeLength(Snake* snake, int length);
void setSnakeDir(Snake* snake, int direction);


#endif
