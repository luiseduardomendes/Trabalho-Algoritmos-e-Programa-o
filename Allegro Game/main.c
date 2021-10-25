#include "headers.h"
#include <allegro5/allegro_image.h>

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));

    /*_____________________________________________________________*/
    //variaveis de temporizador

    clock_t timeCurrent;
    clock_t timeBeginMovement;
    clock_t timeBeginMovementPlayer;
    clock_t timeThrowShurikenPlayer;
    clock_t timeBeginShuriken;
    clock_t timeBeginFrame;
    clock_t timeThrowShuriken;
    clock_t timeMovement;
    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    float frameRate = 120;
    int i, j, k;
    int contador = 0;
    int mobFound, shurikenFound, playerFound;
    typePos playerPos, npcPos[NUM_MOBS];
    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    //inicializacao das posicoes

    playerPos.x = 10;
    playerPos.y = 10;
    for (i = 0; i < NUM_MOBS; i++){
        npcPos[i].x = (1 + (rand() % 60));
        npcPos[i].y = (1 + (rand() % 23));
    }
    npcPos[0].x = 5;
    npcPos[0].y = 10;
    npcPos[1].x = 10;
    npcPos[1].y = 20;
    npcPos[2].x = 15;
    npcPos[2].y = 10;
    npcPos[3].x = 25;
    npcPos[3].y = 15;
    timeBeginMovementPlayer = clock();
    timeThrowShurikenPlayer = clock();
    timeBeginShuriken = clock();
    timeBeginMovement = clock();
    timeBeginFrame = clock();
    timeThrowShuriken = clock();
    timeMovement = clock();
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
    //formas primitivas

    al_init_primitives_addon();
    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    //fontes

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT* font48 = al_load_ttf_font("fonte.ttf", 48, 0);
    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    //teclado

    al_install_keyboard();
    al_install_joystick();
    al_init_image_addon();
    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    //declaraçao do mapa

    char mapMatrix[SIZEMAP_Y][SIZEMAP_X];
    map = fopen("arquivos/maps.txt", "r");
    rewind(map);
    fseek(map, 0 * SIZEMAP_X * SIZEMAP_Y * sizeof(char), SEEK_SET);
    fread(mapMatrix, sizeof(char), SIZEMAP_X * SIZEMAP_Y, map);
    //const int MAPSCALE = 24;
    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    //variaveis para allegro

    const int width = 60*MAPSCALE; //largura
    const int height = 23*MAPSCALE; //algura
    bool endOfGame;
    ALLEGRO_EVENT_QUEUE *events_queue = NULL;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *naruto = al_load_bitmap("assets/naruto.png");
    ALLEGRO_BITMAP *shurikenDraw = al_load_bitmap("assets/shuriken.png");
    /*_____________________________________________________________*/



    /*_____________________________________________________________*/
    //display

    display = al_create_display(width, height);
    if (!display){
        al_show_native_message_box(NULL, "AVISO!", "Erro de execução!", "O display não pode ser criado!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    // Joystick

    ALLEGRO_JOYSTICK *joy = al_get_joystick(0);
    ALLEGRO_JOYSTICK_STATE joyState;

    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    // controle de tempo

    ALLEGRO_TIMER *timer;
    timer = al_create_timer(1.0/frameRate);
    al_start_timer(timer);
    /*_____________________________________________________________*/




    /*_____________________________________________________________*/
    //fila de eventos

    events_queue = al_create_event_queue();
    al_register_event_source(events_queue, al_get_keyboard_event_source());
    al_register_event_source(events_queue, al_get_display_event_source(display));
    al_register_event_source(events_queue, al_get_timer_event_source(timer));
    al_register_event_source(events_queue, al_get_joystick_event_source());
    /*_____________________________________________________________*/




    do {

        ALLEGRO_EVENT ev;
        al_wait_for_event(events_queue, &ev);
        al_get_joystick_state(joy, &joyState);


        timeCurrent = clock();



        for(i = 0; i < SIZEMAP_Y; i++){
            for(j = 0; j < SIZEMAP_X; j++){

                if(mapMatrix[i][j] == WALL){
                    al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(200,200,200));
                    }
                else if(mapMatrix[i][j] == 'X'){
                    al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(100,50,50));
                }
            }
        }
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

        // desenha jogador
        //al_draw_filled_rounded_rectangle((playerPos.x*MAPSCALE), (playerPos.y*MAPSCALE), (playerPos.x*MAPSCALE)+MAPSCALE, (playerPos.y*MAPSCALE)+MAPSCALE, MAPSCALE/3, MAPSCALE/3, al_map_rgb(255,255,0));
        al_draw_bitmap(naruto,(playerPos.x*MAPSCALE), (playerPos.y*MAPSCALE), 0);
        //al_draw_textf(font48, al_map_rgb(255,255,255), width/2, height/2+28, 1, "Quadros: %d   Segundos: %d", contador++, contador/60);
        //al_draw_textf(font48, al_map_rgb(255,255,255), width/2, height/2-28, 1, "Tempo atual: %d    Tempo shuriken: %d", timeCurrent / CLOCKS_PER_SEC, timeBeginShuriken/ CLOCKS_PER_SEC);


        if ((double)(timeCurrent - timeBeginMovement) / CLOCKS_PER_SEC > 0.5){
            npcMovement(npcPos, playerPos, 5, mapMatrix);
            timeBeginMovement = clock();
        }


        if ((double)(timeCurrent - timeThrowShuriken) / CLOCKS_PER_SEC > 0.25){
            throwShuriken(&npcPos[i].shuriken, playerPos, mapMatrix);
            timeThrowShuriken = clock();
        }

        if ((double)(timeCurrent - timeBeginShuriken) / CLOCKS_PER_SEC > 5){
            for(i = 0; i < NUM_MOBS; i ++){
                //printf("NPC %d\n", i);
                //printf("x: %d\ty: %d\tdireção: %d\n", npcPos[i].x,npcPos[i].y,npcPos[i].direction);
                //printf("x: %d\ty: %d\tdireção: x: %d\ty: %d\n", npcPos[i].shuriken.x, npcPos[i].shuriken.y, npcPos[i].shuriken.movex, npcPos[i].shuriken.movey);
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

/* SUBSTITUIRIA A FUNÇÃO ACIMA
        if ((double)(timeCurrent - timeBeginShuriken) / CLOCKS_PER_SEC > 5){
            for(i = 0; i < NUM_MOBS; i ++){
                    if (!npcPos[i].shuriken.throwing) {
                    npcPos[i].shuriken.x = npcPos[i].x;
                    npcPos[i].shuriken.y = npcPos[i].y;
                    verifyShuriken(&npcPos[i].shuriken, npcPos[i], playerPos, mapMatrix);
                    npcPos[i].shuriken.throwing = true;
                    timeBeginShuriken = clock();
                }
            }
        }
*/

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

        // TESTE BOTAO

        if (ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN) {
            //printf("Botao pressionado: %d\n", ev.joystick.button);
            switch (ev.joystick.button){
                case 0:
                    printf("botao A\n");
                    break;
                case 1:
                    printf("botao X\n");
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
                case 2:
                    printf("botao B\n");
                    break;
                case 3:
                    printf("botao Y\n");
                    break;
                case 4:
                    printf("botao LB\n");
                    break;
                case 5:
                    printf("botao RB\n");
                    break;
                case 6:
                    printf("botao options\n");
                    break;
                case 7:
                    printf("botao start\n");
                    break;
                case 8:
                    printf("botao L3\n");
                    break;
                case 9:
                    printf("botao R3\n");
                    break;
            }
        }

        if(ev.type == ALLEGRO_EVENT_JOYSTICK_AXIS && (double) (timeCurrent - timeMovement)/CLOCKS_PER_SEC > 0.05) {
            if(ev.joystick.axis == 0){

                switch((int)round(ev.joystick.pos)){
                    case 1:
                        if (verifyPosition(playerPos.x, playerPos.y, TORIGHT, mapMatrix)) {
                            playerPos.x ++;
                            playerPos.direction = RIGHT;
                        }
                    break;
                    case -1:
                        if (verifyPosition(playerPos.x, playerPos.y, TOLEFT, mapMatrix)) {
                            playerPos.x --;
                            playerPos.direction = LEFT;
                        }
                    break;
                }
            }
            else if(ev.joystick.axis == 1){
                switch((int)round(ev.joystick.pos)){
                    case 1:
                        if (verifyPosition(playerPos.x, playerPos.y, TODOWN, mapMatrix)) {
                            playerPos.y ++;
                            playerPos.direction = DOWN;
                        }
                    break;
                    case -1:
                        if (verifyPosition(playerPos.x, playerPos.y, TOUP, mapMatrix)) {
                            playerPos.y --;
                            playerPos.direction = UP;
                        }
                    break;
                }
            }
            timeMovement = clock();
        }




        if ((double)(timeCurrent - timeThrowShurikenPlayer) / CLOCKS_PER_SEC > 0.1){

            throwShuriken(&playerPos.shuriken, npcPos[0], mapMatrix);
            timeThrowShurikenPlayer = clock();
        }


        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
    } while (!endOfGame);


    al_destroy_bitmap(naruto);
    al_destroy_display(display);
    al_destroy_event_queue(events_queue);
    printf("Hello world!\n");
    return 0;
}
