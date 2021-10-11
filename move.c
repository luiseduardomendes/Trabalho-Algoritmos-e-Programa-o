
// Procedure to control the movement of the enemies
typePos npcMovement(typePos mobPos, typePos playerPos, int rangeViewMob) {
    int flagMov;
    int mapUsed = 0;

    srand(time(NULL));

    flagMov = (1 + ((float)rand() / RAND_MAX) * (4 ));

    char mapMatrix[SIZEMAP_Y][SIZEMAP_X];
    map = fopen("arquivos/maps.bin", "rb");

    rewind(map);
    fseek(map, mapUsed * SIZEMAP_X * SIZEMAP_Y * sizeof(char), SEEK_SET);
    fread(mapMatrix, sizeof(char), SIZEMAP_X * SIZEMAP_Y, map);

    if (fabs(playerPos.x - mobPos.x) < rangeViewMob &&
    fabs(playerPos.y - mobPos.y) < rangeViewMob){
        if (playerPos.x > mobPos.x){
            if (verifyPosition(mobPos.x, mobPos.y, TORIGHT, mapMatrix)) {
                mobPos.x ++;
                mobPos.direction = TORIGHT;
            }
        }
        else {
            if (verifyPosition(mobPos.x, mobPos.y, TOLEFT, mapMatrix)) {
                mobPos.x --;
                mobPos.direction = TOLEFT;
            }
        }
        if (playerPos.y > mobPos.y){
            if (verifyPosition(mobPos.x, mobPos.y, TOUP, mapMatrix)) {
                mobPos.y ++;
                mobPos.direction = TOUP;
            }
        }
        else {
            if (verifyPosition(mobPos.x, mobPos.y, TODOWN, mapMatrix)) {
                mobPos.y --;
                mobPos.direction = TODOWN;
            }
        }
    }
    else{

        switch (flagMov) {
            case 1:
                if (verifyPosition(mobPos.x, mobPos.y, TORIGHT, mapMatrix))
                    mobPos.x ++;
                break;
            case 2:
                if (verifyPosition(mobPos.x, mobPos.y, TOUP, mapMatrix))
                    mobPos.y --;
                break;
            case 3:
                if (verifyPosition(mobPos.x, mobPos.y, TOLEFT, mapMatrix))
                    mobPos.x --;
                break;
            case 4:
                if (verifyPosition(mobPos.x, mobPos.y, TODOWN, mapMatrix))
                    mobPos.y ++;
                break;
        }
    }
    return mobPos;
}

bool verifyPosition(int x, int y, char direction, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]) {
    int validPosition;
    validPosition = true;

    switch (direction) {
        case TOUP:
            if ( mapMatrix[y - 1][x] == WALL )
                validPosition = false;
            break;
        case TOLEFT:
            if ( mapMatrix[y][x - 1] == WALL )
                    validPosition = false;
            break;
        case TODOWN:
            if ( mapMatrix[y + 1][x] == WALL )
                validPosition = false;
            break;
        case TORIGHT:
            if ( mapMatrix[y][x + 1] == WALL )
                validPosition = false;
            break;
    }
    return validPosition;
}

/*  code to test if movement is working
    typePos playerPos, npcPos;
    playerPos.x = 10;
    playerPos.y = 10;
    npcPos.x = 13;
    npcPos.y = 13;
    npcMovement(&npcPos, playerPos, 5);
    printf("Posição do NPC: %d, %d\n", npcPos.x, npcPos.y);
    printf("Posição do Player: %d, %d\n", playerPos.x, playerPos.y);*/