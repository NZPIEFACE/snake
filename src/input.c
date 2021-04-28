// Input module
    /* Module for user input.
    */
// Date: 10/11/2020
// Author: NZPIEFACE

// Changelog:
/*  17/11/2020 - Changed from Input module to IO module. Subsumed render, though will likely replace it later.
    04/04/2021 - Replaced UNIX stuff.
    28/04/2021 - THREAD object.
*/

#include <windows.h>
#include <conio.h>
#include <stdio.h>

#include "input.h"
#include "thread.h"

#define BUFFER_SIZE 16


// Declaration of private functions
char direction_is(char c, char array[DIRECTIONS]);
DWORD WINAPI input_thread_function(LPVOID lpParameter);

// Declaration of private variables
int ch_buffer = 0;
THREAD input_thread;


// Start the input polling
void input_setup(void){
    input_thread.stop_request = FALSE;
    input_thread.handle = CreateThread(0, 0, input_thread_function, NULL, 0, NULL);
    return;
}

void read_ESC(void){
    // Write to console input to clear getch()
    DWORD dwTmp;
	INPUT_RECORD ir[2];

    // Presses ESC
	ir[0].EventType = KEY_EVENT;
	ir[0].Event.KeyEvent.bKeyDown = TRUE;
	ir[0].Event.KeyEvent.dwControlKeyState = 0; // No other keys are pressed
	ir[0].Event.KeyEvent.uChar.AsciiChar = 27;
	ir[0].Event.KeyEvent.wRepeatCount = 1;
	ir[0].Event.KeyEvent.wVirtualKeyCode = 27; // Esc key https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	ir[0].Event.KeyEvent.wVirtualScanCode = 1; // May be different https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html  

	ir[1].EventType = KEY_EVENT;
	ir[1].Event.KeyEvent.bKeyDown = FALSE;
	ir[1].Event.KeyEvent.dwControlKeyState = 0; // No other keys are pressed
	ir[1].Event.KeyEvent.uChar.AsciiChar = 27;
	ir[1].Event.KeyEvent.wRepeatCount = 1;
	ir[1].Event.KeyEvent.wVirtualKeyCode = 27; // Esc key https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	ir[1].Event.KeyEvent.wVirtualScanCode = 1; // May be different https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html  

    WriteConsoleInput( GetStdHandle( STD_INPUT_HANDLE ), ir, 2, & dwTmp );
}

// End the input polling
void input_terminate(void){
    input_thread.stop_request = TRUE;


    // Wait until getch() is actually done before closing thread
    while (input_thread.active == TRUE){read_ESC();}

    TerminateThread(input_thread.handle, 0);
    CloseHandle(input_thread.handle);

    return;
}

// Read to buffer
DWORD WINAPI input_thread_function(LPVOID lpParameter){
    if (lpParameter != NULL) return -1; // This should never happen
    input_thread.active = TRUE;
    
    // Loops reading into input forever until thread closes
    while(input_thread.stop_request == FALSE){
        // Adding _kbhit() here slows the output down a lot
        ch_buffer = getch(); // non-canonical
    }

    input_thread.active = FALSE;

    return 0;
}



// filter input passed from buffer for directions/esc
char read_input(void){
    // Snapshot input
    char input = (char) ch_buffer;

    // 27 is ESC
    char upper = direction_is(input, (char[5]){'W', 'S', 'D', 'A', 'Q'});
    char lower = direction_is(input, (char[5]){'w', 's', 'd', 'a', 'q'});
    char arrow = direction_is(input, (char[5]){'H', 'P', 'M', 'K', 27});

    return arrow + upper + lower;   // Only one is non-0
}

// Chain of if-else's because can't use switch statements.
char direction_is(char c, char array[DIRECTIONS]){
    for (int i = 0; i < DIRECTIONS; i++){
        if (c == array[i]){
            return i + 1;
        }
    }

    return DEFAULT_CHAR;
}