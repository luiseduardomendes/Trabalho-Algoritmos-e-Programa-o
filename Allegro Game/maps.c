#include "headers.h"
void showDisplay (int mapUsed, t_player playerPos, t_npc infMob[], typeShur shuriken[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
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

void loadMap (char mapMatrix[SIZEMAP_Y][SIZEMAP_X], int mapUsed){

    char buffer[SIZEMAP_X+3];
    char mapFileName[99][50] = {{"arquivos/map64x36.txt"},
                                {"arquivos/map2.64x36.txt"}};
    int i, j;

    map = fopen(mapFileName[mapUsed], "r");
    rewind(map);
    for (i = 0; i < SIZEMAP_Y; i ++){
        fgets(buffer, SIZEMAP_X+3, map);
        for (j = 0; j < SIZEMAP_X; j ++){
            mapMatrix[i][j] = buffer[j];
        }
    }
}

