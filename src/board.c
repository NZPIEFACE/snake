// Game board
    // To make and change(?) game board.
// Date: 04/07/2020
// Author: NZPIEFACE

// Changelog:
/* 
*/

#include <stdlib.h>
#include "board.h"
//#include "snake.h"    //snake.h is included in board.h

// Private functions/methods
void reset_board(Board * board);

Board * init_board(int row, int col){
    Board * board = malloc(sizeof(Board));

    board->row = row;
    board->col = col;
    board->snake = init_snake();

    // Init to NULL, change to something else if not null.
    board->moved_body = NULL;
    board->new_body = NULL;

    board->reset = &reset_board;

    board->grid = malloc(sizeof(char *) * row);

    // Initing character grid.
    for (int i = 0; i < board->row; i++){
        board->grid[i] = malloc(sizeof(char) * board->col);

        for (int j = 0; j < col; j++){
            board->grid[i][j] = 0;
        }
    }

    return board;
}

void free_board(Board * board){
    for (int i = 0; i < board->row; i++){
        free(board->grid[i]);
    }

    free(board->grid);
    free_snake(board->snake);
    free(board);

    return;
}

void reset_board(Board * board){
    for (int i = 0; i < board->row; i++){
        for (int j = 0; j < board->col; j++){
            board->grid[i][j] = 0;
        }
    }
    return;
}
