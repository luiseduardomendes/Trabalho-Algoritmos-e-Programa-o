void throwShuriken(typeShur *shuriken, typePos enemy, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
    int throwing = 1;
    
    switch (shuriken->direction) {
        case TOUP: shuriken->y --;
            break;
        case TOLEFT: shuriken->x --;
            break;
        case TORIGHT: shuriken->x ++;
            break;
        case TODOWN: shuriken->y ++;
            break;
    }
    if (shuriken->x == enemy.x && shuriken->y == enemy.y)
        shuriken->throwing = 0;
    if (shuriken->x > 50 || shuriken->x < 0 || shuriken->y > 50 || shuriken->y < 0)
        shuriken->throwing = 0;
    if (mapMatrix[shuriken->y][shuriken->x] == WALL)
        shuriken->throwing = 0; 
}