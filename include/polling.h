// Polling module
    /* Module for timing user input.
    */
// Date: 18/11/2020
// Author: NZPIEFACE

// Changelog:
/*  
*/

#ifndef _POLLING_H
#define _POLLING_H

#define DEFAULT_POLL 200
#define MIN_POLL     10

#define POLLING_DONE -2

void polling_setup(void);
char input_polling(int * polling_duration, clock_t * start_time);

#endif