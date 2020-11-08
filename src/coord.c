// Coord object
// Date: 14/08/2020
// Author: NZPIEFACE

// Changelog:
/*  04/07/2020 - Made the object.
    13/08/2020 - Added defaults.
               - Coordinate arithmetic.
               - Added print_coord function.
    14/08/2020 - bounded_coords was added.
    09/11/2020 - Added Coord_list functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include "coord.h"

Coord UP = {0, -1};
Coord DOWN = {0, 1};
Coord LEFT = {-1, 0};
Coord RIGHT = {0, 1};

Coord coord_add(Coord a, Coord b){
    Coord c = {a.x + b.x, a.y + b.y};
    return c;
}

int coord_eqs(Coord a, Coord b){
    return (a.x == b.x) && (a.y == b.y);
}

void print_coord(Coord a){
    printf("x: %d, y: %d\n", a.x, a.y);
    return;
}

Coord coord_bound(Coord a, int row, int col){
    Coord bounded_a = {a.x % row, a.y % col};
    return bounded_a;
}

Coord coord_gen(int row, int col){
    Coord a = {row, col};
    return a;
}

Coord_list * init_coord_list(int length){
    Coord_list * list = malloc(sizeof(Coord_list));
    list->list = malloc(sizeof(Coord) * length);
    list->length = length;

    return list;
}

void free_coord_list(Coord_list * list){
    free(list->list);
    free(list);
    return;
}