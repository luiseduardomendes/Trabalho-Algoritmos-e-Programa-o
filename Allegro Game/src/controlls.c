#include "headers.h"

void moveJoystick(ALLEGRO_EVENT event, t_player *playerPos, int *openMenu, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
    if(event.joystick.axis == 0){

        if (event.joystick.pos > 0.25){

            if (verifyPosition(playerPos->x, playerPos->y, TORIGHT, mapMatrix)) {
                playerPos->x ++;
                playerPos->direction = RIGHT;
                if(mapMatrix[playerPos->y][playerPos->x] == 'X') {
                    playerPos->hp --;
                    playerPos->invulnerable = 5;
                }
            }
        }

        else if (event.joystick.pos < -0.25) {
                if (verifyPosition(playerPos->x, playerPos->y, TOLEFT, mapMatrix)) {
                    playerPos->x --;
                    playerPos->direction = LEFT;
                    if(mapMatrix[playerPos->y][playerPos->x] == 'X') {
                        playerPos->hp --;
                        playerPos->invulnerable = 5;
                    }
                }

        }
    }
    else if(event.joystick.axis == 1){
        switch((int)round(event.joystick.pos)){
            case 1:
                if (verifyPosition(playerPos->x, playerPos->y, TODOWN, mapMatrix)) {
                    playerPos->y ++;
                    playerPos->direction = DOWN;
                    if(mapMatrix[playerPos->y][playerPos->x] == 'X') {
                        playerPos->hp --;
                        playerPos->invulnerable = 5;
                    }
                }
            break;
            case -1:
                if (verifyPosition(playerPos->x, playerPos->y, TOUP, mapMatrix)) {
                    playerPos->y --;
                    playerPos->direction = UP;
                    if(mapMatrix[playerPos->y][playerPos->x] == 'X') {
                        playerPos->hp --;
                        playerPos->invulnerable = 5;
                    }
                }
            break;
        }
    }
}

void buttonDown(ALLEGRO_EVENT event, t_player *playerPos, int *openMenu, char mapMatrix[][SIZEMAP_X], typeItem items[], int numShur,
                int numKeys, int numChest, t_chest chests[], ALLEGRO_SAMPLE* throwShur, t_exit *mapExit, int *mapUsed, int *endOfLevel){
    al_init_acodec_addon();
    al_install_audio();
    switch (event.joystick.button){
        case CONTROL_BUTTON_A:
            break;
        case CONTROL_BUTTON_B:
            checkKeyShur(playerPos, items, mapMatrix, numShur, numKeys, numChest, chests, mapExit, &mapUsed, endOfLevel);
            break;
        case CONTROL_BUTTON_X:
            //printf("botao X\n");
            if (!playerPos->shuriken.throwing && playerPos->numShur > 0) {
                //al_play_sample_instance(throwShurInst);
                al_play_sample(throwShur, 0.5, 0.0, 0.75, ALLEGRO_PLAYMODE_ONCE, 0);
                playerPos->numShur --;
                playerPos->shuriken.throwing = true;
                playerPos->shuriken.x = playerPos->x;
                playerPos->shuriken.y = playerPos->y;
                switch (playerPos->direction) {
                    case UP:
                        playerPos->shuriken.movex = 0;
                        playerPos->shuriken.movey = -1;
                        break;
                    case DOWN:
                        playerPos->shuriken.movex = 0;
                        playerPos->shuriken.movey = 1;
                        break;
                    case LEFT:
                        playerPos->shuriken.movex = -1;
                        playerPos->shuriken.movey = 0;
                        break;
                    case RIGHT:
                        playerPos->shuriken.movex = 1;
                        playerPos->shuriken.movey = 0;
                        break;
                }
            }
            break;
        case CONTROL_BUTTON_Y:
            break;
        case CONTROL_BUTTON_LB:
            break;
        case CONTROL_BUTTON_RB:
            break;
        case CONTROL_BUTTON_OPTIONS:
            break;
        case CONTROL_BUTTON_START:
            *openMenu = true;
            break;
        case CONTROL_BUTTON_L:
            //printf("botao L3\n");
            break;
        case CONTROL_BUTTON_R:
            //printf("botao R3\n");
            break;
    }
}

