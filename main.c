#include <locale.h>
#include "headers.h"
#include "moveMob.c"
#include "maps.c"




int main() {
    setlocale(LC_ALL, "");
    clock_t timeCurrent;
    clock_t timeBegin;
    typePos playerPos, npcPos;
    printf("Hello world!\n");
    playerPos.x = 10;
    playerPos.y = 10;
    npcPos.x = 20;
    npcPos.y = 3;
    npcMovement(npcPos, playerPos, 5);
    printf("Posição do NPC: %d, %d\n", npcPos.x, npcPos.y);
    printf("Posição do Player: %d, %d\n", playerPos.x, playerPos.y);
    timeBegin = clock();
    do{
        timeCurrent = clock();
        if ((double)(timeCurrent - timeBegin) / CLOCKS_PER_SEC > 0.250){
            npcPos = npcMovement(npcPos, playerPos, 5);
            showDisplay(0, playerPos, npcPos);
            timeBegin = clock();
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