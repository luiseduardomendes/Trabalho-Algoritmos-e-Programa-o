#include "headers.h"

void drawMobs(typePos npcPos[])
{
    int i;

    for (i = 0; i < NUM_MOBS; i++)
        al_draw_filled_rectangle(npcPos[i].x*MAPSCALE, npcPos[i].y*MAPSCALE,(npcPos[i].x*MAPSCALE)+MAPSCALE, (npcPos[i].y*MAPSCALE)+MAPSCALE,al_map_rgb(200,0,0));
}

void drawMobShur(typePos npcPos[], int numMobs, ALLEGRO_BITMAP *shurikenDraw)
{
    int i;

    for(i = 0; i < NUM_MOBS; i++)
    {
        if (npcPos[i].shuriken.throwing)
            al_draw_bitmap(shurikenDraw, npcPos[i].shuriken.x*MAPSCALE,npcPos[i].shuriken.y*MAPSCALE, 0);
            //al_draw_filled_rectangle(npcPos[i].shuriken.x*MAPSCALE, npcPos[i].shuriken.y*MAPSCALE, (npcPos[i].shuriken.x*MAPSCALE)+MAPSCALE, (npcPos[i].shuriken.y*MAPSCALE)+MAPSCALE ,al_map_rgb(0,0,255));
    }
}

void drawMap(char mapMatrix[][SIZEMAP_X], ALLEGRO_BITMAP *spikes, ALLEGRO_BITMAP *keys){



}
