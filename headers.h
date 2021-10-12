#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#define TOUP 'W'
#define TOLEFT 'A'
#define TODOWN 'S'
#define TORIGHT 'D'
#define WALL '#'
#define SIZEMAP_X 60
#define SIZEMAP_Y 23
#define NUM_MOBS 2
typedef struct position{
    int x, y;
    char direction;
}typePos;
typedef struct shuriken
{
    int x, y;
    int throwing;
    char direction;
}typeShur;

FILE *map;
void sleep_ms(int milliseconds);
void showDisplay (int mapUsed, typePos playerPos, typePos npcPos[], typeShur shuriken[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
int verifyPosition(int x, int y, char direction, char map[SIZEMAP_Y][SIZEMAP_X]);
void npcMovement(typePos infMob[], typePos playerPos, int rangeViewMob);
void throwShuriken(typeShur *shuriken, typePos enemy, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
