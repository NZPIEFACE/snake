// I/O module
    /* Module for user input and user output.
    */
// Date: 10/11/2020
// Author: NZPIEFACE

// Changelog:
/*  17/11/2020 - Changed from Input module to IO module. Subsumed render, though will likely replace it later.
    04/04/2021 - Replaced UNIX stuff.
*/

#include <windows.h>
#include <conio.h>
#include <stdio.h>

#include "input.h"

#define BUFFER_SIZE 16


// Declaration of private functions
char direction_is(char c, char array[DIRECTIONS]);
DWORD WINAPI input_thread(LPVOID lpParameter);

// Declaration of private variables
int ch_buffer = 0;
HANDLE input_handle;
int loop = 1;

// Start the input polling
void input_setup(void){
    input_handle = CreateThread(0, 0, input_thread, NULL, 0, NULL);
    loop = 1;
    return;
}

// End the input polling
void input_terminate(void){
    loop = 0; // Stop input

    // Write to console input to clear getch()
    DWORD dwTmp;
	INPUT_RECORD ir[1];

    // Presses ESC
	ir[0].EventType = KEY_EVENT;
	ir[0].Event.KeyEvent.bKeyDown = TRUE;
	ir[0].Event.KeyEvent.dwControlKeyState = 0; // No other keys are pressed
	ir[0].Event.KeyEvent.uChar.AsciiChar = 27;
	ir[0].Event.KeyEvent.wRepeatCount = 1;
	ir[0].Event.KeyEvent.wVirtualKeyCode = 27; // Esc key https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	ir[0].Event.KeyEvent.wVirtualScanCode = 1; // May be different https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html  

    WriteConsoleInput( GetStdHandle( STD_INPUT_HANDLE ), ir, 1, & dwTmp );

    while(!loop);   // Wait until getch() is actually done before closing thread

    TerminateThread(input_handle, 0);
    CloseHandle(input_handle);

    return;
}

// Read to buffer
DWORD WINAPI input_thread(LPVOID lpParameter){
    if (lpParameter != NULL) return -1; // This should never happen
    
    // Loops reading into input forever until thread closes
    while(loop){
        // Adding _kbhit() here slows the output down a lot
        ch_buffer = getch(); // non-canonical
    }

    loop = 1;

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