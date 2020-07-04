#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "snake.h"
#include "render.h"
#include "board.h"

int main(void){
    Board * b = init_board(10, 10);

    render(b->grid, b->row, b->col);
    
    free_board(b);

    return 0;
}