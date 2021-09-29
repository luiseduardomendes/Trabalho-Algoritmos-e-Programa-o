#include <moveMob.c>
#include <stdlib.h>
#include <stdio.h>
#define SIZEMAP_X 64
#define SIZEMAP_Y 64

void showDisplay (int mapUsed, typePos playerPos){
    int i, j;
    char pixel;
    int mapMatrix[SIZEMAP_Y][SIZEMAP_X];
    
    FILE *map;
    map = fopen("maps.bin", "w");
    fread(&mapMatrix, SIZEMAP_X * SIZEMAP_Y * sizeof(int), 1, map);
    
    // não é necessário abrir o arquivo todas as vezes

    for (i = playerPos.x +10; i > playerPos.x - 10; i ++) {
        for (j = playerPos.y - 15; j < playerPos.y + 15; j ++) {
            printf("%c", mapMatrix[j][i]);
        }
        printf("\n");
    }
}