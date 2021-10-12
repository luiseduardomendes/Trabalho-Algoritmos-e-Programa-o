#include <locale.h>
#include <stdlib.h>
#include "headers.h"
#include "attacks.c"
#include "move.c"
#include "maps.c"

void clearscreen();

int main() {
    setlocale(LC_ALL, "");
    clock_t timeCurrent;
    clock_t timeBeginMovement[NUM_MOBS];
    clock_t timeBeginShuriken[NUM_MOBS];
    clock_t timeBeginFrame;
    float frameRate = 0.05;
    int i;
    typePos playerPos, npcPos[NUM_MOBS];
    typeShur shuriken[NUM_MOBS];
    
    playerPos.x = 10;
    playerPos.y = 10;
    npcPos[0].x = 10;
    npcPos[0].y = 3;
    npcPos[1].x = 12;
    npcPos[1].y = 5;
    npcPos[0].direction = TOLEFT;
    npcPos[1].direction = TOLEFT;
    timeBeginShuriken[0] = clock();
    timeBeginShuriken[1] = clock();
    timeBeginMovement[0] = clock();
    timeBeginMovement[1] = clock();
    timeBeginFrame = clock();
    shuriken[0].throwing = 0;
    shuriken[1].throwing = 0;
    char mapMatrix[SIZEMAP_Y][SIZEMAP_X];
    npcMovement(npcPos[0], playerPos, 5);
    map = fopen("arquivos/maps.bin", "rb");
    rewind(map);
    fseek(map, 0 * SIZEMAP_X * SIZEMAP_Y * sizeof(char), SEEK_SET);
    fread(mapMatrix, sizeof(char), SIZEMAP_X * SIZEMAP_Y, map);
    printf("Hello world!\n");
            
    do{
        timeCurrent = clock();
        for(i = 0; i < NUM_MOBS; i ++){
            if ((shuriken[i].throwing  == 0 && (double)(timeCurrent - timeBeginShuriken[i]) / CLOCKS_PER_SEC < 5)){
                shuriken[i].x = npcPos[i].x;
                shuriken[i].y = npcPos[i].y;
                shuriken[i].direction = npcPos[i].direction;
                shuriken[i].throwing = 1;
                timeBeginShuriken[i] = clock();
            }
        }
        for (i = 0; i < NUM_MOBS; i ++) {
            if ((double)(timeCurrent - timeBeginMovement[i]) / CLOCKS_PER_SEC > 0.250){
                npcPos[i] = npcMovement(npcPos[i], playerPos, 5);
                timeBeginMovement[i] = clock();
            }
        }
        if (shuriken[i].throwing == 1) {
            for(i = 0; i < NUM_MOBS; i ++) {
                if ((double)(timeCurrent - timeBeginShuriken[i]) / CLOCKS_PER_SEC > 0.1){
                    throwShuriken(&shuriken[i], playerPos, mapMatrix);
                }
            }
        }
        if ((double)(timeCurrent - timeBeginFrame)/ CLOCKS_PER_SEC > 0.05){
            clearscreen();
            showDisplay(0, playerPos, npcPos, shuriken, mapMatrix);
            timeBeginFrame = clock();
        }
        
    } while (true);
    return 0;
}

void sleep_ms(int milliseconds) {
    #ifdef WIN32
        _sleep(milliseconds);
    #elif _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #else
        usleep(milliseconds * 1000);
    #endif
}

void clearscreen(){
  #ifdef WIN32
    system("cls");
  #else
    system("clear");
  #endif
}
