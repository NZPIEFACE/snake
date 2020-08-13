#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "board.h"
#include "render.h"

int main(void){
    Snake * snake = init_snake();
    printf("%d\n", snake->direction.x);
    return 0;
}