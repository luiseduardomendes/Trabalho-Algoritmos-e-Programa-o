#include "headers.h"
// Procedure to control the movement of the enemies
void npcMovement(typePos mobPos[], typePos playerPos, int rangeViewMob, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]) {
    int flagMov;
    int i;


    srand(time(NULL));


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

/* VERIFICA AS FUTURAS POSIÇÕES DA SHURIKEN. CASO O MOB ESTEJA NA MESMA LINHA DE UM PLAYER, E NÃO TIVER NENHUMA PAREDE ENTRE ELES, ELE IRÁ ATIRAR.
int verifyShuriken(typePos *shuriken, typePos npcPos, typePos playerPos, char mapMatrix[SIZEMAP_Y][SIZEMAP_X])
{
    int validPosition;
    int i;
    validPosition = false;
    clock_t timeBeginShuriken;

    if(npcPos.x == playerPos.x)
    {
        if(npcPos.y >= playerPos.y)
        {
            for(i = npcPos.y; i < playerPos.y; i--)
            {
                if (mapMatrix[i][npcPos.x] != WALL)
                {
                    validPosition = true;
                    npcPos.shuriken.movex = 0;
                    npcPos.shuriken.movey = -1;
                }
            }
        }
        else
        {
            for(i = playerPos.y; i < npcPos.y; i++)
            {
                if(mapMatrix[i][playerPos.x] != WALL)
                {
                    validPosition = true;
                    npcPos.shuriken.movex = 0;
                    npcPos.shuriken.movey = 1;
                }
            }
        }
    }
    else if(npcPos.y == playerPos.y)
    {
        if(npcPos.x >= playerPos.x)
        {
            for(i = npcPos.x; i < playerPos.x; i--)
            {
                if (mapMatrix[npcPos.y][i] != WALL)
                {
                    validPosition = true;
                    npcPos.shuriken.movex = -1;
                    npcPos.shuriken.movey = 0;
                }
            }
        }
        else
        {
            for(i = playerPos.x; i < npcPos.x; i++)
            {
                if(mapMatrix[playerPos.y][i] != WALL)
                {
                    validPosition = true;
                    npcPos.shuriken.movex = 1;
                    npcPos.shuriken.movey = 0;
                }
            }
        }
    }
    return validPosition;
}
*/
