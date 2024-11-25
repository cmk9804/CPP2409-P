#include "bullet.h"

Bullet::Bullet() : b_posX(0), b_posY(0), active(false) {    }

bool Bullet::B_Update(){
    
}

void Bullet::setActive(bool flag){
    active = true;
}

void Bullet::initBullet(int x, int y, bool facing){
    b_posX = x;
    b_posY = y;

}

bool Bullet::isActive(){
    return active;
}

