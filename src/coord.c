// Coord object
// Date: 13/08/2020
// Author: NZPIEFACE

// Changelog:
/*  04/07/2020 - Made the object.
*/

#include <stdio.h>
#include "coord.h"

Coord UP = {0, -1};
Coord DOWN = {0, 1};
Coord LEFT = {-1, 0};
Coord RIGHT = {0, 1};

Coord coord_addition(Coord a, Coord b){
    Coord c = {a.x + b.x, a.y + b.y};
    return c;
}