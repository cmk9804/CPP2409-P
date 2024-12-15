#include <cmath>
#include "bullet.h"

Bullet::Bullet() : b_posX(0), b_posY(0), b_isActive(false) {    }

void Bullet::B_Update(Map* map, int* bulletCount){      //direction == true 이면 오른쪽을 향하고 false이면 왼쪽을 향한다
    if(b_isActive){
        if(direction){
            b_posX += 1;                             
        }else{
            b_posX -= 1;
        }

        if(checkCollision(map)){ // Screen Width
            Deactivation();
            *bulletCount -= 1;
        }
    }
}

bool Bullet::checkCollision(Map* map){
    int b_posX_inMap = b_posX + map->screenOffsetX;
    if(b_posX <= -1 || b_posX >= 32){
        return true;
    }
    if(map->test_room[b_posY][b_posX_inMap] != 0){
        return true;
    }
    if(b_posY > map->ScreenHeight){
        return true;
    }
    return false;
}
void Bullet::Deactivation(){
    b_isActive = false;
}

void Bullet::initBullet(int x, int y, bool facing){
    b_posX = x;
    b_posY = y;
    direction = facing;
    b_isActive = true;
}

bool Bullet::f_isActive(){
    return b_isActive;
}

void Bullet::setActive(bool flag){
    b_isActive = flag;
}

int Bullet::getPosX(){
    return b_posX;
}
int Bullet::getPosY(){
    return b_posY;
}


//==========================SubClasses==========================

//-----------------------------Pipi-----------------------------
PipiBullet::PipiBullet(int e_posX, int e_posY){
    b_inMapPosX = e_posX;
    b_posY = e_posY + 1;
    b_isActive = false;
    holding = true;
}

void PipiBullet::B_Update(Map* map, int e_posX, int e_posY){      
    if(b_isActive && holding){
        b_inMapPosX = e_posX;
    }

    b_posX = b_inMapPosX - map->screenOffsetX;
    
    if(!holding){
        b_posY++;
    }

    if(checkCollision(map)){
        Deactivation();
    }

}

void PipiBullet::setHolding(bool flag){
    holding = flag;
}

bool PipiBullet::getHolding(){
    return holding;
}

int PipiBullet::getMapPosX(){
    return b_inMapPosX;
}

//-------------------------LightningLord------------------------

Lightning::Lightning(){
    b_posX = 0;
    b_inMapPosX = 0;
    b_posY = 0;
    vx = 0;
    vy = 0;

    b_isActive = 0;
    tick = 0;
}

void Lightning::Init(int posX, int posY, double speed, double angle) {
    b_inMapPosX = posX;
    b_posY = posY - 2;
    vx = speed * cos(angle);
    vy = speed * sin(angle);
    b_isActive = true;
    tick = 0;
}

void Lightning::B_Update(Map* map){
    if (!b_isActive) return;
    tick++;

    double newX = b_inMapPosX + vx;
    double newY = b_posY + vy - 0.5 * gravity * tick;

    int dx = (int)round(newX) - (int)b_inMapPosX;  
    int dy = (int)round(newY) - (int)b_posY; 

    if (abs(dx) > 1) dx = (dx > 0) ? 1 : -1;  
    if (abs(dy) > 1) dy = (dy > 0) ? 1 : -1;

    b_inMapPosX += dx;
    b_posY += dy;

    if (checkCollision(map)) {
        Deactivation();
    }
    /*
    b_posX = b_inMapPosX - map->screenOffsetX;
    if(b_isActive){
        tick++;

        b_inMapPosX += vx;
        b_posY += vy - 0.5 * gravity;
    }
    b_inMapPosX = b_posX + map->screenOffsetX;
    
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
*/
    if(checkCollision(map)){
        Deactivation();
    }
}

void Lightning::Deactivation() {
    b_isActive = false;
    vx = 0;
    vy = 0;
}
