// Render file
    // Module to print to terminal.
// Date: 04/07/2020
// Author: NZPIEFACE

// Changelog:
/*  09/11/2020 - Finished writing the function.
    17/11/2020 - Added black/white rendering.
*/

#include <stdio.h>
#include <stdlib.h>

// Very POSIX
void render(char ** grid, int row, int col){
    system("cls");
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            // Snakes
            if (grid[i][j] == 'O' ){
                printf("\x1B[42;1m O \x1B[0m"); // White on green.
            }
            // Food
            else if (grid[i][j] == 'X'){
                printf("\x1B[41;1m\x1B[32;1m   \x1B[0m"); // Green on red.
            }
            // Everything else
            else {
                printf("\x1B[40m   \x1B[0m"); // Black on black.
            }
        }
        printf("\n\x1B[0m"); // Extra scape code to catch whatever leaks.
    }
    return;
}

void bw_render(char ** grid, int row, int col){
    system("clear");
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            // Snakes
            if (grid[i][j] == 'O' ){
                printf("[O]");
            }
            // Food
            else if (grid[i][j] == 'X'){
                printf("[X]"); 
            }
            // Everything else
            else {
                printf("[ ]"); // Black on black.
            }
        }
        printf("\n");
    }
    return;
}