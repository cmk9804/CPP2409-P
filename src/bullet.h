#pragma once

#ifndef MAP_H
#define MAP_H

#include "map.h"

#endif

class Bullet {
protected:
    int b_posX;
    int b_posY;

    bool direction;         //direction == true 이면 오른쪽을 향하고 false이면 왼쪽을 향한다
    bool b_isActive;
public:
    Bullet();
    void Deactivation();
    void initBullet(int x, int y, bool facing);
    bool f_isActive();
    void B_Update(Map* map, int* BulletCount, int r_xPos);   
    bool checkCollision(Map* map);

    int getPosX();
    int getPosY();
};