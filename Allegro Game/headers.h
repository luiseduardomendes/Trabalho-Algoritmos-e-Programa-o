/*_______________________STANDARD_LIBS_________________________*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
/*_____________________________________________________________*/


/*________________________ALLEGRO_LIBS_________________________*/
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*_____________________________________________________________*/

/*____________________________MACROS___________________________*/
#define TOUP 'W'
#define TOLEFT 'A'
#define TODOWN 'S'
#define TORIGHT 'D'
#define WALL '#'
#define SIZEMAP_X 60
#define SIZEMAP_Y 23
#define NUM_MOBS 4
/*_____________________________________________________________*/

enum directions{UP, DOWN, LEFT, RIGHT};


/*___________________________STRUCTS___________________________*/
typedef struct shuriken{
    int x, y;
    int movex, movey;
    bool throwing;
}typeShur;
typedef struct position{
    int x, y;
    int direction;
    typeShur shuriken;
}typePos;
/*_____________________________________________________________*/

FILE *map;
void showDisplay (int mapUsed, typePos playerPos, typePos infMob[], typeShur shuriken[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
int verifyPosition(int x, int y, char direction, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
void npcMovement(typePos infMob[], typePos playerPos, int rangeViewMob, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
void throwShuriken(typeShur *shuriken, typePos enemy, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
