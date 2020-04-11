#ifndef GAME_H_
#define GAME_H_

#include "config.h"
#include "cells.h"

typedef struct {
    Cell board[rows][columns];
    bool state;
    bool stepForward;
} game_t;

void initBoard(game_t *game);
void setNeighbours(game_t *game);
void draw(SDL_Renderer *renderer, game_t *game);
bool processNeighbours(Cell *cell);
void processNextGen(game_t *game);
void countAliveNeighbours(game_t *game, Cell *cell); 
void getNeighbours(Cell *cell, game_t *game);

#endif // GAME_H_
