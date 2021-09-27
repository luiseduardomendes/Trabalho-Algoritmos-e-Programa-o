#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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

/*  code to test if movement is working
    typePos playerPos, npcPos;
    playerPos.x = 10;
    playerPos.y = 10;
    npcPos.x = 13;
    npcPos.y = 13;
    npcMovement(&npcPos, playerPos, 5);
    printf("Posição do NPC: %d, %d\n", npcPos.x, npcPos.y);
    printf("Posição do Player: %d, %d\n", playerPos.x, playerPos.y);*/