// Render file
    // Module to print to terminal.
// Date: 04/07/2020
// Author: NZPIEFACE

// Changelog:
/* 
*/
#include <stdio.h>

void render(char ** grid, int row, int col){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (grid[i][j] != 0){
                printf("%c", grid[i][j]);
            }
            else {
                printf(".");
            }
        }
        printf("\n");
    }
    return;
}