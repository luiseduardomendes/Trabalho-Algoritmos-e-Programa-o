#include "headers.h"

int main()
{
    /*_____________________________________________________________*/
    //variaveis para allegro

    float frameRate = 30;
    int mobRate = 4;
    int shurRate = 8;
    int i, j, k;
    int contador = 0;
    int mapUsed = 0;
    int joystickFound = 1;
    typePos playerPos, npcPos[NUM_MOBS];
    typeSave save;
    const int width = 64*MAPSCALE; //largura
    const int height = 36*MAPSCALE; //algura
    bool endOfGame = false, openMenu = false;
    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    //inicializacao das posicoes

    playerPos.x = 2;
    playerPos.y = 2;
    /*for (i = 0; i < NUM_MOBS; i++){
        npcPos[i].x = (1 + (rand() % 60));
        npcPos[i].y = (1 + (rand() % 23));
    }*/
    npcPos[0].x = 5;
    npcPos[0].y = 10;
    npcPos[1].x = 10;
    npcPos[1].y = 20;
    npcPos[2].x = 15;
    npcPos[2].y = 10;
    npcPos[3].x = 25;
    npcPos[3].y = 15;
    for (i = 0; i < NUM_MOBS; i ++){
        npcPos[i].shuriken.throwing = 0;
        npcPos[i].shuriken.movex = 0;
        npcPos[i].shuriken.movey = 0;
        npcPos[i].shuriken.x = 0;
        npcPos[i].shuriken.y = 0;
    }
    playerPos.shuriken.throwing = 0;
    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    //inicializacao allegro

    if(!al_init()){
        al_show_native_message_box(NULL, "AVISO!", "Erro de execução!", "Allegro não inicializada", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    //fontes && bitmaps && formas primitivas

    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_FONT* font48 = al_load_ttf_font("fonte.ttf", 48, 0);
    ALLEGRO_BITMAP *naruto = al_load_bitmap("assets/naruto.png");
    ALLEGRO_BITMAP *shurikenDraw = al_load_bitmap("assets/shuriken.png");
    ALLEGRO_BITMAP *spikes = al_load_bitmap("assets/espinhos.png");
    ALLEGRO_BITMAP *keys = al_load_bitmap("assets/chave.png");

    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    //teclado

    al_install_keyboard();

    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    //declaraçao do mapa

    char mapMatrix[SIZEMAP_Y][SIZEMAP_X];
    map = fopen("arquivos/map64x36.txt", "r");
    rewind(map);
    fseek(map, 0 * SIZEMAP_X * SIZEMAP_Y * sizeof(char), SEEK_SET);
    fread(mapMatrix, sizeof(char), SIZEMAP_X * SIZEMAP_Y, map);
    //const int MAPSCALE = 24;
    /*_____________________________________________________________*/





    /*_____________________________________________________________*/
    //display

    ALLEGRO_DISPLAY *display = NULL;
    display = al_create_display(width, height);
    if (!display){
        al_show_native_message_box(NULL, "AVISO!", "Erro de execução!", "O display não pode ser criado!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    // Keyboard & Joystick

    ALLEGRO_KEYBOARD_STATE *keyState;
    al_install_joystick();
    ALLEGRO_JOYSTICK *joy = al_get_joystick(0);
    ALLEGRO_JOYSTICK_STATE joyState;
    if (joy == NULL)
        joystickFound = 0;
    /*_____________________________________________________________*/







    ALLEGRO_BITMAP *background = NULL;
    background = al_create_bitmap(MAPSCALE * SIZEMAP_X, MAPSCALE * SIZEMAP_Y);

    al_set_target_bitmap(background);

    for(i = 0; i < SIZEMAP_Y; i++){
        for(j = 0; j < SIZEMAP_X; j++){

            if(mapMatrix[i][j] == WALL){
                al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(200,200,200));
                }
            else if(mapMatrix[i][j] == 'X'){
                al_draw_bitmap(spikes, j*MAPSCALE, i*MAPSCALE, 0);
                //al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(100,50,50));
            }
            else if(mapMatrix[i][j] == 'C'){
                al_draw_bitmap(keys, j*MAPSCALE, i*MAPSCALE, 0);
                //al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(100,150,50));

            }
        }
    }
    al_set_target_bitmap(al_get_backbuffer(display));







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

    while(!endOfGame)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(events_queue, &event);
        //al_get_keyboard_state(&keyState);

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            playerInputKeyboard(event, &playerPos, &openMenu, mapMatrix);
        }
        if(joystickFound) {
            if (event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN) {
                //printf("Botao pressionado: %d\n", ev.joystick.button);
                buttonDown(event, &playerPos, &openMenu, mapMatrix);
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
                npcMovement(npcPos, NUM_MOBS, playerPos, mapMatrix);
            }
            if(event.timer.source == shurTimer)
            {
                updateShurikenPos(&playerPos.shuriken, npcPos[0], mapMatrix);//Player shuriken
                for (i = 0; i < NUM_MOBS; i ++){//Mob shuriken
                    if (npcPos[i].shuriken.throwing)
                        updateShurikenPos(&npcPos[i].shuriken, playerPos, mapMatrix);
                    else
                        shurikenDir(&npcPos[i], playerPos);
                }
            }
            if(event.timer.source == timer)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                //drawMap(mapMatrix, spikes, keys);
                al_draw_bitmap(background, 0, 0, 0);
                drawMobs(npcPos);
                drawMobShur(npcPos, NUM_MOBS, shurikenDraw);
                al_draw_bitmap(naruto, playerPos.x*MAPSCALE, playerPos.y*MAPSCALE, 0);
                //al_draw_filled_rectangle(playerPos.x*MAPSCALE, playerPos.y*MAPSCALE, (playerPos.x*MAPSCALE)+MAPSCALE, (playerPos.y*MAPSCALE)+MAPSCALE ,al_map_rgb(255,255,0));//Temp because naruto.png assertion is failling
                if (playerPos.shuriken.throwing)
                    al_draw_bitmap(shurikenDraw, playerPos.shuriken.x*MAPSCALE, playerPos.shuriken.y*MAPSCALE, 0);//Temp because shuriken.png assertion is failling
                    //al_draw_filled_rectangle(playerPos.shuriken.x*MAPSCALE, playerPos.shuriken.y*MAPSCALE, (playerPos.shuriken.x*MAPSCALE)+MAPSCALE, (playerPos.shuriken.y*MAPSCALE)+MAPSCALE ,al_map_rgb(0,0,255));
                al_flip_display();
            }
        }

        if (openMenu) {
            if (joystickFound)
                showMenu(width, height, &endOfGame, &openMenu, display, events_queue, joy, joyState, npcPos, mobRate, &playerPos, &mapUsed);
            else
                showMenu(width, height, &endOfGame, &openMenu, display, events_queue, NULL, joyState, npcPos, mobRate, &playerPos, &mapUsed);
        }
    }

    al_uninstall_keyboard();
    al_destroy_timer(timer);
    al_destroy_timer(mobTimer);
    al_destroy_timer(shurTimer);
    al_destroy_display(display);
    al_destroy_bitmap(naruto);

    return 0;
}

