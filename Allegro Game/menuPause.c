#include "headers.h"
void showMenu(int width, int height, bool *endOfGame, bool *openMenu, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *events_queue,
              ALLEGRO_JOYSTICK *joy,ALLEGRO_JOYSTICK_STATE joyState) {
    int selectioned = 0;
    enum options{resumeGame, saveGame, loadGame, exitGame};

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT* font20 = al_load_ttf_font("fonte.ttf", 20, 0);

    do{
        ALLEGRO_EVENT ev;
        al_wait_for_event(events_queue, &ev);
        al_get_joystick_state(joy, &joyState);


        al_draw_filled_rounded_rectangle(width/4, height/4, width*3/4, height*3/4, width*1/16, height*1/16, al_map_rgb(255,255, 0));
        al_draw_rectangle(width*2/5, height*(selectioned*2+4.25)/16, width*3/5, height*(selectioned*2+5.5)/16, al_map_rgb(0,128,128), 5);
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
                            //save game function not implemented
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
                    break;
                    case -1:
                    if (selectioned - 1 >= 0)
                        selectioned --;
                    break;
                }
            }
        }
        al_clear_to_color(al_map_rgb(0,0,0));
    } while (*openMenu);
}
