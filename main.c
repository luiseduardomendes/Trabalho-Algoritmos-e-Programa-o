#include <locale.h>
#include <stdlib.h>
#include "headers.h"
#include "attacks.c"
#include "move.c"
#include "maps.c"
#include <unistd.h>
#include <termios.h>

void clearscreen();

void init_attr(void) ;
void close_attr(void) ;
int kbhit(void) ;
struct termios old_attr, new_attr;

int main() {
    setlocale(LC_ALL, "");
    clock_t timeCurrent;
    clock_t timeBeginMovement;
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
    init_attr();
    do{
        flag_ler_nome = kbhit() ;

        if(flag_ler_nome == 'k') {
            break;
        } 
        timeCurrent = clock();

        for(i = 0; i < NUM_MOBS; i ++){
            if (shuriken[i].throwing  == 0 && 
                    (double)(timeCurrent - timeBeginShuriken) / CLOCKS_PER_SEC < 5){
                shuriken[i].x = npcPos[i].x;
                shuriken[i].y = npcPos[i].y;
                shuriken[i].direction = npcPos[i].direction;
                shuriken[i].throwing = 1;
                timeBeginShuriken = clock();
            }
        }
        
        if ((double)(timeCurrent - timeBeginMovement) / CLOCKS_PER_SEC > 0.250){
            npcMovement(npcPos, playerPos, 5);
            timeBeginMovement = clock();
        }
        if ((double)(timeCurrent - timeBeginShuriken) / CLOCKS_PER_SEC > 0.25){
            throwShuriken(shuriken, playerPos, mapMatrix);
        }

        if ((double)(timeCurrent - timeBeginFrame)/ CLOCKS_PER_SEC > 0.25){
            clearscreen();
            showDisplay(0, playerPos, npcPos, shuriken, mapMatrix);
            timeBeginFrame = clock();
        }
        
    } while (true);
    close_attr();
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

/*
 * [dkbhit.c]
 * Simula a função kbhit().
 *
 * [Autor]
 * Daemonio (Marcos Paulo Ferreira)
 * undefinido at gmail com
 * https://daemoniolabs.wordpress.com
 *
 * Versão 1.0, by daemonio @ Thu Dec 27 20:40:22 BRST 2012
 */



void init_attr(void) {
    /* Obtém as configurações atuais. */
    tcgetattr(0,&old_attr);
    new_attr=old_attr;

    /* Desliga modo canônico. */
    new_attr.c_lflag &=~ICANON ;

    /* Desliga ecoamento. */
    new_attr.c_lflag &= ~ECHO;

    new_attr.c_cc[VTIME]=0 ;
    new_attr.c_cc[VMIN]=0 ;
}

/* Retorna configurações antigas. */
void close_attr(void) {
    tcsetattr(STDIN_FILENO,TCSANOW,&old_attr);
}

int kbhit(void) {
    int c ;

    tcsetattr(STDIN_FILENO,TCSANOW,&new_attr);
    c = getchar() ; /* retorna EOF se nada foi pressionado */
    tcsetattr(STDIN_FILENO,TCSANOW,&old_attr);

    return c ;
}

