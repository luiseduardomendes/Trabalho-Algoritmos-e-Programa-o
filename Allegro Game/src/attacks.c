#include "headers.h"
void updateShurikenPos(typeShur *shuriken, t_player *player, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){

    if(shuriken->throwing){
        shuriken->x += shuriken->movex;
        shuriken->y += shuriken->movey;
        if (shuriken->x == player->x && shuriken->y == player->y && player->invulnerable == 0){
            player->hp --;
            player->invulnerable = 5;
            shuriken->throwing = false;
        }
        if (shuriken->x > SIZEMAP_X || shuriken->x < 0 || shuriken->y > SIZEMAP_Y || shuriken->y < 0)
            shuriken->throwing = false;
        if (mapMatrix[shuriken->y][shuriken->x] == WALL)
            shuriken->throwing = false;
    }
}

void updateShurikenPlayer(typeShur *shuriken, t_npc npc[], int numMobs, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
    int i;

    if(shuriken->throwing){
        shuriken->x += shuriken->movex;
        shuriken->y += shuriken->movey;
        for (i = 0; i < numMobs; i ++){
            if ((shuriken->x == npc[i].x) && (shuriken->y == npc[i].y)){
                npc[i].hp --;
                if (npc[i].hp <= 0){
                    npc[i].x = -1;
                    npc[i].y = -1;
                }
                shuriken->throwing = false;
            }
        }

        if (shuriken->x > SIZEMAP_X || shuriken->x < 0 || shuriken->y > SIZEMAP_Y || shuriken->y < 0)
            shuriken->throwing = false;
        if (mapMatrix[shuriken->y][shuriken->x] == WALL)
            shuriken->throwing = false;
    }
}

void shurikenDir(t_npc *npc, t_player playerPos, ALLEGRO_SAMPLE* throwShur)
{
    al_init_acodec_addon();
    al_install_audio();
    if (!npc->shuriken.throwing){
        npc->shuriken.x = npc->x;
        npc->shuriken.y = npc->y;
        if(playerPos.y == npc->y)
        {
            if(abs(playerPos.x - npc->x) <= 10)
            {
                al_play_sample(throwShur, 0.5, 0.0, 0.75, ALLEGRO_PLAYMODE_ONCE, 0);
                if(playerPos.x > npc->x)
                {
                    npc->shuriken.movex = 1;//Move right
                    npc->shuriken.movey = 0;
                }
                else
                {
                    npc->shuriken.movex = -1;//Move left
                    npc->shuriken.movey = 0;
                }
                npc->shuriken.throwing = true;
            }
        }
        else if(playerPos.x == npc->x)
        {
            if(abs(playerPos.y - npc->y) <= 10)
            {
                al_play_sample(throwShur, 0.5, 0.0, 0.75, ALLEGRO_PLAYMODE_ONCE, 0);
                if(playerPos.y > npc->y)
                {
                    npc->shuriken.movex = 0;//Move down
                    npc->shuriken.movey = 1;
                }
                else
                {
                    npc->shuriken.movex = 0;//Move up
                    npc->shuriken.movey = -1;
                }
                npc->shuriken.throwing = true;
            }
        }
    }
}
