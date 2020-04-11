#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "cells.h"

void drawCell(SDL_Renderer *renderer, Cell *cell) {
    if (cell->alive)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    else
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect rect = {cell->column * CELLSIZE,
                     cell->row * CELLSIZE,
                     CELLSIZE, CELLSIZE};
    SDL_RenderFillRect(renderer, &rect);
}


