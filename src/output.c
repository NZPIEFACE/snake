// Output module
    /* Module for game output.
    */
// Date: 05/04/2021
// Author: NZPIEFACE

// Changelog:
/*  28/04/2021 - THREAD object.
*/

#include <windows.h>
#include <stdio.h>

#include "output.h"
#include "thread.h"

HANDLE hConsole;
THREAD output_thread;


DWORD WINAPI output_thread_function(LPVOID lpParameter);
QueueItem * QIConstructor(char c, COORD coord);

void queue_add_item(Queue * q, QueueItem * qi){
    // Special case of empty queue
    if (q->queue == NULL){
        q->queue = qi;
        return;
    }

    QueueItem * i = q->queue;
    while (i->next != NULL){
        i = i->next;
    }
    i->next = qi;
    q->length += 1;
    return;
}

void queue_create_item(Queue * q, char c, COORD coord){
    QueueItem * qi = QIConstructor(c, coord);
    queue_add_item(q, qi);
}

void queue_remove_item(Queue * q){
    QueueItem * next = q->queue->next;
    free(q->queue);
    q->queue = next;
    q->length -= 1;
}

Queue * QueueConstructor(void){
    Queue * q = malloc(sizeof(Queue));
    q->queue = NULL;
    q->length = 0;
    q->add = &queue_create_item;
    q->remove = &queue_remove_item;
    return q;
}

QueueItem * QIConstructor(char c, COORD coord){
    QueueItem * qi = malloc(sizeof(QueueItem));
    qi->c = c;
    qi->coord = coord;
    qi->next = NULL;
    return qi;
}

// This is always used
void GoToXY(int column, int line){
    // Create a COORD structure and fill in its members.
    COORD coord = {.X = column, .Y = line};

    // Finally, call the SetConsoleCursorPosition function.
    if (!SetConsoleCursorPosition(hConsole, coord)){
        // Error is happening due to going to places outside of window
        printf("GoToXY() SetConsoleCursorPosition(): %ld\n", GetLastError());
    }
}

// This is never used
void GoToCOORD(COORD coord){
    // Finally, call the SetConsoleCursorPosition function.
    if (!SetConsoleCursorPosition(hConsole, coord))
        printf("GoToCOORD() SetConsoleCursorPosition(): %ld\n", GetLastError());
}

void init_output(Queue * queue){
    output_thread.stop_request = FALSE;
    output_thread.handle = CreateThread(NULL, 0, output_thread_function, queue, 
    0, 0);
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void term_output(Queue * q){
    output_thread.stop_request = TRUE;
    while(output_thread.active == TRUE && !q->length){}
    TerminateThread(output_thread.handle, 0);
    CloseHandle(output_thread.handle);
}

void write_to_output(char ch, int row, int col){
    int r = row;
    int c = col * 3 + 1;
    GoToXY(c, r);
    putchar(ch);
    return;
}

void complete_request(QueueItem * qi){
    write_to_output(qi->c, qi->coord.Y, qi->coord.X);
    return;
}

DWORD WINAPI output_thread_function(LPVOID lpParamater){
    Queue * q = (Queue *) lpParamater;
    output_thread.active = TRUE;

    while(output_thread.stop_request == FALSE){
        while(q->length != 0){
            complete_request(q->queue); // Prints as fast as it can
            q->remove(q);
        }
        GoToXY(0, 0); // Idle position
    }

    output_thread.active = FALSE;
    return 0;
}

// Print starting state of the board
void print_fresh_board(int row, int col){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("[ ]");
        }
        printf("\n");
    }
}