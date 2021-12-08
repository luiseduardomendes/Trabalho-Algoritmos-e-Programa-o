#include "headers.h"
// Procedure to control the movement of the enemies
void npcMovement(t_npc mobPos[], int numMobs, t_player *playerPos, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]) {
    int flagMov, moved;
    int i;


    srand(time(NULL));


    for (i = 0; i < numMobs; i ++){
        if(mobPos[i].alive){
            if (fabs(playerPos->x - mobPos[i].x) < RANGEVIEWMOB && fabs(playerPos->y - mobPos[i].y) < RANGEVIEWMOB){
                if (playerPos->x > mobPos[i].x){
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
                if (playerPos->y > mobPos[i].y){
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
                do {
                    flagMov = (rand() % 4);
                    moved = 1;
                    switch (flagMov) {
                        case 0:
                            if (verifyPosition(mobPos[i].x, mobPos[i].y, TORIGHT, mapMatrix)){
                                mobPos[i].x ++;
                                mobPos[i].direction = RIGHT;
                            }
                            else{
                                moved = 0;
                            }
                            break;
                        case 1:
                            if (verifyPosition(mobPos[i].x, mobPos[i].y, TOUP, mapMatrix)){
                                mobPos[i].y --;
                                mobPos[i].direction = UP;
                            }
                            else{
                                moved = 0;
                            }
                            break;
                        case 2:
                            if (verifyPosition(mobPos[i].x, mobPos[i].y, TOLEFT, mapMatrix)){
                                mobPos[i].x --;
                                mobPos[i].direction = LEFT;
                            }
                            else{
                                moved = 0;
                            }
                            break;
                        case 3:
                            if (verifyPosition(mobPos[i].x, mobPos[i].y, TODOWN, mapMatrix)){
                                mobPos[i].y ++;
                                mobPos[i].direction = DOWN;
                            }
                            else{
                                moved = 0;
                            }
                            break;
                    }
                } while (!moved);
            }
            if(mobPos[i].x == playerPos->x && mobPos[i].y == playerPos->y && !playerPos->invulnerable)
                if(playerPos->invulnerable == 0)
                {
                    playerPos->hp --;
                    playerPos->invulnerable = TIME_INV;
                }
        }
    }
}

void moveBoss(t_boss *boss, t_player *player, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){

    if(boss->alive) {
        if (player->x > boss->x){
            if (verifyPosition(boss->x, boss->y, TORIGHT, mapMatrix)) {
                boss->x ++;
                boss->direction = RIGHT;
            }
        }
        else {
            if (verifyPosition(boss->x, boss->y, TOLEFT, mapMatrix)) {
                boss->x --;
                boss->direction = LEFT;
            }
        }
        if (player->y > boss->y){
            if (verifyPosition(boss->x, boss->y, TODOWN, mapMatrix)) {
                boss->y ++;
                boss->direction = DOWN;
            }
        }
        else {
            if (verifyPosition(boss->x, boss->y, TOUP, mapMatrix)) {
                boss->y --;
                boss->direction = UP;
            }
        }
    }
    if(boss->x == player->x && boss->y == player->y && !player->invulnerable)
        if(player->invulnerable == 0)
        {
            player->hp --;
            player->invulnerable = TIME_INV;
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

void checkKeyShur(t_player *player, typeItem items[], char mapMatrix[][SIZEMAP_X], t_counting counting, t_chest chests[], t_exit *mapExit, int mapUsed, int *endOfLevel)
{
    int i = 0;

    for (i = 0; i < counting.numShur + counting.numKeys; i ++){
        if(items[i].x == player->x && items[i].y == player->y && items[i].onMap == 1){
            items[i].onMap = 0;
            switch (items[i].nameItems){
            case keys:
                player->numKeys ++;

                if(player->numKeys >= counting.numKeys && mapUsed != 2)
                {
                    mapExit->y = 20;
                    mapExit->x = 33;
                    mapExit->onMap = 1;
                }
                break;
            case shur:
                player->numShur ++;
                break;
            }
        }
        else
        if (chests[i].x == player->x && chests[i].y == player->y && chests[i].closed == 1)
        {
            switch(chests[i].itemStore){
            case shur:
                player->numShur ++;
                break;
            case keys:
                player->numKeys ++;
                if(player->numKeys == counting.numKeys && mapUsed != 2)
                {
                    mapExit->y = 20;
                    mapExit->x = 33;
                    mapExit->onMap = 1;
                }
            break;
            case armorBuff:
                player->fullHp ++;
                player->hp ++;
                break;
            case lamen:
                if (player->hp < player->fullHp)
                    player->hp ++;
                break;
            }
            chests[i].closed = 0;
        }
    }
    if (mapExit->x == player->x && mapExit->y == player->y && mapExit->onMap == 1){
        *endOfLevel = 1;
    }
}

float ultDist(t_player player, t_npc npc, t_boss boss){
    float dist;

    dist = sqrt(pow(npc.x - player.x, 2) + pow(npc.y - player.y, 2));

    return dist;
}
