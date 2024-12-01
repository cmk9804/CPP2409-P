#pragma once

#include <iostream>
#include <math.h>
#include <algorithm>
#include "controls.h"
#include "bullet.h"

#ifndef MAP_H
#define MAP_H

#include "map.h"

#endif

class Rockman {
private:
    int xPos;
    int yPos;

    float xVel, yVel;
    float const acc = 0.5f;
    float const xMaxVel = 1.0f, yMaxVel = 1.0f;
    float const gravity = 0.5f;
    float const jumpforce = 1.0f;

    int tick = 0;
    
    bool onGround;
    bool facingRight;
    bool isInvincible;
public:
    int previousXpos;
    static int const maxBullet = 3;
    Bullet* r_bullet[maxBullet];
    int currentBullet;              //bullet 인덱스
    int bulletCount;                //현재 bullet 개수
    int bulletDelayCount;
    const int bulletDelay = 3;

    ~Rockman();

    void R_Init();
    void R_Update(Controls* control, Map* map);

    bool XCollision(Map* map, Controls* control);
    bool YCollisionUp(Map* map);
    bool YCollisionDown(Map* map);

    void setXPos(int x);
    void setYPos(int y);

    int getXPos();
    int getYPos();

    float getXVel();
    float getYVel();

    bool getfacingRight();

    int calcScreenXpos(Map* map);
};