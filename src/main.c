#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "game.h"
#include "render.h"

int main(void){
    Board * b = init_board(10, 10);

    render(b->grid, b->row, b->col);
    
    free_board(b);

    return 0;
}