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

int readMap(char mapMatrix[][SIZEMAP_X], int mapUsed, int *numMobs, int *numShur, int *numKeys){
    FILE* localMap;
    int flag = 1;
    int i, j;
    char bufferCh[SIZEMAP_X];

    char mapNames[ ][99] = {{"arquivos/map1.txt"},
                            {"arquivos/map2.txt"},
                            {"arquivos/map3.txt"},
                            {"arquivos/map4.txt"}};
    localMap = fopen(mapNames[mapUsed], "r");
    if (localMap != NULL){
        switch (mapUsed){
        case 0:
            *numMobs = 5;
            *numShur = 5;
            *numKeys = 5;
            break;
        case 1:
            *numMobs = 8;
            *numShur = 8;
            *numKeys = 8;
            break;
        case 2:
            *numMobs = 10;
            *numShur = 10;
            *numKeys = 10;
            break;
        default:
            *numMobs = 10;
            *numShur = 10;
            *numKeys = 10;
        }

        rewind(localMap);

        for (i = 0; i < SIZEMAP_Y; i ++) {
            fgets(bufferCh, SIZEMAP_X, localMap);
            for (j = 0; j < SIZEMAP_X; j ++) {
                mapMatrix[i][j] = bufferCh[j];
            }
        }
        fclose(localMap);
    }
    else {
        flag = 0;
    }
    return flag;
}
