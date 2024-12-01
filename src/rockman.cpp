#include "rockman.h"

Rockman::~Rockman() { 
    for (int i = 0; i < maxBullet; ++i) { 
        delete r_bullet[i]; 
    } 
        //delete[] r_bullet; 
    }

void Rockman::R_Init(){
    xPos = 15;
    yPos = 6;

    previousXpos = xPos;

    xVel = 0, yVel = 0;

    for(int i = 0; i < maxBullet; i++){
        r_bullet[i] = new Bullet();
    }

    int currnetBullet = 0;              
    int bulletCount = 0;
    int bulletDelayCount = 0;

    onGround = true;
    facingRight = true;
    isInvincible = false;
}

void Rockman::R_Update(Controls* control, Map* map){
    int screenXpos = calcScreenXpos(map);
    if(control->actionPressed && bulletDelayCount == 0){                
        if(bulletCount < maxBullet){
            if(facingRight){
                r_bullet[currentBullet++]->initBullet(screenXpos+2, yPos, facingRight);
            }else{
                r_bullet[currentBullet++]->initBullet(screenXpos-1, yPos, facingRight);
            }
            bulletCount++;
            bulletDelayCount = bulletDelay;
        }
        
        if(currentBullet > 2){
            currentBullet = 0;
        }
    }else{
        if(tick % 30){
            bulletCount = 0;
        }
    }
    
    for(int i = 0; i < 3; i++){
        r_bullet[i]->B_Update(map, &bulletCount, xPos);
    }

    if(bulletDelayCount > 0) bulletDelayCount--;


    if(xVel != 0 && !control->leftDown && !control->rightDown){
        if (xVel > 0){
            xVel = std::max<float>(xVel - acc, 0);
        } else {
            xVel = std::min<float>(xVel + acc, 0);
        }
    } else {
        if(control->leftDown && xVel > -xMaxVel){
            xVel = std::max<float>(xVel - acc, -xMaxVel);
            facingRight = false;
        }

        if(control->rightDown && xVel < xMaxVel) {
            xVel = std::min<float>(xVel + acc, xMaxVel);
            facingRight = true;
        }
    }
    
    if(xVel != 0 && XCollision(map, control)){ // 충돌 시 xVel = 0 설정
        xVel = 0;
    }
    
    xPos += xVel;

    if(control->jumpPressed && onGround){
        yVel -= jumpforce;
    }else if (yVel < yMaxVel){
        yVel = std::min<float>(yVel + gravity, yMaxVel);
    }

    if(!control->jumpPressed && yVel < 0){
        yVel = 0;
    }

    if(yVel > 0) {
        onGround = YCollisionDown(map);
        if(onGround) {
            yVel = 0;
        }
    }else if (yVel < 0) {
        if(YCollisionUp(map)){
            yVel = 0;
        }
        onGround = false;
    }

    yPos += yVel;

    tick++;
}

bool Rockman::XCollision(Map* map, Controls* control){
    if (!map || !control) { return false;} // 유효하지 않으면 충돌로 간주하지 않음 
    
    if(map->In_testroom){
        if(  control->leftDown 
        && ((map->test_room[yPos][xPos - 1] == 1)
        ||   xPos - 1 <= 0)){
            return true;
        }
        else if(control->rightDown 
            &&((map->test_room[yPos][xPos + 2] == 1)
            ||  (xPos + 2) >= (map->ScreenWidth * map->test_room_numberofScreen))){
            return true;
        }
    }
    
    return false;
}

bool Rockman::YCollisionUp(Map* map){
    if(map->In_testroom){
        if((map->test_room[yPos - 1][xPos] == 1) || map->test_room[yPos - 1][xPos + 1] == 1){
            return true;
        }
    }

    return false;
}
bool Rockman::YCollisionDown(Map* map){
    if(map->In_testroom){
        if((map->test_room[yPos + 1][xPos] == 1) || map->test_room[yPos + 1][xPos + 1] == 1){
            return true;
        }
    }

    return false;
}



int Rockman::getXPos(){
    return xPos;
}

int Rockman::getYPos(){
    return yPos;
}

void Rockman::setXPos(int x){
    this->xPos = x;
}

void Rockman::setYPos(int y){
    this->yPos = y;
}

float Rockman::getXVel(){
    return xVel;
}

float Rockman::getYVel(){
    return yVel;
}

bool Rockman::getfacingRight(){
    return facingRight;
}

int Rockman::calcScreenXpos(Map* map){
    int mapWidth = map->ScreenWidth * map->test_room_numberofScreen;       //방마다 바뀌어야 함
    int screenXpos = xPos - map->screenOffsetX;                            //화면에서의 x좌표

    if (xPos <= map->ScreenWidth / 2) {
        screenXpos = xPos;
    } else if(xPos >= mapWidth - map->ScreenWidth / 2){
        screenXpos = xPos - (mapWidth - map->ScreenWidth);
    }

    return screenXpos;
}
