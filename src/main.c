// main.c, everything I need will go here
    /* 
    */
// Date: 27/09/2020
// Author: NZPIEFACE

// Changelog:
/*  11/11/2020 - Added turn logic.
    17/11/2020 - Added terminal settings.
    04/04/2021 - Got rid of UNIX stuff, including all of polling.h. 
*/

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#include "main.h"
#include "board.h"
#include "io.h"

#define FRAME_DUR 100

int turn_logic(Board * board, char input);

int main(void){

    input_setup();

    clock_t polling_duration = FRAME_DUR;
    clock_t poll_end = clock() + polling_duration;
    char user_input = 0;

    Board * board = init_board(DEFAULT_ROW, DEFAULT_COL);

    while(1){
        if (clock() > poll_end){
            poll_end += polling_duration;   // Very simple polling

            user_input = read_input();  // Input is always up to date
            
            if(turn_logic(board, user_input)){
                break;
            }

            if (user_input == EXIT_CODE){
                break;
            }
        }
    }

    input_terminate();

    printf("Score: %d\n", board->snake->length - 2); // The score no longer starts at 2.
    printf("Press enter to exit...");
    getchar();  // I do not know why getch() doesn't work here. Or why I need to press Enter twice
    // Probably because of a running getch() in the other thread when it terminates.

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