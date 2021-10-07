#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define TOUP 'W'
#define TOLEFT 'A'
#define TODOWN 'S'
#define TORIGHT 'D'
#define WALL '#'
#define SIZEMAP_X 60
#define SIZEMAP_Y 23

int verifyPosition(int x, int y, char direction, char map[SIZEMAP_Y][SIZEMAP_X]);

typedef struct position{
    int x, y;
}typePos;

// Procedure to control the movement of the enemies
void npcMovement(typePos *npcPos, typePos playerPos, int rangeViewMob) {
    int flagMov;
    typePos mobPos = *npcPos;

    srand(time(NULL));

    if (fabs(playerPos.x - mobPos.x) < rangeViewMob && 
                fabs(playerPos.y - mobPos.y) < rangeViewMob){
        if (playerPos.x > mobPos.x){
            if (verifyPosition(mobPos.x, mobPos.y, TORIGHT, map))
            mobPos.x ++;
        }
        else {
            mobPos.x --;        
        }
        if (playerPos.y > mobPos.y){
            mobPos.y ++;        
        }    
        else {
            mobPos.y --;        
        }
    }
    else{
        flagMov = 1 + ((float) rand() / RAND_MAX) * 3;
        switch (flagMov) {
            case 1:
                mobPos.x ++;            
                break;
            case 2:
                mobPos.y ++;            
                break;
            case 3:
                mobPos.x --;            
                break;
            case 4:
                mobPos.y --;            
                break;
        }
    }
    npcPos->x = mobPos.x;
    npcPos->y = mobPos.y;
}

int verifyPosition(int x, int y, char direction, char map[SIZEMAP_Y][SIZEMAP_X]) {
    int validPosition;
    validPosition = 1;

    switch (direction) {
        case TOUP:
            if( map[y + 1] == WALL )
                validPosition = 0;
            break;
        case TOLEFT:
            if ( map[x - 1] == WALL )
                validPosition = 0;
        case TODOWN:
            if( map[y - 1] == WALL )
                validPosition = 0;
            break;
        case TORIGHT:
            if ( map[x + 1] == WALL )
                 validPosition = 0;
            break;
    }
    return validPosition;
}

/*  code to test if movement is working
    typePos playerPos, npcPos;
    playerPos.x = 10;
    playerPos.y = 10;
    npcPos.x = 13;
    npcPos.y = 13;
    npcMovement(&npcPos, playerPos, 5);
    printf("Posição do NPC: %d, %d\n", npcPos.x, npcPos.y);
    printf("Posição do Player: %d, %d\n", playerPos.x, playerPos.y);*/