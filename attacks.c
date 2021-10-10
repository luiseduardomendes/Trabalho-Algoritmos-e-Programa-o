int throwShuriken(clock_t timeCurrent, clock_t timeBegin, typePos *shuriken, typePos enemy){
    int throwing = 1;
    if ((double)(timeCurrent - timeBegin) / CLOCKS_PER_SEC > 0.15){
        timeBegin = clock();
        switch (shuriken->direction) {
            case TOUP: shuriken->y ++;
                break;
            case TOLEFT: shuriken->x --;
                break;
            case TORIGHT: shuriken->y --;
                break;
            case TODOWN: shuriken->x ++;
                break;
        }
        /*if (shuriken->x == enemy.x && shuriken->y == enemy.y) {
            throwing = 0;
        }
        if (shuriken->x > 50 || shuriken->x < 0 || shuriken->y > 50 || shuriken->y < 0)
            throwing = 0;*/
    }
    timeCurrent = clock();
    return throwing;
}