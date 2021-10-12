
void showDisplay (int mapUsed, typePos playerPos, typePos npcPos, typePos shuriken, char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
    int i, j;

    for (i = 0; i < SIZEMAP_Y ; i ++)  {

        for (j = 0; j < SIZEMAP_X; j ++) {
            if (playerPos.y == i && playerPos.x == j)
                printf("P");
            else if (npcPos.y == i && npcPos.x == j)
                printf("M");
            else if (shuriken.y == i && shuriken.x == j)
                printf("Z");
            else
                printf("%c", mapMatrix[i][j]);
        }
        printf("\n");
    }
}
