#include <iostream>
#include <math.h>
#include <algorithm>
#include "map.h"
#include "controls.h"

class Rockman {
private:
    int xPos;
    int yPos;

    float xVel, yVel;
    float const acc = 0.5f;
    float const xMaxVel = 1.0f, yMaxVel = 1.0f;
    float const gravity = 0.5f;
    float const jumpforce = 1.0f;
    
    bool onGround;
    bool facingRight;
    bool isInvincible;
public:
    int previousXpos;

    void R_Init();
    void R_Update(Controls* control, Map* map);

    bool XCollision(Map* map, Controls* control);
    bool YCollision(Map* map, Controls* control);

    void setXPos(int x);
    void setYPos(int y);

    int getXPos();
    int getYPos();

    float getXVel();
    float getYVel();

    bool getfacingRight();
};