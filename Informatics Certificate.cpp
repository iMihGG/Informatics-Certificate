#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <conio.h>
using namespace std;

int viteza1, viteza2;

int x1 = 20, x2 = 100, x3 = 20,x4 = 100,x5 = 40, x6= 80,x7 = 20, x8 = 100;
int x9 = 20,x10 = 100,x11 = 40,x12 = 80,x13 = 50,x14 = 130,x15 = 55,x16 = 55;

void INTRODUCERE()
{
    settextstyle(3, HORIZ_DIR, 90);
    setcolor(3);
    outtextxy(10, 100, "CHOOSE SPEED OF CARD:");
    outtextxy(10, 125, "SPEED OF CAR 1 IS:");
    cin >> viteza1;
    outtextxy(10, 150, "SPEED OF CAR 2 IS:");
    cin >> viteza2;
    cleardevice();
    settextstyle(3, HORIZ_DIR, 60);
    setcolor(3);
    outtextxy(10, 100, "RACE WILL BEGIN IN:");
    delay(1000);
    cleardevice();
    outtextxy(330, 100, "3");
    delay(1000);
    cleardevice();
    outtextxy(330, 100, "2");
    delay(1000);
    cleardevice();
    outtextxy(330, 100, "1");
    delay(1000);
    cleardevice();
    outtextxy(250, 100, "START!");
    delay(300);
    cleardevice();
}
/*introduction for the car race*/

void MASINI()
{
    while(x4 <= 400 || x10 <= 400)
    {
        line(0, 439, 640, 439);
        line(0, 350, 640, 350);
        line(0, 261, 640, 261);

        circle(x1, 330, 20);
        circle(x2, 330, 20);
        rectangle(x3, 270, x4, 310);
        rectangle(x5, 240, x6, 270);
        settextstyle(3, HORIZ_DIR, 70);
        outtextxy(x16, 275, "1");
        delay(100);
        x1 = x1 + viteza1;
        x2 = x2 + viteza1;
        x3 = x3 + viteza1;
        x4 = x4 + viteza1;
        x5 = x5 + viteza1;
        x6 = x6 + viteza1;
        x16 = x16 + viteza1;

        circle(x7, 420, 20);
        circle(x8, 420, 20);
        rectangle(x9, 360, x10, 400);
        settextstyle(3, HORIZ_DIR, 70);
        outtextxy(x15, 365, "2");
        rectangle(x11, 330, x12, 360);
        delay(100);
        x7 = x7 + viteza2;
        x8 = x8 + viteza2;
        x9 = x9 + viteza2;
        x10 = x10 + viteza2;
        x11 = x11 + viteza2;
        x12 = x12 + viteza2;
        x13 = x13 + viteza2;
        x14 = x14 + viteza2;
        x15 = x15 + viteza2;
        cleardevice();
    }
}
/*moving the cars*/

int gameOver;
int width = 20;
int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
                /*printing the snake's head*/
            else if (i == fruitY && j == fruitX)
                cout << "F";
                /*printing the fruit*/
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                    /*printing the tail*/
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}
/*drawing the map for Snake*/

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
/*taking the input from the keyboard in order to move the snake*/

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    /*the coordinates of the head are stored in order to assure the
    tail moves along with head*/
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
        /*each segment follows the segment in front of it*/
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
/*logic for the head movement*/
    if (x >= width) x = 0;
    else if (x < 0) x = width - 1;
    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;
    /*the snake can go through wall*/
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
            /*if the head hits the tail the game will end*/

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
    /*if the snake eats the fruits, another fruit will randomly
    spawn on the map and the tail will increase its size, along with
    the score*/
}

void CASA ()
{
    line(0, 375, 640, 375);
    line(170, 180, 450, 180);
    line(170, 180, 170, 375);
    line(450, 180, 450, 375);
}
/*drawing the house*/

void ACOPERIS ()
{
    line(170, 180, 310, 50);
    line(450, 180, 310, 50);
}
/*drawing the roof*/

void SOARE ()
{
    circle(1, 1, 100);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(1, 1, WHITE);
    setcolor(14);
    line(1, 1, 20, 150);
    line(1, 1, 100, 120);
    line(1, 1, 170,60);
    setcolor(15);

}
/*drawing the sun*/

int main()
{
    int a, b;
    int gd = DETECT,gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    /*initializing the graphic window*/
    settextstyle(3, HORIZ_DIR, 200);
    outtextxy(10, 200, "HELLO! TODAY, I WILL SHOW YOU HOW TO DRAW!");
    delay(4000);
    outtextxy(10, 150, "PRESS 1 IF YOU WANT TO SEE A LANDSCAPE");
    delay(3000);
    cleardevice();
    cin >> a;
    if(a == 1)
    {
        delay(3000);
        CASA();
        delay(1500);
        ACOPERIS();
        delay(1500);
        SOARE();
        getch();
        cleardevice();
    }
    cleardevice();

    cout << "PRESS 2 FOR THE CAR RACE OR 3 TO PLAY SNAKE"<<endl;
    cin >> b;
    if(b == 2)
    {
        INTRODUCERE();
        MASINI();
        if(viteza1 == viteza2)
        {
            settextstyle(3, HORIZ_DIR ,90);
            outtextxy(10, 200, "RACE FINISHED!IT'S A DRAW");
        }
        else if(viteza1 > viteza2)
        {
            settextstyle(3, HORIZ_DIR, 90);
            outtextxy(10, 200, "RACE FINISHED!FIRST CAR WON!");
        }
        else
        {
            settextstyle(3, HORIZ_DIR, 90);
            outtextxy(10, 200, "RACE FINISHED!SECOND CAR WON!");
        }
        getch();
        closegraph();
    }
    else if(b == 3)
    {
        Setup();
        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            Sleep(50);
        }
    }

    if(b == 2)
    {
        cout << "LET'S TRY TO PLAY SNAKE, TOO!" << endl;
        delay(3000);
        Setup();
        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            Sleep(25);
        }
    }
    else
    {
        cout << "LET'S TAKE A LOOK AT A CAR RACE!" << endl;
        delay(3000);
        INTRODUCERE();
        MASINI();
        if(viteza1 == viteza2)
        {
            settextstyle(3, HORIZ_DIR ,90);
            outtextxy(10, 200, "RACE FINISHED!IT'S A DRAW");
        }
        else if(viteza1 > viteza2)
        {
            settextstyle(3, HORIZ_DIR, 90);
            outtextxy(10, 200, "RACE FINISHED!FIRST CAR WON!");
        }
        else
        {
            settextstyle(3, HORIZ_DIR, 90);
            outtextxy(10, 200, "RACE FINISHED!SECOND CAR WON!");
        }
        getch();
        getch();
        closegraph();
    }


    return 0;
}
