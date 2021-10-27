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
#include <allegro5/allegro_image.h>
/*_____________________________________________________________*/

/*____________________________MACROS___________________________*/
#define TOUP 'W'
#define TOLEFT 'A'
#define TODOWN 'S'
#define TORIGHT 'D'
#define WALL '#'
#define SIZEMAP_X 60
#define SIZEMAP_Y 23
#define SIZENAMEMAPS 101
#define NUM_MOBS 4
#define MAPSCALE 24
#define RANGEVIEWMOB 5
/*_____________________________________________________________*/

enum directions{UP, DOWN, LEFT, RIGHT};
enum control_buttons{CONTROL_BUTTON_A, CONTROL_BUTTON_B, CONTROL_BUTTON_X, CONTROL_BUTTON_Y, CONTROL_BUTTON_LB, CONTROL_BUTTON_RB,
    CONTROL_BUTTON_OPTIONS, CONTROL_BUTTON_START, CONTROL_BUTTON_L, CONTROL_BUTTON_R};


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
typedef struct save{
    typePos player;
    typePos npc[NUM_MOBS];
    int mapUsed;
}typeSave;
/*_____________________________________________________________*/

FILE *map;
FILE *saveFile;
//void showDisplay (int mapUsed, typePos playerPos, typePos infMob[], typeShur shuriken[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
int verifyPosition(int x, int y, char direction, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
void npcMovement(typePos infMob[], typePos playerPos, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
void throwShuriken(typeShur *shuriken, typePos enemy, char mapMatrix[SIZEMAP_Y][SIZEMAP_X], typePos npcPos[]);
void showMenu(int width, int height, bool *endOfGame, bool *openMenu, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue, ALLEGRO_JOYSTICK *joy,ALLEGRO_JOYSTICK_STATE joyState, typePos npcPos[], typePos *playerPos, int *mapUsed);
int saveFunction (typePos npcPos[], typePos playerPos, int mapUsed);
int loadSave(typePos npcPos[], typePos *playerPos, int *mapUsed);
void drawMobShur(typePos npcPos[], ALLEGRO_BITMAP *shurikenDraw);
void playerMovement(typePos playerPos, ALLEGRO_EVENT event, char mapMatrix[][SIZEMAP_X], int joystickFound);
