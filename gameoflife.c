#include <stdio.h>
#include <SDL2/SDL.h>

#include "gameoflife.h"

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("Error initialising SDL %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("CGOL",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WIDTH, HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, renderFlags);
    if (renderer == NULL) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    game_t game;
    game.state = false;
    initBoard(&game);
    setNeighbours(&game);
    SDL_Color gridColor;

    SDL_Event input;
    while (GameRunning) {
        getEvents(input, &game);
        if (game.state || game.stepForward) {
            processNextGen(&game);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
        }
        gridColor = game.state ? runningState : pauseState;
        update(renderer, &game, &gridColor);

        if (game.stepForward) game.stepForward = false;
    }
    close(renderer, window);
    return 1;
}

void close(SDL_Renderer* renderer, SDL_Window* window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    window = NULL;
    renderer = NULL;

    SDL_Quit();
}

void getEvents(SDL_Event input, game_t *game) {
    while (SDL_PollEvent(&input)) {
        switch (input.type) {
            case SDL_QUIT:
                GameRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                clickCell(game);
                break;
            case SDL_KEYDOWN:
                handleKeyboardEvent(game);
                break;
            default: {}
        }
    }
}

void update(SDL_Renderer* renderer, game_t *game, const SDL_Color *color) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw(renderer, game);
    drawGrid(renderer, color);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/10);
}

void drawGrid(SDL_Renderer *renderer, const SDL_Color *color) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

    for (int i = 1; i < columns; i++) {
        SDL_RenderDrawLine(renderer,
                           i * CELLSIZE, 0,
                           i * CELLSIZE, HEIGHT);
        SDL_RenderDrawLine(renderer,
                           0,     i * CELLSIZE,
                           WIDTH, i * CELLSIZE);
    }
}

void clickCell(game_t *game) {
    int row, col;
    SDL_GetMouseState(&col, &row);

    row /= CELLSIZE;
    col /= CELLSIZE;

    game->board[row][col].alive = !game->board[row][col].alive;
}

void handleKeyboardEvent(game_t *game) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_SPACE]) {
        game->state = !game->state;
    }
    else if (state[SDL_SCANCODE_RIGHT]) {
        game->stepForward = true;
    }
    else if (state[SDL_SCANCODE_ESCAPE]) {
        game->state = false;
        initBoard(game);
    }
}
