#include <stdlib.h>
#include <stdio.h>
#define SIZEMAP_X 60
#define SIZEMAP_Y 23

FILE *map;

void showDisplay (int mapUsed, typePos playerPos){
    int i, j;
    char mapMatrix[SIZEMAP_Y][SIZEMAP_X];
    map = fopen("arquivos/maps.bin", "rb");
    if (map != NULL)
        printf("Arquivo aberto com sucesso!\n");
    else
        printf("Erro na abertura do arquivo!\n");

    rewind(map);
    fseek(map, mapUsed * SIZEMAP_X * SIZEMAP_Y * sizeof(char), SEEK_SET);
    fread(mapMatrix, sizeof(char), SIZEMAP_X * SIZEMAP_Y, map);
    // não é necessário abrir o arquivo todas as vezes
    // implementar a abertura do arquivo a cada nova fase

    for (i = 0; i < SIZEMAP_Y ; i ++)  {

        for (j = 0; j < SIZEMAP_X; j ++) {
            printf("%c", mapMatrix[i][j]);
        }
        printf("\n");
    }
}