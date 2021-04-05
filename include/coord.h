// Coord object
// Date: 14/08/2020
// Author: NZPIEFACE

// Changelog:
/*  04/07/2020 - Made the object.
    13/08/2020 - Added defaults.
               - Coordinate arithmetic.
               - Added print_coord function.
    14/08/2020 - bounded_coords was added.
    09/11/2020 - Added Coord_list.
    17/11/2020 - Added ORIGIN and ERROR.
               - Changed globals into definitions.
    04/04/2021 - Changed ERROR to COORD_ERROR.
    05/04/2021 - Added coord2COORD.
*/

#ifndef _COORD_H
#define _COORD_H

#include <windows.h>

typedef struct Coord {
    int x;
    int y;
} Coord;

typedef struct Coord_list {
    Coord * list;
    int length;
} Coord_list;

Coord coord_add(Coord a, Coord b);
int coord_eqs(Coord a, Coord b);
int coord_in(Coord coord, Coord top_left, Coord bottom_right);
void print_coord(Coord a);
Coord coord_bound(Coord a, int row, int col);
Coord coord_gen(int row, int col);

COORD coord2COORD(Coord coord);


Coord_list * init_coord_list(int length);
void free_coord_list(Coord_list * list);

/*
Coord UP;
Coord DOWN;
Coord LEFT;
Coord RIGHT;
Coord ORIGIN;
Coord ERROR;
*/

#define UP coord_gen(-1, 0)
#define DOWN coord_gen(1, 0)
#define LEFT coord_gen(0, -1)
#define RIGHT coord_gen(0, 1)
#define ORIGIN coord_gen(0, 0)
#define COORD_ERROR coord_gen(-1, -1)

#endif