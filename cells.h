#ifndef CELLS_H_
#define CELLS_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    bool alive;
    int row;
    int column;
    int aliveNeighbours;
    int neighbours[8][2];
} Cell;

void drawCell(SDL_Renderer *renderer, Cell *cell);

#endif // CELLS_H_
