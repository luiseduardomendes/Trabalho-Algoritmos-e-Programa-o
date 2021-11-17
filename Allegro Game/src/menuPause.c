#include "headers.h"
void showMenu(int width, int height, bool *endOfGame, bool *openMenu, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue,
            ALLEGRO_JOYSTICK *joy,ALLEGRO_JOYSTICK_STATE joyState, t_npc npcPos[], int *numMobs, t_player *playerPos, int *mapUsed,
            int *numShur, int *numKeys, int *numChest, typeItem items[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X], t_chest chests[],
            int *playerLogout) {
    int selectioned = 0;
    enum options{resumeGame, saveGame, loadGame, exitGame};

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT* font20 = al_load_ttf_font("fonts/fonte.ttf", 40, 0);


    do{
        ALLEGRO_EVENT ev;
        al_wait_for_event(events_queue, &ev);
        if (joy != NULL)
            al_get_joystick_state(joy, &joyState);

        al_draw_filled_rounded_rectangle(width*2.5/8, height/4, width*5.5/8, height*3/4, width*0.5/16, height*1/16, al_map_rgb(255,255, 0));
        al_draw_rectangle(width*2/5, height*(selectioned*2+4.25)/16, width*3/5, height*(selectioned*2+6)/16, al_map_rgb(0,128,128), 5);
        al_draw_text(font20, al_map_rgb(0,0,0), width/2, height*4.5/16, ALLEGRO_ALIGN_CENTER, "Continuar");
        al_draw_text(font20, al_map_rgb(0,0,0), width/2, height*6.5/16, ALLEGRO_ALIGN_CENTER, "Salvar jogo");
        al_draw_text(font20, al_map_rgb(0,0,0), width/2, height*8.5/16, ALLEGRO_ALIGN_CENTER, "Carregar jogo");
        al_draw_text(font20, al_map_rgb(0,0,0), width/2, height*10.5/16, ALLEGRO_ALIGN_CENTER, "Sair");
        al_flip_display();


        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    *openMenu = false;
                    break;
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_W:
                    if (selectioned - 1 >= 0)
                        selectioned --;
                    else
                        selectioned = 3;
                    break;
                case ALLEGRO_KEY_DOWN:
                case ALLEGRO_KEY_S:
                    if (selectioned + 1 <= 3)
                        selectioned ++;
                    else
                        selectioned = 0;
                    break;
                case ALLEGRO_KEY_ENTER:
                    switch (selectioned){
                        case resumeGame:
                            *openMenu = false;
                            break;
                        case saveGame:
                            saveFunction(npcPos, *numMobs, *playerPos, *mapUsed, *numShur, *numKeys, *numChest, items, chests);
                            break;
                        case loadGame:
                            loadSave(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, numChest, items, chests, mapMatrix);
                            break;
                        case exitGame:
                            *playerLogout = true;
                            *openMenu = false;
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
                    switch (selectioned){
                        case resumeGame:
                            *openMenu = false;
                            break;
                        case saveGame:
                            saveFunction(npcPos, *numMobs, *playerPos, *mapUsed, *numShur, *numKeys, *numChest, items, chests);
                            break;
                        case loadGame:
                            loadSave(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, numChest, items, chests, mapMatrix);
                            break;
                        case exitGame:
                            *playerLogout = true;
                            *openMenu = false;
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
                        if (selectioned + 1 <= 3)
                            selectioned ++;
                        else
                            selectioned = 0;
                        break;
                        case -1:
                        if (selectioned - 1 >= 0)
                            selectioned --;
                        else
                            selectioned = 3;
                        break;
                    }
                }
            }
        }
    } while (*openMenu);
}

