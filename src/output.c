#include <windows.h>
#include <stdio.h>

#include "output.h"


int output_thread_active;
HANDLE output_thread_handle;

DWORD WINAPI output_thread(LPVOID lpParameter);
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

void GoToXY(int column, int line){
    // Create a COORD structure and fill in its members.
    COORD coord = {.X = column, .Y = line};

    // Obtain a handle to the console screen buffer.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Finally, call the SetConsoleCursorPosition function.
    if (!SetConsoleCursorPosition(hConsole, coord))
        printf("GoToXY() SetConsoleCursorPosition(): %ld\n", GetLastError());
}

void GoToCOORD(COORD coord){
    // Obtain a handle to the console screen buffer.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Finally, call the SetConsoleCursorPosition function.
    if (!SetConsoleCursorPosition(hConsole, coord))
        printf("GoToCOORD() SetConsoleCursorPosition(): %ld\n", GetLastError());
}

void init_output(Queue * queue){
    output_thread_handle = CreateThread(NULL, 0, output_thread, queue, 0, 0);
    output_thread_active = 1;
}

void term_output(Queue * q){
    output_thread_active = 0;
    while(!output_thread_active && !q->length){}
    TerminateThread(output_thread_handle, 0);
    CloseHandle(output_thread_handle);
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

DWORD WINAPI output_thread(LPVOID lpParamater){
    Queue * q = (Queue *) lpParamater;
    output_thread_active = 1;

    while(output_thread_active){
        while(q->length != 0){
            complete_request(q->queue);
            q->remove(q);
        }
        GoToXY(0, 0);
    }

    output_thread_active = 1;
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