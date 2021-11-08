#include "headers.h"
// Procedure to control the movement of the enemies
void npcMovement(t_npc mobPos[], int numMobs, t_player playerPos, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]) {
    int flagMov;
    int i;


    srand(time(NULL));


    for (i = 0; i < NUM_MOBS; i ++){
        flagMov = (rand() % 4);
        if (fabs(playerPos.x - mobPos[i].x) < RANGEVIEWMOB && fabs(playerPos.y - mobPos[i].y) < RANGEVIEWMOB){
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
                case 0:
                    if (verifyPosition(mobPos[i].x, mobPos[i].y, TORIGHT, mapMatrix)){
                        mobPos[i].x ++;
                        mobPos[i].direction = RIGHT;
                    }
                    break;
                case 1:
                    if (verifyPosition(mobPos[i].x, mobPos[i].y, TOUP, mapMatrix)){
                        mobPos[i].y --;
                        mobPos[i].direction = UP;
                    }
                    break;
                case 2:
                    if (verifyPosition(mobPos[i].x, mobPos[i].y, TOLEFT, mapMatrix)){
                        mobPos[i].x --;
                        mobPos[i].direction = LEFT;
                    }
                    break;
                case 3:
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

void checkKeyShur(t_player *player, typeItem items[], char mapMatrix[][SIZEMAP_X], int numShur, int numKeys)
{
    int i = 0;

    for (i = 0; i < numShur + numKeys; i ++){
        if(items[i].x == player->x && items[i].y == player->y && items[i].onMap == 1){
            items[i].onMap = 0;
            switch (items[i].nameItems){
            case keys:
                player->numKeys ++;
                break;
            case shur:
                player->numShur ++;
                break;
            }
        }
    }


}
