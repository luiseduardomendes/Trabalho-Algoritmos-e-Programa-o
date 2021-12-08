#include "headers.h"
void showMenu(int width, int height, bool *endOfLevel, bool *openMenu, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue,
            ALLEGRO_JOYSTICK *joy,ALLEGRO_JOYSTICK_STATE joyState, t_npc npcPos[], t_player *playerPos, int *mapUsed, t_counting *counting,
            typeItem items[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X], t_chest chests[], int *playerLogout, t_boss *boss, t_fonts fonts, t_bitmaps bmps) {
    int selected = 0;
    enum options{resumeGame, saveGame, loadGame, exitGame};

    al_init_font_addon();
    al_init_ttf_addon();


    do{
        ALLEGRO_EVENT ev;
        al_wait_for_event(events_queue, &ev);
        if (joy != NULL)
            al_get_joystick_state(joy, &joyState);

        drawInGameMenu(bmps, width, height, selected, fonts);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    *openMenu = false;
                    break;
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_W:
                    if (selected - 1 >= 0)
                        selected --;
                    else
                        selected = 3;
                    break;
                case ALLEGRO_KEY_DOWN:
                case ALLEGRO_KEY_S:
                    if (selected + 1 <= 3)
                        selected ++;
                    else
                        selected = 0;
                    break;
                case ALLEGRO_KEY_ENTER:
                    switch (selected){
                        case resumeGame:
                            *openMenu = false;
                            break;
                        case saveGame:
                            saveFunction(npcPos, *playerPos, *mapUsed, *counting, items, chests, *boss);
                            break;
                        case loadGame:
                            loadSave(npcPos, playerPos, mapUsed, counting, items, chests, mapMatrix, boss);
                            break;
                        case exitGame:
                            *playerLogout = true;
                            *openMenu = false;
                            *endOfLevel = 1;
                            break;
                        }
                    break;

            }
        }
        if (joy != NULL) {
            if(ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN){
                switch(ev.joystick.button){
                case 6: // Xbox_options
                case 1: // Xbox_B
                    *openMenu = false;
                    break;
                case 0: //Xbox_A
                    switch (selected){
                        case resumeGame:
                            *openMenu = false;
                            break;
                        case saveGame:
                            saveFunction(npcPos, *playerPos, *mapUsed, *counting, items, chests, *boss);
                            break;
                        case loadGame:
                            loadSave(npcPos, playerPos, mapUsed, counting, items, chests, mapMatrix, boss);
                            break;
                        case exitGame:
                            *playerLogout = true;
                            *openMenu = false;
                            *endOfLevel = 1;
                            break;
                        }
                    break;
                }
            }
            if(ev.type == ALLEGRO_EVENT_JOYSTICK_AXIS) {
                if(ev.joystick.axis == 1){
                    switch((int)round(ev.joystick.pos)){
                        case 1:
                        if (selected + 1 <= 3)
                            selected ++;
                        else
                            selected = 0;
                        break;
                        case -1:
                        if (selected - 1 >= 0)
                            selected --;
                        else
                            selected = 3;
                        break;
                    }
                }
            }
        }
    } while (*openMenu);
}

int saveFunction (t_npc npcPos[], t_player playerPos, int mapUsed, t_counting counting,
                  typeItem items[], t_chest chests[], t_boss boss) {
    int k, flag = 1;
    typeSave save;

    save.mapUsed = mapUsed;
    save.counting = counting;

    for(k = 0; k < save.counting.numMobs; k ++) {
        save.npc[k] = npcPos[k];
    }
    for (k = 0; k < save.counting.numKeys + save.counting.numShur; k ++) {
        save.object[k] = items[k];
    }
    for (k = 0; k < save.counting.numChests; k ++){
        save.chestItem[k] = chests[k];
    }

    save.player = playerPos;


    save.boss = boss;


    saveFile = fopen("save.sav", "wb");
    if (saveFile == NULL)
        flag = 0;
    else {
        fwrite(&save, sizeof(save), 1, saveFile);
        fclose(saveFile);
    }

    return flag;
}

