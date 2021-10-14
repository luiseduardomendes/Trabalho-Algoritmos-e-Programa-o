#include "headers.h"
void throwShuriken(typeShur shuriken[], typePos enemy, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
    int i;
    for (i = 0; i < NUM_MOBS; i ++){
        if(shuriken[i].throwing){
            switch (shuriken[i].direction) {
                case TOUP: shuriken[i].y --;
                    break;
                case TOLEFT: shuriken[i].x --;
                    break;
                case TORIGHT: shuriken[i].x ++;
                    break;
                case TODOWN: shuriken[i].y ++;
                    break;
            }
            if (shuriken[i].x == enemy.x && shuriken[i].y == enemy.y)
                shuriken[i].throwing = 0;
            if (shuriken[i].x > 60 || shuriken[i].x < 0 || shuriken[i].y > 23 || shuriken[i].y < 0)
                shuriken[i].throwing = 0;
            if (mapMatrix[shuriken[i].y][shuriken[i].x] == WALL)
                shuriken[i].throwing = 0;
        }
    }
}
