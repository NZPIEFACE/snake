#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "main.h"
#include "cell.h"
#include "coord.h"
#include "grid.h"
#include "snake.h"
#include "world.h"

int main(int argc, char* argv[])
{
    system("cls");

    int height = 10;
    int width = 10;

    if (argc != 1)
    {
        if (atoi(argv[1]))
        {
            height = atoi(argv[1]);
        }
        
        if (atoi(argv[2]))
        {
            width = atoi(argv[2]);
        }
    }
    
    Coord** coords = initAllCoord(height, width);
    Cell** cells = initAllCell(coords, height, width);
    Grid* grid = initGrid(cells, height, width);
    Snake* snake = initSnake(coords[0]);
    World* world = initWorld(grid, snake);
    
    setSnake(world->grid->cells[0], 1);
    printGrid(world->grid);

    refresh();

    
    freeWorld(&world);
    freeSnake(&snake);
    freeGrid(&grid);
    freeAllCell(&cells, height, width);
    freeAllCoord(&coords, height, width);

    return 0;
}

void refresh(void)
{
    getch();
    system("cls");
    return;
}