int saveFunction (t_npc npcPos[], int numMobs, t_player playerPos, int mapUsed, int numShur, int numKeys, int numChest,
                  typeItem items[], t_chest chests[]) {
    int k, flag = 1;
    typeSave save;
    save.mapUsed = mapUsed;
    save.numMobs = numMobs;
    save.numShur = numShur;
    save.numKeys = numKeys;
    save.numChest = numChest;
    for(k = 0; k < save.numMobs; k ++) {
        save.npc[k] = npcPos[k];
    }
    for (k = 0; k < save.numKeys + save.numShur; k ++) {
        save.object[k] = items[k];
    }
    for (k = 0; k < numChest; k ++){
        save.chestItem[k] = chests[k];
    }

    save.player = playerPos;

    saveFile = fopen("save.sav", "wb");
    if (saveFile == NULL)
        flag = 0;
    else {
        fwrite(&save, sizeof(save), 1, saveFile);
        fclose(saveFile);
    }

    return flag;
}

void loadSave(t_npc npcPos[], int *numMobs, t_player *playerPos, int *mapUsed, int *numShur, int *numKeys, int *numChest,
              typeItem items[], t_chest chests[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X]) {
    typeSave save;
    int k;
    loadMap(mapMatrix, *mapUsed);

    saveFile = fopen("save.sav", "rb");
    if (saveFile != NULL){
        fread(&save, sizeof(save), 1, saveFile);
        fclose(saveFile);
        *numMobs = save.numMobs;
        *mapUsed = save.mapUsed;
        *numShur = save.numShur;
        *numKeys = save.numKeys;
        *numChest = save.numChest;
        for(k = 0; k < *numMobs; k ++) {
            npcPos[k] = save.npc[k];
        }
        for (k = 0; k < *numKeys + *numShur; k ++) {
            items[k] = save.object[k];
        }
        for (k = 0; k < *numChest; k ++){
            chests[k] = save.chestItem[k];
        }
        *playerPos = save.player;
    }
}

