// Snake object (and related functions)
    /* Only want to pass the Snake object from this file, really. 
    */
// Date: 27/05/2020
// Author: NZPIEFACE

// Changelog:
/*  27/05/2020 - Added Snake stuff.
    13/08/2020 - Made SnakeBody object private.
               - Added methods.
    09/11/2020 - Added populat_snake_coords.
*/

#ifndef _SNAKE_H
#define _SNAKE_H

#include "coord.h"

typedef struct SnakeBody SnakeBody;
typedef struct Snake Snake;

typedef struct Snake {
    SnakeBody * head;
    //SnakeBody * tail;
    int length;
    Coord direction;

    Coord (* next_position)(Snake *);
    SnakeBody * (* tail_to_head)(Snake *);  // returns new head
    SnakeBody * (*new_head)(Snake *, Coord);
    void (* print_head_position)(Snake *);
    Coord_list * (*coord_list)(Snake *, Coord_list *);
    int (* overlap)(Snake *);
} Snake;

typedef struct SnakeBody {
    Coord position; // this line... it needs to be public to use print_coord in main.c
    SnakeBody * previous;
    SnakeBody * next;
} SnakeBody;

Snake * init_snake(void);
void    free_snake(Snake * snake);

#endif