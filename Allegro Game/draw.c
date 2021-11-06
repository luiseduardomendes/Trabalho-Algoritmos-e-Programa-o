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

ALLEGRO_BITMAP* createBgBitmap(ALLEGRO_BITMAP *background, char mapMatrix[][SIZEMAP_X], ALLEGRO_BITMAP* wall,
                    ALLEGRO_BITMAP *spikes, ALLEGRO_BITMAP *grass, ALLEGRO_DISPLAY *display){
    int i, j;
    al_init_image_addon();
    background = al_create_bitmap(MAPSCALE * SIZEMAP_X, MAPSCALE * SIZEMAP_Y);
    al_set_target_bitmap(background);


    for(i = 0; i < SIZEMAP_Y; i++){
        for(j = 0; j < SIZEMAP_X; j++){
            al_draw_bitmap(grass, j*MAPSCALE, i*MAPSCALE, 0);
            if(mapMatrix[i][j] == WALL){
                al_draw_bitmap(wall, j*MAPSCALE, i*MAPSCALE, 0);
                }
            else if(mapMatrix[i][j] == 'X'){
                al_draw_bitmap(spikes, j*MAPSCALE, i*MAPSCALE, 0);
                //al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(100,50,50));
            }
            /*else if(mapMatrix[i][j] == 'C'){
                al_draw_bitmap(keys, j*MAPSCALE, i*MAPSCALE, 0);
                //al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(100,150,50));

            }*/
        }
    }
    al_set_target_bitmap(al_get_backbuffer(display));
    return background;

}
