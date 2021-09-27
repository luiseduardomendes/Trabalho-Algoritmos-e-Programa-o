#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct position{
    int x, y;
};

// Procedure to control the movement of the enemies
void npcMovement(struct position npcPos, struct position playerPos, bool silentMove) {
    int flagMov, rangeViewMob, rangeViewMobLower;
    struct position mobPos;

    srand(time(NULL));

    
    if (silentMove){
        if (fabs(playerPos.x - mobPos.x) < rangeViewMobLower && 
                    fabs(playerPos.y - mobPos.y) < rangeViewMobLower){
            if (playerPos.x > mobPos.x){
                mobPos.x ++;    
            }
            else {
                mobPos.x --;        
            }
            if (playerPos.y > mobPos.y){
                mobPos.y ++;        
            }    
            else {
                mobPos.y --;        
            }
        }
        else{
            flagMov = 1 + ((float) rand() / RAND_MAX) * 3;
            switch (flagMov) {
                case 1:
                    mobPos.x ++;            
                    break;
                case 2:
                    mobPos.y ++;            
                    break;
                case 3:
                    mobPos.x --;            
                    break;
                case 4:
                    mobPos.y --;            
                    break;
            }
        }
    }  
    else {
        if (fabs(playerPos.x - mobPos.x) < rangeViewMob && 
                    fabs(playerPos.y - mobPos.y) < rangeViewMob){
            if (playerPos.x > mobPos.x){
                mobPos.x ++;    
            }
            else {
                mobPos.x --;        
            }
            if (playerPos.y > mobPos.y){
                mobPos.y ++;        
            }    
            else {
                mobPos.y --;        
            }
        }
        else{
            flagMov = 1 + ((float) rand() / RAND_MAX) * 3;
            switch (flagMov) {
                case 1:
                    mobPos.x ++;            
                    break;
                case 2:
                    mobPos.y ++;            
                    break;
                case 3:
                    mobPos.x --;            
                    break;
                case 4:
                    mobPos.y --;            
                    break;
            }
        }
    }
}