#include "bullet.h"

Bullet::Bullet() : b_posX(0), b_posY(0), b_isActive(false) {    }

void Bullet::B_Update(Map* map, int* bulletCount, int r_xPos){      //direction == true 이면 오른쪽을 향하고 false이면 왼쪽을 향한다
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

int Bullet::getPosX(){
    return b_posX;
}
int Bullet::getPosY(){
    return b_posY;
}
