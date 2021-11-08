#include "headers.h"

/*
void drawMove(typePos npcPos[], typePos playerPos, ALLEGRO_BITMAP *shurikenDraw){
    int i, j, k, mobFound, playerFound, shurikenFound;

    for(i = 0; i < SIZEMAP_Y; i++){
        for(j = 0; j < SIZEMAP_X; j++){
            mobFound = 0;
            playerFound = 0;
            shurikenFound = 0;
            for(k = 0; k < NUM_MOBS; k++){
                if((npcPos[k].x == j) && (npcPos[k].y == i)){
                    al_draw_filled_rectangle(npcPos[k].x*MAPSCALE, npcPos[k].y*MAPSCALE, (npcPos[k].x*MAPSCALE)+MAPSCALE, (npcPos[k].y*MAPSCALE)+MAPSCALE,al_map_rgb(200,0,0));
                    mobFound = 1;
                }
            }
            if(mobFound == 0){
                if (playerPos.shuriken.x == j && playerPos.shuriken.y == i && playerPos.shuriken.throwing){
                    al_draw_bitmap(shurikenDraw, playerPos.shuriken.x*MAPSCALE, playerPos.shuriken.y*MAPSCALE, 0);
                    //al_draw_filled_rectangle(playerPos.shuriken.x*MAPSCALE, playerPos.shuriken.y*MAPSCALE, (playerPos.shuriken.x*MAPSCALE)+MAPSCALE, (playerPos.shuriken.y*MAPSCALE)+MAPSCALE,al_map_rgb(0,0,200));
                }
                else{
                    for(k = 0; k < NUM_MOBS; k++){
                        if((npcPos[k].shuriken.x == j) && (npcPos[k].shuriken.y == i) && npcPos[i].shuriken.throwing == 1){
                            al_draw_bitmap(shurikenDraw, npcPos[k].shuriken.x*MAPSCALE,npcPos[k].shuriken.y*MAPSCALE, 0);
                            //al_draw_filled_rectangle(npcPos[k].shuriken.x*MAPSCALE,npcPos[k].shuriken.y*MAPSCALE, (npcPos[k].shuriken.x*MAPSCALE)+MAPSCALE, (npcPos[k].shuriken.y*MAPSCALE)+MAPSCALE,al_map_rgb(150,150,150));
                            shurikenFound = 1;
                        }
                    }
                }
            }
        }
    }
}

        // desenha jogador
        //al_draw_filled_rounded_rectangle((playerPos.x*MAPSCALE), (playerPos.y*MAPSCALE), (playerPos.x*MAPSCALE)+MAPSCALE, (playerPos.y*MAPSCALE)+MAPSCALE, MAPSCALE/3, MAPSCALE/3, al_map_rgb(255,255,0));
void drawbitMap(naruto, (playerPos.x*MAPSCALE), (playerPos.y*MAPSCALE)){
    al_draw_bitmap(naruto,(playerPos.x*MAPSCALE), (playerPos.y*MAPSCALE), 0);
}
        //al_draw_textf(font48, al_map_rgb(255,255,255), width/2, height/2+28, 1, "Quadros: %d   Segundos: %d", contador++, contador/60);
        //al_draw_textf(font48, al_map_rgb(255,255,255), width/2, height/2-28, 1, "Tempo atual: %d    Tempo shuriken: %d", timeCurrent / CLOCKS_PER_SEC, timeBeginShuriken/ CLOCKS_PER_SEC);


        if ((double)(timeCurrent - timeBeginMovement) / CLOCKS_PER_SEC > 0.5){
            npcMovement(npcPos, playerPos, 5, mapMatrix);
            timeBeginMovement = clock();
        }


        if ((double)(timeCurrent - timeThrowShuriken) / CLOCKS_PER_SEC > 0.25){
            for (i = 0; i < NUM_MOBS; i ++) {
                throwShuriken(&npcPos[i].shuriken, playerPos, mapMatrix);
            }
            timeThrowShuriken = clock();
        }

        if ((double)(timeCurrent - timeBeginShuriken) / CLOCKS_PER_SEC > 5){
            for(i = 0; i < NUM_MOBS; i ++){
                printf("NPC %d\n", i);
                printf("x: %d\ty: %d\tdireção: %d\n", npcPos[i].x,npcPos[i].y,npcPos[i].direction);
                printf("x: %d\ty: %d\tdireção: x: %d\ty: %d\n", npcPos[i].shuriken.x, npcPos[i].shuriken.y, npcPos[i].shuriken.movex, npcPos[i].shuriken.movey);
                if (!npcPos[i].shuriken.throwing) {
                    npcPos[i].shuriken.x = npcPos[i].x;
                    npcPos[i].shuriken.y = npcPos[i].y;
                    switch (npcPos[i].direction) {
                        case UP:
                            npcPos[i].shuriken.movex = 0;
                            npcPos[i].shuriken.movey = -1;
                            break;
                        case DOWN:
                            npcPos[i].shuriken.movex = 0;
                            npcPos[i].shuriken.movey = 1;
                            break;
                        case LEFT:
                            npcPos[i].shuriken.movex = -1;
                            npcPos[i].shuriken.movey = 0;
                            break;
                        case RIGHT:
                            npcPos[i].shuriken.movex = 1;
                            npcPos[i].shuriken.movey = 0;
                            break;
                        default:
                            npcPos[i].shuriken.movex = 0;
                            npcPos[i].shuriken.movey = 0;
                            break;
                    }
                    npcPos[i].shuriken.throwing = true;
                    timeBeginShuriken = clock();
                }
            }
        }

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_W:
                    if (verifyPosition(playerPos.x, playerPos.y, TOUP, mapMatrix)) {
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
                    endOfGame = true;
                    break;
                case ALLEGRO_KEY_K:
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
                    timeThrowShurikenPlayer = clock();
                    break;
            }
        }
        if ((double)(timeCurrent - timeThrowShurikenPlayer) / CLOCKS_PER_SEC > 0.1){

            throwShuriken(&playerPos.shuriken, npcPos[0], mapMatrix);
            timeThrowShurikenPlayer = clock();
        }
*/
