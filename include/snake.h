// Snake object (and related functions)
    /* Only want to pass the Snake object from this file, really. 
    */
// Date: 27/05/2020
// Author: NZPIEFACE

// Changelog:
/*  27/05/2020 - Added Snake stuff.
*/

#ifndef _SNAKE_H
#define _SNAKE_H

#include "coord.h"

typedef struct SnakeBody SnakeBody;

typedef struct SnakeBody {
    Coord position;
    SnakeBody * previous;
    SnakeBody * next;
} SnakeBody;

typedef struct Snake {
    SnakeBody * head;
    SnakeBody * tail;
    int length;
} Snake;

Snake * init_snake(void);
void    free_snake(Snake * snake);

SnakeBody * init_body(Coord position);
void        free_body(SnakeBody * body);

#endif