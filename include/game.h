// Game object
// Date: 12/08/2020
// Author: NZPIEFACE

// Changelog:
/*  12/08/2020 - Made the Game object
*/

#include "board.h"
#include "snake.h"

typedef struct Game {
    Board * board;

} Game;

Game *  init_game(int row, int col);
void    gree_game(Game * board);