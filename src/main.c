#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "board.h"
#include "render.h"

int main(void){
    srand(time(0));

    Board * board = init_board(5, 5);

    board->apply_to_grid(board);
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = (1/10) * 1000000000;
    for(;;){
        nanosleep(&ts, NULL);
        render(board->display_grid, 5, 5);
    }

    free_board(board);
    return 0;
}