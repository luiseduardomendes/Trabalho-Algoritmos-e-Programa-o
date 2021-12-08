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
#define MULT 2
#define MINIMAP_SCALE 3
#define OPACITY 0.75
#define TIME_INV 50
#define MIN_XP_UP 25
/*_____________________________________________________________*/

enum directions{UP, DOWN, LEFT, RIGHT};
enum control_buttons{CONTROL_BUTTON_A, CONTROL_BUTTON_B, CONTROL_BUTTON_X, CONTROL_BUTTON_Y, CONTROL_BUTTON_LB, CONTROL_BUTTON_RB,
    CONTROL_BUTTON_OPTIONS, CONTROL_BUTTON_START, CONTROL_BUTTON_L, CONTROL_BUTTON_R};
enum itemsID{shur, keys, armorBuff, lamen};

/*___________________________STRUCTS___________________________*/
typedef struct shuriken{
    int x, y;
    int movex, movey;
    bool throwing;
}typeShur;

typedef struct position{
    int x,y;
    int hp, fullHp;
    int ultBar, fullUltBar;
    int direction;
    int numShur, numKeys;
    int xp;
    int level;
    int invulnerable;
    int armor, shurikenItem;
    typeShur shuriken;
}t_player;

typedef struct{
    int x,y;
    int hp, fullHp;
    int direction;
    int alive;
    typeShur shuriken;
}t_npc;

typedef struct items{
    int x, y;
    int onMap;
    int nameItems;
}typeItem;

typedef struct {
    int itemStore;
    int closed;
    int x, y;
} t_chest;

typedef struct {
    int x, y;
    int onMap;
}t_exit;

typedef struct {
    int x, y;
    int direction;
    typeShur shurikens[8];
    int hp, fullHp;
    int alive;
}t_boss;

typedef struct{
    int numMobs, numShur, numKeys, numChests;
}t_counting;

typedef struct save{
    t_player player;
    t_npc npc[25];
    typeItem object[25];
    t_chest chestItem[10];
    int mapUsed;
    t_counting counting;
    t_boss boss;
}typeSave;

typedef struct{
    ALLEGRO_FONT* font48;
    ALLEGRO_FONT* font36;
}t_fonts;

typedef struct{
    ALLEGRO_BITMAP *naruto,*shurikenDraw,*spikes,*keys,*enemy,*wall,*grass,*darkGrass,*lightGrass,*heart,*voidheart,*narutoDialog,
    *loading_screen,*background,*dialogBmp,*narutoback,*narutoleft,*narutoright,*enemyback,*enemyleft,*enemyright,*chest,*openchest,
    *trapdoor,*XPbarEmptyLeft,*XPbarEmptyMid,*XPbarEmptyRight,*XPbarFullMid,*XPbarFullLeft,*XPbarFullRight,*enemyBoss,*miniMap;
}bitmaps, t_bitmaps;


FILE *map;
FILE *saveFile;

// attacks.c
void updateShurikenPos(typeShur *shuriken, t_player *player, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
void updateShurikenPlayer(t_player *player, t_npc npc[], t_boss *boss, int numMobs, char mapMatrix[SIZEMAP_Y][SIZEMAP_X], t_exit *mapExit);
void shurikenDir(t_npc *npc, t_player playerPos, ALLEGRO_SAMPLE* throwShur);
void shurikenDirBoss(t_boss *boss, t_player playerPos, ALLEGRO_SAMPLE* throwShur);
void updateShurikenBoss(t_boss *boss, t_player *player, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);

// controlls.c
/*
void moveJoystick(ALLEGRO_EVENT event, t_player *playerPos, int *openMenu, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
void buttonDown(ALLEGRO_EVENT event, t_player *playerPos, int *openMenu, char mapMatrix[][SIZEMAP_X], typeItem items[], int numShur,
                int numKeys, int numChest, t_chest chests[], ALLEGRO_SAMPLE* throwShur, t_exit *mapExit, int mapUsed, int *endOfLevel);
void playerInputKeyboard(ALLEGRO_EVENT event, t_player *playerPos, int *openMenu, char mapMatrix[SIZEMAP_Y][SIZEMAP_X], typeItem items[],
                int numShur, int numKeys, int numChest, t_chest chests[], ALLEGRO_SAMPLE* throwShur, t_exit *mapExit, int mapUsed, int *endOfLevel);
*/
// draw.c
void drawMobs(t_npc npcPos[], int numMobs, bitmaps bmps, t_player playerPos);
void drawMobShur(t_npc npcPos[], int numMobs, ALLEGRO_BITMAP *shurikenDraw, t_player playerPos);
ALLEGRO_BITMAP* createBackground(bitmaps bmps, ALLEGRO_DISPLAY* display,
            char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
void createMiniMap(char mapMatrix[][SIZEMAP_X], ALLEGRO_BITMAP** miniMap, ALLEGRO_DISPLAY *display, t_player player);

// level.c
void levelUp(t_player *player);

// maps.c
void loadMap (char mapMatrix[SIZEMAP_Y][SIZEMAP_X], int mapUsed);

//menuPause.c
/*void showMenu(int width, int height, bool *endOfGame, bool *openMenu, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue,
            ALLEGRO_JOYSTICK *joy,ALLEGRO_JOYSTICK_STATE joyState, t_npc npcPos[], int *numMobs, t_player *playerPos, int *mapUsed,
            int *numShur, int *numKeys, int *numChest, typeItem items[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X], t_chest chests[],
            int *playerLogout, t_boss *boss);
int saveFunction (t_npc npcPos[], int numMobs, t_player playerPos, int mapUsed, int numShur, int numKeys, int numChest,
            typeItem items[], t_chest chests[], t_boss boss);
void loadSave(t_npc npcPos[], int *numMobs, t_player *playerPos, int *mapUsed, int *numShur, int *numKeys, int *numChest,
            typeItem items[], t_chest chests[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X], t_boss *boss);
void menuIniciar(int width, int height, bool *endOfGame, int *endOfLevel, int *playerLogout, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue,
            ALLEGRO_JOYSTICK *joy, ALLEGRO_JOYSTICK_STATE joyState, t_npc npcPos[], int *numMobs, t_player *playerPos, int *mapUsed,
            int *numShur, int *numKeys, int *numChest, typeItem items[], t_chest chests[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X], t_boss *boss);
void standardSave(int mapUsed);
*/
// move.c
void npcMovement(t_npc mobPos[], int numMobs, t_player *playerPos, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
void moveBoss(t_boss *boss, t_player *player, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
int verifyPosition(int x, int y, char direction, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]);
//void checkKeyShur(t_player *player, typeItem items[], char mapMatrix[][SIZEMAP_X], int numShur, int numKeys, int numChest, t_chest chests[],
//                t_exit *mapExit, int mapUsed, int *endOfLevel);

