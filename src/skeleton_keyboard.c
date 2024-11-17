/*
#include <iostream>
#include <Windows.h>
#include <conio.h>

#define MAX_X 60
#define MAX_Y 20

void gotoxy(int x, int y)
{
  COORD Pos;
  Pos.X = x;
  Pos.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main() {
  int X = (MAX_X / 2) + 2;
  int Y = (MAX_Y / 2) + 1;

  char icon = '+';
  int keyin = 0;

  while (1) {
    gotoxy(0, MAX_Y + 1);
    printf("X: %d \n", X);
    printf("X: %d \n", Y);
    printf("Last keyin value: %d \n", keyin);

    gotoxy(X, Y);
    printf("%c", icon);
    keyin = _getch();
    printf("\b ");

    switch (keyin) {
      case 224: // arrow keys
        keyin = _getch();
        switch (keyin) {
          case 72: // up
            if (Y != 0) Y--;
            break;

          case 75: // left
            if (X != 0) X--;
            break;
          case 77: // right
            if (X != MAX_X) X++;
            break;

          case 80: // down
            if (Y != MAX_Y) Y++;
            break;
        }
        break;

      case 13: // enter
        icon = '@';
        break;
      case 32: // space
        icon = '#';
        break;
    }
  }
}
*/