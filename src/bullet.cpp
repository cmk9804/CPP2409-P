#include <Windows.h>
#include <iostream>
#include "bullet.h"

//char getCharAtPosition(int x, int y);

//Bullet::Bullet() : b_posX_inScreen(0), b_posX_inMap(0), b_posY(0), b_isActive(false) {    }
Bullet::Bullet() : b_posX(0), b_posY(0), tick(0), b_isActive(false) {    }

void Bullet::B_Update(Map* map, int* bulletCount, int r_xPos){      //direction == true 이면 오른쪽을 향하고 false이면 왼쪽을 향한다
    if(b_isActive){
        if(direction){
            //b_posX_inScreen++;
            //b_posX_inMap++;

            b_posX += 1;                             //화면상의 탄환 위치 - screenOffset 이면 맵 상의 탄환 위치?
        }else{
            //b_posX_inScreen--;
            //b_posX_inMap--;
            b_posX -= 1;
        }
        
        //int screenX = b_posX_inMap - map->screenOffsetX;
        //char ch = getCharAtPosition(screenX, b_posY);

        if(checkCollision(map)){ // Screen Width
            Deactivation();
            *bulletCount -= 1;
        }
    }
}
/*
bool Bullet::checkCollision(char ch){
    if(b_posX_inScreen <= -1 || b_posX_inScreen >= 32){
        return true;
    }
    if(ch == '='){
        return true;
    }
    return false;
}
*/
bool Bullet::checkCollision(Map* map){
    int b_posX_inMap = b_posX + map->screenOffsetX;
    if(b_posX <= -1 || b_posX >= 32){
        return true;
    }
    if(map->test_room[b_posY][b_posX_inMap] == 1){
        return true;
    }
    return false;
}
void Bullet::Deactivation(){
    b_isActive = false;
    tick = 0;
}
/*
void Bullet::initBullet(int x_inScreen, int x_inMap, int y, bool facing){
    //b_posX_inMap = x_inMap;
    //b_posX_inScreen = x_inScreen;

    b_posY = y;
    direction = facing;
    tick = 0;
    b_isActive = true;
}
*/
void Bullet::initBullet(int x_inMap, int y, bool facing){
    //b_posX_inMap = x_inMap;
    //b_posX_inScreen = x_inScreen;
    b_posX = x_inMap;
    b_posY = y;
    direction = facing;
    tick = 0;
    b_isActive = true;
}

bool Bullet::f_isActive(){
    return b_isActive;
}

int Bullet::getPosX(){
    //return b_posX_inScreen;
    return b_posX;
}
int Bullet::getPosY(){
    return b_posY;
}
/*
char getCharAtPosition(int x, int y) { 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    CHAR_INFO ci; COORD coord = {0, 0}; 
    SMALL_RECT rect = {x, y, x, y}; 
    COORD bufferSize = {1, 1}; // 콘솔 화면 버퍼에서 특정 좌표의 문자 읽기 
    if (!ReadConsoleOutput(hConsole, &ci, bufferSize, coord, &rect)) { 
        return '\0'; 
    } 
        
    return ci.Char.AsciiChar; 
}*/