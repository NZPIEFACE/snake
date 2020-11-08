// Game board
    // To make and change(?) game board.
// Date: 04/07/2020
// Author: NZPIEFACE

// Changelog:
/*  04/07/2020 - Created the board and init functions.
    12/08/2020 - Added header guards.
               - Added the snake object
    14/08/2020 - Food was added.
*/

#ifndef _BOARD_H
#define _BOARD_H

#include "snake.h"
//#include "coord.h"    //coord.h i in snake.h

typedef struct Board Board;

typedef struct Board {
    char ** grid;
    int row;
    int col;
    Snake * snake;
    Coord food;

    SnakeBody * moved_body;
    SnakeBody * new_body;

    void (* reset)(Board *);
} Board;

Board * init_board(int row, int col);
void    free_board(Board * board);

#endif