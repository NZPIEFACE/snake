#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#include "main.h"
#include "cell.h"
#include "coord.h"
#include "grid.h"
#include "snake.h"
#include "world.h"
#include "game.h"

#define DEFAULT 10

int main(int argc, char* argv[])
{
    system("cls");
    srand(time(0));

    intro();

    int height = DEFAULT;
    int width = DEFAULT;

    height_width(argc, argv, &height, &width);
    
    Coord** coords = initAllCoord(height, width);
    Cell** cells = initAllCell(coords, height, width);
    Grid* grid = initGrid(cells, height, width);
    Snake* snake = initSnake(coords[0]);
    World* world = initWorld(grid, snake, coords);

    int a = 1;
    while(a)
    {
        game(world);
        a = cont();
    }
    
    outro();
    
    freeWorld(&world);
    freeSnake(&snake);
    freeGrid(&grid);
    freeAllCell(&cells);
    freeAllCoord(&coords);

    return 0;
}

void height_width(int argc, char* argv[], int* height, int* width)
{
    int h_flag = 1;
    int w_flag = 1;

    if (argc != 1)
    {
        if (atoi(argv[1]))
        {
            *height = atoi(argv[1]);
            h_flag = 0;
        }
        
        if (atoi(argv[2]))
        {
            *width = atoi(argv[2]);
            w_flag = 0;
            return;
        }
    }

    if (h_flag) *height = read_int_input("height");

    if (w_flag) *width = read_int_input("width");

    return;
}

int read_int_input(char* prompt)
{
    int a;
    char str[10];           // size 10 for buffer
    char* pos;

    printf("What is the %s?\n", prompt);
    fgets(str, 5, stdin);     // 5 for 3 digit number, needs \n and \0
    
    pos = strchr(str, '\n');
    a = atoi(str);

    if (pos == NULL) clear();
    system("cls");

    if (&str[0] == pos)
    {
        return DEFAULT;
    }
    else if (pos != NULL && a)
    {
        return a;
    }
    else
    {
        printf("Please use a valid input.\n");
        return read_int_input(prompt);
    }
}