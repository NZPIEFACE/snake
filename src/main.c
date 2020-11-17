// main.c, everything I need will go here
    /* 
    */
// Date: 27/09/2020
// Author: NZPIEFACE

// Changelog:
/*  11/11/2020 - Added turn logic.      
*/

#include <stdio.h>
#include <time.h>
#include <sys/times.h>

#include "main.h"
#include "board.h"
#include "polling.h"
#include "io.h"

void turn_logic(Board * board, char input);

int frame = 0;

int main(void){

    terminal_setup();
    polling_setup();

    int polling_duration = DEFAULT_POLL;
    clock_t start_time = times(NULL);
    char user_input, saved_input;

    Board * board = init_board(DEFAULT_ROW, DEFAULT_COL);

    while(1){
        user_input = input_polling(&polling_duration, &start_time);

        if (user_input == POLLING_DONE){
            //turn_logic(board, saved_input);
            printf("%d\n", saved_input);
            printf("frame: %d\n", frame++);
        }
        else {
            saved_input = user_input;
        }

        if (user_input == EXIT_CODE){
            break;
        }

        
    }

    terminal_reset();

    return 0;
}


void turn_logic(Board * board, char input){
    board->apply_to_grid(board);
    render(board->display_grid, board->row, board->col);
    printf("%d\n", input);
    printf("frame: %d\n", frame++);
}