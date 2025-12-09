#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "snake.h"

/*
1. 定义蛇结构体
2. 初始化蛇和食物
3. 开始游戏
    3.1蛇和墙的碰撞
    3.2蛇和自身的碰撞
    3.3蛇和食物的碰撞
        3.3.1 重新随机食物
        3.3.2 蛇的身体增长
        3.3.3 分数增长
    3.4方向键控制
4.游戏结束

*/

void Initfood()
{
    srand((size_t)time(NULL));  //随机数种子
    food[0] = rand() % WIDE;
    food[1] = rand() % HIGH;
    
}

void Initsanke()
{
    snake.size = 2;  //两节
    snake.body[0].X = WIDE/2;
    snake.body[0].Y = HIGH/2;

    snake.body[1].X = WIDE/2  - 1 ;
    snake.body[1].Y = HIGH/2;

}

void ShowUI()
{
    // //设置光标位置
    // COORD coord;
    // coord.X = food[0];
    // coord.Y = food[1];
    // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    // printf("@");
    // printf("%d  %d",food[0],food[1]);

    COORD coord;
    //更新末尾空格
    coord.X = lx;
    coord.Y = ly;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    putchar(' ');

    //显示蛇的位置
    for(int i = 0; i < snake.size; i++){
        coord.X = snake.body[i].X;
        coord.Y = snake.body[i].Y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
        if(i == 0){
            putchar('@');
        }else{
            putchar('+');
        }
    }
    
    //显示食物位置
    coord.X = food[0];
    coord.Y = food[1];
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    putchar('$');

}

void PlayGame()
{
    char key = 'D';
    //设置区域
    while (snake.body[0].X >= 0 && snake.body[0].X < WIDE && snake.body[0].Y>=0 && snake.body[0].Y < HIGH)
    {
        
        //显示界面
        ShowUI();

        //控制台输入字符
        //让程序在没输入时，仍可自己执行
        while (_kbhit())   //检查控制台是否有输入
        {
            key = _getch();  // 无显回值，存在等待操作，不输入值，程序不会向下进行
        }
        
        //方向控制移动
        switch (key)
        {
            case 'W':case 'w':dx =  0; dy = -1; break;
            case 'A':case 'a':dx = -1; dy =  0; break;
            case 'S':case 's':dx =  0; dy =  1; break;
            case 'D':case 'd':dx =  1; dy =  0; break;
        }
        
        
        
        //是否吃到自己
        for(int i = 1; i < snake.size; i++)
        {
            if (snake.body[0].X == snake.body[i].X && snake.body[0].Y == snake.body[i].Y)
            {
                return;
            }
        }

        //吃到食物
        if (snake.body[0].X == food[0] && snake.body[0].Y == food[1])
        {
            //产生新食物
            Initfood();
            //分数增加
            sorce += 10;
            //蛇身增加
            snake.size++;
            //可扩充关卡、障碍物、速度等

        }

        //蛇更新坐标
        lx = snake.body[snake.size-1].X;
        ly = snake.body[snake.size-1].Y;
        //从蛇尾开始依次复制上一个的坐标
        for(int i = snake.size - 1; i > 0; i--)
        {
            snake.body[i].X = snake.body[i-1].X;
            snake.body[i].Y = snake.body[i-1].Y;
        }
        snake.body[0].X += dx;
        snake.body[0].Y += dy;


        Sleep(200);
        //system("cls");
        
    }
    

}

void InitWall()
{
    for(int i =0; i <= HIGH; i++)
    {
        for(int j =0; j <= WIDE; j++)
        {
            if(i == HIGH)
                putchar('=');
            else if (j == WIDE)
                putchar('=');
            else
                putchar(' ');
            
        }
        putchar('\n');
    }
}

int main()
{

    //控制台光标隐藏
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = sizeof(cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);



    system("cls");
    InitWall();
    Initfood();
    Initsanke();
    ShowUI();
    PlayGame();

    //getchar();


    
    return 0;
}


