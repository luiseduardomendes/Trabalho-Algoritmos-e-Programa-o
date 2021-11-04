#include "headers.h"
void showMenu(int width, int height, bool *endOfGame, bool *openMenu, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue,
            ALLEGRO_JOYSTICK *joy,ALLEGRO_JOYSTICK_STATE joyState, t_npc npcPos[], int *numMobs, t_player *playerPos, int *mapUsed,
            int *numShur, int *numKeys, typeItem items[]) {
    int selectioned = 0;
    enum options{resumeGame, saveGame, loadGame, exitGame};

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT* font20 = al_load_ttf_font("fonte.ttf", 40, 0);

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
                            saveFunction(npcPos, *numMobs, *playerPos, *mapUsed, *numShur, *numKeys, items);
                            break;
                        case loadGame:
                            loadSave(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, items);
                            break;
                        case exitGame:
                            *openMenu = false;
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
                    *openMenu = false;
                    break;
                case 0: //Xbox_A
                    switch (selectioned){
                        case resumeGame:
                            *openMenu = false;
                            break;
                        case saveGame:
                            saveFunction(npcPos, *numMobs, *playerPos, *mapUsed, *numShur, *numKeys, items);
                            break;
                        case loadGame:
                            loadSave(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, items);
                            break;
                        case exitGame:
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

int saveFunction (t_npc npcPos[], int numMobs, t_player playerPos, int mapUsed, int numShur, int numKeys, typeItem items[]) {
    int k, flag = 1;
    typeSave save;
    save.mapUsed = mapUsed;
    save.numMobs = numMobs;
    save.numShur = numShur;
    save.numKeys = numKeys;
    for(k = 0; k < save.numMobs; k ++) {
        save.npc[k].direction = npcPos[k].direction;
        save.npc[k].shuriken.movex = npcPos[k].shuriken.movex;
        save.npc[k].shuriken.movey = npcPos[k].shuriken.movey;
        save.npc[k].shuriken.throwing = npcPos[k].shuriken.throwing;
        save.npc[k].shuriken.x = npcPos[k].shuriken.x;
        save.npc[k].shuriken.y = npcPos[k].shuriken.y;
        save.npc[k].x = npcPos[k].x;
        save.npc[k].y = npcPos[k].y;
    }
    for (k = 0; k < save.numKeys + save.numShur; k ++) {
        save.object[k].nameItems = items[k].nameItems;
        save.object[k].onMap = items[k].onMap;
        save.object[k].x = items[k].x;
        save.object[k].y = items[k].y;
    }
    save.player.direction = playerPos.direction;
    save.player.shuriken.movex = playerPos.shuriken.movex;
    save.player.shuriken.movey = playerPos.shuriken.movey;
    save.player.shuriken.throwing = playerPos.shuriken.throwing;
    save.player.shuriken.x = playerPos.shuriken.x;
    save.player.shuriken.y = playerPos.shuriken.y;
    save.player.x = playerPos.x;
    save.player.y = playerPos.y;
    save.player.fullHp = playerPos.fullHp;
    save.player.hp = playerPos.hp;
    save.player.numShur = playerPos.numShur;
    save.player.numKeys = playerPos.numKeys;
    save.player.xp = playerPos.xp;
    save.player.level = playerPos.level;
    save.player.shurikenItem = playerPos.shurikenItem;
    save.player.armor = playerPos.armor;
    save.numKeys = numKeys;
    save.numShur = numShur;

    saveFile = fopen("save.sav", "wb");
    if (saveFile == NULL)
        flag = 0;
    else {
        fwrite(&save, sizeof(save), 1, saveFile);
        fclose(saveFile);
    }

    return flag;
}

void loadSave(t_npc npcPos[], int *numMobs, t_player *playerPos, int *mapUsed, int *numShur, int *numKeys, typeItem items[]) {
    typeSave save;
    int k;
    saveFile = fopen("save.sav", "rb");
    if (saveFile != NULL){
        fread(&save, sizeof(save), 1, saveFile);
        fclose(saveFile);
        *numMobs = save.numMobs;
        *mapUsed = save.mapUsed;
        *numShur = save.numShur;
        *numKeys = save.numKeys;
        for(k = 0; k < NUM_MOBS; k ++) {
            npcPos[k].direction = save.npc[k].direction;
            npcPos[k].shuriken.movex = save.npc[k].shuriken.movex;
            npcPos[k].shuriken.movey = save.npc[k].shuriken.movey;
            npcPos[k].shuriken.throwing = save.npc[k].shuriken.throwing;
            npcPos[k].shuriken.x = save.npc[k].shuriken.x;
            npcPos[k].shuriken.y = save.npc[k].shuriken.y;
            npcPos[k].x = save.npc[k].x;
            npcPos[k].y = save.npc[k].y;
        }
        for (k = 0; k < save.numKeys + save.numShur; k ++) {
            items[k].nameItems = save.object[k].nameItems;
            items[k].onMap = save.object[k].onMap;
            items[k].x = save.object[k].x;
            items[k].y = save.object[k].y;
        }
        playerPos->direction = save.player.direction;
        playerPos->shuriken.movex = save.player.shuriken.movex;
        playerPos->shuriken.movey = save.player.shuriken.movey;
        playerPos->shuriken.throwing = save.player.shuriken.throwing;
        playerPos->shuriken.x = save.player.shuriken.x;
        playerPos->shuriken.y = save.player.shuriken.y;
        playerPos->x = save.player.x;
        playerPos->y = save.player.y;
        playerPos->fullHp = save.player.fullHp;
        playerPos->hp = save.player.hp;
        playerPos->numShur = save.player.numShur;
        playerPos->numKeys = save.player.numKeys;
        playerPos->xp = save.player.xp;
        playerPos->level = save.player.level;
        playerPos->shurikenItem = save.player.shurikenItem;
        playerPos->armor = save.player.armor;
    }
}

void menuIniciar(int width, int height, bool *endOfGame, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue,
            ALLEGRO_JOYSTICK *joy, ALLEGRO_JOYSTICK_STATE joyState, t_npc npcPos[], int *numMobs, t_player *playerPos, int *mapUsed,
            int *numShur, int *numKeys, typeItem items[]){
    int selectioned = 0, beginGame = 0;
    enum options{newGame, loadGame, credits, exitGame};

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT* font20 = al_load_ttf_font("fonte.ttf", 40, 0);


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
                            loadSave(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, items);
                            break;
                        case loadGame:
                            loadSave(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, items);
                            beginGame = true;
                            *endOfGame = false;
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
                            loadSave(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, items);
                            break;
                        case loadGame:
                            loadSave(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, items);
                            beginGame = true;
                            *endOfGame = false;
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

void standardSave(int mapUsed) {
    char mapMatrix[SIZEMAP_Y][SIZEMAP_X];
    typeSave save;
    int i;
    int numShur, numKeys;
    save.player.x = 1;
    save.player.y = 1;
    save.player.direction = TORIGHT;
    save.numMobs = 5;
    save.mapUsed = 0;

    switch (mapUsed) {
    case 0:
        if(map = fopen("arquivos/map64x36.txt", "r")){
            rewind(map);
            fread(mapMatrix, sizeof(char), SIZEMAP_X * SIZEMAP_Y, map);
            fclose(map);
            save.numShur = 5;
            save.numKeys = 5;
        }
        break;
    case 1:
        if(map = fopen("arquivos/map2.64x36.txt", "r")){
            rewind(map);
            fread(mapMatrix, sizeof(char), SIZEMAP_X * SIZEMAP_Y, map);
            fclose(map);
            save.numShur = 7;
            save.numKeys = 7;
        }
        break;
    }
    for (i = 0; i < save.numMobs; i++){
        do{
            save.npc[i].x = (1 + (rand() % SIZEMAP_X));
            save.npc[i].y = (1 + (rand() % SIZEMAP_Y));
        } while (mapMatrix[save.npc[i].y][save.npc[i].x] == WALL);
    }
    switch(save.object->nameItems)
    {
        case 'shur':
            for (i = 0; i < save.numShur; i++){
                do{
                    save.object[i].x = (1 + (rand() % SIZEMAP_X));
                    save.object[i].y = (1 + (rand() % SIZEMAP_Y));
                } while (mapMatrix[save.object[i].y][save.object[i].x] == WALL);
            }
            break;
        case 'keys':
            for (i = save.numShur; i < (save.numShur + save.numKeys); i++){
                do{
                    save.object[i].x = (1 + (rand() % SIZEMAP_X));
                    save.object[i].y = (1 + (rand() % SIZEMAP_Y));
                } while (mapMatrix[save.object[i].y][save.object[i].x] == WALL);
            }
            break;
    }
    for (i = 0; i < save.numMobs; i ++){
        save.npc[i].shuriken.throwing = 0;
        save.npc[i].shuriken.movex = 0;
        save.npc[i].shuriken.movey = 0;
        save.npc[i].shuriken.x = 0;
        save.npc[i].shuriken.y = 0;
    }
    save.player.shuriken.throwing = 0;
    save.player.fullHp = 5;
    save.player.hp = 5;

    for(i = 0; i < save.numMobs; i ++) {
        save.npc[i].hp = 1;
    }
    save.player.numShur = 5;

    if(saveFile = fopen("save.sav", "wb"))
        fwrite(&save, sizeof(save), 1, saveFile);
        fclose(saveFile);
}
