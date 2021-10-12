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
    clock_t timeBeginMovement;
    clock_t timeBeginShuriken;
    clock_t timeBeginFrame;
    float frameRate = 0.05;
    typePos playerPos, npcPos[NUM_MOBS], shuriken;
    int throwing = 0;
    printf("Hello world!\n");
    playerPos.x = 10;
    playerPos.y = 10;
    npcPos[0].x = 10;
    npcPos[0].y = 3;
    npcPos[1].x = 12;
    npcPos[1].y = 5;
    npcPos.direction = TOLEFT;
    npcMovement(npcPos, playerPos, 5);
    timeBeginMovement = clock();
    timeBeginShuriken = clock();
    timeBeginFrame = clock();
            
    do{
        timeCurrent = clock();
        if (!(throwing)){
            shuriken.x = npcPos.x;
            shuriken.y = npcPos.y;
            shuriken.direction = npcPos.direction;
            throwing = 1;
            timeBeginShuriken = clock();
        }
        if ((double)(timeCurrent - timeBeginMovement) / CLOCKS_PER_SEC > 0.250){
            npcPos = npcMovement(npcPos[], playerPos, 5);
            timeBeginMovement = clock();
        }
        if (throwing){
            throwing = throwShuriken(timeCurrent, timeBeginShuriken, &shuriken, playerPos);
        }
        if ((double)(timeCurrent - timeBeginFrame)/ CLOCKS_PER_SEC > 0.05){
            clearscreen();
            showDisplay(0, playerPos, npcPos[], shuriken);
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
