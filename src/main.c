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
    28/04/2021 - Added console_size() to ensure that GoToXY is always within bounds.
*/

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#include "main.h"
#include "board.h"
#include "input.h"
#include "output.h"
#include "thread.h"

void console_size(void);
void init_board_print(Board * board, Queue * q);
int turn_logic(Board * board, Queue * q, char input);
int update_game(Board * board, Queue * q);

int main(void){
    // Random seed at game start
    srand(time(0));

    // Making sure the console is large enough
    console_size();

    clock_t polling_duration = FRAME_DUR;
    clock_t poll_end = clock() + polling_duration;

    Board * board = init_board(DEFAULT_ROW, DEFAULT_COL);
    
    // Print board here...
    system("cls");
    print_fresh_board(board->row, board->col);
    
    Queue * q = QueueConstructor();
    // Add requests for the first food and snake
    init_board_print(board, q);

    input_setup();
    init_output(q);

    while(1){
        if (clock() > poll_end){
            int exit_code = update_game(board, q);
            
            if(exit_code){
                break;
            }

            poll_end += polling_duration;   // Very simple polling done at the end
        }
    }

    term_output(q);
    input_terminate();

    // Go to the end of the board
    GoToXY(0, board->row);
    printf("Score: %d\n", board->snake->length - 2); // The score no longer starts at 2.
    
    free(board);
    free(q);

    printf("Press any key to exit...\n");

    clock_t start, end;

    while(1){
        start = clock();
        getch();
        end = clock();

        if (end > start + 50){
            break;
        }
    }

    return 0;
}

// Ensure that the console is at the right size
void console_size(void){
    HANDLE hStdout;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    SMALL_RECT srctWindow;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("Please resize the screen until it is large enough.");

    while(1){
        if (! GetConsoleScreenBufferInfo(hStdout, &csbiInfo)){
            printf("GetConsoleScreenBufferInfo (%ld)\n", GetLastError());
            return;
        }
        srctWindow = csbiInfo.srWindow;

        if (srctWindow.Right > DEFAULT_COL*3 && srctWindow.Bottom > DEFAULT_ROW){
            break;
        }
    }

    system("cls");
    printf("Press any key to start the game.\n");
    getch();

    return;
}

// Add the starting requests
void init_board_print(Board * board, Queue * q){
    SnakeBody * body = board->snake->head;
    for (int i = 0; i < board->snake->length; i++){
        q->add(q, 'O', coord2COORD(body->position));
        body = body->next;
    }

    q->add(q, 'X', coord2COORD(board->food));
    
    return;
}

int update_game(Board * board, Queue * q){
    char user_input = 0;
    int return_code = 0;

    user_input = read_input();  // Input is always up to date

    if (user_input == EXIT_CODE){
        return 1;
    }

    return_code = turn_logic(board, q, user_input);


    if(return_code){
        return 1;
    } else {
        return 0;
    }
}


int turn_logic(Board * board, Queue * q, char input){
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
        // Apply new head position.
        board->snake->new_head(board->snake, board->snake->next_position(board->snake));

        // Add request for it.
        q->add(q, 'O', coord2COORD(board->snake->head->position));

        // Check if win
        if (board->snake->length >= board->row * board->col){
            return 1;
        } // This is because the spawn_food function fails whenever there is no empty space

        // Spawn food
        board->spawn_food(board);

        // Add request for the food
        q->add(q, 'X', coord2COORD(board->food));
    }
        // N - Move tail to head.
    else {
        // Clear the previous spot
        Coord tail = board->snake->head->previous->position;

        // New head position
        board->snake->tail_to_head(board->snake);

        // Add request for it
        q->add(q, 'O', coord2COORD(board->snake->head->position));

        // Add request to clear tail position
        q->add(q, ' ', coord2COORD(tail));

        // Add request to clear tail position
        q->add(q, ' ', coord2COORD(tail));  // To get rid of ghost tail 
    }
    
    return 0;
}