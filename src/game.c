#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

#include "game.h"
#include "world.h"
#include "grid.h"
#include "snake.h"
#include "cell.h"
#include "coord.h"

void snakeStart(World* w)
{
    int row = w->grid->height / 2;
    int col = w->grid->width / 2;

    Coord* pos = findCoord(w->coords, row, col);
    if (pos) setSnakeHead(w->snake, pos);
    else setSnakeHead(w->snake, w->coords[0]);  // default if pos returns NULL
    
    snakeHead(w);
    
    return;
}

void snakeHead(World* w)
{
    Cell* cell = findCell(w->grid->cells, w->snake->head);
    setSnake(cell, 1);
    return;
}

void moveHead(World* w)
{
    int dir = w->snake->direction;  // nsew = 1423

    if (dir == 1) setSnakeHead(w->snake, deltaCoord(w->coords, w->snake->head, -1, 0));
    else if (dir == 4) setSnakeHead(w->snake, deltaCoord(w->coords, w->snake->head, 1, 0));
    else if (dir == 2) setSnakeHead(w->snake, deltaCoord(w->coords, w->snake->head, 0, 1));
    else if (dir == 3) setSnakeHead(w->snake, deltaCoord(w->coords, w->snake->head, 0, -1));

    return;
}

int snakeDead(World* w)
{
    Cell* cell = findCell(w->grid->cells, w->snake->head);
    if (cell == NULL) return 1;
    if (cell->snake) return 1;
    return 0;
}

void incrementSnake(World* w)
{
    for(;*(w->grid->cells); ++w->grid->cells) addSnake(*(w->grid->cells));
    return;
}

void pruneSnake(World* w)
{
    Cell** cell;
    for(;*(w->grid->cells); ++w->grid->cells)
    {
        cell = &(*(w->grid->cells));
        if ((*cell)->snake > w->snake->length) (*cell)->snake = 0;
    }

    return;
}

void generateFood(World* w)
{
    Coord* pos = NULL;
    while(pos == NULL || !findCell(w->grid->cells, pos)->snake) pos = roll(w);

    w->food = findCell(w->grid->cells, pos);
    w->food->food = 1;
    return;
}

int foodCheck(World* w)
{
    if (w->snake->head == w->food->coord) return 1;
    else return 0;
}

void eatFood(World* w)
{
    w->food->food = 0;
    w->food = NULL;
    setSnakeLength(w->snake, w->snake->length + 1);
    return;
}

Coord* roll(World* w)
{
    int row = rand() % w->grid->height;
    int col = rand() % w->grid->width;

    return findCoord(w->coords, row, col);
}

int dirInput(World* w)
{
    int dir = w->snake->direction;
    int a;

    char c[2]= {singleInput(), 0};
    a = atoi(c);
    if (c[0] == 0) return dir;
    else if (a > 4 || a < 1) return dir;
    else if (a + dir == 5) return dir;
    else return a;

    return dir;
}

char singleInput(void)
{
    char c = getchar();
    if (c == 0 || c == '\n' || c == EOF || c == ' ') return 0;
    clear();
    return c;
}

void clear(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return;
}

void refresh(void)
{
    getchar();
    system("cls");
    return;
}

void game(World* w)
{
    snakeStart(w);

    loop(w);

    printf("You died.\n");
    refresh();

    return;
}

void loop(World* w)
{
    int alive = 1;

    while(alive)
    {
        generateFood(w);

        alive = gameplayLoop(w);
        if(!alive) break;

        eatFood(w);
    }

    return;
}

int gameplayLoop(World* w)
{
    while(1)
    {
        incrementSnake(w);
        pruneSnake(w);
        moveHead(w);
        if (snakeDead(w)) return 0;
        snakeHead(w);

        system("cls");
        frame(w);

        if (foodCheck(w)) return 1;
    }

    return 0;
}

void frame(World* w)
{
    printGrid(w->grid);


}

int cont(void)
{
    puts("Do you wish to continue? (Y/N)");
    char c = tolower(singleInput());
    system("cls");

    if (c == 'y') return 1;
    else if (c == 'n') return 0;
    else return cont();
}

void intro(void)
{
    system("cls");
    puts("Welcome to this game of Snake.");
    puts("I hope you enjoy!");
    puts("Play the game using the WASD keys.");
    refresh();
}

void outro(void)
{
    system("cls");
    puts("Thank you for playing!");
    refresh();
}
