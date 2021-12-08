#include "headers.h"

int main()
{
    /*_____________________________________________________________*/
    //variaveis para allegro

    float frameRate = 30;

    int mobRate = 2;
    int shurRate = 12;
    int throwShurRate = 2;
    int i, j, k;
    int contador = 0;
    int mapUsed = 0;
    int dialogClosed = 1;
    int joystickFound = 1;
    int throwingBoss;
    int closeCongrats;
    t_player playerPos;
    t_npc npcPos[NUM_MOBS];
    t_chest chests[10];
    t_boss boss;
    t_exit mapExit;
    t_counting *counting;



    int openMainMenu = 1;
    typeSave save;
    typeItem items[MIN_ITEMS];

    char mapMatrix[SIZEMAP_Y][SIZEMAP_X];

    const int width = SIZEMAP_X*MAPSCALE; //largura
    const int height = SIZEMAP_Y*MAPSCALE; //algura
    bool endOfGame = false, endOfLevel = false, openMenu = false;

    srand(time(NULL));
    /*_____________________________________________________________*/

    /*_____________________________________________________________*/
    //inicializacao allegro

    if(!al_init()){
        al_show_native_message_box(NULL, "AVISO!", "Erro de execucao!", "Allegro nao inicializada", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    /*_____________________________________________________________*/

    /*_____________________________________________________________*/
    //display

    ALLEGRO_DISPLAY *display = NULL;
    display = al_create_display(width, height);
    if (!display){
        al_show_native_message_box(NULL, "AVISO!", "Erro de execucao!", "O display nao pode ser criado!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    /*_____________________________________________________________*/

    /*_____________________________________________________________*/
    //fontes && bitmaps && formas primitivas

    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    bitmaps bmps;

    t_fonts fonts;

    fonts.font48 = al_load_ttf_font("fonts/fonte.ttf", 48, 0);
    fonts.font36 = al_load_ttf_font("fonts/fonte.ttf", 36, 0);


    bmps.naruto = al_load_bitmap("assets/naruto.png");
    bmps.shurikenDraw = al_load_bitmap("assets/shuriken2.png");
    bmps.spikes = al_load_bitmap("assets/spikes.png");
    bmps.keys = al_load_bitmap("assets/chave.png");
    bmps.enemy = al_load_bitmap("assets/akatsuki.png");
    bmps.wall = al_load_bitmap("assets/wall.png");
    bmps.grass = al_load_bitmap("assets/grass.png");
    bmps.darkGrass = al_load_bitmap("assets/darkGrass.png");
    bmps.lightGrass = al_load_bitmap("assets/lightGrass.png");
    bmps.heart = al_load_bitmap("assets/heart.png");
    bmps.voidheart = al_load_bitmap("assets/voidheart.png");
    bmps.narutoDialog = al_load_bitmap("assets/narutodialog.png");
    bmps.loading_screen = al_load_bitmap("assets/loading_screen.png");
    bmps.background = NULL;
    bmps.dialogBmp = al_load_bitmap("assets/dialogChat.png");
    bmps.narutoback = al_load_bitmap("assets/narutoback.png");
    bmps.narutoleft = al_load_bitmap("assets/narutoleft.png");
    bmps.narutoright = al_load_bitmap("assets/narutoright.png");
    bmps.enemyback = al_load_bitmap("assets/akatsukiback.png");
    bmps.enemyleft = al_load_bitmap("assets/akatsukileft.png");
    bmps.enemyright = al_load_bitmap("assets/akatsukiright.png");
    bmps.chest = al_load_bitmap("assets/bau.png");
    bmps.openchest = al_load_bitmap("assets/bauaberto.png");
    bmps.trapdoor = al_load_bitmap("assets/trapdoor.png");
    bmps.XPbarEmptyLeft = al_load_bitmap("assets/EXPbarEmptyLeft.png");
    bmps.XPbarEmptyMid = al_load_bitmap("assets/EXPbarEmptyMid.png");
    bmps.XPbarEmptyRight = al_load_bitmap("assets/EXPbarEmptyRight.png");
    bmps.XPbarFullMid = al_load_bitmap("assets/EXPbarFullMid.png");
    bmps.XPbarFullLeft = al_load_bitmap("assets/EXPbarFullLeft.png");
    bmps.XPbarFullRight = al_load_bitmap("assets/EXPbarFullRight.png");
    bmps.enemyBoss = al_load_bitmap("assets/orochimaru.png");
    bmps.ultimate = al_load_bitmap("assets/ultimate.png");
    bmps.miniMap = NULL;
    al_convert_mask_to_alpha(bmps.narutoDialog, al_map_rgb(255,0,255));



    /*_____________________________________________________________*/


    /*_____________________________________________________________*/
    //Audio

    ALLEGRO_SAMPLE *throwShur = NULL;

    al_init_acodec_addon();
    al_install_audio();
    al_reserve_samples(true);
    throwShur = al_load_sample("sfx/throwShur.wav");
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

    ALLEGRO_TIMER *timer, *mobTimer, *shurTimer, *throwShurTimer, *ultTimer;
    timer = al_create_timer(1.0/frameRate);
    al_start_timer(timer);
    mobTimer = al_create_timer(1.0/mobRate);
    al_start_timer(mobTimer);
    shurTimer = al_create_timer(1.0/shurRate);
    al_start_timer(shurTimer);
    throwShurTimer = al_create_timer(1.0/throwShurRate);
    al_start_timer(throwShurTimer);
    ultTimer = al_create_timer(1.0);
    al_start_timer(ultTimer);
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
    al_register_event_source(events_queue, al_get_timer_event_source(throwShurTimer));
    al_register_event_source(events_queue, al_get_timer_event_source(ultTimer));
    al_register_event_source(events_queue, al_get_joystick_event_source());
    /*_____________________________________________________________*/

    /*_____________________________________________________________*/
    //menu iniciar

    openMainMenu = 1;
    /*_____________________________________________________________*/
    do{

        if (openMainMenu){
            al_clear_to_color(al_map_rgb(0,0,0));
            if(joystickFound){

                menuIniciar(width, height, &endOfGame, &endOfLevel, &openMainMenu, display, events_queue, joy, joyState,
                            npcPos, &playerPos, &mapUsed, counting, items, chests, mapMatrix, &boss, fonts, bmps);
            }
            else{
                menuIniciar(width, height, &endOfGame, &endOfLevel, &openMainMenu, display, events_queue, NULL, joyState,
                            npcPos, &playerPos, &mapUsed, counting, items, chests, mapMatrix, &boss, fonts, bmps);
            }
        }
        else{
            endOfLevel = 0;

            standardSave(mapUsed);
            loadSave(npcPos, &playerPos, &mapUsed, counting, items, chests, mapMatrix, &boss);
            playerPos.numKeys = 0;
            mapExit.onMap = 0;
        }
        dialogClosed = 0;
        loadMap(mapMatrix, mapUsed);
        bmps.background = createBackground(bmps, display, mapMatrix);

        while(!endOfLevel)
        {
            ALLEGRO_EVENT event;
            al_wait_for_event(events_queue, &event);

            if(event.type == ALLEGRO_EVENT_KEY_DOWN)
                playerInputKeyboard(event, &playerPos, &openMenu, mapMatrix, items, *counting, chests, throwShur, &mapExit, mapUsed, &endOfLevel);

            if(joystickFound) {
                if (event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN) {
                    //printf("Botao pressionado: %d\n", ev.joystick.button);
                    buttonDown(event, &playerPos, &openMenu, mapMatrix, items, *counting, chests, throwShur, &mapExit, mapUsed, &endOfLevel);
                }
                if(event.type == ALLEGRO_EVENT_JOYSTICK_AXIS) {
                    moveJoystick(event, &playerPos, &openMenu, mapMatrix);
                }
            }
            if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                endOfGame = true;
                endOfLevel = true;
            }
            if(event.type == ALLEGRO_EVENT_TIMER)
            {
                if(event.timer.source == mobTimer)
                {
                    npcMovement(npcPos, counting->numMobs, &playerPos, mapMatrix);
                    moveBoss(&boss, &playerPos, mapMatrix);
                }

                if(event.timer.source == throwShurTimer)
                {
                    for (i = 0; i < counting->numMobs; i ++){
                        if (npcPos[i].alive)
                            if (!npcPos[i].shuriken.throwing)
                                shurikenDir(&npcPos[i], playerPos, throwShur);
                    }

                    if (boss.alive){
                        throwingBoss = 0;
                        for (i = 0; i < 8; i ++){
                            if (boss.shurikens[i].throwing)
                                throwingBoss = 1;
                        }
                        if(!throwingBoss) {
                            shurikenDirBoss(&boss, playerPos, throwShur);
                        }
                    }

                }
                if(event.timer.source == shurTimer)
                {

                    updateShurikenPlayer(&playerPos, npcPos, &boss, counting->numMobs, mapMatrix, &mapExit);//Player shuriken
                    for (i = 0; i < counting->numMobs; i ++){ //Mob shuriken
                        if (npcPos[i].alive) {
                            if (npcPos[i].shuriken.throwing)
                                updateShurikenPos(&npcPos[i].shuriken, &playerPos, mapMatrix);
                        }
                    }
                    if(boss.alive){
                        updateShurikenBoss(&boss, &playerPos, mapMatrix);
                    }
                }

                if(playerPos.xp >= MIN_XP_UP){
                    levelUp(&playerPos);
                }

                if(event.timer.source == ultTimer){
                    if(playerPos.ultBar < playerPos.fullUltBar)
                        playerPos.ultBar ++;
                }


                if(event.timer.source == timer)
                {
                    if(playerPos.invulnerable > 0)
                        playerPos.invulnerable --;

                    createMiniMap(mapMatrix, &bmps.miniMap, display, playerPos);
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_bitmap(bmps.background, (SIZEMAP_X/(2*MULT) - playerPos.x)*MAPSCALE*MULT, (SIZEMAP_Y/(2*MULT) - playerPos.y)*MAPSCALE*MULT, 0);

                    drawMapElements(npcPos, items, chests, mapExit, playerPos, boss, *counting, bmps, width, height);

                    drawInterface(bmps, playerPos, boss, width, height, mapUsed, fonts);

                    al_flip_display();

                    while (!dialogClosed){ // dialogo

                        drawDialog(bmps, width, height, mapUsed, fonts);
                        al_wait_for_event(events_queue, &event);


                        if((event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER ) ||
                        (event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN && event.joystick.button == CONTROL_BUTTON_A))
                                dialogClosed = 1;
                    }


                }
            }

            if (openMenu) {
                if (joystickFound)
                    showMenu(width, height, &endOfLevel, &openMenu, display, events_queue, joy, joyState, npcPos,
                             &playerPos, &mapUsed, counting, items, mapMatrix, chests, &openMainMenu, &boss, fonts, bmps);
                else
                    showMenu(width, height, &endOfLevel, &openMenu, display, events_queue, NULL, joyState, npcPos,
                             &playerPos, &mapUsed, counting, items, mapMatrix, chests, &openMainMenu, &boss, fonts, bmps);
            }

            if (playerPos.hp == 0){
                do{
                    al_wait_for_event(events_queue, &event);
                    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                        endOfGame = true;
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_draw_bitmap(bmps.loading_screen, 0,0,0);
                    al_draw_text(fonts.font48, al_map_rgb(255, 255, 255), width/2, height/2, 1, "Voce morreu!");
                    al_flip_display();


                    if((event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER ) ||
                       (event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN && event.joystick.button == CONTROL_BUTTON_A)){


                            standardSave(0);
                            loadSave(npcPos, &playerPos, &mapUsed, counting, items, chests, mapMatrix, &boss);
                            endOfLevel = 1;
                            openMainMenu = 1;
                            saveFunction(npcPos, playerPos, mapUsed, *counting, items, chests, boss);


                    }
                } while(!endOfLevel);
            }

        }

        if (!openMainMenu){
            if (mapUsed != 2)
                mapUsed ++;
            else {
                closeCongrats = 0;
                do{

                    ALLEGRO_EVENT event;
                    al_wait_for_event(events_queue, &event);
                    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                        endOfGame = true;
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_draw_bitmap(bmps.loading_screen, 0,0,0);
                    al_draw_text(fonts.font48, al_map_rgb(255, 255, 255), width/2, (height-120)/2, 1, "Parabens!");
                    al_draw_text(fonts.font48, al_map_rgb(255, 255, 255), width/2, height/2, 1, "Voce derrotou Orochimaru e recuperou");
                    al_draw_text(fonts.font48, al_map_rgb(255, 255, 255), width/2, (height+120)/2, 1, "o pergaminho roubado da vila da folha!");
                    al_flip_display();


                    if((event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER ) ||
                       (event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN && event.joystick.button == CONTROL_BUTTON_A)){
                        closeCongrats = 1;
                    }
                    endOfLevel = 1;
                    openMainMenu = 1;
                } while(!closeCongrats);
            }

            saveFunction(npcPos, playerPos, mapUsed, *counting, items, chests, boss);
        }

    }while(!endOfGame);

    al_destroy_display(display);
    al_uninstall_keyboard();
    al_destroy_timer(timer);
    al_destroy_timer(mobTimer);
    al_destroy_timer(shurTimer);
    al_destroy_timer(throwShurTimer);
    al_destroy_timer(ultTimer);
    al_destroy_bitmap(bmps.naruto);
    al_destroy_bitmap(bmps.shurikenDraw);
    al_destroy_bitmap(bmps.spikes);
    al_destroy_bitmap(bmps.keys);
    al_destroy_bitmap(bmps.enemy);
    al_destroy_bitmap(bmps.wall);
    al_destroy_bitmap(bmps.grass);
    al_destroy_bitmap(bmps.heart);
    al_destroy_bitmap(bmps.voidheart);
    al_destroy_bitmap(bmps.narutoDialog);

    return 0;
}

