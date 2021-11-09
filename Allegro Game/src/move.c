#include "headers.h"
// Procedure to control the movement of the enemies
void npcMovement(t_npc mobPos[], int numMobs, t_player playerPos, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]) {
    int flagMov, moved;
    int i;


    srand(time(NULL));


    for (i = 0; i < NUM_MOBS; i ++){

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

void checkKeyShur(t_player *player, typeItem items[], char mapMatrix[][SIZEMAP_X], int numShur, int numKeys, int numChest, t_chest chests[])
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
        else if (chests[i].x == player->x && chests[i].y == player->y && chests[i].closed == 1){
            switch(chests[i].itemStore){
            case shur:
                player->numShur ++;
                break;
            case keys:
                player->numKeys ++;
                break;
            case armorBuff:
                player->fullHp ++;
                player->hp ++;
                break;
            case shurikenBuff:
                break;
            case lamen:
                player->hp ++;
                break;
            }
            chests[i].closed = 0;
        }
    }


}
//void playerMovement(typePos *playerPos, ALLEGRO_EVENT event, char mapMatrix[][SIZEMAP_X], int joystickFound)
/*{
    bool openMenu = false;

    switch (event.keyboard.keycode){
        case ALLEGRO_KEY_UP:
        case ALLEGRO_KEY_W:
            if (verifyPosition(playerPos.x, playerPos.y, TOUP, mapMatrix)){
                playerPos.y --;
                playerPos.direction = UP;
            }
            break;
        case ALLEGRO_KEY_DOWN:
        case ALLEGRO_KEY_S:
            if (verifyPosition(playerPos.x, playerPos.y, TODOWN, mapMatrix)) {
                playerPos.y ++;
                playerPos.direction = DOWN;
            }
            break;
        case ALLEGRO_KEY_LEFT:
        case ALLEGRO_KEY_A:
            if (verifyPosition(playerPos.x, playerPos.y, TOLEFT, mapMatrix)) {
                playerPos.x --;
                playerPos.direction = LEFT;
            }
            break;
        case ALLEGRO_KEY_RIGHT:
        case ALLEGRO_KEY_D:
            if (verifyPosition(playerPos.x, playerPos.y, TORIGHT, mapMatrix)){
                playerPos.x ++;
                playerPos.direction = RIGHT;
            }
            break;
        case ALLEGRO_KEY_ESCAPE:
            openMenu = true;
            if (joystickFound)
                showMenu(width, height, &endOfGame, &openMenu, display, events_queue, joy, joyState, npcPos, &playerPos, &mapUsed);
            else
                showMenu(width, height, &endOfGame, &openMenu, display, events_queue, NULL, joyState, npcPos, &playerPos, &mapUsed);
            break;
        case ALLEGRO_KEY_K:
            if (!playerPos.shuriken.throwing){
                playerPos.shuriken.throwing = true;
                playerPos.shuriken.x = playerPos.x;
                playerPos.shuriken.y = playerPos.y;
                switch (playerPos.direction) {
                    case UP:
                        playerPos.shuriken.movex = 0;
                        playerPos.shuriken.movey = -1;
                        break;
                    case DOWN:
                        playerPos.shuriken.movex = 0;
                        playerPos.shuriken.movey = 1;
                        break;
                    case LEFT:
                        playerPos.shuriken.movex = -1;
                        playerPos.shuriken.movey = 0;
                        break;
                    case RIGHT:
                        playerPos.shuriken.movex = 1;
                        playerPos.shuriken.movey = 0;
                        break;
                }
            }
            break;
    }
}*/


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
