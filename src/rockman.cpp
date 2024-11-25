#include "rockman.h"

void Rockman::R_Init(){
    xPos = 15;
    yPos = 6;

    previousXpos = xPos;

    xVel = 0, yVel = 0;

    for(int i = 0; i < maxBullet; i++){
        r_bullet[i] = new Bullet();
    }

    onGround = true;
    facingRight = true;
    isInvincible = false;
}

void Rockman::R_Update(Controls* control, Map* map){
    
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
    
    xPos += xVel;

    if(xVel != 0 && XCollision(map, control)){ // 충돌 시 xVel = 0 설정
        xVel = 0;
    }

    if(control->jumpPressed && onGround){
        yVel -= jumpforce;
    }else if (yVel < yMaxVel){
        yVel = std::min<float>(yVel + gravity, yMaxVel);
    }

    if(!control->jumpPressed && yVel < 0){
        yVel = 0;
    }

    yPos += yVel;

    if(yVel > 0) {
        onGround = YCollision(map, control);
        if(onGround) {
            yVel = 0;
        }
    }else if (yVel < 0) {
        if(YCollision(map, control)){
            yVel = 0;
        }
        onGround = false;
    }

    if(control->actionPressed && facingRight){
        
    }
    else if(control->actionPressed && !facingRight){
        
    }
}

bool Rockman::XCollision(Map* map, Controls* control){
    if (!map || !control) { return false;} // 유효하지 않으면 충돌로 간주하지 않음 
    
    if(map->In_testroom){
        if(  control->leftDown 
        && ((map->test_room[yPos][xPos - 1] == 1)
        ||   xPos - 1 <= 0)){
            std::cout << "Left Wall Collision Detected\n";
            return true;
        }
        else if(control->rightDown 
            &&((map->test_room[yPos][xPos + 2] == 1)
            ||  (xPos + 2) >= (map->ScreenWidth * map->test_room_numberofScreen))){
            std::cout << "Right Wall Collision Detected\n";
            return true;
        }
    }
    
    return false;
}

bool Rockman::YCollision(Map* map, Controls* control){
    if(map->In_testroom){
        if((map->test_room[yPos + 1][xPos] == 1) || map->test_room[yPos + 1][xPos + 1] == 1){
            return true;
        }else if((map->test_room[yPos - 2][xPos] == 1) || map->test_room[yPos - 2][xPos + 1] == 1){
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
