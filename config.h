#ifndef CONFIG_H_
#define CONFIG_H_

#define CELLSIZE 30
#define rows 30
#define columns 30
#define FPS 10

#include <stdbool.h>

static bool GameRunning = true;
static int GENERATION = 0;
static int POPULATION = 0;

static const int WIDTH = CELLSIZE * columns;
static const int HEIGHT = CELLSIZE * rows;

#endif
