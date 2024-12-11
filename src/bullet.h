#pragma once

#ifndef MAP_H
#define MAP_H

#include "map.h"

#endif

#include <math.h>
#include <algorithm>

class Bullet {
protected:
    int b_posX;             //화면 내의 x, y좌표
    int b_posY;

    bool direction;         //direction == true 이면 오른쪽을 향하고 false이면 왼쪽을 향한다
    bool b_isActive;
public:
    Bullet();
    void Deactivation();
    void initBullet(int x, int y, bool facing);
    bool f_isActive();
    void B_Update(Map* map, int* BulletCount);   
    bool checkCollision(Map* map);
    void setActive(bool flag);

    int getPosX();
    int getPosY();
};

class PipiBullet : public Bullet {
private:
    int b_inMapPosX;
    bool holding;
public:
    PipiBullet(int e_posX, int e_posY);
    void B_Update(Map* map, int e_posX, int e_posY);
    void setHolding(bool flag);
    bool getHolding();
    int getMapPosX();
};

class Lightning : public Bullet {
private:
    int b_inMapPosX;

    
    const float maxVel = 1.0f;
    const float gravity = 0.5f;
    
public:
    float vx, vy;
    int tick;
    Lightning();
    void Init(int posX, int posY, double speed, double angle);
    void Deactivation();
    void B_Update(Map* map);
};