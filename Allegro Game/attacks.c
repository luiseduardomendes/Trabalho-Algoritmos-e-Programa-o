#include "headers.h"
void updateShurikenPos(typeShur *shuriken, typePos player, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){

    if(shuriken->throwing){
        shuriken->x += shuriken->movex;
        shuriken->y += shuriken->movey;
        if (shuriken->x == player.x && shuriken->y == player.y)
            shuriken->throwing = false;
        if (shuriken->x > 60 || shuriken->x < 0 || shuriken->y > 23 || shuriken->y < 0)
            shuriken->throwing = false;
        if (mapMatrix[shuriken->y][shuriken->x] == WALL)
            shuriken->throwing = false;
    }
}

void shurikenDir(typePos *npc, typePos playerPos)
{
    if (!npc->shuriken.throwing){
        npc->shuriken.x = npc->x;
        npc->shuriken.y = npc->y;
        if(playerPos.y == npc->y)
        {
            if(abs(playerPos.x - npc->x) <= 7)
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
        }
        else if(playerPos.x == npc->x)
        {
            if(abs(playerPos.y - npc->y) <= 7)
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
}
