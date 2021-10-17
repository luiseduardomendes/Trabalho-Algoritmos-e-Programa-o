#include "headers.h"
void showDisplay (int mapUsed, typePos playerPos, typePos infMob[], typeShur shuriken[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
    int i, j, k, mobFound = 0, shurikenFound, playerFound;

    for(i = 0; i < SIZEMAP_Y; i++){
        for(j = 0; j < SIZEMAP_X; j++){
            mobFound = 0;
            playerFound = 0;
            shurikenFound = 0;
            for(k = 0; k < NUM_MOBS; k++){
                if((infMob[k].x == j) && (infMob[k].y == i)){
                    printf("M");
                    mobFound = 1;
                }
            }
            if(mobFound == 0){
                if (playerPos.y == i && playerPos.x == j){
                    printf("P");
                    playerFound = 1;
                }
                else {
                    for(k = 0; k < NUM_MOBS; k++){
                        if((shuriken[k].x == j) && (shuriken[k].y == i)){
                            printf("Z");
                            shurikenFound = 1;
                        }
                    }
                    if(!(shurikenFound)){
                        printf("%c", mapMatrix[i][j]);
                    }
                }
            }
        }
        printf("\n");
    }
}
