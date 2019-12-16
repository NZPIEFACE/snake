#ifndef _GAME_H
#define _GAME_H

typedef struct World World;
typedef struct Coord Coord;

void snakeStart(World* w);
void snakeHead(World* w);
void moveHead(World* w);
int snakeDead(World* w);
void incrementSnake(World* w);
void pruneSnake(World* w);

void generateFood(World* w);
int foodCheck(World* w);
void eatFood(World* w);

Coord* roll(World* w);

int dirInput(World* w);

char singleInput(void);
void clear(void);
void refresh(void);

void game(World* w);
void loop(World* w);
int gameplayLoop(World* w);
void frame(World* w);

int cont(void);

#endif
