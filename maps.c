
void showDisplay (int mapUsed, typePos playerPos, typePos npcPos[], typeShur shuriken[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
    int i, j, k;
    ;
    
    // não é necessário abrir o arquivo todas as vezes
    // implementar a abertura do arquivo a cada nova fase

    for (i = 0; i < SIZEMAP_Y ; i ++)  {

        for (j = 0; j < SIZEMAP_X; j ++) {
            if (playerPos.y == i && playerPos.x == j)
                printf("P");
            else if (npcPos[0].y == i && npcPos[0].x == j)
                printf("M");
            else if (npcPos[1].y == i && npcPos[1].x == j)
                printf("M");
            else if (shuriken[0].y == i && shuriken[0].x == j)
                printf("Z");
            else if (shuriken[1].y == i && shuriken[1].x == j)
                printf("Z");            
            else
                printf("%c", mapMatrix[i][j]);
        }
        printf("\n");
    }
}
