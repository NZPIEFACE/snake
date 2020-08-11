// Game board
    // To make and change(?) game board.
// Date: 04/07/2020
// Author: NZPIEFACE

// Changelog:
/*  04/07/2020 - Created the board and init functions.
*/

typedef struct Board {
    char ** grid;
    int row;
    int col;
} Board;

Board * init_board(int row, int col);
void    free_board(Board * board);