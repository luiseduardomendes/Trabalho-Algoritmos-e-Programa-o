#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#define SIZEMAP_X 60
#define SIZEMAP_Y 23
enum directions {w, a, s, d};
typedef struct position{
    int x, y;
    int direction;
}typePos;
FILE *map;
void sleep_ms(int milliseconds);
void showDisplay (int mapUsed, typePos playerPos, typePos npcPos);
bool verifyPosition(int x, int y, char direction, char map[SIZEMAP_Y][SIZEMAP_X]);
typePos npcMovement(typePos npcPos, typePos playerPos, int rangeViewMob);
