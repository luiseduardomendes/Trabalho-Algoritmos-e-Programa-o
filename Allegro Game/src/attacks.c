#include "headers.h"
void updateShurikenPos(typeShur *shuriken, t_player *player, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){

    if(shuriken->throwing){
        shuriken->x += shuriken->movex;
        shuriken->y += shuriken->movey;
        if (shuriken->x == player->x && shuriken->y == player->y && player->invulnerable == 0){
            player->hp --;
            player->invulnerable = TIME_INV;
            shuriken->throwing = false;
        }
        if (shuriken->x > SIZEMAP_X || shuriken->x < 0 || shuriken->y > SIZEMAP_Y || shuriken->y < 0)
            shuriken->throwing = false;
        if (mapMatrix[shuriken->y][shuriken->x] == WALL)
            shuriken->throwing = false;
    }
}

void updateShurikenPlayer(t_player *player, t_npc npc[], t_boss *boss, int numMobs, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
    int i;

    if(player->shuriken.throwing){
        player->shuriken.x += player->shuriken.movex;
        player->shuriken.y += player->shuriken.movey;
        for (i = 0; i < numMobs; i ++){
            if ((player->shuriken.x == npc[i].x) && (player->shuriken.y == npc[i].y) && npc[i].alive){
                npc[i].hp --;
                if (npc[i].hp <= 0){
                    npc[i].alive = 0;
                    player->xp += 5;
                }
                player->shuriken.throwing = false;
            }
        }

        if (player->shuriken.x > SIZEMAP_X || player->shuriken.x < 0 || player->shuriken.y > SIZEMAP_Y || player->shuriken.y < 0)
            player->shuriken.throwing = false;
        if ((player->shuriken.x == boss->x) && (player->shuriken.y == boss->y) && boss[i].alive)
            player->shuriken.throwing = false;
        if (mapMatrix[player->shuriken.y][player->shuriken.x] == WALL)
            player->shuriken.throwing = false;
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

void shurikenDirBoss(t_boss *boss, t_player playerPos, ALLEGRO_SAMPLE* throwShur)
{
    al_init_acodec_addon();
    al_install_audio();
    int i;
    int throwingBoss = 0;
    if (boss->alive){
        for (i = 0; i < 8; i ++){
            if (boss->shurikens[i].throwing)
                throwingBoss = 1;
        }
    }
    if(!throwingBoss) {
        for (i = 0; i < 8; i ++){
            boss->shurikens[i].x = boss->x;
            boss->shurikens[i].y = boss->y;
        }
        if(playerPos.y == boss->y || playerPos.x == boss->x)
        {

            al_play_sample(throwShur, 0.5, 0.0, 0.75, ALLEGRO_PLAYMODE_ONCE, 0);

            boss->shurikens[0].movex = -1;//Move down
            boss->shurikens[0].movey = 0;

            boss->shurikens[1].movex = -1;//Move up
            boss->shurikens[1].movey = 1;

            boss->shurikens[2].movex = 0;//Move down
            boss->shurikens[2].movey = 1;

            boss->shurikens[3].movex = 1;//Move up
            boss->shurikens[3].movey = 1;

            boss->shurikens[4].movex = 1;//Move down
            boss->shurikens[4].movey = 0;

            boss->shurikens[5].movex = 1;//Move up
            boss->shurikens[5].movey = -1;

            boss->shurikens[6].movex = 0;//Move down
            boss->shurikens[6].movey = -1;

            boss->shurikens[7].movex = -1;//Move up
            boss->shurikens[7].movey = -1;

            for(i = 0; i < 8; i ++){
                boss->shurikens[i].throwing = true;
            }
        }
    }
}

void updateShurikenBoss(t_boss *boss, t_player *player, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
    int i;

    for (i = 0; i < 8; i ++){
        if(boss->shurikens[i].throwing){
            boss->shurikens[i].x += boss->shurikens[i].movex;
            boss->shurikens[i].y += boss->shurikens[i].movey;
            if (boss->shurikens[i].x == player->x && boss->shurikens[i].y == player->y && player->invulnerable == 0){
                player->hp --;
                player->invulnerable = TIME_INV;
                boss->shurikens[i].throwing = false;
            }
            if (boss->shurikens[i].x > SIZEMAP_X || boss->shurikens[i].x < 0 || boss->shurikens[i].y > SIZEMAP_Y || boss->shurikens[i].y < 0)
                boss->shurikens[i].throwing = false;
            if (mapMatrix[boss->shurikens[i].y][boss->shurikens[i].x] == WALL)
                boss->shurikens[i].throwing = false;
        }
    }
}
