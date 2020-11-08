// Coord object
// Date: 14/08/2020
// Author: NZPIEFACE

// Changelog:
/*  04/07/2020 - Made the object.
    13/08/2020 - Added defaults.
               - Coordinate arithmetic.
               - Added print_coord function.
    14/08/2020 - bounded_coords was added.
*/

#ifndef _COORD_H
#define _COORD_H

typedef struct Coord {
    int x;
    int y;
} Coord;

Coord coord_add(Coord a, Coord b);
int coord_eqs(Coord a, Coord b);
void print_coord(Coord a);
Coord coord_bound(Coord a, int row, int col);
Coord coord_gen(int row, int col);

Coord UP;
Coord DOWN;
Coord LEFT;
Coord RIGHT;

#endif