#include "headers.h"

int main()
{
    /*_____________________________________________________________*/
    //variaveis para allegro

    float frameRate = 30;
    int numMobs = 4;
    int mobRate = 2;
    int shurRate = 12;
    int throwShurRate = 2;
    int i, j, k;
    int contador = 0;
    int mapUsed = 0;
    int dialogClosed = 1;
    int joystickFound = 1;
    int throwingBoss;
    t_player playerPos;
    t_npc npcPos[NUM_MOBS];
    t_chest chests[10];
    t_boss boss;
    t_exit mapExit;
    int numChest;
    int playerLogout = 0;
    typeSave save;
    typeItem items[MIN_ITEMS];
    int numShur, numKeys;
    char mapMatrix[SIZEMAP_Y][SIZEMAP_X];

    const int width = SIZEMAP_X*MAPSCALE; //largura
    const int height = SIZEMAP_Y*MAPSCALE; //algura
    bool endOfGame = false, endOfLevel = false, openMenu = false;

    srand(time(NULL));
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
    ALLEGRO_FONT* font36 = al_load_ttf_font("fonts/fonte.ttf", 36, 0);
    ALLEGRO_BITMAP *naruto = al_load_bitmap("assets/naruto.png");
    ALLEGRO_BITMAP *shurikenDraw = al_load_bitmap("assets/shuriken2.png");
    ALLEGRO_BITMAP *spikes = al_load_bitmap("assets/spikes.png");
    ALLEGRO_BITMAP *keys = al_load_bitmap("assets/chave.png");
    ALLEGRO_BITMAP *enemy = al_load_bitmap("assets/akatsuki.png");
    ALLEGRO_BITMAP *wall = al_load_bitmap("assets/wall.png");
    ALLEGRO_BITMAP *grass = al_load_bitmap("assets/grass.png");
    ALLEGRO_BITMAP *darkGrass = al_load_bitmap("assets/darkGrass.png");
    ALLEGRO_BITMAP *lightgrass = al_load_bitmap("assets/lightGrass.png");
    ALLEGRO_BITMAP *heart = al_load_bitmap("assets/heart.png");
    ALLEGRO_BITMAP *voidheart = al_load_bitmap("assets/voidheart.png");
    ALLEGRO_BITMAP *narutoDialog = al_load_bitmap("assets/narutodialog.png");
    ALLEGRO_BITMAP *loading_screen = al_load_bitmap("assets/loading_screen.png");
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *dialogBmp = al_load_bitmap("assets/dialogChat.png");
    ALLEGRO_BITMAP *narutoback = al_load_bitmap("assets/narutoback.png");
    ALLEGRO_BITMAP *narutoleft = al_load_bitmap("assets/narutoleft.png");
    ALLEGRO_BITMAP *narutoright = al_load_bitmap("assets/narutoright.png");
    ALLEGRO_BITMAP *enemyback = al_load_bitmap("assets/akatsukiback.png");
    ALLEGRO_BITMAP *enemyleft = al_load_bitmap("assets/akatsukileft.png");
    ALLEGRO_BITMAP *enemyright = al_load_bitmap("assets/akatsukiright.png");
    ALLEGRO_BITMAP *chest = al_load_bitmap("assets/bau.png");
    ALLEGRO_BITMAP *openchest = al_load_bitmap("assets/bauaberto.png");
    ALLEGRO_BITMAP *trapdoor = al_load_bitmap("assets/trapdoor.png");
    ALLEGRO_BITMAP *XPbarEmptyLeft = al_load_bitmap("assets/EXPbarEmptyLeft.png");
    ALLEGRO_BITMAP *XPbarEmptyMid = al_load_bitmap("assets/EXPbarEmptyMid.png");
    ALLEGRO_BITMAP *XPbarEmptyRight = al_load_bitmap("assets/EXPbarEmptyRight.png");
    ALLEGRO_BITMAP *XPbarFullMid = al_load_bitmap("assets/EXPbarFullMid.png");
    ALLEGRO_BITMAP *XPbarFullLeft = al_load_bitmap("assets/EXPbarFullLeft.png");
    ALLEGRO_BITMAP *XPbarFullRight = al_load_bitmap("assets/EXPbarFullRight.png");
    ALLEGRO_BITMAP *miniMap = NULL;
    al_convert_mask_to_alpha(narutoDialog, al_map_rgb(255,0,255));

    /*_____________________________________________________________*/


    /*_____________________________________________________________*/
    //Audio

    ALLEGRO_SAMPLE *throwShur = NULL;
    //ALLEGRO_SAMPLE_INSTANCE *throwShurInst = NULL;

    al_init_acodec_addon();
    al_install_audio();
    al_reserve_samples(true);
    throwShur = al_load_sample("sfx/throwShur.wav");
    //throwShurInst = al_create_sample_instance(throwShur);
    //al_attach_sample_instance_to_mixer(throwShurInst, al_get_default_mixer());
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

    ALLEGRO_TIMER *timer, *mobTimer, *shurTimer, *throwShurTimer;
    timer = al_create_timer(1.0/frameRate);
    al_start_timer(timer);
    mobTimer = al_create_timer(1.0/mobRate);
    al_start_timer(mobTimer);
    shurTimer = al_create_timer(1.0/shurRate);
    al_start_timer(shurTimer);
    throwShurTimer = al_create_timer(1.0/throwShurRate);
    al_start_timer(throwShurTimer);
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
    al_register_event_source(events_queue, al_get_joystick_event_source());
    /*_____________________________________________________________*/

    /*_____________________________________________________________*/
    //menu iniciar


    /*_____________________________________________________________*/
    playerLogout = 1;
    do{

        if (playerLogout){
            al_clear_to_color(al_map_rgb(0,0,0));
            if(joystickFound){
                menuIniciar(width, height, &endOfGame, &endOfLevel, &playerLogout, display, events_queue, joy, joyState, npcPos, &numMobs, &playerPos, &mapUsed, &numShur,
                            &numKeys, &numChest, items, chests, mapMatrix, &boss);
            }
            else{
                menuIniciar(width, height, &endOfGame, &endOfLevel, &playerLogout, display, events_queue, NULL, joyState, npcPos, &numMobs, &playerPos, &mapUsed, &numShur,
                            &numKeys, &numChest, items, chests, mapMatrix, &boss);
            }
            loadMap(mapMatrix, mapUsed);
            background = createBackground(background, wall, spikes, keys, grass, darkGrass, lightgrass, display, mapMatrix);
        }
        else{
            endOfLevel = 0;

            loadMap(mapMatrix, mapUsed);

            standardSave(mapUsed);
            loadSave(npcPos, &numMobs, &playerPos, &mapUsed, &numShur, &numKeys, &numChest, items, chests, mapMatrix, &boss);
            playerPos.numKeys = 4;

            background = createBackground(background, wall, spikes, keys, grass, darkGrass, lightgrass, display, mapMatrix);

            dialogClosed = 0;
        }


        while(!endOfLevel && !playerLogout)
        {
            playerLogout = 0;
            ALLEGRO_EVENT event;
            al_wait_for_event(events_queue, &event);
            //al_get_keyboard_state(&keyState);




            if(event.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                playerInputKeyboard(event, &playerPos, &openMenu, mapMatrix, items, numShur, numKeys, numChest, chests, throwShur, &mapExit, mapUsed, &endOfLevel);
            }
            if(joystickFound) {
                if (event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN) {
                    //printf("Botao pressionado: %d\n", ev.joystick.button);
                    buttonDown(event, &playerPos, &openMenu, mapMatrix, items, numShur, numKeys, numChest, chests, throwShur, &mapExit, mapUsed, &endOfLevel);
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
                    npcMovement(npcPos, numMobs, &playerPos, mapMatrix);
                    moveBoss(&boss, &playerPos, mapMatrix);
                }

                if(event.timer.source == throwShurTimer)
                {
                    for (i = 0; i < numMobs; i ++){
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

                    updateShurikenPlayer(&playerPos, npcPos, &boss, numMobs, mapMatrix);//Player shuriken
                    for (i = 0; i < numMobs; i ++){ //Mob shuriken
                        if (npcPos[i].alive) {
                            if (npcPos[i].shuriken.throwing)
                                updateShurikenPos(&npcPos[i].shuriken, &playerPos, mapMatrix);
                        }
                        if(boss.alive){
                            updateShurikenBoss(&boss, &playerPos, mapMatrix);
                        }
                    }
                }

                if(playerPos.xp >= MIN_XP_UP){
                    levelUp(&playerPos);
                }


                if(event.timer.source == timer)
                {

                    createMiniMap(mapMatrix, &miniMap, display, playerPos);
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_bitmap(background, (SIZEMAP_X/(2*MULT) - playerPos.x)*MAPSCALE*MULT, (SIZEMAP_Y/(2*MULT) - playerPos.y)*MAPSCALE*MULT, 0);
                    if(playerPos.invulnerable > 0){
                        playerPos.invulnerable --;
                    }
                    if (boss.alive){
                        al_draw_filled_rectangle((boss.x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (boss.y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, (boss.x - playerPos.x +1+ SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (boss.y - playerPos.y+1 + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, al_map_rgb(255,255,0));
                    }

                    for (i = 0; i < playerPos.hp; i++)
                        al_draw_tinted_bitmap(heart, al_map_rgba_f(OPACITY, OPACITY, OPACITY, OPACITY), (i+1)*MAPSCALE*MULT, 0, 0);
                    for (i = playerPos.hp; i < playerPos.fullHp; i ++)
                        al_draw_tinted_bitmap(voidheart, al_map_rgba_f(OPACITY, OPACITY, OPACITY, OPACITY), (i+1)*MAPSCALE*MULT, 0, 0);
                    for (i = 0; i < playerPos.numShur; i ++)
                        al_draw_tinted_bitmap(shurikenDraw, al_map_rgba_f(OPACITY, OPACITY, OPACITY, OPACITY), (i+1)*MAPSCALE*MULT, (1)*MAPSCALE*MULT, 0);
                    for (i = 0; i < playerPos.numKeys; i ++)
                        al_draw_tinted_bitmap(keys, al_map_rgba_f(OPACITY, OPACITY, OPACITY, OPACITY), (i+1)*MAPSCALE*MULT, (2)*MAPSCALE*MULT, 0);
                    for (i = 0; i < numShur + numKeys; i ++)
                        if (items[i].onMap == 1)
                            if (items[i].nameItems == 1)
                                al_draw_bitmap(keys, (items[i].x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (items[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
                            else if (items[i].nameItems == 0)
                                al_draw_bitmap(shurikenDraw, (items[i].x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (items[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);

                    for (i = 0; i < numChest; i ++){
                        if (chests[i].closed){
                            al_draw_bitmap(chest, (chests[i].x - playerPos.x + SIZEMAP_X/(2*MULT)) * MAPSCALE*MULT, (chests[i].y - playerPos.y + SIZEMAP_Y/(2*MULT)) * MAPSCALE*MULT, 0);
                        }
                        else {
                            al_draw_bitmap(openchest, (chests[i].x - playerPos.x + SIZEMAP_X/(2*MULT)) * MAPSCALE*MULT, (chests[i].y - playerPos.y + SIZEMAP_Y/(2*MULT)) * MAPSCALE*MULT, 0);
                        }
                    }

                    for (i = 0; i < 8; i ++){
                        al_draw_bitmap(shurikenDraw, (boss.shurikens[i].x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (boss.shurikens[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
                    }

                    if(mapExit.onMap == 1)
                    {
                        al_draw_bitmap(trapdoor, (mapExit.x - playerPos.x + SIZEMAP_X/(2*MULT)) * MAPSCALE*MULT, (mapExit.y - playerPos.y + SIZEMAP_Y/(2*MULT)) * MAPSCALE*MULT, 0);
                    }


                    drawMobs(npcPos, numMobs, enemy, enemyback, enemyleft, enemyright, playerPos);
                    drawMobShur(npcPos, numMobs, shurikenDraw, playerPos);

                    if (playerPos.invulnerable){
                        switch(playerPos.direction){
                            case UP:
                                al_draw_tinted_bitmap(narutoback, al_map_rgba_f(0.5, 0.5, 0.5, 0.5), width/2, height/2, 0);
                                break;
                            case DOWN:
                                al_draw_tinted_bitmap(naruto, al_map_rgba_f(0.5, 0.5, 0.5, 0.5),width/2, height/2, 0);
                                break;
                            case LEFT:
                                al_draw_tinted_bitmap(narutoleft, al_map_rgba_f(0.5, 0.5, 0.5, 0.5),width/2, height/2, 0);
                                break;
                            case RIGHT:
                                al_draw_tinted_bitmap(narutoright, al_map_rgba_f(0.5, 0.5, 0.5, 0.5),width/2, height/2, 0);
                                break;
                            default:
                                al_draw_tinted_bitmap(naruto, al_map_rgba_f(0.5, 0.5, 0.5, 0.5),width/2, height/2, 0);
                        }
                    }
                    else{
                        switch(playerPos.direction){
                            case UP:
                                al_draw_bitmap(narutoback, width/2, height/2, 0);
                                break;
                            case DOWN:
                                al_draw_bitmap(naruto, width/2, height/2, 0);
                                break;
                            case LEFT:
                                al_draw_bitmap(narutoleft, width/2, height/2, 0);
                                break;
                            case RIGHT:
                                al_draw_bitmap(narutoright, width/2, height/2, 0);
                                break;
                            default:
                                al_draw_bitmap(naruto, width/2, height/2, 0);
                        }
                    }


                    //al_draw_filled_rectangle(playerPos.x*MAPSCALE, playerPos.y*MAPSCALE, (playerPos.x*MAPSCALE)+MAPSCALE, (playerPos.y*MAPSCALE)+MAPSCALE ,al_map_rgb(255,255,0));//Temp because naruto.png assertion is failling
                    if (playerPos.shuriken.throwing)
                        al_draw_bitmap(shurikenDraw, (playerPos.shuriken.x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (playerPos.shuriken.y - playerPos.y + SIZEMAP_Y/(2*MULT))
                                       *MAPSCALE*MULT, 0);//Temp because shuriken.png assertion is failling
                    al_draw_tinted_bitmap(miniMap, al_map_rgba_f(0.5, 0.5, 0.5, 0.5), width - (SIZEMAP_X + 3)*MINIMAP_SCALE, height - (SIZEMAP_Y + 3)*MINIMAP_SCALE, 0);
                        //al_draw_filled_rectangle(playerPos.shuriken.x*MAPSCALE, playerPos.shuriken.y*MAPSCALE, (playerPos.shuriken.x*MAPSCALE)+MAPSCALE, (playerPos.shuriken.y*MAPSCALE)+MAPSCALE ,al_map_rgb(0,0,255));

                    for (i = 0; i < playerPos.xp; i++)
                    {
                        if(i == 0)
                            al_draw_bitmap(XPbarFullLeft, (i+1)*MAPSCALE*MULT, height - 40, 0);
                        else if(i == 24)
                            al_draw_bitmap(XPbarFullRight, (i+1)*MAPSCALE*MULT, height - 40, 0);
                        else
                            al_draw_bitmap(XPbarFullMid, (i+1)*MAPSCALE*MULT, height - 40, 0);
                    }

                    for (i = playerPos.xp; i < 25; i++)
                    {
                        if(i == 0)
                            al_draw_bitmap(XPbarEmptyLeft, (i+1)*MAPSCALE*MULT, height - 40, 0);
                        else if(i == 24)
                            al_draw_bitmap(XPbarEmptyRight, (i+1)*MAPSCALE*MULT, height - 40, 0);
                        else
                            al_draw_bitmap(XPbarEmptyMid, (i+1)*MAPSCALE*MULT, height - 40, 0);
                    }

                    al_draw_textf(font48, al_map_rgb(102, 187, 106), (width - 200)/2, height-70, ALLEGRO_ALIGN_CENTER, "%d", playerPos.level);


                    al_flip_display();

                    while (!dialogClosed){ // dialogo

                        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
                            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                                dialogClosed = 1;

                        al_draw_bitmap(dialogBmp, width/5, height*1/2, 0);
                        al_draw_text(font36, al_map_rgb(0,0,0), width*1.7/3, height*2.5/4, ALLEGRO_ALIGN_CENTER, "Voces nao vao se sair bem dessa");
                        al_draw_text(font36, al_map_rgb(0,0,0), width*1.7/3, height*2.75/4, ALLEGRO_ALIGN_CENTER, "Voces estao enfrentando o futuro hokage");
                        al_draw_text(font36, al_map_rgb(0,0,0), width*1.7/3, height*3.0/4, ALLEGRO_ALIGN_CENTER, "da vila da folha");
                        al_draw_bitmap(narutoDialog, -70, height-433,0);
                        al_flip_display();
                        al_wait_for_event(events_queue, &event);
                    }


                }
            }

            if (openMenu) {
                if (joystickFound)
                    showMenu(width, height, &endOfGame, &openMenu, display, events_queue, joy, joyState, npcPos,
                            &numMobs, &playerPos, &mapUsed, &numShur, &numKeys, &numChest, items, mapMatrix, chests, &playerLogout, &boss);
                else
                    showMenu(width, height, &endOfGame, &openMenu, display, events_queue, NULL, joyState, npcPos,
                            &numMobs, &playerPos, &mapUsed, &numShur, &numKeys, &numChest, items, mapMatrix, chests, &playerLogout, &boss);
            }

            if (playerPos.hp == 0){
                endOfLevel = 1;
                do{
                    al_wait_for_event(events_queue, &event);
                    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                        endOfGame = true;
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_draw_bitmap(loading_screen, 0,0,0);
                    al_draw_text(font48, al_map_rgb(255, 255, 255), width/2, height/2, 1, "Você morreu!");
                    al_flip_display();
                } while(!endOfGame);
            }

        }

        if (!playerLogout){
            mapUsed ++;
        }
        saveFunction(npcPos, numMobs, playerPos, mapUsed, numShur, numKeys, numChest, items, chests, boss);
    }while(!endOfGame);

    al_destroy_display(display);
    al_uninstall_keyboard();
    al_destroy_timer(timer);
    al_destroy_timer(mobTimer);
    al_destroy_timer(shurTimer);
    al_destroy_timer(throwShurTimer);
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

