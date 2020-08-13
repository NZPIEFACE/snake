// Coord object
// Date: 04/07/2020
// Author: NZPIEFACE

// Changelog:
/*  04/07/2020 - Made the object.
    13/08/2020 - Added defaults.
               - Coordinate arithmetic.
*/

#ifndef _COORD_H
#define _COORD_H

typedef struct Coord {
    int x;
    int y;
} Coord;

Coord coord_addition(Coord a, Coord b);

Coord UP;
Coord DOWN;
Coord LEFT;
Coord RIGHT;

#endif