#include <bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

//Global variables
bool gameover;
const int width=60;
const int height=30;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
    gameover = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls"); //this command clears the screen
    for (int i = 0; i < width+2; i++)
    cout << "#"; //printing the top wall
    cout<<'\n';
    
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if (j==0) cout<<"#";
            
            if (i==y && j==x) cout<<"O";
            else if (i==fruitY && j==fruitX) cout<<"Q";
            else 
            {
                bool print = false;
                for (int k=0; k<nTail; k++)
                {
                    if (tailX[k]==j && tailY[k]==i)
                    {
                        cout<<"+";
                        print = true;
                    }
                }
                if (!print) cout<<" ";
            }

            if (j==width-1) cout<<"#";
        }
        cout<<'\n';
    }
    
    for (int i = 0; i < width+2; i++)
    cout << "#";
    cout<<'\n';

    cout<<"Score: "<<score;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'w': dir=UP;
            break;
            case 'a': dir=LEFT;
            break;
            case 's': dir=DOWN;
            break;
            case 'd': dir=RIGHT;
            break;
            case 'x': gameover=true;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i=1; i<nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
        case UP: y--;
        break;
        case LEFT: x--;
        break;
        case DOWN: y++;
        break;
        case RIGHT: x++;
        break;
        default: 
        break;
    }
    
    // if (x==width || y==height || x==0 || y<0) gameover=true; 

    if (x>=width) x=1;
    else if (x<=0) x=width;
    else if (y>=height) y=0;
    else if (y<0) y=height;

    for (int i=0; i<nTail; i++)
    if (tailX[i]==x && tailY[i]==y) gameover=true;

    if (x==fruitX && y==fruitY) 
    {
        fruitX = rand() % width;
        fruitY = rand() % height;
        score+=10;
        nTail++;
    }
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int main()
{
    Setup();
    while (!gameover)
    {
        hidecursor();
        Draw();
        Input();
        Logic();
        // Sleep(1);
    }

    return 0;
}