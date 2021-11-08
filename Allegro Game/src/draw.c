#include "headers.h"

void drawMobs(t_npc npcPos[], ALLEGRO_BITMAP *enemy)
{
    int i;

    for (i = 0; i < NUM_MOBS; i++)
        al_draw_bitmap(enemy, npcPos[i].x*MAPSCALE, npcPos[i].y*MAPSCALE, 0);
}

void drawMobShur(t_npc npcPos[], int numMobs, ALLEGRO_BITMAP *shurikenDraw)
{
    int i;

    for(i = 0; i < NUM_MOBS; i++)
    {
        if (npcPos[i].shuriken.throwing)
            al_draw_bitmap(shurikenDraw, npcPos[i].shuriken.x*MAPSCALE,npcPos[i].shuriken.y*MAPSCALE, 0);
            //al_draw_filled_rectangle(npcPos[i].shuriken.x*MAPSCALE, npcPos[i].shuriken.y*MAPSCALE, (npcPos[i].shuriken.x*MAPSCALE)+MAPSCALE, (npcPos[i].shuriken.y*MAPSCALE)+MAPSCALE ,al_map_rgb(0,0,255));
    }
}

ALLEGRO_BITMAP* createBackground(ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* wall, ALLEGRO_BITMAP* spikes, ALLEGRO_BITMAP* keys,
                                 ALLEGRO_BITMAP* grass, ALLEGRO_DISPLAY* display, char mapMatrix[SIZEMAP_Y][SIZEMAP_X])
{
    background = al_create_bitmap(MAPSCALE * SIZEMAP_X, MAPSCALE * SIZEMAP_Y);
    al_set_target_bitmap(background);
    int i, j;

    for(i = 0; i < SIZEMAP_Y; i++){
        for(j = 0; j < SIZEMAP_X; j++){

            if(mapMatrix[i][j] == WALL){
                al_draw_bitmap(wall, j*MAPSCALE, i*MAPSCALE, 0);
                }
            else if(mapMatrix[i][j] == 'X'){
                al_draw_bitmap(spikes, j*MAPSCALE, i*MAPSCALE, 0);
                //al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(100,50,50));
            }
            else if(mapMatrix[i][j] == 'C'){
                al_draw_bitmap(keys, j*MAPSCALE, i*MAPSCALE, 0);
                //al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(100,150,50));

            }
            else{
                al_draw_bitmap(grass, j*MAPSCALE, i*MAPSCALE, 0);
            }
        }
    }
    al_set_target_bitmap(al_get_backbuffer(display));
    return background;
}

void showLoadingScreen (ALLEGRO_FONT* font48, ALLEGRO_BITMAP* loading_screen) {
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(loading_screen, 0,0,0);
    al_draw_text(font48, al_map_rgb(255, 255, 255), 10, 10, 0, "CARREGANDO...");
    al_flip_display();
}
