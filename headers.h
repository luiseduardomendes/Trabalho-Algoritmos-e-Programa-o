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
typedef struct position{
    int x, y;
    char direction;
}typePos;
FILE *map;
void sleep_ms(int milliseconds);
void showDisplay (int mapUsed, typePos playerPos, typePos npcPos, typePos shuriken, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
bool verifyPosition(int x, int y, char direction, char map[SIZEMAP_Y][SIZEMAP_X]);
typePos npcMovement(typePos npcPos, typePos playerPos, int rangeViewMob, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
int throwShuriken(typePos *shuriken, typePos enemy, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
