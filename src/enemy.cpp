
#include "enemy.h"

void gotoxy(int x, int y);

Enemy::Enemy(){

}

/*
bool Enemy::CheckCrash(int b_X, int b_Y){

}

void Enemy::GetDamage(){

}
*/

void Enemy::setXY(int x, int y){
    e_posX = x;
    e_posY = y;
}

bool Enemy::getIsActive(){
    return isActive;
}

bool Enemy::outOfScreen(int screenOffset){
    int e_posX_inScreen = e_posX - screenOffset;
    if(e_posX_inScreen + e_width - 1 <= -1 || e_posX_inScreen >= 32){
        return true;
    }

    return false;
}

int Enemy::getX(){
    return e_posX;
}
int Enemy::getY(){
    return e_posY;
}

//==========================SubClasses==========================

//----------------------------Gremlin---------------------------
Gremlin::Gremlin(){
    e_hp = 1;           
    e_width = 2, e_height = 1;  //타일 크기로 1x1
    e_posX = 0, e_posY = 0; //맵 상의 위치
    
    e_contactDamage = 2;

    isActive = false;
}

void Gremlin::Init(int e_posX, int e_posY){
    this->e_posX = e_posX;
    this->e_posY = e_posY;

    isActive = true;
}

void Gremlin::Update(int r_posX, int r_posY, int screenOffset){
    if(isActive){
        static int startTick = tick;
        if(tick > startTick + 4){
            if(tick % 5 == 0){
                if(e_posY > r_posY){
                    e_posY--;
                }else if(e_posY < r_posY){
                    e_posY++;
                }else{
                    if(e_posX > r_posX){
                        e_posX--;
                    }else if(e_posX < r_posX){
                        e_posX++;
                    }
                }
            }
        }
        
        gotoxy(15, 22);
        if(outOfScreen(screenOffset)){
            isActive = false;
        }
    }
}

void Gremlin::Render(Map* map){
    if(isActive){
        int renderX = e_posX - map->screenOffsetX;
        gotoxy(renderX, e_posY);
        printf("#");
    }
}

void Gremlin::setTicks(int t){
    tick = t;
}

//---------------------------AirTikki---------------------------
AirTikki::AirTikki(int x, int y){           //rockman이 발판 범위 안에 있으면 Gremlin을 양옆으로 번갈아가며 뱉음 (최대 3마리)
    e_hp = -1;           // -1 이면 무적
    e_width = 10, e_height = 5;  //타일 크기로 5x5
    e_posX = x, e_posY = y; //맵 상의 위치
    
    e_contactDamage = 0;
    e_attackDamage = 2;

    gremlinCount = 0;
    totalGremlins = 0;
    currentGremlin = 0;

    for(int i = 0; i < 3; i++){
        gremlins[i] = new Gremlin();
    }

    isActive = false;
}

void AirTikki::Update(int r_posX, int r_posY, int screenOffset){
    if(e_posX - r_posX == 5){
        isActive = true;
    }
    
    if(isActive){
        if(r_posX >= e_posX && r_posX <= e_posX + e_width){
            ActivateGremlins(r_posX, r_posY, screenOffset);
        }
        ActivateHorns();
    }
    tick++;

    int count = 0;
    for(int i = 0; i < maxGremlin; i++){
        gremlins[i]->Update(r_posX, r_posY, screenOffset);
        gremlins[i]->setTicks(tick);

        if(gremlins[i]->getIsActive()){
            count++;
        }
    }
    gremlinCount = count;
    

    if(outOfScreen(screenOffset)){
        isActive = false;
    }
}

void AirTikki::ActivateHorns(){
    static int startTick = tick;
    if(startTick + 20 == tick){
        if(isHornActivate == false){
            isHornActivate = true;
        }else if(isHornActivate == true){
            isHornActivate = false;
        }
        startTick = tick;
    }
}

