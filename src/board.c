// Game board
    // To make and change(?) game board.
// Date: 04/07/2020
// Author: NZPIEFACE

// Changelog:
/* 
*/

#include <stdlib.h>
#include "board.h"

Board * init_board(int row, int col){
    Board * board = malloc(sizeof(Board));
    board->row = row;
    board->col = col;

    board->grid = malloc(sizeof(char *) * row);

    for (int i = 0; i < row; i++){
        board->grid[i] = malloc(sizeof(char) * col);

        for (int j = 0; j < col; j++){
            board->grid[i][j] = 0;       // init as nothing
        }
    }

    return board;
}

void free_board(Board * board){
    for (int i = 0; i < board->row; i++){
        free(board->grid[i]);
    }

    free(board->grid);
    free(board);

    return;
}