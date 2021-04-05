// main.c, everything I need will go here
    /* 
    */
// Date: 27/09/2020
// Author: NZPIEFACE

// Changelog:
/*  11/11/2020 - Added turn logic.
    17/11/2020 - Added terminal settings.
    04/04/2021 - Got rid of UNIX stuff, including all of polling.h.
    05/04/2021 - Added update_game() to clear up main().
*/

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#include "main.h"
#include "board.h"
#include "io.h"


int turn_logic(Board * board, char input);
int update_game(Board * board);
void init_snake_string(Board * board);
void wrapper(char c, Coord coord);

#ifdef STRINGOUT
Board * b;
char * o;
#endif

int main(void){

    input_setup();

    clock_t polling_duration = FRAME_DUR;
    clock_t poll_end = clock() + polling_duration;

    Board * board = init_board(DEFAULT_ROW, DEFAULT_COL);

#ifdef STRINGOUT
    char * output_string = initialize_output_string(board->row, board->col);

    b = board;
    o = output_string;

    init_snake_string(board);
#endif

    while(1){
        if (clock() > poll_end){
            int exit_code = update_game(board);
            
            if(exit_code){
                break;
            }

            poll_end += polling_duration;   // Very simple polling done at the end
        }
    }

    input_terminate();

    printf("Score: %d\n", board->snake->length - 2); // The score no longer starts at 2.
    printf("Press any key to exit...");
    getch();

    free(board);
    return 0;
}

#ifdef STRINGOUT
void wrapper(char c, Coord coord){
    write_to_string(o, c, coord.x, coord.y, b->col);
}

void init_snake_string(Board * board){
    Coord_list * snake_coords = init_coord_list(board->snake->length);
    snake_coords = board->snake->coord_list(board->snake, snake_coords);

    for (int i = 0; i < snake_coords->length; i++){
        wrapper('O', snake_coords->list[i]);
    }

    wrapper('X', board->food);

    free(snake_coords);
    return;
}
#endif

int update_game(Board * board){
    char user_input = 0;
    int return_code = 0;

    user_input = read_input();  // Input is always up to date
    return_code = turn_logic(board, user_input);

#ifdef STRINGOUT
    system("clear");
    printf("%s", o);
#endif

    if(return_code|| user_input == EXIT_CODE){
        return 1;
    } else {
        return 0;
    }
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

    // Changes to position start here

    // Does it eat food?
        // Y - New head on food.
    if (coord_eqs(board->snake->next_position(board->snake), board->food)){
        
        board->snake->new_head(board->snake, board->snake->next_position(board->snake));
#ifdef STRINGOUT
        wrapper('O', board->snake->head->position);
#endif

        // Check if win
        if (board->snake->length >= board->row * board->col){
            return 1;
        } // This is because the spawn_food function fails whenever there is no empty space

        board->spawn_food(board);
#ifdef STRINGOUT
        wrapper('X', board->food);
#endif
    }
        // N - Move tail to head.
    else {
        // Clear the previous spot
        Coord tail = board->snake->head->previous->position;
#ifdef STRINGOUT
        wrapper(' ', tail);
#endif

#ifdef BWOUT
        board->display_grid[tail.x][tail.y] = 0;
#endif

        board->snake->tail_to_head(board->snake);

#ifdef STRINGOUT
        wrapper('O', board->snake->head->position);
#endif
    }

#ifdef BWOUT
    // Render
    board->apply_to_grid(board);
    bw_render(board->display_grid, board->row, board->col);
#endif
    
    return 0;
}