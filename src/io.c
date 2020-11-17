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

#include "io.h"

#define BUFFER_SIZE 16


// Declaration of private functions
char direction_is(char c, char up, char down, char right, char left, char quit);

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
char read_input(void){
    char ch_buffer[BUFFER_SIZE] = {0};
    int c_read = read(STDIN_FILENO, ch_buffer, BUFFER_SIZE);

    if (c_read == 1){
        // 27 is ESC
        char upper = direction_is(ch_buffer[0], 'W', 'S', 'D', 'A', 27);
        char lower = direction_is(ch_buffer[0], 'w', 's', 'd', 'a', 0);     // Only need to check for ESC once.

        return upper + lower;   // One is 0
    }
    else if (c_read == 3){
        return direction_is(ch_buffer[2], 'A', 'B', 'C', 'D', 0);
    }
    else {
        return 0;
    }
}

// Chain of if-else's because can't use switch statements.
char direction_is(char c, char up, char down, char right, char left, char quit){
    if (c == up){
        return UP_CHAR;
    }
    else if (c == down){
        return DN_CHAR;
    }
    else if (c == right){
        return RT_CHAR;
    }
    else if (c == left){
        return LT_CHAR;
    }
    else if (c == quit){
        return EXIT_CODE;
    }
    else {
        return DEFAULT_CHAR;
    }
}