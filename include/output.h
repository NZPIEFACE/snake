// Output module
    /* Module for game output.
    */
// Date: 05/04/2021
// Author: NZPIEFACE

#ifndef _OUTPUT_H
#define _OUTPUT_H


#include <windows.h>

typedef struct Qi QueueItem;
typedef struct Q Queue;

typedef struct Q {
    QueueItem * queue;
    int length;
    void (* add)(Queue *, char, COORD);
    void (* remove)(Queue *);
} Queue;

typedef struct Qi {
    char c;
    COORD coord;
    QueueItem * next;
} QueueItem;

Queue * QueueConstructor(void);

void init_output(Queue * queue);
void term_output(Queue * queue);

void GoToXY(int column, int line);

void print_fresh_board(int row, int col);

#endif