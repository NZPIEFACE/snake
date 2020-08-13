#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "board.h"
#include "render.h"

int main(void){
    Snake * snake = init_snake();
    printf("Direction: ");
    print_coord(snake->direction);
    snake->print_head_position(snake);

    snake->tail_to_head(snake);
    snake->print_head_position(snake);

    snake->new_head(snake);
    snake->print_head_position(snake);
    printf("Length: %d\n", snake->length);

    free_snake(snake);
    return 0;
}