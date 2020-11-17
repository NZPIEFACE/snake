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

#define EXIT_CODE -1
#define DEFAULT 0
#define UP_CHAR 1
#define DN_CHAR 2
#define RT_CHAR 3
#define LT_CHAR 4

void terminal_setup(void);
void terminal_reset(void);

char read_input(void);

#endif