#include <time.h>
#include <iostream>
#include <Windows.h>
#include "rockman.h"

class Engine
{
    private:
        Controls* buttons;
        Rockman* rockman;
        Map* map;
       
        HANDLE CIN = 0;
        HANDLE COUT = 0;

        bool Key_input();
    public:
        double FPS;// = 30.0;

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
};