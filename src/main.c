// main.c, everything I need will go here
    /* 
    */
// Date: 27/09/2020
// Author: NZPIEFACE

// Changelog:
/*  11/11/2020 - Added turn logic.      
*/

#include <stdio.h>
#include <time.h>
#include <sys/times.h>

#include "board.h"
#include "polling.h"
#include "io.h"


int main(void){

    terminal_setup();
    polling_setup();

    int polling_duration = DEFAULT_POLL;
    clock_t start_time = times(NULL);
    char user_input, saved_input;

    while(1){
        user_input = input_polling(&polling_duration, &start_time);

        if (user_input == -2){
            printf("%d\n", saved_input);
        }
        else {
            saved_input = user_input;
        }

        if (user_input == -1){
            break;
        }

        
    }

    terminal_reset();

    return 0;
}
