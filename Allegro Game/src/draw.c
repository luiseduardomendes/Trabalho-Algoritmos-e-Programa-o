#include "headers.h"

void drawMobs(t_npc npcPos[], int numMobs, ALLEGRO_BITMAP *enemy, ALLEGRO_BITMAP *enemyback, ALLEGRO_BITMAP *enemyleft,
            ALLEGRO_BITMAP *enemyright, t_player playerPos)
{
    int i;

    for (i = 0; i < numMobs; i++)
    {
        if(npcPos[i].alive)
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
                    al_draw_bitmap(enemy, (npcPos[i].x - playerPos.x + SIZEMAP_X)/(2*MULT)*MAPSCALE*MULT, (npcPos[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
            }
        }
    }
}

void drawMobShur(t_npc npcPos[], int numMobs, ALLEGRO_BITMAP *shurikenDraw, t_player playerPos)
{
    int i;

    for(i = 0; i < numMobs; i++)
    {
        if (npcPos[i].shuriken.throwing && npcPos[i].alive)
            al_draw_bitmap(shurikenDraw, (npcPos[i].shuriken.x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT,(npcPos[i].shuriken.y - playerPos.y + SIZEMAP_Y/(2*MULT))*
                           MAPSCALE*MULT, 0);
            //al_draw_filled_rectangle(npcPos[i].shuriken.x*MAPSCALE, npcPos[i].shuriken.y*MAPSCALE, (npcPos[i].shuriken.x*MAPSCALE)+MAPSCALE, (npcPos[i].shuriken.y*MAPSCALE)+MAPSCALE ,al_map_rgb(0,0,255));
    }
}

ALLEGRO_BITMAP* createBackground(ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* wall, ALLEGRO_BITMAP* spikes, ALLEGRO_BITMAP* keys,
                                 ALLEGRO_BITMAP* grass, ALLEGRO_BITMAP* darkGrass, ALLEGRO_BITMAP* lightGrass, ALLEGRO_DISPLAY* display,
                                 char mapMatrix[SIZEMAP_Y][SIZEMAP_X])
{
    background = al_create_bitmap(MAPSCALE * SIZEMAP_X * MULT, MAPSCALE * SIZEMAP_Y * MULT);
    al_set_target_bitmap(background);
    int i, j, flag;

    for(i = 0; i < SIZEMAP_Y; i++){
        for(j = 0; j < SIZEMAP_X; j++){

            if(mapMatrix[i][j] == WALL){
                al_draw_bitmap(wall, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                }
            else if(mapMatrix[i][j] == 'X'){
                al_draw_bitmap(spikes, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                //al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(100,50,50));
            }
            else {
                flag = rand() % 20;
                switch (flag) {
                case 8:
                    al_draw_bitmap(lightGrass, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                    break;
                case 9:
                    al_draw_bitmap(darkGrass, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                    break;
                default:
                    al_draw_bitmap(grass, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                    break;
                }
            }


        }
    }
    al_set_target_bitmap(al_get_backbuffer(display));
    return background;
}


void createMiniMap(char mapMatrix[][SIZEMAP_X], ALLEGRO_BITMAP** miniMap, ALLEGRO_DISPLAY *display, t_player player){
    int i, j;

    *miniMap = al_create_bitmap(MINIMAP_SCALE * SIZEMAP_X, MINIMAP_SCALE * SIZEMAP_Y);
    al_set_target_bitmap(*miniMap);

    for (i = 0; i < SIZEMAP_Y; i ++) {
        for (j = 0; j < SIZEMAP_X; j ++) {
            switch (mapMatrix[i][j]){
            case WALL:
                al_draw_filled_rectangle(j * MINIMAP_SCALE, i * MINIMAP_SCALE, (j + 1) * MINIMAP_SCALE, (i + 1) * MINIMAP_SCALE,
                                  al_map_rgb(50,50,50));
                break;
            case 'X':
                al_draw_filled_rectangle(j * MINIMAP_SCALE, i * MINIMAP_SCALE, (j + 1) * MINIMAP_SCALE, (i + 1) * MINIMAP_SCALE,
                                  al_map_rgb(255,0,100));
                break;
            default:
                al_draw_filled_rectangle(j * MINIMAP_SCALE, i * MINIMAP_SCALE, (j + 1) * MINIMAP_SCALE, (i + 1) * MINIMAP_SCALE,
                                  al_map_rgb(100,200,10));
                break;
            }
        }
    }
    al_draw_filled_rectangle(player.x * MINIMAP_SCALE, player.y * MINIMAP_SCALE, (player.x + 1) * MINIMAP_SCALE,
                             (player.y + 1) * MINIMAP_SCALE, al_map_rgb(255,242,0));

    al_set_target_bitmap(al_get_backbuffer(display));
}


