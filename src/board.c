// Game board
    // To make and change(?) game board.
// Date: 14/08/2020
// Author: NZPIEFACE

// Changelog:
/*  14/08/2020 - Food was added.
    09/11/2020 - Spawn food completed.
               - Finished tying it into the render function.
*/

#include <stdlib.h>
#include "board.h"
//#include "snake.h"    //snake.h is included in board.h

#define DEFAULT_FOOD {2, 2}

// Private functions/methods
void reset_board(Board * board);
Coord spawn_food(Board * board);
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

    Coord food = DEFAULT_FOOD;
    board->food = food;

    // Init to NULL, change to something else if not null.
    board->moved_body = NULL;
    board->new_body = NULL;

    board->reset = &reset_board;
    board->apply_to_grid = &snake_and_food_to_grid;

    board->display_grid = malloc(sizeof(char *) * row);

    // Initing character grid.
    for (int i = 0; i < board->row; i++){
        board->display_grid[i] = malloc(sizeof(char) * board->col);

        for (int j = 0; j < col; j++){
            board->display_grid[i][j] = 0;
        }
    }

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
Coord spawn_food(Board * board){
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

    // Retrieves a list of coordinates from the Snake object. Can be more efficient.
    Coord_list * snake_coords = init_coord_list(board->snake->length);
    snake_coords = board->snake->coord_list(board->snake, snake_coords);

    // Setting already existing coords as FALSE.
    for (int i = 0; i < board->snake->length; i++){
        all_coords[snake_coords->list[i].x][snake_coords->list[i].y] = 0;
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
    Coord food_space = free_spaces->list[random_number];

    free(all_coords);
    free_coord_list(snake_coords);
    free_coord_list(free_spaces);

    return food_space;
}

// Completed function
void write_to_grid(Board * board, Coord coord, char c){
    board->display_grid[coord.x][coord.y] = c;
    return;
}

// Applying the characters to the board.
void snake_and_food_to_grid(Board * board){
    Coord_list * snake_coords = init_coord_list(board->snake->length);
    snake_coords = board->snake->coord_list(board->snake, snake_coords);

    // Go through all the snake positions and print them to the board.
    for (int i = 0; i < snake_coords->length; i++){
        Coord current = snake_coords->list[i];
        write_to_grid(board, current, 'O');
    }

    // Find out if the food exists or not.
    Coord error_case = {-1, -1};
    if (coord_eqs(board->food, error_case) == 0){
        write_to_grid(board, board->food, 'X');
    }

    free(snake_coords);
    return;
}

//void grab_cell

//Action to perform when the food is eaten.
void food_eaten(Board * board){
    board->snake->new_head(board->snake);
    board->food = spawn_food(board);

    return;
}