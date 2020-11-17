// main.c, everything I need will go here
    /* 
    */
// Date: 27/09/2020
// Author: NZPIEFACE

// Changelog:
/*  11/11/2020 - Added turn logic.     
    17/11/2020 - Added terminal settings.
*/

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

#include "main.h"
#include "board.h"
#include "io.h"
#include "polling.h"

int turn_logic(Board * board, char input);

int main(void){

    terminal_setup();
    polling_setup();

    int polling_duration = DEFAULT_POLL;
    clock_t start_time = times(NULL);
    char user_input, saved_input;

    Board * board = init_board(DEFAULT_ROW, DEFAULT_COL);

    while(1){
        user_input = input_polling(&polling_duration, &start_time);
        polling_duration = DEFAULT_POLL;
        start_time = times(NULL);
        
        if (user_input == POLLING_DONE){
            if(turn_logic(board, saved_input)){
                break;
            }
        }
        else if (user_input != DEFAULT_CHAR && user_input != EXIT_CODE){
            saved_input = user_input;
        }

        if (user_input == EXIT_CODE){
            break;
        }
        
    }

    printf("Score: %d\n", board->snake->length);
    printf("Press anything to continue...");
    getc(stdin);

    terminal_reset();
    free(board);
    return 0;
}



int turn_logic(Board * board, char input){
    static Coord snake_directions[4];
    snake_directions[0] = UP;
    snake_directions[1] = DOWN;
    snake_directions[2] = RIGHT;
    snake_directions[3] = LEFT;

    // Calculate new direction
    if (input != 0){
        // Check if opposites
        Coord result = coord_add(snake_directions[input - 1], board->snake->direction);
        if (!coord_eqs(ORIGIN, result)){
            board->snake->direction = snake_directions[input-1];
        }
    }

    // Does it still live?
    Coord bottom_right = {board->row - 1, board->col - 1};
    if (!coord_in(board->snake->next_position(board->snake), ORIGIN, bottom_right)){
        return 1;
    }
    if (board->snake->overlap(board->snake)){
        return 1;
    }

    // Does it eat food?
        // Y - New head on food.
    if (coord_eqs(board->snake->next_position(board->snake), board->food)){
        board->spawn_food(board);
        board->snake->new_head(board->snake, board->snake->next_position(board->snake));
    }
        // N - Move tail to head.
    else {
        // Clear the previous spot
        Coord tail = board->snake->head->previous->position;
        board->display_grid[tail.x][tail.y] = 0;
        board->snake->tail_to_head(board->snake);

    }

    // Render
    board->apply_to_grid(board);
    bw_render(board->display_grid, board->row, board->col);
    
    return 0;
}