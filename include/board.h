// Game board
    // To make and change(?) game board.
// Date: 04/07/2020
// Author: NZPIEFACE

// Changelog:
/*  04/07/2020 - Created the board and init functions.
    12/08/2020 - Added header guards.
               - Added the snake object
*/

#ifndef BOARD_H
#define BOARD_H

#include "snake.h"

typedef struct Board {
    char ** grid;
    int row;
    int col;
    Snake * snake;

    SnakeBody * moved_body;
    SnakeBody * new_body;

    void (* reset)(Board *);
} Board;

Board * init_board(int row, int col);
void    free_board(Board * board);

#endif