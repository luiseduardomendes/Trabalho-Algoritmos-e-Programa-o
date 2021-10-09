#include "headers.h"

int throwShuriken(clock_t timeCurrent, clock_t timeBegin, typePos shuriken, typePos enemy){
    int throwing = 1;
    if ((double)(timeCurrent - timeBegin) / CLOCKS_PER_SEC > 0.15){
        printf("%d %d\n", shuriken.x, shuriken.y);
        timeBegin = clock();
        switch (shuriken.direction) {
            case w: shuriken.y ++;
                break;
            case a: shuriken.x --;
                break;
            case s: shuriken.y --;
                break;
            case d: shuriken.x ++;
                break;
        }
        if (shuriken.x == enemy.x && shuriken.y == enemy.y) {
            throwing = 0;
        }
    }
    timeCurrent = clock();
    return throwing;
}