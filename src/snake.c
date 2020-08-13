// Snake object (and related functions)
    /* Only want to pass the Snake object from this file, really. 
    */
// Date: 27/05/2020
// Author: NZPIEFACE

// Changelog:
/*  27/05/2020 - Added Snake stuff.
    13/08/2020 - Made SnakeBody object private.
               - Made free_snake iterative.
*/

#include <stdlib.h>
#include "snake.h"

#define DEFAULT_LENGTH 2
#define DEFAULT_HEAD {0, 1}
#define DEFAULT_TAIL {0, 0}
#define DEFAULT_DIRECTION DOWN

// Private structure definitions
typedef struct SnakeBody {
    Coord position;
    SnakeBody * previous;
    SnakeBody * next;
} SnakeBody;

// Private functions/methods
SnakeBody * init_body(Coord position);
void free_body(SnakeBody * body);
Coord next_position(Snake * snake);

Snake * init_snake(void){
    Snake * snake = (Snake *)malloc(sizeof(Snake));
    snake->length = DEFAULT_LENGTH;

    Coord head = DEFAULT_HEAD;
    snake->head = init_body(head);

    Coord tail = DEFAULT_TAIL;
    snake->tail = init_body(tail);

    snake->direction = DEFAULT_DIRECTION;

    snake->next_position = &next_position;

    return snake;
}

void free_snake(Snake * snake){
    SnakeBody * now;
    SnakeBody * next;
    now = snake->head;
    next = now->next;

    while (next != NULL){
        free_body(now);
        now = next;
        next = next->next;
    }

    free_body(snake->tail);
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