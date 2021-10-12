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
    clock_t timeBeginMovementPlayer;
    clock_t timeBeginShuriken;
    clock_t timeBeginFrame;
    float frameRate = 0.05;
    int i;
    typePos playerPos, npcPos[NUM_MOBS];
    typeShur shuriken[NUM_MOBS];
    int flag_ler_nome = 0;
    char nome [20];
    
    
    playerPos.x = 10;
    playerPos.y = 10;
    npcPos[0].x = 10;
    npcPos[0].y = 3;
    npcPos[1].x = 12;
    npcPos[1].y = 5;
    npcPos[0].direction = TOLEFT;
    npcPos[1].direction = TOLEFT;
    npcPos[2].x = 15;
    npcPos[2].y = 3;
    npcPos[3].x = 17;
    npcPos[3].y = 5;
    npcPos[2].direction = TOLEFT;
    npcPos[3].direction = TOLEFT;
    timeBeginMovementPlayer = clock();
    timeBeginShuriken = clock();
    timeBeginMovement = clock();
    timeBeginFrame = clock();
    shuriken[0].throwing = 0;
    shuriken[1].throwing = 0;
    shuriken[2].throwing = 0;
    shuriken[3].throwing = 0;
    char mapMatrix[SIZEMAP_Y][SIZEMAP_X];
    npcMovement(npcPos, playerPos, 5);
    map = fopen("arquivos/maps.bin", "rb");
    rewind(map);
    fseek(map, 0 * SIZEMAP_X * SIZEMAP_Y * sizeof(char), SEEK_SET);
    fread(mapMatrix, sizeof(char), SIZEMAP_X * SIZEMAP_Y, map);
    printf("Hello world!\n");
    do{
        
        timeCurrent = clock();

        /*if ((double)(timeCurrent - timeBeginMovementPlayer) / CLOCKS_PER_SEC > 0.250){
            playerMovement(playerPos, mapMatrix);
            timeBeginMovementPlayer = clock();
        }*/
        for(i = 0; i < NUM_MOBS; i ++){
            if (shuriken[i].throwing  == 0 && 
                    (double)(timeCurrent - timeBeginShuriken) / CLOCKS_PER_SEC > 5){
                shuriken[i].x = npcPos[i].x;
                shuriken[i].y = npcPos[i].y;
                shuriken[i].direction = npcPos[i].direction;
                shuriken[i].throwing = 1;
                timeBeginShuriken = clock();
            }
        }
        
        if ((double)(timeCurrent - timeBeginMovement) / CLOCKS_PER_SEC > 0.5){
            npcMovement(npcPos, playerPos, 5);
            timeBeginMovement = clock();
        }
        if ((double)(timeCurrent - timeBeginShuriken) / CLOCKS_PER_SEC > 0.1){
            throwShuriken(shuriken, playerPos, mapMatrix);
            timeBeginShuriken = clock();
        }

        if ((double)(timeCurrent - timeBeginFrame)/ CLOCKS_PER_SEC > 0.1){
            clearscreen();
            showDisplay(0, playerPos, npcPos, shuriken, mapMatrix);
            timeBeginFrame = clock();
        }
        
    } while (true);
    
    return 0;
}

void sleep_ms(int milliseconds) {
    #ifdef WIN32
        Sleep(milliseconds);
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


#ifdef WIN32
    int _getch(void)
    {
    HANDLE hConsole;
    DWORD cm, n;
    char buffer[4];

    hConsole = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hConsole, &cm);
    SetConsoleMode(hConsole, cm &
                ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
    ReadConsole(hConsole, buffer, 1, &n, NULL);
    SetConsoleMode(hConsole, cm);

    return buffer[0];
    }
#endif