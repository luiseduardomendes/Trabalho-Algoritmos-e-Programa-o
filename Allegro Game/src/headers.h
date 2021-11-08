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
#include <allegro5/allegro_audio.h>
/*_____________________________________________________________*/

/*____________________________MACROS___________________________*/
#define TOUP 'W'
#define TOLEFT 'A'
#define TODOWN 'S'
#define TORIGHT 'D'
#define WALL '#'
#define SIZEMAP_X 64
#define SIZEMAP_Y 36
#define SIZENAMEMAPS 101
#define NUM_MOBS 5
#define MAPSCALE 20
#define RANGEVIEWMOB 5
#define MIN_ITEMS 25
/*_____________________________________________________________*/

enum directions{UP, DOWN, LEFT, RIGHT};
enum control_buttons{CONTROL_BUTTON_A, CONTROL_BUTTON_B, CONTROL_BUTTON_X, CONTROL_BUTTON_Y, CONTROL_BUTTON_LB, CONTROL_BUTTON_RB,
    CONTROL_BUTTON_OPTIONS, CONTROL_BUTTON_START, CONTROL_BUTTON_L, CONTROL_BUTTON_R};
enum itemsID{shur, keys};

/*___________________________STRUCTS___________________________*/
typedef struct shuriken{
    int x, y;
    int movex, movey;
    bool throwing;
}typeShur;

typedef struct position{
    int x,y;
    int hp, fullHp;
    int direction;
    int numShur, numKeys;
    int xp;
    int level;
    int armor, shurikenItem;
    typeShur shuriken;
}t_player;

typedef struct{
    int x,y;
    int hp, fullHp;
    int direction;
    typeShur shuriken;
}t_npc;

typedef struct items{
    int x, y;
    int onMap;
    int nameItems;
}typeItem;
typedef struct save{
    t_player player;
    t_npc npc[25];
    typeItem object[25];
    int numMobs;
    int mapUsed;
    int numShur;
    int numKeys;
}typeSave;
/*_____________________________________________________________*/

FILE *map;
FILE *saveFile;
//void showDisplay (int mapUsed, typePos playerPos, typePos infMob[], typeShur shuriken[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);

int verifyPosition(int x, int y, char direction, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);

void npcMovement(t_npc infMob[], int numMobs, t_player playerPos, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);

void updateShurikenPos(typeShur* shuriken, t_player *player, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);

void updateShurikenPlayer(typeShur *shuriken, t_npc npc[], int numMobs, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);

void shurikenDir(t_npc *npc, t_player playerPos);

void showMenu(int width, int height, bool *endOfGame, bool *openMenu, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue,
            ALLEGRO_JOYSTICK *joy,ALLEGRO_JOYSTICK_STATE joyState, t_npc npcPos[], int *numMobs, t_player *playerPos, int *mapUsed,
            int *numShur, int *numKeys, typeItem items[]);

int saveFunction (t_npc npcPos[], int numMobs, t_player playerPos, int mapUsed, int numShur, int numKeys, typeItem items[]);

void loadSave(t_npc npcPos[], int *numMobs, t_player *playerPos, int *mapUsed, int *numShur, int *numKeys, typeItem items[]);

void drawMobShur(t_npc npcPos[], int numMobs, ALLEGRO_BITMAP *shurikenDraw);

void playerMovement(t_player playerPos, ALLEGRO_EVENT event, char mapMatrix[][SIZEMAP_X], int joystickFound);

void checkKeyShur(t_player *player, typeItem items[], char mapMatrix[][SIZEMAP_X], int numShur, int numKeys);
