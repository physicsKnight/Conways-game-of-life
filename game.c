#include <SDL2/SDL.h>
#include <stdlib.h>

#include "config.h"
#include "cells.h"
#include "game.h"

void initBoard(game_t *game) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            game->board[row][col].alive = false;
            game->board[row][col].row = row;
            game->board[row][col].column = col;
            game->board[row][col].aliveNeighbours = 0;
        }
    }
}

void setNeighbours(game_t *game) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            getNeighbours(&game->board[row][col], game);
        }
    }
}

void draw(SDL_Renderer *renderer, game_t *game) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            Cell *currCell = &game->board[row][col];
            drawCell(renderer, currCell);
        }
    }
}

bool processNeighbours(Cell *cell) {
    if (cell->alive)
        return (cell->aliveNeighbours == 2 ||
                cell->aliveNeighbours == 3);
    else
        return cell->aliveNeighbours == 3;
}

void processNextGen(game_t *game) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            Cell *cell = &game->board[row][col];
            countAliveNeighbours(game, cell);
        }
    }
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            Cell *cell = &game->board[row][col];
            game->board[row][col].alive = processNeighbours(cell);
        }
    }
}

void countAliveNeighbours(game_t *game, Cell *cell) {
    int aliveNeighbours = 0;
    for (int i = 0; i < 8; i++) {
        int row = cell->neighbours[i][0];
        int col = cell->neighbours[i][1];
        if (game->board[row][col].alive)
            aliveNeighbours++;
    }
    cell->aliveNeighbours = aliveNeighbours;
}

int mod(int a, int b) {
    // C version of '%' is a remainder function not modulo
    // so we must implement our own mod function
    int r = a % b;
    return r < 0 ? r + b : r;
}

void getNeighbours(Cell *cell, game_t *game) {
    // put all 8 neighbour locations in cell neighbour array
    int neighbourPos[2];
    int (*rowPtr)[2] = cell->neighbours;
    int *colPtr = NULL;
    for (int row = -1; row <= 1; row++) {
        for (int col = -1; col <= 1; col++) {
            if (!(row == 0 && col == 0)) {
                // mod function needed to reverse loop the gameboard
                neighbourPos[0] = mod(cell->row + row, rows);
                neighbourPos[1] = mod(cell->column + col, columns);
                if (rowPtr != cell->neighbours+8) {
                    colPtr = *(rowPtr++);
                    *colPtr = neighbourPos[0];
                    *(++colPtr) = neighbourPos[1];
                }
            }
        }
    }
}

