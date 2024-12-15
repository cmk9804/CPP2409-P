#include <time.h>
#include <iostream>
#include <Windows.h>
#include <array>
#include <memory>
#include "rockman.h"
#include "enemy.h"

class Engine
{
    private:
        Controls* buttons;
        Rockman* rockman;
        //std::array<std::unique_ptr<Enemy>, 1> enemies;      //테스트용. 스테이지 구현 할 때에는 수정해야함
        AirTikki airTikki_1 {34, 4};
        Pipi pipi_1 {44, 1};
        LightningLord lightningLord_1 {54, 2};
        Scworm scworm_1{59, 6};
        FanFriend fanfriend_1{54, 6};
        
        Map* map;
       
        HANDLE CIN = 0;
        HANDLE COUT = 0;

        bool Key_input();
    public:
        double FPS;

        bool Render();
        void Shutdown();
        void E_Init();
        void gotoxy(int x, int y);

        //void renderRoom1();
        //void renderRoom2();
        //void renderRoom3();
        //void renderBossRoom();

        void renderTestRoom(Map* map);
        void updateScreenOffset(Map* map, int xPos);

        void renderRockman(Rockman* rockman, Map* map);
        void renderProjectiles(Rockman* rockman);
        void renderEnemies();
};