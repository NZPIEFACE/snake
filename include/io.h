// I/O module
    /* Module for user input and user output.
    */
// Date: 17/11/2020
// Author: NZPIEFACE

// Changelog:
/*  17/11/2020 - Changed from Input module to IO module. Subsumed render.
               - Added terminal function and input direction.
*/

#ifndef _INPUT_H
#define _INPUT_H

#include "render.h"
#include "coord.h"

void terminal_setup(void);
void terminal_reset(void);

char read_input(void);

#endif