// Game board
    // To make and change(?) game board.
// Date: 14/08/2020
// Author: NZPIEFACE

// Changelog:
/*  14/08/2020 - Food was added.
    09/11/2020 - Spawn food completed.
               - Finished tying it into the render function.
    11/11/2020 - Added spawn_food to board object.
*/

#include <stdlib.h>
#include "board.h"
//#include "snake.h"    //snake.h is included in board.h

#define DEFAULT_FOOD {2, 2}

// Private functions/methods
void reset_board(Board * board);
void spawn_food(Board * board);
void food_eaten(Board * board);
void write_to_grid(Board * board, Coord coord, char c);
void format_display(Board * board);
void snake_and_food_to_grid(Board * board);

Board * init_board(int row, int col){
    Board * board = malloc(sizeof(Board));

    board->row = row;
    board->col = col;
    board->size = row * col;
    board->snake = init_snake();

    // Init to NULL, change to something else if not null.
    board->moved_body = NULL;
    board->new_body = NULL;

    board->reset = &reset_board;
    board->apply_to_grid = &snake_and_food_to_grid;
    board->write = &write_to_grid;
    board->spawn_food = &spawn_food;

    board->display_grid = malloc(sizeof(char *) * row);

    // Initing character grid.
    for (int i = 0; i < board->row; i++){
        board->display_grid[i] = malloc(sizeof(char) * board->col);

        for (int j = 0; j < col; j++){
            board->display_grid[i][j] = 0;
        }
    }

    board->spawn_food(board);

    return board;
}

void free_board(Board * board){
    for (int i = 0; i < board->row; i++){
        free(board->display_grid[i]);
    }

    free(board->display_grid);
    free_snake(board->snake);
    free(board);

    return;
}

// Completed function
void reset_board(Board * board){
    for (int i = 0; i < board->row; i++){
        for (int j = 0; j < board->col; j++){
            board->display_grid[i][j] = 0;
        }
    }
    return;
}

// Completed function
Coord find_empty_cell(Board * board){
    // Create boolean grid
    char ** all_coords = malloc(sizeof(char) * board->size + sizeof(char*) * board->row);
    for (int i = 0; i < board->row; i++){
        all_coords[i] = (char *)(all_coords + board->row) + i * board->col;
    }

    // Initiate them all as TRUE
    for (int i = 0; i < board->row; i++){
        for (int j = 0; j < board->col; j++){
            all_coords[i][j] = 1;
        }
    }

    // Iterate over the snake.
    SnakeBody * body = board->snake->head;

    // Setting already existing coords as FALSE.
    for (int i = 0; i < board->snake->length; i++){
        Coord snake_body = body->position;
        all_coords[snake_body.x][snake_body.y] = 0;
        body = body->next;
    }
    
    // Initiating coordinate list of free spaces of which food can be populated on.
    Coord_list * free_spaces = init_coord_list(board->size - board->snake->length);
    int counter = 0;
    for (int i = 0; i < board->row; i++){
        for (int j = 0; j < board->col; j++){
            if (all_coords[i][j]){
                free_spaces->list[counter++] = coord_gen(i, j);
            }
        }
    }

    // Finding a random space from the array
    int random_number = rand() % free_spaces->length;
    Coord empty_cell = free_spaces->list[random_number];

    free(all_coords);
    free_coord_list(free_spaces);

    return empty_cell;
}

void spawn_food(Board * board){
    board->food = find_empty_cell(board);
    return;
}

// Completed function
void write_to_grid(Board * board, Coord coord, char c){
    board->display_grid[coord.x][coord.y] = c;
    return;
}

// Applying the characters to the board.
void snake_and_food_to_grid(Board * board){
    SnakeBody * body = board->snake->head;

    // Go through all the snake positions and print them to the board.
    for (int i = 0; i < board->snake->length; i++){
        Coord current = body->position;
        body = body->next;
        write_to_grid(board, current, 'O');
    }

    // Find out if the food exists or not.
    Coord error_case = {-1, -1};
    if (coord_eqs(board->food, error_case) == 0){
        write_to_grid(board, board->food, 'X');
    }

    return;
}

//void grab_cell