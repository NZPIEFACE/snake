// main.c, everything I need will go here
    /* 
    */
// Date: 27/09/2020
// Author: NZPIEFACE

// Changelog:
/*  11/11/2020 - Added turn logic.      
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "board.h"
#include "io.h"

void sleep_hz(int f);
struct timespec hz(int f);

int main(void){

    terminal_setup();

    while(1){
        Coord read = read_input();
        print_coord(read);

        if (coord_eqs(read, ERROR)){
            break;
        }
    }

    terminal_reset();

    return 0;
}

void sleep_hz(int f){
    struct timespec ts = hz(f);
    nanosleep(&ts, NULL);
    return;
}

struct timespec hz(int f){
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000000/f;
    return ts;
}