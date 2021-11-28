#include "headers.h"

void drawMobs(t_npc npcPos[], int numMobs, bitmaps bmps, t_player playerPos)
{
    int i;

    for (i = 0; i < numMobs; i++)
    {
        if(npcPos[i].alive)
        {
            switch(npcPos[i].direction){
                case UP:
                    al_draw_bitmap(bmps.enemyback, (npcPos[i].x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (npcPos[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
                    break;
                case DOWN:
                    al_draw_bitmap(bmps.enemy, (npcPos[i].x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (npcPos[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
                    break;
                case LEFT:
                    al_draw_bitmap(bmps.enemyleft, (npcPos[i].x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (npcPos[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
                    break;
                case RIGHT:
                    al_draw_bitmap(bmps.enemyright, (npcPos[i].x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (npcPos[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
                    break;
                default:
                    al_draw_bitmap(bmps.enemy, (npcPos[i].x - playerPos.x + SIZEMAP_X)/(2*MULT)*MAPSCALE*MULT, (npcPos[i].y - playerPos.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
            }
        }
    }
}

void drawMobShur(t_npc npcPos[], int numMobs, ALLEGRO_BITMAP *shurikenDraw, t_player playerPos)
{
    int i;

    for(i = 0; i < numMobs; i++)
    {
        if (npcPos[i].shuriken.throwing && npcPos[i].alive)
            al_draw_bitmap(shurikenDraw, (npcPos[i].shuriken.x - playerPos.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT,(npcPos[i].shuriken.y - playerPos.y + SIZEMAP_Y/(2*MULT))*
                           MAPSCALE*MULT, 0);
            //al_draw_filled_rectangle(npcPos[i].shuriken.x*MAPSCALE, npcPos[i].shuriken.y*MAPSCALE, (npcPos[i].shuriken.x*MAPSCALE)+MAPSCALE, (npcPos[i].shuriken.y*MAPSCALE)+MAPSCALE ,al_map_rgb(0,0,255));
    }
}

ALLEGRO_BITMAP* createBackground(bitmaps bmps, ALLEGRO_DISPLAY* display, char mapMatrix[SIZEMAP_Y][SIZEMAP_X])
{
    bmps.background = al_create_bitmap(MAPSCALE * SIZEMAP_X * MULT, MAPSCALE * SIZEMAP_Y * MULT);
    al_set_target_bitmap(bmps.background);
    int i, j, flag;

    for(i = 0; i < SIZEMAP_Y; i++){
        for(j = 0; j < SIZEMAP_X; j++){

            if(mapMatrix[i][j] == WALL){
                al_draw_bitmap(bmps.wall, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                }
            else if(mapMatrix[i][j] == 'X'){
                al_draw_bitmap(bmps.spikes, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                //al_draw_filled_rectangle(j*MAPSCALE, i*MAPSCALE, (j*MAPSCALE)+MAPSCALE, (i*MAPSCALE)+MAPSCALE ,al_map_rgb(100,50,50));
            }
            else {
                flag = rand() % 20;
                switch (flag) {
                case 8:
                    al_draw_bitmap(bmps.lightGrass, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                    break;
                case 9:
                    al_draw_bitmap(bmps.darkGrass, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                    break;
                default:
                    al_draw_bitmap(bmps.grass, j*MAPSCALE*MULT, i*MAPSCALE*MULT, 0);
                    break;
                }
            }


        }
    }
    al_set_target_bitmap(al_get_backbuffer(display));
    return bmps.background;
}

void drawNaruto(bitmaps bmps, t_player player, int width, int height){
    if (player.invulnerable){
        switch(player.direction){
            case UP:
                al_draw_tinted_bitmap(bmps.narutoback, al_map_rgba_f(0.5, 0.5, 0.5, 0.5), width/2, height/2, 0);
                break;
            case DOWN:
                al_draw_tinted_bitmap(bmps.naruto, al_map_rgba_f(0.5, 0.5, 0.5, 0.5),width/2, height/2, 0);
                break;
            case LEFT:
                al_draw_tinted_bitmap(bmps.narutoleft, al_map_rgba_f(0.5, 0.5, 0.5, 0.5),width/2, height/2, 0);
                break;
            case RIGHT:
                al_draw_tinted_bitmap(bmps.narutoright, al_map_rgba_f(0.5, 0.5, 0.5, 0.5),width/2, height/2, 0);
                break;
            default:
                al_draw_tinted_bitmap(bmps.naruto, al_map_rgba_f(0.5, 0.5, 0.5, 0.5),width/2, height/2, 0);
        }
    }
    else{
        switch(player.direction){
            case UP:
                al_draw_bitmap(bmps.narutoback, width/2, height/2, 0);
                break;
            case DOWN:
                al_draw_bitmap(bmps.naruto, width/2, height/2, 0);
                break;
            case LEFT:
                al_draw_bitmap(bmps.narutoleft, width/2, height/2, 0);
                break;
            case RIGHT:
                al_draw_bitmap(bmps.narutoright, width/2, height/2, 0);
                break;
            default:
                al_draw_bitmap(bmps.naruto, width/2, height/2, 0);
        }
    }
}

void drawInterface(bitmaps bmps, t_player player, t_boss boss, int width, int height, int mapUsed, t_fonts fonts){
    int i;
    for (i = 0; i < player.xp; i++)
    {
        if(i == 0)
            al_draw_bitmap(bmps.XPbarFullLeft, (i+1)*MAPSCALE*MULT, height - 40, 0);
        else if(i == 24)
            al_draw_bitmap(bmps.XPbarFullRight, (i+1)*MAPSCALE*MULT, height - 40, 0);
        else
            al_draw_bitmap(bmps.XPbarFullMid, (i+1)*MAPSCALE*MULT, height - 40, 0);
    }

    for (i = player.xp; i < 25; i++)
    {
        if(i == 0)
            al_draw_bitmap(bmps.XPbarEmptyLeft, (i+1)*MAPSCALE*MULT, height - 40, 0);
        else if(i == 24)
            al_draw_bitmap(bmps.XPbarEmptyRight, (i+1)*MAPSCALE*MULT, height - 40, 0);
        else
            al_draw_bitmap(bmps.XPbarEmptyMid, (i+1)*MAPSCALE*MULT, height - 40, 0);
    }

    if (mapUsed == 2){
        for (i = 0; i < boss.hp; i ++){

            if(i == 0)
                al_draw_tinted_bitmap(bmps.XPbarFullLeft, al_map_rgb(255,0,0), (i+13)*MAPSCALE*MULT, 80, 0);
            else if(i == boss.fullHp-1)
                al_draw_tinted_bitmap(bmps.XPbarFullRight, al_map_rgb(255,0,0), (i+13)*MAPSCALE*MULT, 80, 0);
            else
                al_draw_tinted_bitmap(bmps.XPbarFullMid, al_map_rgb(255,0,0), (i+13)*MAPSCALE*MULT, 80, 0);
        }
        for (i = boss.hp; i < boss.fullHp; i ++){

            if(i == 0)
                al_draw_tinted_bitmap(bmps.XPbarEmptyLeft, al_map_rgb(255,0,0), (i+13)*MAPSCALE*MULT, 80, 0);
            else if(i == boss.fullHp-1)
                al_draw_tinted_bitmap(bmps.XPbarEmptyRight, al_map_rgb(255,0,0), (i+13)*MAPSCALE*MULT, 80, 0);
            else
                al_draw_tinted_bitmap(bmps.XPbarEmptyMid, al_map_rgb(255,0,0), (i+13)*MAPSCALE*MULT, 80, 0);
        }
        al_draw_text(fonts.font36, al_map_rgb(255,50,0), width/2 - 15, 105, ALLEGRO_ALIGN_CENTER, "Orochimaru");
    }

    for (i = 0; i < player.hp; i++)
        al_draw_tinted_bitmap(bmps.heart, al_map_rgba_f(OPACITY, OPACITY, OPACITY, OPACITY), (i+1)*MAPSCALE*MULT, 0, 0);
    for (i = player.hp; i < player.fullHp; i ++)
        al_draw_tinted_bitmap(bmps.voidheart, al_map_rgba_f(OPACITY, OPACITY, OPACITY, OPACITY), (i+1)*MAPSCALE*MULT, 0, 0);
    for (i = 0; i < player.numShur; i ++)
        al_draw_tinted_bitmap(bmps.shurikenDraw, al_map_rgba_f(OPACITY, OPACITY, OPACITY, OPACITY), (i+1)*MAPSCALE*MULT, (1)*MAPSCALE*MULT, 0);
    for (i = 0; i < player.numKeys; i ++)
        al_draw_tinted_bitmap(bmps.keys, al_map_rgba_f(OPACITY, OPACITY, OPACITY, OPACITY), (i+1)*MAPSCALE*MULT, (2)*MAPSCALE*MULT, 0);

    al_draw_textf(fonts.font48, al_map_rgb(102, 187, 106), (width - 200)/2, height-70, ALLEGRO_ALIGN_CENTER, "%d", player.level);
    al_draw_tinted_bitmap(bmps.miniMap, al_map_rgba_f(0.5, 0.5, 0.5, 0.5), width - (SIZEMAP_X + 3)*MINIMAP_SCALE, height - (SIZEMAP_Y + 3)*MINIMAP_SCALE, 0);
}

void drawDialog(bitmaps bmps, int width, int height, int mapUsed, t_fonts fonts){
    al_draw_bitmap(bmps.dialogBmp, width*1.15/4, height*1/2, 0);
    switch(mapUsed){
    case 0:
        al_draw_text(fonts.font36, al_map_rgb(0,0,0), width*1.7/3, height*2.5/4, ALLEGRO_ALIGN_CENTER, "Voces nao vao se sair bem dessa");
        al_draw_text(fonts.font36, al_map_rgb(0,0,0), width*1.7/3, height*2.75/4, ALLEGRO_ALIGN_CENTER, "Voces estao enfrentando o ");
        al_draw_text(fonts.font36, al_map_rgb(0,0,0), width*1.7/3, height*3.0/4, ALLEGRO_ALIGN_CENTER, "futuro hokageda vila da folha!");
        al_draw_text(fonts.font36, al_map_rgb(0,0,0), width*1.7/3, height*3.25/4, ALLEGRO_ALIGN_CENTER, "To certo!");
        break;
    case 1:
        al_draw_text(fonts.font36, al_map_rgb(0,0,0), width*1.7/3, height*2.5/4, ALLEGRO_ALIGN_CENTER, "Voces nao desistem mesmo");
        al_draw_text(fonts.font36, al_map_rgb(0,0,0), width*1.7/3, height*2.75/4, ALLEGRO_ALIGN_CENTER, "devolvam o pergaminho da");
        al_draw_text(fonts.font36, al_map_rgb(0,0,0), width*1.7/3, height*3.0/4, ALLEGRO_ALIGN_CENTER, "vila da folha! Ou terei que");
        al_draw_text(fonts.font36, al_map_rgb(0,0,0), width*1.7/3, height*3.25/4, ALLEGRO_ALIGN_CENTER, "derrotar todos voces!");
        break;
    case 2:
        al_draw_text(fonts.font36, al_map_rgb(0,0,0), width*1.7/3, height*2.5/4, ALLEGRO_ALIGN_CENTER, "OROCHIMARU! Eu sabia que voce");
        al_draw_text(fonts.font36, al_map_rgb(0,0,0), width*1.7/3, height*2.75/4, ALLEGRO_ALIGN_CENTER, "estaria por tras de tudo isso!");
        al_draw_text(fonts.font36, al_map_rgb(0,0,0), width*1.7/3, height*3.0/4, ALLEGRO_ALIGN_CENTER, "Eu vou derrotar voce!");
        al_draw_text(fonts.font36, al_map_rgb(0,0,0), width*1.7/3, height*3.25/4, ALLEGRO_ALIGN_CENTER, "Dattebayo!");
        break;
    }




    al_draw_bitmap(bmps.narutoDialog, -70, height-433,0);
    al_flip_display();
}

void createMiniMap(char mapMatrix[][SIZEMAP_X], ALLEGRO_BITMAP** miniMap, ALLEGRO_DISPLAY *display, t_player player){
    int i, j;

    *miniMap = al_create_bitmap(MINIMAP_SCALE * SIZEMAP_X, MINIMAP_SCALE * SIZEMAP_Y);
    al_set_target_bitmap(*miniMap);

    for (i = 0; i < SIZEMAP_Y; i ++) {
        for (j = 0; j < SIZEMAP_X; j ++) {
            switch (mapMatrix[i][j]){
            case WALL:
                al_draw_filled_rectangle(j * MINIMAP_SCALE, i * MINIMAP_SCALE, (j + 1) * MINIMAP_SCALE, (i + 1) * MINIMAP_SCALE,
                                  al_map_rgb(50,50,50));
                break;
            case 'X':
                al_draw_filled_rectangle(j * MINIMAP_SCALE, i * MINIMAP_SCALE, (j + 1) * MINIMAP_SCALE, (i + 1) * MINIMAP_SCALE,
                                  al_map_rgb(255,0,100));
                break;
            default:
                al_draw_filled_rectangle(j * MINIMAP_SCALE, i * MINIMAP_SCALE, (j + 1) * MINIMAP_SCALE, (i + 1) * MINIMAP_SCALE,
                                  al_map_rgb(100,200,10));
                break;
            }
        }
    }
    al_draw_filled_rectangle(player.x * MINIMAP_SCALE, player.y * MINIMAP_SCALE, (player.x + 1) * MINIMAP_SCALE,
                             (player.y + 1) * MINIMAP_SCALE, al_map_rgb(255,242,0));

    al_set_target_bitmap(al_get_backbuffer(display));
}

void drawMainMenu(bitmaps bmps, int width, int height, int selected, t_fonts fonts){
    al_draw_filled_rounded_rectangle(width*2.5/8, height/4, width*5.5/8, height*3/4, width*0.5/16, height*1/16, al_map_rgb(255,255, 0));
    al_draw_rectangle(width*2/5, height*(selected*2+4.25)/16, width*3/5, height*(selected*2+6)/16, al_map_rgb(0,128,128), 5);
    al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*4.5/16, ALLEGRO_ALIGN_CENTER, "Novo Jogo");
    al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*6.5/16, ALLEGRO_ALIGN_CENTER, "Carregar jogo");
    al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*8.5/16, ALLEGRO_ALIGN_CENTER, "Creditos");
    al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*10.5/16, ALLEGRO_ALIGN_CENTER, "Sair");
    al_flip_display();
}

void drawInGameMenu(bitmaps bmps, int width, int height, int selected, t_fonts fonts){
    al_draw_filled_rounded_rectangle(width*2.5/8, height/4, width*5.5/8, height*3/4, width*0.5/16, height*1/16, al_map_rgb(255,255, 0));
    al_draw_rectangle(width*2/5, height*(selected*2+4.25)/16, width*3/5, height*(selected*2+6)/16, al_map_rgb(0,128,128), 5);
    al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*4.5/16, ALLEGRO_ALIGN_CENTER, "Continuar");
    al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*6.5/16, ALLEGRO_ALIGN_CENTER, "Salvar jogo");
    al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*8.5/16, ALLEGRO_ALIGN_CENTER, "Carregar jogo");
    al_draw_text(fonts.font36, al_map_rgb(0,0,0), width/2, height*10.5/16, ALLEGRO_ALIGN_CENTER, "Sair");
    al_flip_display();
}

void drawItems(typeItem items[],t_chest chests[], t_exit mapExit, t_player player, t_counting counting, t_bitmaps bmps){
    int i;
    for (i = 0; i < counting.numShur + counting.numKeys; i ++)
        if (items[i].onMap == 1)
            if (items[i].nameItems == 1)
                al_draw_bitmap(bmps.keys, (items[i].x - player.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (items[i].y - player.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
            else if (items[i].nameItems == 0)
                al_draw_bitmap(bmps.shurikenDraw, (items[i].x - player.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (items[i].y - player.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);

    for (i = 0; i < counting.numChests; i ++){
        if (chests[i].closed){
            al_draw_bitmap(bmps.chest, (chests[i].x - player.x + SIZEMAP_X/(2*MULT)) * MAPSCALE*MULT, (chests[i].y - player.y + SIZEMAP_Y/(2*MULT)) * MAPSCALE*MULT, 0);
        }
        else {
            al_draw_bitmap(bmps.openchest, (chests[i].x - player.x + SIZEMAP_X/(2*MULT)) * MAPSCALE*MULT, (chests[i].y - player.y + SIZEMAP_Y/(2*MULT)) * MAPSCALE*MULT, 0);
        }
    }
    if(mapExit.onMap == 1)
        al_draw_bitmap(bmps.trapdoor, (mapExit.x - player.x + SIZEMAP_X/(2*MULT)) * MAPSCALE*MULT, (mapExit.y - player.y + SIZEMAP_Y/(2*MULT)) * MAPSCALE*MULT, 0);

}

void drawEnemies(t_player player,t_npc npc[], t_boss boss,t_counting counting,t_bitmaps bmps){
    int i;
    if(boss.alive)
        for (i = 0; i < 8; i ++)
            if(boss.shurikens[i].throwing)
                al_draw_bitmap(bmps.shurikenDraw, (boss.shurikens[i].x - player.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (boss.shurikens[i].y - player.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);

    drawMobs(npc, counting.numMobs, bmps, player);
    drawMobShur(npc, counting.numMobs, bmps.shurikenDraw, player);
    if(boss.alive)
        al_draw_bitmap(bmps.enemyBoss, (boss.x - player.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (boss.y - player.y + SIZEMAP_Y/(2*MULT))*MAPSCALE*MULT, 0);
    if (player.shuriken.throwing)
        al_draw_bitmap(bmps.shurikenDraw, (player.shuriken.x - player.x + SIZEMAP_X/(2*MULT))*MAPSCALE*MULT, (player.shuriken.y - player.y + SIZEMAP_Y/(2*MULT))
                       *MAPSCALE*MULT, 0);

}

void drawMapElements(t_npc npc[], typeItem items[], t_chest chests[], t_exit mapExit, t_player player,t_boss boss,t_counting counting,t_bitmaps bmps, int width, int height){
    drawItems(items, chests, mapExit, player, counting, bmps);

    drawEnemies(player, npc, boss, counting, bmps);

    drawNaruto(bmps, player, width, height);
}
