
#include "enemy.h"

void gotoxy(int x, int y);

Enemy::Enemy(){

}


bool Enemy::CheckCrash(int b_X, int b_Y, int screenOffset){
    int e_posX_inScreen = e_posX - screenOffset;
    if(b_X >= e_posX_inScreen || b_X <= e_posX_inScreen + e_width - 1){
        if(b_Y >= e_posY || b_Y <= e_posY + e_height - 1){
            return true;
        }
    }

    return false;
}

void Enemy::GetDamage(){
    e_hp--;

    if(e_hp <= 0){
        isActive == false;
    }
}


void Enemy::Update(Map* map, int r_posX, int r_posY, int screenOffset){
    gotoxy(15, 19);
    printf("Enemy's Update");
}

void Enemy::Render(Map* map){
    gotoxy(15, 20);
    printf("Enemy's Render");
}

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

void Gremlin::Update(Map* map, int r_posX, int r_posY, int screenOffset){
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
        if(outOfScreen(screenOffset)){
            isActive = false;
        }
    }
}

void Gremlin::Render(Map* map){
    if(isActive){
        int renderX = e_posX - map->screenOffsetX;
        gotoxy(renderX, e_posY);
        printf("[]");
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
    isHornActivate = false;
    isEncountered = false;
}

void AirTikki::Update(Map* map, int r_posX, int r_posY, int screenOffset){
    if(e_posX - r_posX <= 7){
        isEncountered = true;
    }

    if(!outOfScreen(screenOffset) && isEncountered){
        isActive = true;
    }else{
        isActive = false;
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
        gremlins[i]->Update(map, r_posX, r_posY, screenOffset);
        gremlins[i]->setTicks(tick);

        if(gremlins[i]->getIsActive()){
            count++;
        }
    }
    gremlinCount = count;
    
}

void AirTikki::ActivateHorns(){
    static int startTick = tick;
    if(startTick + 20 <= tick){
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
    if(startTick + 15 <= tick){
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



//-----------------------------Pipi-----------------------------
Pipi::Pipi(int x, int y){
    e_hp = 1;           
    e_width = 2, e_height = 1;  //타일 크기로 1x1
    e_posX = x, e_posY = y; //맵 상의 위치

    e_contactDamage = 4;
    e_attackDamage = 4;

    isActive = false;

    egg = new PipiBullet(x, y);
}

void Pipi::Update(Map* map, int r_posX, int r_posY, int screenOffset){
    if(!outOfScreen(screenOffset)){
        isActive = true;
        if(egg->getHolding()){      //알을 들고있을때만 알 활성화(안하면 비활성화가 안됨)
            egg->setActive(true);
        }
    }
    
    if(isActive){
        e_posX--;
        egg->B_Update(map, e_posX, e_posY);
        if(r_posX + 2 >= e_posX){
            egg->setHolding(false);
        }
    }

    if(outOfScreen(screenOffset)){
        isActive = false;
    }
}

PipiBullet* Pipi::getEgg(){
    return egg;
}

void Pipi::Render(Map* map){
    if(isActive){
        int renderX = e_posX - map->screenOffsetX;
        gotoxy(renderX, e_posY);
        printf("<}");
    }
}


//-------------------------LightningLord------------------------
LightningLord::LightningLord(int x, int y){
    e_hp = 2;           
    e_width = 4, e_height = 3;  //타일 크기로 2x3
    e_posX = x, e_posY = y; //맵 상의 위치
    
    e_contactDamage = 4;
    e_attackDamage = 2;

    radius = 4;
    angle = 0.0;
    centerpoint_x = e_posX;
    centerpoint_y = e_posY + radius;

    isActive = false;
    isAlive = true;

    lightning = new Lightning();
}

void LightningLord::Update(Map* map, int r_posX, int r_posY, int screenOffset){
    if(!outOfScreen(screenOffset)){
        isActive = true;
        tick++;
    }else{
        isActive = false;
    }
    
    if(isActive){
        angle -= 0.0261799387799167;  // 10초에 한 바퀴
        double_x = 2 * cos(angle - 3.14159265359 / 2) * radius + centerpoint_x;
        double_y = sin(angle - 3.14159265359 / 2) * radius + centerpoint_y;

        e_posX = (int)double_x;
        e_posY = (int)double_y;

        /*
        if(tick >= e_attackDelay && tick % e_attackDelay == 0){
            //throwLightning(r_posX, r_posY);
        }
        */
    }

    //lightning->B_Update(map);

    /*
    gotoxy(15, 18);
    printf("lightning x: %d, y: %d", lightning->getPosX(), lightning->getPosY());
    gotoxy(15, 19);
    printf("lightning vx: %d, vy: %d", lightning->vx, lightning->vy);
    gotoxy(15, 20);
    printf("lightningTick: %d", lightning->tick);
    */
}

void LightningLord::throwLightning(int r_posX, int r_posY){
    if(!lightning->f_isActive()){
        double dx = r_posX - e_posX;
        double dy = r_posY - e_posY;
        angle = atan2(dy, dx);
        double speed = 1.0;

        gotoxy(15, 21);
        printf("lightning dx: %f, dy: %f", dx, dy);
        gotoxy(15, 22);
        printf("lightningAngle: %f", angle);

        lightning->Init(e_posX, e_posY, speed, angle);
    }
}

Lightning* LightningLord::getLightning(){
    return lightning;
}

void LightningLord::Render(Map* map) {
    if (isActive) {
        // 현재 위치와 이전 위치를 저장
        static int prevPosX = -1, prevPosY = -1;
        static int prevTile_0, prevTile_1, prevTile_2, prevTile_3;

        if (prevPosX != -1 && prevPosY != -1) { // 초기 상태가 아닌 경우에만 복구 수행
            if (prevPosX != e_posX || prevPosY != e_posY) { // 이전 위치와 현재 위치가 다른 경우
                map->test_room[prevPosY][prevPosX + 0] = prevTile_0;
                map->test_room[prevPosY][prevPosX + 1] = prevTile_1;
                map->test_room[prevPosY][prevPosX + 2] = prevTile_2;
                map->test_room[prevPosY][prevPosX + 3] = prevTile_3;
                
                // 현재 위치의 타일 값을 저장
                prevTile_0 = map->test_room[e_posY][e_posX + 0];
                prevTile_1 = map->test_room[e_posY][e_posX + 1];
                prevTile_2 = map->test_room[e_posY][e_posX + 2];
                prevTile_3 = map->test_room[e_posY][e_posX + 3];
            }
        }
        
        prevPosX = e_posX;
        prevPosY = e_posY;

        // 현재 위치를 적의 타일로 표시
        map->test_room[e_posY][e_posX + 0] = 1;
        map->test_room[e_posY][e_posX + 1] = 1;
        map->test_room[e_posY][e_posX + 2] = 1;
        map->test_room[e_posY][e_posX + 3] = 1;

        // 적을 화면에 렌더링
        int renderX = e_posX - map->screenOffsetX;
        gotoxy(renderX, e_posY - 2);
        printf("/==\\");
        gotoxy(renderX, e_posY - 1);
        printf("[--]");
    }
}



//----------------------------Scworm----------------------------
Scworm::Scworm(int x, int y){
    e_hp = 3;           
    e_width = 2, e_height = 1;  //타일 크기로 1x1
    e_posX = x, e_posY = y; //맵 상의 위치
    
    e_contactDamage = 2;
    e_attackDamage = 2;

    isActive = false;
}

void Scworm::Update(Map* map, int r_posX, int r_posY, int screenOffset){
    isActive = !outOfScreen(screenOffset);
}

void Scworm::Render(Map* map){
    if(isActive){
        int renderX = e_posX - map->screenOffsetX;
        gotoxy(renderX, e_posY);
        printf("==");
    }
}


//--------------------------FanFriend---------------------------
FanFriend::FanFriend(int x, int y){
    e_hp = 3;           
    e_width = 4, e_height = 2;  //타일 크기로 2x2
    e_posX = x, e_posY = y; //맵 상의 위치
    
    e_contactDamage = 6;

    isActive = false;
}
void FanFriend::Update(Map* map, int r_posX, int r_posY, int screenOffset){
    isActive = !outOfScreen(screenOffset);
}

void FanFriend::Render(Map* map){
    if(isActive){
        int renderX = e_posX - map->screenOffsetX;
        gotoxy(renderX, e_posY - 1);
        printf("<]-_");
        gotoxy(renderX, e_posY);
        printf("[__\\");
    }
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



void gotoxy(int x, int y)
{
    HANDLE COUT = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(COUT, Pos);
}
