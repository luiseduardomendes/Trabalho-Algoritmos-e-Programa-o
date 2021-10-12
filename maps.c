
void showDisplay (int mapUsed, typePos playerPos, typePos infMob[], typeShur shuriken[], char mapMatrix[SIZEMAP_Y][SIZEMAP_X]){
    int i, j, k, mobFound = 0;
    
    // não é necessário abrir o arquivo todas as vezes
    // implementar a abertura do arquivo a cada nova fase

    for(i = 0; i < SIZEMAP_Y; i++){
        for(j = 0; j < SIZEMAP_X; j++){
            mobFound = 0;
            for(k = 0; k < NUM_MOBS; k++){
                if((infMob[k].x == j) && (infMob[k].y == i)){
                    printf("M");
                    mobFound = 1;
                }
            }
            if(mobFound == 0){
                printf("%c", mapMatrix[i][j]);;
            }
        }
        printf("\n");
    }
}
