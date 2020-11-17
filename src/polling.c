// Polling module
    /* Module for timing user input.
    */
// Date: 18/11/2020
// Author: NZPIEFACE

// Changelog:
/*  
*/

#include <poll.h>
#include <unistd.h>
#include <sys/times.h>
#include <time.h>

#include "polling.h"
#include "io.h"

// Define private variable
struct pollfd stdin_poll[1];

void polling_setup(void){
    stdin_poll[0].fd = STDIN_FILENO;
    stdin_poll[0].events = POLLIN;
    return;
}

char input_polling(int * polling_duration, clock_t * start_time){
    int poll_result = poll(stdin_poll, 1, *polling_duration);
    clock_t polling_time = times(NULL); // Not storing the CPU time
    int remaining_duration = DEFAULT_POLL - (polling_time - *start_time);
    *polling_duration = remaining_duration;

    // Poll successful
    if (poll_result > 0){
        if (stdin_poll[0].revents & POLLIN){    // There is something to read
            return read_input();    // Read input
        }
    }

    // Poll unsuccessful and remainder too short.
    if (poll_result == 0 || remaining_duration < MIN_POLL){
        *start_time = times(NULL);  // New start time
        *polling_duration = DEFAULT_POLL;   // Reset polling duration
        return POLLING_DONE;  // -1 is reserved for read_input.
    }

    // Unsuccessful but still has time left to poll
    return 0;
}
