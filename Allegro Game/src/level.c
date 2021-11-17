#include "headers.h"

void levelUp(t_player *player){
    player->xp -= MIN_XP_UP;
    player->level ++;
    player->fullHp ++;
    player->hp ++;
}
