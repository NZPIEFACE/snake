// main.c, everything I need will go here
    /* 
    */
// Date: 27/09/2020
// Author: NZPIEFACE

// Changelog:
/*  11/11/2020 - Added turn logic.      
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "board.h"
#include "render.h"

int turn_logic(Board * board);
void wait_fz(int hertz);

int main(void){
    // Initialise the game
    srand(time(0));
    Board * board = init_board(10, 10);
    // input_init();
    // press any key to start

    int playing = 1;
    while (playing){
        playing = turn_logic(board);
        wait_fz(15);
    }

    // Clean-up.
    // Freeze screen. Press any key to continue.
    // input_de_init()
    free_board(board);
    return 0;
}

int turn_logic(Board * board){
    // Read input (will do on input branch.)
    Coord input = DOWN;       // Default
    Coord error_case = {-1, -1};
    Coord origin = {0, 0};
    Coord end = {board->row - 1, board->col - 1}; // Need -1 'cause 0 indexing.

    if (coord_eqs(input, error_case)){ // player pressed ESC or game ended.
        return 0;
    }

    // Calculate snake move
    board->snake->direction = input;
    Coord snake_move = board->snake->next_position(board->snake);

    if (coord_eqs(board->snake->next_position(board->snake), board->food)){
        // Is on food. Grow head on top and replace food.
        board->snake->new_head(board->snake, snake_move);
        board->spawn_food(board);
    }
    else {
        // Check if game ends
            // Does it hit wall? (I can't be bothered implementing looping.)
            if (coord_in(snake_move, origin, end) == 0){
                return 0;
            }

            // Does it eat itself?
            Coord_list * snake = init_coord_list(board->snake->length);
            board->snake->coord_list(board->snake, snake);

            for (int i = 0; i < snake->length; i++){
                if (coord_eqs(snake_move, snake->list[i])){
                    return 0;
                }
            }

            free_coord_list(snake);

        // Is not on food. Move tail block to head.
        board->snake->tail_to_head(board->snake);
    }

    // Render resulting game scene
    board->apply_to_grid(board);
    render(board->display_grid, board->row, board->col);

    // Buffer inputs and wait

    return 1;
}

void wait_fz(int hertz){
    const struct timespec wait_time = {0, 999999999 / hertz}; // Can't be longer than 999999999.
    nanosleep(wait_time, NULL);
    return;
}