void playerInputKeyboard(ALLEGRO_EVENT event, t_player *playerPos, int *openMenu, char mapMatrix[SIZEMAP_Y][SIZEMAP_X], typeItem items[],
                         int numShur, int numKeys, int numChest, t_chest chests[], ALLEGRO_SAMPLE* throwShur, t_exit *mapExit, int *mapUsed, int *endOfLevel) {
    al_init_acodec_addon();
    al_install_audio();
    switch (event.keyboard.keycode){
        case ALLEGRO_KEY_UP:
        case ALLEGRO_KEY_W:
            if (verifyPosition(playerPos->x, playerPos->y, TOUP, mapMatrix)){
                playerPos->y --;
                playerPos->direction = UP;
                if(mapMatrix[playerPos->y][playerPos->x] == 'X') {
                    playerPos->hp --;
                    playerPos->invulnerable = 5;
                }
            }
            break;
        case ALLEGRO_KEY_DOWN:
        case ALLEGRO_KEY_S:
            if (verifyPosition(playerPos->x, playerPos->y, TODOWN, mapMatrix)) {
                playerPos->y ++;
                playerPos->direction = DOWN;
                if(mapMatrix[playerPos->y][playerPos->x] == 'X') {
                    playerPos->hp --;
                    playerPos->invulnerable = 5;
                }
            }
            break;
        case ALLEGRO_KEY_LEFT:
        case ALLEGRO_KEY_A:
            if (verifyPosition(playerPos->x, playerPos->y, TOLEFT, mapMatrix)) {
                playerPos->x --;
                playerPos->direction = LEFT;
                if(mapMatrix[playerPos->y][playerPos->x] == 'X') {
                    playerPos->hp --;
                    playerPos->invulnerable = 5;
                }
            }
            break;
        case ALLEGRO_KEY_RIGHT:
        case ALLEGRO_KEY_D:
            if (verifyPosition(playerPos->x, playerPos->y, TORIGHT, mapMatrix)){
                playerPos->x ++;
                playerPos->direction = RIGHT;
                if(mapMatrix[playerPos->y][playerPos->x] == 'X') {
                    playerPos->hp --;
                    playerPos->invulnerable = 5;
                }
            }
            break;
        case ALLEGRO_KEY_ESCAPE:
            *openMenu = true;

            break;
        case ALLEGRO_KEY_K:
            if (!playerPos->shuriken.throwing && playerPos->numShur > 0){
                al_play_sample(throwShur, 0.5, 0.0, 0.75, ALLEGRO_PLAYMODE_ONCE, 0);
                playerPos->numShur --;
                playerPos->shuriken.throwing = true;
                playerPos->shuriken.x = playerPos->x;
                playerPos->shuriken.y = playerPos->y;
                switch (playerPos->direction) {
                    case UP:
                        playerPos->shuriken.movex = 0;
                        playerPos->shuriken.movey = -1;
                        break;
                    case DOWN:
                        playerPos->shuriken.movex = 0;
                        playerPos->shuriken.movey = 1;
                        break;
                    case LEFT:
                        playerPos->shuriken.movex = -1;
                        playerPos->shuriken.movey = 0;
                        break;
                    case RIGHT:
                        playerPos->shuriken.movex = 1;
                        playerPos->shuriken.movey = 0;
                        break;
                }
            }
            break;
        case ALLEGRO_KEY_E:
            checkKeyShur(playerPos, items, mapMatrix, numShur, numKeys, numChest, chests, mapExit, &mapUsed, endOfLevel);
            break;
    }
}
