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
*/

#ifndef _COORD_H
#define _COORD_H

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
void print_coord(Coord a);
Coord coord_bound(Coord a, int row, int col);
Coord coord_gen(int row, int col);

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

#define UP coord_gen(0, -1)
#define DOWN coord_gen(0, 1)
#define LEFT coord_gen(-1, 0)
#define RIGHT coord_gen(1, 0)
#define ORIGIN coord_gen(0, 0)
#define ERROR coord_gen(-1, -1)

#endif