void loadSave(t_npc npcPos[], t_player *playerPos, int *mapUsed, t_counting *counting,
              typeItem items[], t_chest chests[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X], t_boss *boss) {
    typeSave save;
    int k;
    loadMap(mapMatrix, *mapUsed);

    saveFile = fopen("save.sav", "rb");
    if (saveFile != NULL){
        fread(&save, sizeof(save), 1, saveFile);
        fclose(saveFile);

        mapUsed = save.mapUsed;

        *counting = save.counting;

        for(k = 0; k < counting->numMobs; k ++) {
            npcPos[k] = save.npc[k];
        }
        for (k = 0; k < counting->numKeys + counting->numShur; k ++) {
            items[k] = save.object[k];
        }
        for (k = 0; k < counting->numChests; k ++){
            chests[k] = save.chestItem[k];
        }

        *boss = save.boss;

        *playerPos = save.player;
    }
}

void menuIniciar(int width, int height, bool *endOfGame, int *endOfLevel, int *playerLogout, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue,
            ALLEGRO_JOYSTICK *joy, ALLEGRO_JOYSTICK_STATE joyState, t_npc npcPos[], t_player *playerPos, int *mapUsed, t_counting *counting, typeItem items[],
            t_chest chests[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X], t_boss *boss, t_fonts fonts, t_bitmaps bmps){
    int selected = 0, closeMenu = 0;

    enum {newGame, loadGame, credits, exitGame};

    al_init_font_addon();
    al_init_ttf_addon();

    do{
        ALLEGRO_EVENT ev;
        al_wait_for_event(events_queue, &ev);
        if (joy != NULL)
            al_get_joystick_state(joy, &joyState);

        drawMainMenu(bmps, width, height, selected, fonts);


        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:

                    break;
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_W:
                    if (selected - 1 >= 0)
                        selected --;
                    else
                        selected = 3;
                    break;
                case ALLEGRO_KEY_DOWN:
                case ALLEGRO_KEY_S:
                    if (selected + 1 <= 3)
                        selected ++;
                    else
                        selected = 0;
                    break;
                case ALLEGRO_KEY_ENTER:
                    switch (selected){
                        case newGame:
                            closeMenu = true;
                            *endOfGame = false;
                            standardSave(0);
                            loadSave(npcPos, playerPos, mapUsed, counting, items, chests, mapMatrix, boss);
                            *playerLogout = 0;
                            *endOfLevel = 0;
                            break;
                        case loadGame:
                            saveFile = fopen("save.sav", "rb");
                            if (saveFile != NULL){
                                loadSave(npcPos, playerPos, mapUsed, counting, items, chests, mapMatrix, boss);
                                closeMenu = true;
                                *endOfGame = false;
                                *playerLogout = 0;
                                *endOfLevel = 0;
                            }
                            break;
                        case credits:
                            creditFunction(width, height, display, events_queue, joy, fonts);
                            break;
                        case exitGame:
                            closeMenu = true;
                            *endOfGame = true;

                            break;
                        }
                    break;
                }

            }

        if (joy != NULL) {
            if(ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN){
                switch(ev.joystick.button){
                case 6: // Xbox_options
                case 1: // Xbox_B
                    break;
                case 0: //Xbox_A
                    switch (selected){
                        case newGame:
                            closeMenu = true;
                            *endOfGame = false;
                            standardSave(0);
                            loadSave(npcPos, playerPos, mapUsed, counting, items, chests, mapMatrix, boss);
                            *playerLogout = 0;
                            *endOfLevel = 0;
                            break;
                        case loadGame:
                            saveFile = fopen("save.sav", "rb");
                            if (saveFile != NULL){
                                loadSave(npcPos, playerPos, mapUsed, counting, items, chests, mapMatrix, boss);
                                closeMenu = true;
                                *endOfGame = false;
                                *playerLogout = 0;
                                *endOfLevel = 0;
                            }
                            break;
                        case credits:
                            creditFunction(width, height, display, events_queue, joy);
                            break;
                        case exitGame:
                            closeMenu = true;
                            *endOfGame = true;
                            break;
                        }
                    break;

                }
            }
            if(ev.type == ALLEGRO_EVENT_JOYSTICK_AXIS) {
                if(ev.joystick.axis == 1){
                    switch((int)round(ev.joystick.pos)){
                        case 1:
                        if (selected + 1 <= 3)
                            selected ++;
                        else
                            selected = 0;
                        break;
                        case -1:
                        if (selected - 1 >= 0)
                            selected --;
                        else
                            selected = 3;
                        break;
                    }
                }
            }
        }
    } while (!closeMenu);
}

