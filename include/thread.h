// Thread object
    /* To keep track of thread states
    */
// Date: 28/04/2021
// Author: NZPIEFACE

// Changelog:
/*  
*/

#ifndef _THREAD_H
#define _THREAD_H

#include <windows.h>

typedef struct THREAD {
    HANDLE handle;
    BOOL active;
    BOOL stop_request;
} THREAD;


#endif