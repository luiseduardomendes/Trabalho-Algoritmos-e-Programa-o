#include "headers.h"

void loadMap (char mapMatrix[SIZEMAP_Y][SIZEMAP_X], int mapUsed){

    char buffer[SIZEMAP_X+3];
    char mapFileName[99][50] = {{"arquivos/map64x36.txt"},
                                {"arquivos/mapa2.64x36.txt"}};
    int i, j;

    map = fopen(mapFileName[mapUsed], "r");
    rewind(map);
    for (i = 0; i < SIZEMAP_Y; i ++){
        fgets(buffer, SIZEMAP_X+3, map);
        for (j = 0; j < SIZEMAP_X; j ++){
            mapMatrix[i][j] = buffer[j];
        }
    }
}

