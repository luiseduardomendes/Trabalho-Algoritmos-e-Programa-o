#include "headers.h"

int main()
{
    /*_____________________________________________________________*/
    //variaveis para allegro

    float frameRate = 30;
    int numMobs = 4;
    int mobRate = 2;
    int shurRate = 8;
    int i, j, k;
    int contador = 0;
    int mapUsed = 0;
    int joystickFound = 1;
    t_player playerPos;
    t_npc npcPos[NUM_MOBS];
    typeSave save;
    typeItem items[MIN_ITEMS];
    int numShur, numKeys;
    char mapMatrix[SIZEMAP_Y][SIZEMAP_X];

    const int width = SIZEMAP_X*MAPSCALE; //largura
    const int height = SIZEMAP_Y*MAPSCALE; //algura
    bool endOfGame = false, openMenu = false;
    /*_____________________________________________________________*/

    /*_____________________________________________________________*/
    //inicializacao allegro

    if(!al_init()){
        al_show_native_message_box(NULL, "AVISO!", "Erro de execu��o!", "Allegro n�o inicializada", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    /*_____________________________________________________________*/

    /*_____________________________________________________________*/
    //display

    ALLEGRO_DISPLAY *display = NULL;
    display = al_create_display(width, height);
    if (!display){
        al_show_native_message_box(NULL, "AVISO!", "Erro de execu��o!", "O display n�o pode ser criado!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    /*_____________________________________________________________*/

    /*_____________________________________________________________*/
    //fontes && bitmaps && formas primitivas

    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();


    ALLEGRO_FONT* font48 = al_load_ttf_font("fonts/fonte.ttf", 48, 0);
    ALLEGRO_BITMAP *naruto = al_load_bitmap("assets/Naruto.png");
    ALLEGRO_BITMAP *shurikenDraw = al_load_bitmap("assets/shuriken.png");
    ALLEGRO_BITMAP *spikes = al_load_bitmap("assets/spikes.png");
    ALLEGRO_BITMAP *keys = al_load_bitmap("assets/chave.png");
    ALLEGRO_BITMAP *enemy = al_load_bitmap("assets/akatsuck.png");
    ALLEGRO_BITMAP *wall = al_load_bitmap("assets/wall.png");
    ALLEGRO_BITMAP *grass = al_load_bitmap("assets/grass.png");
    ALLEGRO_BITMAP *heart = al_load_bitmap("assets/heart.png");
    ALLEGRO_BITMAP *voidheart = al_load_bitmap("assets/voidheart.png");
    ALLEGRO_BITMAP *narutoDialog = al_load_bitmap("assets/narutodialog.png");
    ALLEGRO_BITMAP *loading_screen = al_load_bitmap("assets/loading_screen.png");
    ALLEGRO_BITMAP *background = NULL;
    al_convert_mask_to_alpha(narutoDialog, al_map_rgb(255,0,255));

    /*_____________________________________________________________*/

    /*_____________________________________________________________*/
    //Audio

    /*ALLEGRO_SAMPLE *throwShur = NULL;
    ALLEGRO_SAMPLE_INSTANCE *throwShurInst = NULL;
    al_reserve_samples(true);
    al_install_audio();
    al_init_acodec_addon();
    throwShur = al_load_sample("throwShur.wav");
    throwShurInst = al_create_sample_instance(throwShur);
    al_attach_sample_instance_to_mixer(throwShurInst, al_get_default_mixer());*/
    /*_____________________________________________________________*/

    /*_____________________________________________________________*/
    // Keyboard & Joystick

    al_install_keyboard();
    ALLEGRO_KEYBOARD_STATE *keyState;
    al_install_joystick();
    ALLEGRO_JOYSTICK *joy = al_get_joystick(0);
    ALLEGRO_JOYSTICK_STATE joyState;
    if (joy == NULL)
        joystickFound = 0;
    /*_____________________________________________________________*/

    /*_____________________________________________________________*/
    // controle de tempo

    ALLEGRO_TIMER *timer, *mobTimer, *shurTimer;
    timer = al_create_timer(1.0/frameRate);
    al_start_timer(timer);
    mobTimer = al_create_timer(1.0/mobRate);
    al_start_timer(mobTimer);
    shurTimer = al_create_timer(1.0/shurRate);
    al_start_timer(shurTimer);
    /*_____________________________________________________________*/


    /*_____________________________________________________________*/
    //fila de eventos

    ALLEGRO_EVENT_QUEUE *events_queue = NULL;
    events_queue = al_create_event_queue();
    al_register_event_source(events_queue, al_get_keyboard_event_source());
    al_register_event_source(events_queue, al_get_display_event_source(display));
    al_register_event_source(events_queue, al_get_timer_event_source(timer));
    al_register_event_source(events_queue, al_get_timer_event_source(mobTimer));
    al_register_event_source(events_queue, al_get_timer_event_source(shurTimer));
    al_register_event_source(events_queue, al_get_joystick_event_source());
    /*_____________________________________________________________*/

    /*_____________________________________________________________*/
    //menu iniciar

    if(joystickFound){
        menuIniciar(width, height, &endOfGame, display, events_queue, joy, joyState, npcPos, &numMobs, &playerPos, &mapUsed, &numShur, &numKeys, items);
    }
    else
        menuIniciar(width, height, &endOfGame, display, events_queue, NULL, joyState, npcPos, &numMobs, &playerPos, &mapUsed, &numShur, &numKeys, items);
    playerPos.numKeys = 0;
    /*_____________________________________________________________*/

    showLoadingScreen(font48, loading_screen);
    loadMap(mapMatrix, mapUsed);
    background = createBackground(background, wall, spikes, keys, grass, display, mapMatrix);

    /*_____________________________________________________________*/
    // Inicialização das posições dos itens

    for(i= 0; i < 3; i ++){
        items[i].x = 5+i;
        items[i].y = 5+i;
    }
    for(i= 3; i < 5; i ++){
        items[i].x = 8+i;
        items[i].y = 8+i;
    }
    /*_____________________________________________________________*/

    while(!endOfGame)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(events_queue, &event);
        //al_get_keyboard_state(&keyState);

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            playerInputKeyboard(event, &playerPos, &openMenu, mapMatrix, items, numShur, numKeys);
        }
        if(joystickFound) {
            if (event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN) {
                //printf("Botao pressionado: %d\n", ev.joystick.button);
                buttonDown(event, &playerPos, &openMenu, mapMatrix, items, numShur, numKeys);
            }
            if(event.type == ALLEGRO_EVENT_JOYSTICK_AXIS) {
                moveJoystick(event, &playerPos, &openMenu, mapMatrix);
            }
        }
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            endOfGame = true;
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            if(event.timer.source == mobTimer)
            {
                npcMovement(npcPos, numMobs, playerPos, mapMatrix);
            }
            if(event.timer.source == shurTimer)
            {
                updateShurikenPlayer(&playerPos.shuriken, npcPos, numMobs, mapMatrix);//Player shuriken
                for (i = 0; i < numMobs; i ++){//Mob shuriken
                    if (npcPos[i].shuriken.throwing)
                        updateShurikenPos(&npcPos[i].shuriken, &playerPos, mapMatrix);
                    else
                        shurikenDir(&npcPos[i], playerPos);
                }
            }
            if(event.timer.source == timer)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(background, 0, 0, 0);

                for (i = 0; i < playerPos.hp; i++)
                    al_draw_bitmap(heart, (i+1)*MAPSCALE, 0, 0);
                for (i = playerPos.hp; i < playerPos.fullHp; i ++)
                    al_draw_bitmap(voidheart, (i+1)*MAPSCALE, 0, 0);
                for (i = 0; i < playerPos.numShur; i ++)
                    al_draw_bitmap(shurikenDraw, (i+7)*MAPSCALE, 0, 0);
                for (i = 0; i < playerPos.numKeys; i ++)
                    al_draw_bitmap(keys, (i+20)*MAPSCALE, 0, 0);
                for (i = 0; i < numShur + numKeys; i ++)
                    if (items[i].onMap == 1)
                        if (items[i].nameItems == 1)
                            al_draw_bitmap(keys, items[i].x*MAPSCALE, items[i].y*MAPSCALE, 0);
                        else if (items[i].nameItems == 0)
                            al_draw_bitmap(shurikenDraw, items[i].x*MAPSCALE, items[i].y*MAPSCALE, 0);

                drawMobs(npcPos, enemy);
                drawMobShur(npcPos, numMobs, shurikenDraw);
                al_draw_bitmap(naruto, playerPos.x*MAPSCALE, playerPos.y*MAPSCALE, 0);
                //al_draw_filled_rectangle(playerPos.x*MAPSCALE, playerPos.y*MAPSCALE, (playerPos.x*MAPSCALE)+MAPSCALE, (playerPos.y*MAPSCALE)+MAPSCALE ,al_map_rgb(255,255,0));//Temp because naruto.png assertion is failling
                if (playerPos.shuriken.throwing)
                    al_draw_bitmap(shurikenDraw, playerPos.shuriken.x*MAPSCALE, playerPos.shuriken.y*MAPSCALE, 0);//Temp because shuriken.png assertion is failling

                    //al_draw_filled_rectangle(playerPos.shuriken.x*MAPSCALE, playerPos.shuriken.y*MAPSCALE, (playerPos.shuriken.x*MAPSCALE)+MAPSCALE, (playerPos.shuriken.y*MAPSCALE)+MAPSCALE ,al_map_rgb(0,0,255));
                if (0){ // dialogo
                    al_draw_filled_rectangle(width/5, height*2/4, width*4.75/5, height*15/16, al_map_rgb(255,230,106));
                    al_draw_rectangle(width/5, height*2/4, width*4.75/5, height*15/16, al_map_rgb(0,0,0), 5);
                    al_draw_text(font48, al_map_rgb(0,0,0), width*1.75/3, height*2.2/4, ALLEGRO_ALIGN_CENTER, "VoceS nao vao se sair bem dessa");
                    al_draw_text(font48, al_map_rgb(0,0,0), width*1.75/3, height*2.7/4, ALLEGRO_ALIGN_CENTER, "Voces estao enfrentando o futuro hokage");
                    al_draw_text(font48, al_map_rgb(0,0,0), width*1.75/3, height*3.2/4, ALLEGRO_ALIGN_CENTER, "da vila da folha");
                    al_draw_bitmap(narutoDialog, -50, height-433,0);
                }
                al_flip_display();
            }
        }

        if (openMenu) {
            if (joystickFound)
                showMenu(width, height, &endOfGame, &openMenu, display, events_queue, joy, joyState, npcPos, &numMobs, &playerPos, &mapUsed, &numShur, &numKeys, items);
            else
                showMenu(width, height, &endOfGame, &openMenu, display, events_queue, NULL, joyState, npcPos, &numMobs, &playerPos, &mapUsed, &numShur, &numKeys, items);
        }
        if (playerPos.hp == 0){
            endOfGame = 1;
            do{
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_bitmap(loading_screen, 0,0,0);
                al_draw_text(font48, al_map_rgb(255, 255, 255), width/2, height/2, 1, "Você morreu!");
                al_flip_display();

            } while(1);
        }
    }

    al_uninstall_keyboard();
    al_destroy_timer(timer);
    al_destroy_timer(mobTimer);
    al_destroy_timer(shurTimer);
    al_destroy_display(display);
    al_destroy_bitmap(naruto);
    al_destroy_bitmap(shurikenDraw);
    al_destroy_bitmap(spikes);
    al_destroy_bitmap(keys);
    al_destroy_bitmap(enemy);
    al_destroy_bitmap(wall);
    al_destroy_bitmap(grass);
    al_destroy_bitmap(heart);
    al_destroy_bitmap(voidheart);
    al_destroy_bitmap(narutoDialog);
    al_destroy_display(display);

    return 0;
}
