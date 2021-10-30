#include "headers.h"
void updateShurikenPos(typeShur *shuriken, typePos enemy, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){

    if(shuriken->throwing){
        shuriken->x += shuriken->movex;
        shuriken->y += shuriken->movey;
        if (shuriken->x == enemy.x && shuriken->y == enemy.y)
            shuriken->throwing = 0;
        if (shuriken->x > 60 || shuriken->x < 0 || shuriken->y > 23 || shuriken->y < 0)
            shuriken->throwing = 0;
        if (mapMatrix[shuriken->y][shuriken->x] == WALL)
            shuriken->throwing = 0;
    }
}

void shurikenDir(typeshur *npc)
{
    int i;


    if (!npc->shuriken.throwing) {
        npc->shuriken.x = npc->x;
        npc->shuriken.y = npc->y;
        switch (npc->direction) {
            case UP:
                npc->shuriken.movex = 0;
                npc->shuriken.movey = -1;
                break;
            case DOWN:
                npc->shuriken.movex = 0;
                npc->shuriken.movey = 1;
                break;
            case LEFT:
                npc->shuriken.movex = -1;
                npc->shuriken.movey = 0;
                break;
            case RIGHT:
                npc->shuriken.movex = 1;
                npc->shuriken.movey = 0;
                break;
            default:
                npc->shuriken.movex = 0;
                npc->shuriken.movey = 0;
                break;
        }
        npc->shuriken.throwing = true;

    }
}