void standardSave(int mapUsed){
    char mapMatrix[SIZEMAP_Y][SIZEMAP_X];
    char fileNames[99][49] =   {{"arquivos/map64x36.txt"},
                                {"arquivos/mapa2.64x36.txt"},
                                {"arquivos/map3.txt"}};
    typeSave save, bufferSave;
    int i;

    switch (mapUsed){
        case 0:
            save.counting.numKeys = 5;
            save.counting.numMobs = 5;
            save.counting.numShur = 5;
            save.counting.numChests = 2;
        case 1:
            save.counting.numKeys = 10;
            save.counting.numMobs = 8;
            save.counting.numShur = 8;
            save.counting.numChests = 10;
        case 2:
            save.counting.numKeys = 5;
            save.counting.numMobs = 5;
            save.counting.numShur = 5;
            save.counting.numChests = 5;
    }

    save.player.x = 1;
    save.player.y = 1;
    save.player.direction = TORIGHT;



    loadMap(mapMatrix, mapUsed);
    save.mapUsed = mapUsed;

    if(mapUsed == 2){
        save.boss.alive = 1;
        save.boss.fullHp = 5;
        save.boss.hp = 5;
        save.boss.x = 32;
        save.boss.y = 18;
        save.boss.direction = RIGHT;
        for (i = 0; i < 8; i ++){
            save.boss.shurikens[i].movex = 0;
            save.boss.shurikens[i].movey = 0;
            save.boss.shurikens[i].throwing = 0;
            save.boss.shurikens[i].x = 0;
            save.boss.shurikens[i].y = 0;
        }
    }
    else{
        save.boss.alive = 0;
        save.boss.fullHp = 0;
        save.boss.hp = 0;
        save.boss.x = 0;
        save.boss.y = 0;
        save.boss.direction = RIGHT;
        for (i = 0; i < 8; i ++){
            save.boss.shurikens[i].movex = 0;
            save.boss.shurikens[i].movey = 0;
            save.boss.shurikens[i].throwing = 0;
            save.boss.shurikens[i].x = 0;
            save.boss.shurikens[i].y = 0;
        }
    }

    for (i = 0; i < save.counting.numMobs; i++){
        do{
            save.npc[i].x = (1 + (rand() % (SIZEMAP_X-2)));
            save.npc[i].y = (1 + (rand() % (SIZEMAP_Y-2)));
        } while (mapMatrix[save.npc[i].y][save.npc[i].x] == WALL && ((save.npc[i].x < 10) && (save.npc[i].y < 10)));
        save.npc[i].alive = 1;
    }

    for (i = 0; i < save.counting.numShur; i++){
        do{
            save.object[i].nameItems = shur;
            save.object[i].onMap = 1;
            save.object[i].x = (1 + (rand() % (SIZEMAP_X-2)));
            save.object[i].y = (1 + (rand() % (SIZEMAP_Y-2)));
        } while (mapMatrix[save.object[i].y][save.object[i].x] == WALL || mapMatrix[save.object[i].y][save.object[i].x] == 'X');
    }

    for (i = save.counting.numShur; i < (save.counting.numShur + save.counting.numKeys); i++){
        do{
            save.object[i].nameItems = keys;
            save.object[i].onMap = 1;
            save.object[i].x = (1 + (rand() % (SIZEMAP_X-2)));
            save.object[i].y = (1 + (rand() % (SIZEMAP_Y-2)));
        } while (mapMatrix[save.object[i].y][save.object[i].x] == WALL || mapMatrix[save.object[i].y][save.object[i].x] == 'X');
    }
    for (i = 0; i < save.counting.numChests; i ++){
        do {
            save.chestItem[i].closed = 1;
            save.chestItem[i].itemStore = (rand() % 4);
            save.chestItem[i].x = (1 + (rand() % (SIZEMAP_X-2)));
            save.chestItem[i].y = (1 + (rand() % (SIZEMAP_Y-2)));
        }while (mapMatrix[save.chestItem[i].y][save.chestItem[i].x] == WALL || mapMatrix[save.chestItem[i].y][save.chestItem[i].x] == 'X');
    }

    for (i = 0; i < save.counting.numMobs; i ++){
        save.npc[i].shuriken.throwing = 0;
        save.npc[i].shuriken.movex = 0;
        save.npc[i].shuriken.movey = 0;
        save.npc[i].shuriken.x = 0;
        save.npc[i].shuriken.y = 0;
    }

    save.player.ultimate.actived = false;
    save.player.ultimate.maxRadius = 8;


    if (mapUsed == 0){
        save.player.shuriken.throwing = 0;
        save.player.fullHp = 5;
        save.player.hp = 5;
        save.player.armor = 0;
        save.player.level = 0;
        save.player.numKeys = 0;
        save.player.numShur = 5;
        save.player.xp = 0;
        save.player.shurikenItem = 0;
        save.player.invulnerable = 0;
        save.player.ultBar = 0;
        save.player.fullUltBar = 25;
    }
    else{
        if (saveFile = fopen("save.sav", "rb")){
            fread(&bufferSave, sizeof(typeSave), 1, saveFile);
            fclose(saveFile);
            save.player.shuriken.throwing = bufferSave.player.shuriken.throwing;
            save.player.fullHp = bufferSave.player.fullHp;
            save.player.hp = bufferSave.player.hp;
            save.player.armor = bufferSave.player.armor;
            save.player.level = bufferSave.player.level;
            save.player.numKeys = bufferSave.player.numKeys;
            save.player.numShur = bufferSave.player.numShur;
            save.player.xp = bufferSave.player.xp;
            save.player.shurikenItem = bufferSave.player.shurikenItem;
            save.player.invulnerable = bufferSave.player.invulnerable;
            save.player.ultBar = bufferSave.player.ultBar;
            save.player.fullUltBar = bufferSave.player.fullUltBar;
        }
    }

    for(i = 0; i < save.counting.numMobs; i ++) {
        save.npc[i].hp = 1;
    }

    if(saveFile = fopen("save.sav", "wb")){
        fwrite(&save, sizeof(save), 1, saveFile);
        fclose(saveFile);
    }

}

void creditFunction(int width, int height, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue, ALLEGRO_JOYSTICK *joy, t_fonts fonts){

    int creditScreen = 0;
    ALLEGRO_EVENT ev;
    al_init_font_addon();
    al_init_ttf_addon();


    al_draw_filled_rounded_rectangle(width*2.5/8, height/4, width*5.5/8, height*3/4, width*0.5/16, height*1/16, al_map_rgb(255,255, 0));
    al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*4.5/16, ALLEGRO_ALIGN_CENTER, "Creditos");
    al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*6.5/16, ALLEGRO_ALIGN_CENTER, "Luis Eduardo Mendes");
    al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*8.5/16, ALLEGRO_ALIGN_CENTER, "Eduardo Bolson");
    al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*10.5/16, ALLEGRO_ALIGN_CENTER, "Vinicius Boff Alves");
    //al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*12.5/16, ALLEGRO_ALIGN_CENTER, "O Mestre rlam12"); Salvador do nosso código e sanidade via stack overflow.

    al_flip_display();

    do{
        al_wait_for_event(events_queue, &ev);

        if((ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ENTER ) ||
                       (ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN && ev.joystick.button == CONTROL_BUTTON_A))
                creditScreen = 1;
    }while(creditScreen != 1);
}
