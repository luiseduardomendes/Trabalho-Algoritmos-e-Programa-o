#include <stdio.h>
FILE *map;
#include "moveMob.c"
#include "maps.c"



int main() {
    printf("Hello world!\n");
    typePos playerPos;
    showDisplay(0, playerPos);
    return 0;
}