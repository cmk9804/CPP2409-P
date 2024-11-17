#include "engine.h"

void switchControls(int VirtualKey, bool &key);

bool Engine::Render()
{
    static int Frames = 0;
    bool Return  = true;
    while(Return){
        time_t start, end;
        start = clock();
        end = clock();
        while((double)(end - start) < (1000.0 / FPS)){
            if(!Key_input()){
                Return = false;
            }
            end = clock();
        }

        rockman->R_Update(buttons, map);

        updateScreenOffset(map, rockman->getXPos());
        renderTestRoom(map);

        renderRockman(rockman, map);

        gotoxy(15, 18);
        //printf("xPos: %d, yPos: %d, xVel: %f, yVel: %f, prevXpos: %d, screenOffset: %d", rockman->getXPos(), rockman->getYPos(), rockman->getXVel(), rockman->getYVel(), rockman->previousXpos, map->screenOffsetX);
        
        end = clock();
        std::cout << "FPS: " << Frames << " : " << end - start << "ms" ;
        Frames++;
    }

    return true;
}

bool Engine::Key_input()
{   
    switchControls('W', buttons->upDown);
    switchControls('S', buttons->downDown);
    switchControls('A', buttons->leftDown);
    switchControls('D', buttons->rightDown);

    switchControls('J', buttons->actionPressed);
    switchControls('K', buttons->jumpPressed);

    return true;
}

void Engine::E_Init()
{
    //커서 제거
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; 
    cursorInfo.bVisible = FALSE; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    CIN = GetStdHandle(STD_INPUT_HANDLE);
    COUT = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTitle(TEXT("Rockman_Airman"));

    FPS = 30.0;
    
    buttons = new Controls;
    rockman = new Rockman();
    map = new Map();

    rockman->R_Init();

    {
        buttons->upDown = false;
        buttons->downDown = false;
        buttons->leftDown = false;
        buttons->rightDown = false;

        buttons->jumpPressed = false;
        buttons->actionPressed = false;
    }
    
    system("cls");
}

void switchControls(int VirtualKey, bool &key){
    if (GetAsyncKeyState(VirtualKey) < 0 && key == false)
    {
        key = true;
    }
    if (GetAsyncKeyState(VirtualKey) == 0 && key == true)
    {
        key = false;
    }
}

void Engine::gotoxy(int x, int y)
{
  COORD Pos;
  Pos.X = x;
  Pos.Y = y;
  SetConsoleCursorPosition(COUT, Pos);
}

void Engine::renderTestRoom(Map* map) {
    for (int y = 0; y < map->ScreenHeight; ++y) {
        for (int x = 0; x < map->ScreenWidth; ++x) {
            int mapX = x + map->screenOffsetX;
            if (mapX < map->ScreenWidth * map->test_room_numberofScreen) {
                gotoxy(x, y);  // 커서 위치 설정
                switch (map->test_room[y][mapX]) {
                    case 0: printf(" "); break;
                    case 1: printf("="); break;
                }
            }
        }
    }
}

void Engine::updateScreenOffset(Map* map, int xPos) {
    int dx = xPos - rockman->previousXpos;
    int mapWidth = map->ScreenWidth * map->test_room_numberofScreen;

    if (xPos < map->ScreenWidth / 2) {
        map->screenOffsetX = 0;
    } else if (xPos > mapWidth - map->ScreenWidth / 2) {
        map->screenOffsetX = mapWidth - map->ScreenWidth;
    } else {
        map->screenOffsetX += dx;
    }

    rockman->previousXpos = xPos;
}


void Engine::renderRockman(Rockman* rockman, Map* map) {
    int mapWidth = map->ScreenWidth * map->test_room_numberofScreen;
    int renderX = rockman->getXPos() - map->screenOffsetX;

    if (rockman->getXPos() <= map->ScreenWidth / 2) {
        renderX = rockman->getXPos();
    } else if(rockman->getXPos() >= mapWidth - map->ScreenWidth / 2){
        renderX = rockman->getXPos() - (mapWidth - map->ScreenWidth);
    }

    gotoxy(renderX, rockman->getYPos());
    if (rockman->getfacingRight()) {
        printf("[\\");
    } else {
        printf("/]");
    }
}
