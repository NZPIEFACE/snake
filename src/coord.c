// Coord object
// Date: 13/08/2020
// Author: NZPIEFACE

// Changelog:
/*  04/07/2020 - Made the object.
    13/08/2020 - Added defaults.
               - Coordinate arithmetic.
*/

#include <stdio.h>
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