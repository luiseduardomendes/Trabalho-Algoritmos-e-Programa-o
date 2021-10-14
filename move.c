#include "headers.h"
// Procedure to control the movement of the enemies
void npcMovement(typePos mobPos[], typePos playerPos, int rangeViewMob) {
    int flagMov;
    int mapUsed = 0;
    int i;


    srand(time(NULL));

    char mapMatrix[SIZEMAP_Y][SIZEMAP_X];
    map = fopen("arquivos/maps.bin", "rb");

    rewind(map);
    fseek(map, mapUsed * SIZEMAP_X * SIZEMAP_Y * sizeof(char), SEEK_SET);
    fread(mapMatrix, sizeof(char), SIZEMAP_X * SIZEMAP_Y, map);
    for (i = 0; i < NUM_MOBS; i ++){
        flagMov = (1 + (rand() % 4));
        if (fabs(playerPos.x - mobPos[i].x) < rangeViewMob &&
        fabs(playerPos.y - mobPos[i].y) < rangeViewMob){
            if (playerPos.x > mobPos[i].x){
                if (verifyPosition(mobPos[i].x, mobPos[i].y, TORIGHT, mapMatrix)) {
                    mobPos[i].x ++;
                    mobPos[i].direction = RIGHT;
                }
            }
            else {
                if (verifyPosition(mobPos[i].x, mobPos[i].y, TOLEFT, mapMatrix)) {
                    mobPos[i].x --;
                    mobPos[i].direction = LEFT;
                }
            }
            if (playerPos.y > mobPos[i].y){
                if (verifyPosition(mobPos[i].x, mobPos[i].y, TODOWN, mapMatrix)) {
                    mobPos[i].y ++;
                    mobPos[i].direction = DOWN;
                }
            }
            else {
                if (verifyPosition(mobPos[i].x, mobPos[i].y, TOUP, mapMatrix)) {
                    mobPos[i].y --;
                    mobPos[i].direction = UP;
                }
            }
        }
        else{

            switch (flagMov) {
                case 1:
                    if (verifyPosition(mobPos[i].x, mobPos[i].y, TORIGHT, mapMatrix)){
                        mobPos[i].x ++;
                        mobPos[i].direction = RIGHT;
                    }
                    break;
                case 2:
                    if (verifyPosition(mobPos[i].x, mobPos[i].y, TOUP, mapMatrix)){
                        mobPos[i].y --;
                        mobPos[i].direction = UP;
                    }
                    break;
                case 3:
                    if (verifyPosition(mobPos[i].x, mobPos[i].y, TOLEFT, mapMatrix)){
                        mobPos[i].x --;
                        mobPos[i].direction = LEFT;
                    }
                    break;
                case 4:
                    if (verifyPosition(mobPos[i].x, mobPos[i].y, TODOWN, mapMatrix)){
                        mobPos[i].y ++;
                        mobPos[i].direction = DOWN;
                    }
                    break;
            }
        }
    }
}

int verifyPosition(int x, int y, char direction, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]) {
    int validPosition;
    validPosition = true;

    switch (direction) {
        case TOUP:
            if ( mapMatrix[y - 1][x] == WALL )
                validPosition = false;
            break;
        case TOLEFT:
            if ( mapMatrix[y][x - 1] == WALL )
                    validPosition = false;
            break;
        case TODOWN:
            if ( mapMatrix[y + 1][x] == WALL )
                validPosition = false;
            break;
        case TORIGHT:
            if ( mapMatrix[y][x + 1] == WALL )
                validPosition = false;
            break;
    }
    return validPosition;
}