void moveJoystick(ALLEGRO_EVENT event, typePos *playerPos, int *openMenu, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
    if(event.joystick.axis == 0){

        if (event.joystick.pos > 0.25){

            if (verifyPosition(playerPos->x, playerPos->y, TORIGHT, mapMatrix)) {
                playerPos->x ++;
                playerPos->direction = RIGHT;
            }
        }

        else if (event.joystick.pos < -0.25) {
                if (verifyPosition(playerPos->x, playerPos->y, TOLEFT, mapMatrix)) {
                    playerPos->x --;
                    playerPos->direction = LEFT;
                }

        }
    }
    else if(event.joystick.axis == 1){
        switch((int)round(event.joystick.pos)){
            case 1:
                if (verifyPosition(playerPos->x, playerPos->y, TODOWN, mapMatrix)) {
                    playerPos->y ++;
                    playerPos->direction = DOWN;
                }
            break;
            case -1:
                if (verifyPosition(playerPos->x, playerPos->y, TOUP, mapMatrix)) {
                    playerPos->y --;
                    playerPos->direction = UP;
                }
            break;
        }
    }
}

void buttonDown(ALLEGRO_EVENT event, typePos *playerPos, int *openMenu){
    switch (event.joystick.button){
        case CONTROL_BUTTON_A:
            break;
        case CONTROL_BUTTON_B:
            break;
        case CONTROL_BUTTON_X:
            //printf("botao X\n");
            if (!playerPos->shuriken.throwing) {
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

void playerInputKeyboard(ALLEGRO_EVENT event, typePos *playerPos, int *openMenu, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]) {
    switch (event.keyboard.keycode){
        case ALLEGRO_KEY_UP:
        case ALLEGRO_KEY_W:
            if (verifyPosition(playerPos->x, playerPos->y, TOUP, mapMatrix)){
                playerPos->y --;
                playerPos->direction = UP;
            }
            break;
        case ALLEGRO_KEY_DOWN:
        case ALLEGRO_KEY_S:
            if (verifyPosition(playerPos->x, playerPos->y, TODOWN, mapMatrix)) {
                playerPos->y ++;
                playerPos->direction = DOWN;
            }
            break;
        case ALLEGRO_KEY_LEFT:
        case ALLEGRO_KEY_A:
            if (verifyPosition(playerPos->x, playerPos->y, TOLEFT, mapMatrix)) {
                playerPos->x --;
                playerPos->direction = LEFT;
            }
            break;
        case ALLEGRO_KEY_RIGHT:
        case ALLEGRO_KEY_D:
            if (verifyPosition(playerPos->x, playerPos->y, TORIGHT, mapMatrix)){
                playerPos->x ++;
                playerPos->direction = RIGHT;
            }
            break;
        case ALLEGRO_KEY_ESCAPE:
            *openMenu = true;

            break;
        case ALLEGRO_KEY_K:
            if (!playerPos->shuriken.throwing){
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
    }
}
