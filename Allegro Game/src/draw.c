#include "headers.h"

void drawMobs(t_npc npcPos[], ALLEGRO_BITMAP *enemy, ALLEGRO_BITMAP *enemyback, ALLEGRO_BITMAP *enemyleft, ALLEGRO_BITMAP *enemyright, t_player playerPos)
{
    int i;

    for (i = 0; i < NUM_MOBS; i++)
    {
        switch(npcPos[i].direction){
            case UP:
                al_draw_bitmap(enemyback, (npcPos[i].x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (npcPos[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
                break;
            case DOWN:
                al_draw_bitmap(enemy, (npcPos[i].x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (npcPos[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
                break;
            case LEFT:
                al_draw_bitmap(enemyleft, (npcPos[i].x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (npcPos[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
                break;
            case RIGHT:
                al_draw_bitmap(enemyright, (npcPos[i].x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (npcPos[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
                break;
            default:
                al_draw_bitmap(enemy, (npcPos[i].x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (npcPos[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
        }
    }
}

void drawMobShur(t_npc npcPos[], int numMobs, ALLEGRO_BITMAP *shurikenDraw, t_player playerPos)
{
    int i;

    for(i = 0; i < NUM_MOBS; i++)
    {
        if (npcPos[i].shuriken.throwing)
            al_draw_bitmap(shurikenDraw, (npcPos[i].shuriken.x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT,(npcPos[i].shuriken.y - playerPos.y + SIZEMAP_Y/(2*MULT))*
                           MAPSCALE*MULT, 0);
            //al_draw_filled_rectangle(npcPos[i].shuriken.x*MAPSCALE, npcPos[i].shuriken.y*MAPSCALE, (npcPos[i].shuriken.x*MAPSCALE)+MAPSCALE, (npcPos[i].shuriken.y*MAPSCALE)+MAPSCALE ,al_map_rgb(0,0,255));
    }
}

ALLEGRO_BITMAP* createBackground(ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* wall, ALLEGRO_BITMAP* spikes, ALLEGRO_BITMAP* keys,
                                 ALLEGRO_BITMAP* grass, ALLEGRO_DISPLAY* display, char mapMatrix[SIZEMAP_Y][SIZEMAP_X])
{
    background = al_create_bitmap(MAPSCALE * SIZEMAP_X * MULT, MAPSCALE * SIZEMAP_Y * MULT);
    al_set_target_bitmap(background);
    int i, j;

    for(i = 0; i < SIZEMAP_Y; i++){
        for(j = 0; j < SIZEMAP_X; j++){

            if(mapMatrix[i][j] == WALL){
                al_draw_bitmap(wall, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                }
            else if(mapMatrix[i][j] == 'X'){
                al_draw_bitmap(spikes, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                //al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(100,50,50));
            }
            else if(mapMatrix[i][j] == 'C'){
                al_draw_bitmap(keys, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                //al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(100,150,50));

            }
            else{
                al_draw_bitmap(grass, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
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
