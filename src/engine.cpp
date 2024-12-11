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
        airTikki_1.Update(map, rockman->getXPos(), rockman->getYPos(), map->screenOffsetX);
        pipi_1.Update(map, rockman->getXPos(), rockman->getYPos(), map->screenOffsetX);
        //lightningLord_1.Update(map, rockman->getXPos(), rockman->getYPos(), map->screenOffsetX);
        scworm_1.Update(map, rockman->getXPos(), rockman->getYPos(), map->screenOffsetX);
        fanfriend_1.Update(map, rockman->getXPos(), rockman->getYPos(), map->screenOffsetX);

        updateScreenOffset(map, rockman->getXPos());
        renderTestRoom(map);

        renderRockman(rockman, map);
        renderEnemies();
        renderProjectiles(rockman);

        //gotoxy(15, 18);
        //printf("gremlinCount: %d, totalGremlins: %d, currentGremlin: %d", enemy.gremlinCount, enemy.totalGremlins, enemy.currentGremlin);
        //printf("currentBullet: %d, bulletCount: %d", rockman->currentBullet, rockman->bulletCount);
        //printf("xVel: %f, yVel: %f", rockman->getXVel(), rockman->getYVel());
        //printf("bullet holding: %s, bullet activation: %s", pipi_1.getEgg()->holding? "true":"false", pipi_1.getEgg()->b_isActive? "true":"false");
        
        //end = clock();
        //std::cout << "FPS: " << Frames << " : " << end - start << "ms" ;
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
    //system("mode con: cols=32 lines=16");

    FPS = 24.0;
    
    buttons = new Controls;
    rockman = new Rockman();
    //enemies[0] = std::make_unique<AirTikki>(34, 4); //, Pipi(22, 1)};
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
                    case 1: printf("░"); break;
                    case 2: printf("/"); break;
                    case 3: printf("\\"); break;
                }
            }
        }
    }
}

void Engine::updateScreenOffset(Map* map, int xPos) {                   //맵의 어떤 부분을 그려야하는지 정해주는 함수 
    int dx = xPos - rockman->previousXpos;                              //스크린오프셋의 값에서부터 화면을 그리기 시작함
    int mapWidth = map->ScreenWidth * map->test_room_numberofScreen;

    if (xPos < map->ScreenWidth / 2) {                                  //록맨의 맵 상 좌표가 화면 넓이의 절반이면 0
        map->screenOffsetX = 0;
    } else if (xPos > mapWidth - map->ScreenWidth / 2) {                //록맨의 맵 상 좌표가 맵의 넓이 - 화면 넓이의 절반이면 맵의 넓이 - 화면 넓이
        map->screenOffsetX = mapWidth - map->ScreenWidth;
    } else {                                                            //위의 두 가지 값의 사이라면 이전 틱과 현재 틱을 비교해 움직인 정도에 따라 값을 조정
        map->screenOffsetX += dx;
    }

    rockman->previousXpos = xPos;
}


void Engine::renderRockman(Rockman* rockman, Map* map) {                
    int mapWidth = map->ScreenWidth * map->test_room_numberofScreen;       //방마다 바뀌어야 함
    int renderX = rockman->getXPos() - map->screenOffsetX;
    
    gotoxy(renderX, rockman->getYPos());
    if (rockman->getfacingRight()) {
        printf("[\\");
    } else {
        printf("/]");
    }
} 


void Engine::renderProjectiles(Rockman* rockman){                   //현재는 록맨의 투사체만 그림, 적 투사체를 그리는 것도 추가
    for(int i = 0; i < rockman->maxBullet; i++){
        if(rockman->r_bullet[i]->f_isActive()){
            gotoxy(rockman->r_bullet[i]->getPosX(), rockman->r_bullet[i]->getPosY());
            printf("o");
        }
    }

    if(pipi_1.getEgg()->f_isActive()){    //Pipi's Egg
        gotoxy(pipi_1.getEgg()->getPosX(), pipi_1.getEgg()->getPosY());
        printf("()");
    }

    /*
    if(lightningLord_1.getLightning()->f_isActive()){
        if(lightningLord_1.getLightning()->getPosY() >= 0 ){
            gotoxy(lightningLord_1.getLightning()->getPosX(), lightningLord_1.getLightning()->getPosY());
            printf("//");
        }
    }
    */
}

void Engine::renderEnemies(){                                       //테스트용. 스테이지 구현 할 때에는 수정해야함
    airTikki_1.Render(map);
    pipi_1.Render(map);
    //lightningLord_1.Render(map);
    scworm_1.Render(map);
    fanfriend_1.Render(map);
}