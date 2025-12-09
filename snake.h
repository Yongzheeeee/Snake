#pragma once
#define WIDE 60
#define HIGH 20



struct BODY
{
    int X;
    int Y;
};

struct SNAKE
{
    int size;
    struct BODY body[WIDE*HIGH];
}snake;

int food[2] = {0};   //food[0]=X,  food[1]=Y;

//初始化
int sorce = 0;
//偏移坐标
int dx = 0;
int dy = 0;
//记录蛇尾坐标
int lx = 0;
int ly = 0;
//初始化
void Initfood();
void Initsanke();
void ShowUI();
void PlayGame();
void InitWall();

