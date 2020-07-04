#include "snake.h"
#include <stdlib.h>

#define DEFAULT_LENGTH 2
#define DEFAULT_HEAD {0, 0}
#define DEFAULT_TAIL {0, 1}

Snake * init_snake(void){
    Snake * snake = (Snake *)malloc(sizeof(Snake));
    snake->length = DEFAULT_LENGTH;

    Coord head = DEFAULT_HEAD;
    snake->head = init_body(head);

    Coord tail = DEFAULT_TAIL;
    snake->tail = init_body(tail);

    return snake;
}

void free_snake(Snake * snake){
    free_body(snake->tail);
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