#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include "game.h"

const SDL_Color runningState = {.r = 25, .g = 255, .b = 25};
const SDL_Color pauseState = {.r = 255, .g = 25, .b = 25};

void close(SDL_Renderer* renderer, SDL_Window* window); 
void getEvents(SDL_Event input, game_t *g);
void clickCell(game_t *game);
void handleKeyboardEvent(game_t *game);
void update(SDL_Renderer* renderer, game_t *game, const SDL_Color *color);
void drawGrid(SDL_Renderer *renderer, const SDL_Color *color); 
void toggleGame();
void draw();
void resetGrid();

#endif
