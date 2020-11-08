// Game board
    // To make and change(?) game board.
// Date: 14/08/2020
// Author: NZPIEFACE

// Changelog:
/* 14/08/2020 - Food was added.
*/

#include <stdlib.h>
#include "board.h"
//#include "snake.h"    //snake.h is included in board.h

#define DEFAULT_FOOD {2, 2}

// Private functions/methods
void reset_board(Board * board);
Coord spawn_food(Board * board);
void write_to_grid(Board * board, Coord coord, char c);

Board * init_board(int row, int col){
    Board * board = malloc(sizeof(Board));

    board->row = row;
    board->col = col;
    board->snake = init_snake();

    Coord food = DEFAULT_FOOD;
    board->food = food;

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

Coord spawn_food(Board * board){
    return;
}

void write_to_grid(Board * board, Coord coord, char c){
    board->grid[coord.x][coord.y] = c;
    return;
}