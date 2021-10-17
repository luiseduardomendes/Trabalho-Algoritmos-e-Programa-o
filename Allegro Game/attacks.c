#include "headers.h"
void throwShuriken(typeShur *shuriken, typePos enemy, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){

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
