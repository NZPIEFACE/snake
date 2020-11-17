// I/O module
    /* Module for user input and user output.
    */
// Date: 10/11/2020
// Author: NZPIEFACE

// Changelog:
/*  17/11/2020 - Changed from Input module to IO module. Subsumed render, though will likely replace it later.
*/

#include <termios.h>
#include <unistd.h>

#include "coord.h"
#include "io.h"

#define BUFFER_SIZE 16


// Declaration of private functions
Coord direction_is(char c, char up, char down, char right, char left, char quit);

// Declaration of private variables
struct termios old_attributes, new_attributes;

// function to change input echo and input buffering
    // needs to read input even if user doesn't press enter, save that to buffer, then pass that along
void terminal_setup(void){
    tcgetattr(STDIN_FILENO, &old_attributes);
    new_attributes = old_attributes;
    new_attributes.c_lflag = old_attributes.c_lflag & ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attributes);
}

// funciton to change that back
void terminal_reset(void){
    tcsetattr(STDIN_FILENO, TCSANOW, &old_attributes);
}

// filter input passed from buffer for directions/esc
Coord read_input(void){
    char ch_buffer[BUFFER_SIZE] = {0};
    int c_read = read(STDIN_FILENO, ch_buffer, BUFFER_SIZE);

    if (c_read == 1){
        // 27 is ESC
        Coord upper = direction_is(ch_buffer[0], 'W', 'S', 'D', 'A', 27);
        Coord lower = direction_is(ch_buffer[0], 'w', 's', 'd', 'a', 27);

        if (!coord_eqs(upper, ORIGIN)){
            return upper;
        }
        else if (!coord_eqs(lower, ORIGIN)){
            return lower;
        }
        else {
            return ORIGIN;
        }
    }
    else if (c_read == 3){
        return direction_is(ch_buffer[2], 'A', 'B', 'C', 'D', 0);
    }
    else {
        return ORIGIN;
    }
}

// Chain of if-else's because can't use switch statements.
Coord direction_is(char c, char up, char down, char right, char left, char quit){
    if (c == up){
        return UP;
    }
    else if (c == down){
        return DOWN;
    }
    else if (c == right){
        return RIGHT;
    }
    else if (c == left){
        return LEFT;
    }
    else if (c == quit){
        return ERROR;
    }
    else {
        return ORIGIN;
    }
}