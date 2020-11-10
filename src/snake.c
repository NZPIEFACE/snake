// Snake object (and related functions)
    /* Only want to pass the Snake object from this file, really. 
    */
// Date: 13/08/2020
// Author: NZPIEFACE

// Changelog:
/*  27/05/2020 - Added Snake stuff.
    13/08/2020 - Made SnakeBody object private.
               - Made free_snake iterative.
               - Added methods.
               - Added SnakeBody linking.
    09/11/2020 - Added populat_snake_coords.
*/

#include <stdlib.h>
#include "snake.h"

#define DEFAULT_LENGTH 2
#define DEFAULT_HEAD {0, 1}
#define DEFAULT_TAIL {0, 0}
#define DEFAULT_DIRECTION DOWN

// Private struct definitions
typedef struct SnakeBody {
    Coord position; // this line... it needs to be public to use print_coord in main.c
    SnakeBody * previous;
    SnakeBody * next;
} SnakeBody;

// Private functions/methods
SnakeBody * init_body(Coord position);
void free_body(SnakeBody * body);
Coord next_position(Snake * snake);
SnakeBody * move_snake_tail_to_head(Snake * snake);
SnakeBody * create_new_head(Snake * snake, Coord head_position);
SnakeBody * add_next_link(SnakeBody * this, SnakeBody * next);
SnakeBody * add_previous_link(SnakeBody * this, SnakeBody * previous);
void print_head_position(Snake * snake);
Coord_list * populate_snake_coords(Snake * snake, Coord_list * coord_list);

SnakeBody * grab_next_body(SnakeBody * this);

// Function definitions
Snake * init_snake(void){
    Snake * snake = (Snake *)malloc(sizeof(Snake));
    snake->length = DEFAULT_LENGTH;

    Coord head = DEFAULT_HEAD;
    snake->head = init_body(head);

    Coord tail = DEFAULT_TAIL;
    SnakeBody * snake_tail = init_body(tail);

    // Snake loops on itself, technically.
    add_next_link(snake->head, snake_tail);
    add_previous_link(snake->head, snake_tail);

    snake->direction = DEFAULT_DIRECTION;

    snake->next_position = &next_position;
    snake->tail_to_head = &move_snake_tail_to_head;
    snake->new_head = &create_new_head;
    snake->print_head_position = &print_head_position;
    snake->coord_list = &populate_snake_coords;

    return snake;
}

void free_snake(Snake * snake){
    SnakeBody * now;
    SnakeBody * next;
    now = snake->head->next;
    next = now->next;

    while (now != snake->head){
        free_body(now);
        now = next;
        next = next->next;
    }

    free_body(snake->head);
    free(snake);
    return;
}

SnakeBody * init_body(Coord position){
    SnakeBody * body = (SnakeBody *) malloc(sizeof(SnakeBody));
    body->position = position;
    body->previous = NULL;
    body->next = NULL;

    return body;
}

void free_body(SnakeBody * body){
    free(body);
    return;
}

Coord next_position(Snake * snake){
    Coord position = coord_add(snake->head->position, snake->direction);
    return position;
}

SnakeBody * move_snake_tail_to_head(Snake * snake){
    // Calculate the new position
    snake->head->previous->position = snake->next_position(snake);

    // Move the "tail" to the head.
    snake->head = snake->head->previous;

    return snake->head;
}

SnakeBody * create_new_head(Snake * snake, Coord head_position){
    SnakeBody * new_head = init_body(head_position);
    
    // Link the tail to the new head
    add_previous_link(new_head, snake->head->previous);
    
    // Link the current head as the next node
    add_next_link(new_head, snake->head);

    // Make the new head the current head
    snake->head = new_head;

    // Increment snake length
    snake->length++;

    return new_head;
}

SnakeBody * add_next_link(SnakeBody * this, SnakeBody * next){
    this->next = next;
    next->previous = this;
    return this->next;
}

SnakeBody * add_previous_link(SnakeBody * this, SnakeBody * previous){
    this->previous = previous;
    previous->next = this;
    return this->previous;
}

void print_head_position(Snake * snake){
    print_coord(snake->head->position);
    return;
}

// Returns the next body section
SnakeBody * grab_next_body(SnakeBody * this){
    return this->next;
}

// Returns a list of coordinates that the snake occupies.
Coord_list * populate_snake_coords(Snake * snake, Coord_list * coord_list){
    SnakeBody * this = snake->head;

    for (int i = 0; i < snake->length; i++){
        coord_list->list[i] = this->position;
        this = this->next;
    }

    return coord_list;
}
