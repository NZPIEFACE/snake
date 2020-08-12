#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "board.h"
#include "render.h"

int main(void){
    Coord c = coord_addition(UP, LEFT);
    printf("%d, %d\n", c.x, c.y);

    return 0;
}