void menuIniciar(int width, int height, bool *endOfGame, int *endOfLevel, int *playerLogout, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue,
            ALLEGRO_JOYSTICK *joy, ALLEGRO_JOYSTICK_STATE joyState, t_npc npcPos[], int *numMobs, t_player *playerPos, int *mapUsed,
            int *numShur, int *numKeys, int *numChest, typeItem items[], t_chest chests[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
    int selectioned = 0, beginGame = 0;
    enum options{newGame, loadGame, credits, exitGame};

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT* font20 = al_load_ttf_font("fonts/fonte.ttf", 40, 0);



    do{
        ALLEGRO_EVENT ev;
        al_wait_for_event(events_queue, &ev);
        if (joy != NULL)
            al_get_joystick_state(joy, &joyState);

        al_draw_filled_rounded_rectangle(width*2.5/8, height/4, width*5.5/8, height*3/4, width*0.5/16, height*1/16, al_map_rgb(255,255, 0));
        al_draw_rectangle(width*2/5, height*(selectioned*2+4.25)/16, width*3/5, height*(selectioned*2+6)/16, al_map_rgb(0,128,128), 5);
        al_draw_text(font20, al_map_rgb(0,0,0), width/2, height*4.5/16, ALLEGRO_ALIGN_CENTER, "Novo Jogo");
        al_draw_text(font20, al_map_rgb(0,0,0), width/2, height*6.5/16, ALLEGRO_ALIGN_CENTER, "Carregar jogo");
        al_draw_text(font20, al_map_rgb(0,0,0), width/2, height*8.5/16, ALLEGRO_ALIGN_CENTER, "Creditos");
        al_draw_text(font20, al_map_rgb(0,0,0), width/2, height*10.5/16, ALLEGRO_ALIGN_CENTER, "Sair");
        al_flip_display();

        al_flip_display();
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:

                    break;
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_W:
                    if (selectioned - 1 >= 0)
                        selectioned --;
                    else
                        selectioned = 3;
                    break;
                case ALLEGRO_KEY_DOWN:
                case ALLEGRO_KEY_S:
                    if (selectioned + 1 <= 3)
                        selectioned ++;
                    else
                        selectioned = 0;
                    break;
                case ALLEGRO_KEY_ENTER:
                    switch (selectioned){
                        case newGame:
                            beginGame = true;
                            *endOfGame = false;
                            standardSave(0);
                            loadSave(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, numChest, items, chests, mapMatrix);
                            *playerLogout = 0;
                            *endOfLevel = 0;
                            break;
                        case loadGame:
                            loadSave(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, numChest, items, chests, mapMatrix);
                            beginGame = true;
                            *endOfGame = false;
                            *playerLogout = 0;
                            *endOfLevel = 0;
                            break;
                        case credits:
                            break;
                        case exitGame:
                            beginGame = true;
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
                    switch (selectioned){
                        case newGame:
                            beginGame = true;
                            *endOfGame = false;
                            standardSave(0);
                            loadSave(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, numChest, items, chests, mapMatrix);
                            *playerLogout = 0;
                            *endOfLevel = 0;
                            break;
                        case loadGame:
                            loadSave(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, numChest, items, chests, mapMatrix);
                            beginGame = true;
                            *endOfGame = false;
                            *playerLogout = 0;
                            *endOfLevel = 0;
                            break;
                        case credits:
                            break;
                        case exitGame:
                            beginGame = true;
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
                        if (selectioned + 1 <= 3)
                            selectioned ++;
                        else
                            selectioned = 0;
                        break;
                        case -1:
                        if (selectioned - 1 >= 0)
                            selectioned --;
                        else
                            selectioned = 3;
                        break;
                    }
                }
            }
        }
    } while (!beginGame);
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
            save.numKeys = 5;
            save.numMobs = 5;
            save.numShur = 5;
            save.numChest = 2;
        case 1:
            save.numKeys = 10;
            save.numMobs = 8;
            save.numShur = 8;
            save.numChest = 10;
        case 2:
            save.numKeys = 5;
            save.numMobs = 5;
            save.numShur = 5;
            save.numChest = 5;
    }

    save.player.x = 1;
    save.player.y = 1;
    save.player.direction = TORIGHT;

    loadMap(mapMatrix, mapUsed);
    save.mapUsed = mapUsed;

    for (i = 0; i < save.numMobs; i++){
        do{
            save.npc[i].x = (7 + (rand() % (SIZEMAP_X-1)));
            save.npc[i].y = (7 + (rand() % (SIZEMAP_Y-1)));
        } while (mapMatrix[save.npc[i].y][save.npc[i].x] == WALL);
        save.npc.alive = 1;
    }

    for (i = 0; i < save.numShur; i++){
        do{
            save.object[i].nameItems = shur;
            save.object[i].onMap = 1;
            save.object[i].x = (7 + (rand() % (SIZEMAP_X-1)));
            save.object[i].y = (7 + (rand() % (SIZEMAP_Y-1)));
        } while (mapMatrix[save.object[i].y][save.object[i].x] == WALL);
    }

    for (i = save.numShur; i < (save.numShur + save.numKeys); i++){
        do{
            save.object[i].nameItems = keys;
            save.object[i].onMap = 1;
            save.object[i].x = (7 + (rand() % (SIZEMAP_X-1)));
            save.object[i].y = (7 + (rand() % (SIZEMAP_Y-1)));
        } while (mapMatrix[save.object[i].y][save.object[i].x] == WALL);
    }
    for (i = 0; i < save.numChest; i ++){
        do {
            save.chestItem[i].closed = 1;
            save.chestItem[i].itemStore = (rand() % 4);
            save.chestItem[i].x = (7 + (rand() % (SIZEMAP_X-1)));
            save.chestItem[i].y = (7 + (rand() % (SIZEMAP_Y-1)));
        }while (mapMatrix[save.object[i].y][save.object[i].x] == WALL);
    }

    for (i = 0; i < save.numMobs; i ++){
        save.npc[i].shuriken.throwing = 0;
        save.npc[i].shuriken.movex = 0;
        save.npc[i].shuriken.movey = 0;
        save.npc[i].shuriken.x = 0;
        save.npc[i].shuriken.y = 0;
    }

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
        }
    }

    for(i = 0; i < save.numMobs; i ++) {
        save.npc[i].hp = 1;
    }

    if(saveFile = fopen("save.sav", "wb")){
        fwrite(&save, sizeof(save), 1, saveFile);
        fclose(saveFile);
    }

}
