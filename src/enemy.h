#include <iostream>
#include <Windows.h>

#ifndef MAP_H
#define MAP_H

#include "map.h"

#endif


class Enemy {
protected:
    int e_hp;           // -1 이면 무적
    int e_width, e_height;
    int e_posX, e_posY; //맵 상의 위치
    
    int e_contactDamage;

    bool isActive;

    int tick = 0;
public:
    Enemy();
    bool CheckCrash(int b_X, int b_Y);
    void GetDamage();
    void setXY(int x, int y);
    int getX();
    int getY();
    bool getIsActive();
    bool outOfScreen(int screenOffset);

    virtual void Update(int r_posX, int r_posY, int screenOffset) = 0;
    virtual void Render(Map* map) = 0;
};

class Gremlin : public Enemy{
private: 

public: 
    bool previousState;

    Gremlin();
    void Init(int e_posX, int e_posY);
    void Update(int r_posX, int r_posY, int screenOffset) override; 
    void Render(Map* map) override; 
    void setTicks(int t);
};

class AirTikki : public Enemy{
private: 
    int e_attackDamage;

    static const int maxGremlin = 3;
    Gremlin* gremlins[maxGremlin];
    //int gremlinCount;           //현재 활성화 되어있는 Gremlin의 수
    //int totalGremlins;          //현재까지 나온 Gremlin의 수
    //int currentGremlin;         //gremlins index

    bool isHornActivate;
public: 
    int gremlinCount;           //현재 활성화 되어있는 Gremlin의 수
    int totalGremlins;          //현재까지 나온 Gremlin의 수
    int currentGremlin;         //gremlins index

    AirTikki(int x, int y);
    void Update(int r_posX, int r_posY, int screenOffset) override; 
    void ActivateHorns();
    void ActivateGremlins(int r_posX, int r_posY, int screenOffset);
    void Render(Map* map) override; 
};
/*
class Pipi : public Enemy{
private: 
    int e_attackDamage;
public: 
    Pipi(int x, int y);
    void Update(int r_posX, int r_posY);
    void Render(Map* map);
};

class LightningLord : public Enemy{
private: 
    int e_attackDamage;
public: 
    LightningLord(int x, int y);
    void Update(int r_posX, int r_posY);
    void Render(Map* map);
};

class Scworm : public Enemy{
private: 
    int e_attackDamage;
public: 
    Scworm(int x, int y);
    void Update(int r_posX, int r_posY);
    void Render(Map* map);
};

class FanFriend : public Enemy{
private:

public:
    FanFriend(int x, int y);
    void Update(int r_posX, int r_posY);
    void Render(Map* map);
};

class Airman : public Enemy{
private: 
    int e_attackDamage;
    bool isInvincible;
public: 
    Airman(int x, int y);
    void Update(int r_posX, int r_posY);
    void Render(Map* map);
};
*/