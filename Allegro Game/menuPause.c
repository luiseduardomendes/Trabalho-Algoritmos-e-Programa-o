#include "headers.h"
void showMenu(int width, int height, bool *endOfGame, bool *openMenu, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue,
              ALLEGRO_JOYSTICK *joy,ALLEGRO_JOYSTICK_STATE joyState, typePos npcPos[], typePos playerPos, int mapUsed) {
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
                                saveFunction(npcPos, playerPos, mapUsed);
                                break;
                            case loadGame:
                                //load game function not implemented
                                break;
                            case exitGame:
                                *openMenu = false;
                                *endOfGame = true;
                                break;
                        }
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

int saveFunction (typePos npcPos[], typePos playerPos, int mapUsed) {
    int k, flag = 1;
    typeSave save;
    mapUsed = 0;
    save.mapUsed = mapUsed;
    for(k = 0; k < NUM_MOBS; k ++) {
        save.npc[k].direction = npcPos[k].direction;
        save.npc[k].shuriken.movex = npcPos[k].shuriken.movex;
        save.npc[k].shuriken.movey = npcPos[k].shuriken.movey;
        save.npc[k].shuriken.throwing = npcPos[k].shuriken.throwing;
        save.npc[k].shuriken.x = npcPos[k].shuriken.x;
        save.npc[k].shuriken.y = npcPos[k].shuriken.y;
        save.npc[k].x = npcPos[k].x;
        save.npc[k].y = npcPos[k].y;
    }
    save.player.direction = playerPos.direction;
    save.player.shuriken.movex = playerPos.shuriken.movex;
    save.player.shuriken.movey = playerPos.shuriken.movey;
    save.player.shuriken.throwing = playerPos.shuriken.throwing;
    save.player.shuriken.x = playerPos.shuriken.x;
    save.player.shuriken.y = playerPos.shuriken.y;
    save.player.x = playerPos.x;
    save.player.y = playerPos.y;
    saveFile = fopen("save.sav", "wb");
    if (saveFile == NULL)
        flag = 0;
    fwrite(&save, sizeof(save), 1, saveFile);
    fclose(saveFile);
    return flag;
}
