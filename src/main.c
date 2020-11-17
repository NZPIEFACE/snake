#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "board.h"
#include "io.h"

void sleep_hz(int hz);

int main(void){

    terminal_setup();

    while(1){
        print_coord(read_input());
    }

    terminal_reset();

    return 0;
}

void sleep_hz(int hz){
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = (1/hz) * 1000000000;

    nanosleep(&ts, NULL);
    return;
}