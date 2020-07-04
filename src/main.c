#include "snake.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void){
    printf("Snake size: %ld\n", sizeof(Snake));
    printf("Snake * size: %ld\n", sizeof(Snake *));
    printf("SnakeBody size: %ld\n", sizeof(SnakeBody));
    printf("SnakeBody * size: %ld\n", sizeof(SnakeBody *));
    printf("Coord size: %ld\n", sizeof(Coord));
    printf("Coord * size: %ld\n", sizeof(Coord *));
    printf("int size: %ld\n", sizeof(int));
    printf("int * size: %ld\n", sizeof(int *));
    return 0;
}