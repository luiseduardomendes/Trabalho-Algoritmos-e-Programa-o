#include "headers.h"
void throwShuriken(typeShur *shuriken, typePos enemy, char mapMatrix[SIZEMAP_Y][SIZEMAP_X], typePos npcPos[]){

    shurikenDir(npcPos);
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

void shurikenDir(typePos npcPos[])
{
    int i;

    for(i = 0; i < NUM_MOBS; i ++){
        if (!npcPos[i].shuriken.throwing) {
            npcPos[i].shuriken.x = npcPos[i].x;
            npcPos[i].shuriken.y = npcPos[i].y;
            switch (npcPos[i].direction) {
                case UP:
                    npcPos[i].shuriken.movex = 0;
                    npcPos[i].shuriken.movey = -1;
                    break;
                case DOWN:
                    npcPos[i].shuriken.movex = 0;
                    npcPos[i].shuriken.movey = 1;
                    break;
                case LEFT:
                    npcPos[i].shuriken.movex = -1;
                    npcPos[i].shuriken.movey = 0;
                    break;
                case RIGHT:
                    npcPos[i].shuriken.movex = 1;
                    npcPos[i].shuriken.movey = 0;
                    break;
                default:
                    npcPos[i].shuriken.movex = 0;
                    npcPos[i].shuriken.movey = 0;
                    break;
            }
            npcPos[i].shuriken.throwing = true;
        }
    }
}