void AirTikki::ActivateGremlins(int r_posX, int r_posY, int screenOffset){
    static int startTick = tick;
    if(startTick + 15 == tick){
        if(gremlinCount < maxGremlin){              
            if(totalGremlins % 2 == 0){                         //번갈아
                gremlins[currentGremlin]->Init(e_posX - 1, e_posY + 2);
            }else{
                gremlins[currentGremlin]->Init(e_posX + e_width, e_posY + 2);
            }
            
            currentGremlin++;
            totalGremlins++;
        }
        startTick = tick;
    }

    if(currentGremlin > maxGremlin - 1){
        currentGremlin = 0;
    }
    /*
    for(int i = 0; i < maxGremlin; i++){
        gremlins[i]->Update(r_posX, r_posY, screenOffset);
        gotoxy(15, 19 + i);
        printf("[%d] g_ePosX: %d, g_ePosY: %d", i, gremlins[i]->getX(), gremlins[i]->getY());
    }*/
}

void AirTikki::Render(Map* map){
    if(isActive){
        for(int i = 0; i < e_width; i++){
            map->test_room[e_posY][e_posX + i] = 1;
        }
        for(int k = 0; k < e_height; k++){
            map->test_room[e_posY + k][e_posX] = 1;
            map->test_room[e_posY + k][e_posX + e_width - 1] = 1;
        }

        if(isHornActivate){
            map->test_room[e_posY - 1][e_posX] = 2;                 //왼쪽 뿔
            map->test_room[e_posY - 1][e_posX + 1] = 3;

            map->test_room[e_posY - 1][e_posX + e_width - 2] = 2;                 //오른쪽 뿔
            map->test_room[e_posY - 1][e_posX + e_width - 2 + 1] = 3;
        }else{
            map->test_room[e_posY - 1][e_posX] = 0;                 //왼쪽 뿔
            map->test_room[e_posY - 1][e_posX + 1] = 0;

            map->test_room[e_posY - 1][e_posX + e_width - 2] = 0;                 //오른쪽 뿔
            map->test_room[e_posY - 1][e_posX + e_width - 2 + 1] = 0;
        }
    }

    for(int i = 0; i < maxGremlin; i++){
        gremlins[i]->Render(map);
    }
}



/*
//-----------------------------Pipi-----------------------------
Pipi::Pipi(int x, int y){
    e_hp = 1;           
    e_width = 2, e_height = 1;  //타일 크기로 1x1
    e_posX = x, e_posY = y; //맵 상의 위치
    
    e_contactDamage = 4;
    e_attackDamage = 4;

    isActive = true;
}

//-------------------------LightningLord------------------------
LightningLord::LightningLord(int x, int y){
    e_hp = 2;           
    e_width = 4, e_height = 3;  //타일 크기로 2x3
    e_posX = x, e_posY = y; //맵 상의 위치
    
    e_contactDamage = 4;
    e_attackDamage = 2;

    isActive = true;
}

//----------------------------Scworm----------------------------
Scworm::Scworm(int x, int y){
    e_hp = 3;           
    e_width = 2, e_height = 1;  //타일 크기로 1x1
    e_posX = x, e_posY = y; //맵 상의 위치
    
    e_contactDamage = 2;
    e_attackDamage = 2;

    isActive = true;
}

//--------------------------FanFriend---------------------------
FanFriend::FanFriend(int x, int y){
    e_hp = 3;           
    e_width = 4, e_height = 2;  //타일 크기로 2x2
    e_posX = x, e_posY = y; //맵 상의 위치
    
    e_contactDamage = 6;

    isActive = true;
}

//----------------------------AirMan----------------------------
Airman::Airman(int x, int y){
    e_hp = 28;           
    e_width = 2, e_height = 1;  //타일 크기로 1x1
    e_posX = x, e_posY = y; //맵 상의 위치
    
    e_contactDamage = 8;
    e_attackDamage = 4;

    isActive = true;
    isInvincible = false;
}
*/
void gotoxy(int x, int y)
{
    HANDLE COUT = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(COUT, Pos);
}
