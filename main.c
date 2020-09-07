#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<strings.h>
#include<stdbool.h>
#include<windows.h>
#include<windowsx.h>
#include<math.h>
#define COLOR(X) SetConsoleTextAttribute(hConsole, X);
#define SOUND(X) PlaySound (TEXT(X),0,SND_ASYNC);
#define BLUE 9
#define GREEN 10
#define WHITE 15
#define YELLOW 14
#define MAGENTA 13
#define RED 12
#define BG_BLUE 31
#define BG_GREEN 47
#define BG_WHITE 127
#define BG_YELLOW 111
#include <conio.h>

HANDLE hConsole;

int E[50][50];
int mapSize;

struct cell {
    int x;
    int y;
    int energy;
    char name[6];
    struct cell * next;
};
typedef struct cell cell;

struct energyStation {
    int x;
    int y;
    int value;
    struct energyStation *next;
};
typedef struct energyStation ES;


#include"funcs.h"
#include"display.h"
#include"Actions.h"
#include"linkListFunctions.h"
#include"singlePlayer.h"
#include"multiPlayer.h"
#include"load.h"
#include"mapEditor.h"

#include"debugFunctions.h"

int main(){

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);     //Set Color to white
    COLOR(WHITE);
    //SetConsoleDisplayMode(hConsole,1,0);
    SOUND("sounds\\GameEntry.wav");
    //ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
    system("mode 650");

    time_t t = time(NULL);
    srand(t);
    while(1){
        system("cls");
        printf("[1] Load\n[2] New Single Player Game\n[3] New Multiplayer Game\n[4] Map Editor\n[5] Exit\n");
        fflush(stdin);
        switch(_getch()-'0'){
        case 1:
            loadMenu();
            break;
        case 2:
            singlePlayerMenu(NULL,NULL);
            break;
        case 3:
            multiPlayerMenu(NULL,NULL,NULL,1);
            break;
        case 4:
            mapEditorMenu();
            break;
        case 5:
            return 0;
            break;
        }
    }
}
