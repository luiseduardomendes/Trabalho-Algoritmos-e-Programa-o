#include "headers.h"
void updateShurikenPos(typeShur *shuriken, typePos enemy, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){

    if(shuriken->throwing){
        shuriken->x += shuriken->movex;
        shuriken->y += shuriken->movey;
        if (shuriken->x == enemy.x && shuriken->y == enemy.y)
            shuriken->throwing = false;
        if (shuriken->x > 60 || shuriken->x < 0 || shuriken->y > 23 || shuriken->y < 0)
            shuriken->throwing = false;
        if (mapMatrix[shuriken->y][shuriken->x] == WALL)
            shuriken->throwing = false;
    }
}

void shurikenDir(typePos *npc, typePos playerPos)
{
    int i;


    if (!npc->shuriken.throwing){
        npc->shuriken.x = npc->x;
        npc->shuriken.y = npc->y;
        if(playerPos.y == npc->y)
        {
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
        else if(playerPos.x == npc->x)
        {
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
