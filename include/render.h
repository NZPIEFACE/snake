// Render file
    // Module to print to terminal.
    // Only want to shove an array of strings in.
// Date: 04/07/2020
// Author: NZPIEFACE

// Changelog:
/*  17/11/2020 - Added black/white rendering.
    05/04/2021 - Added string rendering.
*/

#ifndef _RENDER_H
#define _RENDER_H

#define BWOUT

void render(char ** grid, int row, int col);
void bw_render(char ** grid, int row, int col);
char * initialize_output_string(int row, int col);
void write_to_string(char * char_str, char ch, int row, int col, int board_col);

#endif