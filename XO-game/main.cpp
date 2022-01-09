#include <iostream>
#include <graphics.h>
#include <stdio.h>
using namespace std;

int hole[4][4] = {} , player_o = 0, player_x = 0;
int zarib = 150, win = 0, turn = 1;
int x_mabda = (1350 - 3*zarib)/2, y_mabda = (700- 3*zarib)/2;

void drow_board(void);
void drow_score_bord(void);
void game(void);
int drow_xo(int turn);
int win_check(void);
int full(void);
void show_score(void);
//void finish_game(void);

int main()
{

    initwindow(1350,700);
    setbkcolor(COLOR(0,60,120));
    cleardevice();

    //drow_board();
    drow_score_bord();
    while(!kbhit())
    {
        drow_board();
        show_score();
        //drow_score_bord();
        game();
        delay(1000);
        for(int i = 1; i <= 3; i++)
            for(int j = 1; j <= 3; j++)
                hole[i][j] = 0;
        if(win == 1) player_x++;
        else if(win == 2) player_o++;
        if(turn == 1) turn = 2;
        else turn = 1;
    }


	getch();
}

void drow_board(void)
{
//    int k = 90, n = 2;
//    for(int i=255-zarib, j=0 ; i<255-zarib/n ; i++, j++)
//    {
//        setcolor(COLOR(i-50,i-k+50,i+50));
//        line(x_mabda+3*zarib+j,y_mabda-j,x_mabda+3*zarib+j,y_mabda+3*zarib+j);
//        line(x_mabda-j,y_mabda-j,x_mabda-j,y_mabda+3*zarib+j);
//        line(x_mabda-j,y_mabda-j,x_mabda+3*zarib+j,y_mabda-j);
//        line(x_mabda-j,y_mabda+3*zarib+j,x_mabda+3*zarib+j+1,y_mabda+3*zarib+j);
//    }
//
    setfillstyle(1, COLOR(0,100,120));
    setcolor(COLOR(0,100,120));
    //bar(x_mabda-20,y_mabda-20,x_mabda+3*zarib+20,y_mabda+3*zarib+20);
    fillellipse(x_mabda+3*zarib/2, y_mabda+3*zarib/2, 7*zarib/3, 13*zarib/6);
    setlinestyle(1,1,6);
    setcolor(0);
    line(x_mabda,y_mabda+zarib,x_mabda+3*zarib,y_mabda+zarib);
    line(x_mabda,y_mabda+2*zarib,x_mabda+3*zarib,y_mabda+2*zarib);
    line(x_mabda+zarib,y_mabda,x_mabda+zarib,y_mabda+3*zarib);
    line(x_mabda+2*zarib,y_mabda,x_mabda+2*zarib,y_mabda+3*zarib);

}

void drow_score_bord(void)
{
    setlinestyle(1,1,4);
    setcolor(0);
    rectangle(60,80,290,220);
    rectangle(getmaxx()-60,80,getmaxx()-290,220);
    setfillstyle(1,COLOR(177,50,10));
    bar(60,80,290,220);
    bar(getmaxx()-60,80,getmaxx()-290,220);

    setcolor(0);
    setlinestyle(1,1,3);
    line(100,0,100,100);
    line(250,0,250,100);
    line(getmaxx()-100,0,getmaxx()-100,100);
    line(getmaxx()-250,0,getmaxx()-250,100);
    setlinestyle(1,1,6);
    circle(100,100,4);
    circle(250,100,4);
    circle(getmaxx()-100,100,4);
    circle(getmaxx()-250,100,4);

    setbkcolor(COLOR(177,50,10));
    settextstyle(4,0,6);
    setcolor(0);
    outtextxy(80,120, "\"x\"");
    outtextxy(getmaxx()-270,120, "\"o\"");
}

void game(void)
{
    int i = 0;
    while(!kbhit())
    {
        if(mousex() > x_mabda && mousex() < getmaxx()-x_mabda && mousey() > y_mabda && mousey() < getmaxy()-y_mabda)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                turn = drow_xo(turn);
                if(win_check() != 0) return;
                if(full() == 1) return;
            }
        }
    }
}

int drow_xo(int turn)
{
    int x = (mousex()-x_mabda)/zarib;
    int y = (mousey()-y_mabda)/zarib;
    if(hole[x+1][y+1] == 0)
    {
        setbkcolor(COLOR(0,100,120));
        settextstyle(4,0,10);
        setcolor(2);
        if(turn == 1)
        {
            outtextxy(x_mabda+x*zarib+25, y_mabda+y*zarib+3, "x");
            hole[x+1][y+1] = 1;
        // *turn++;
        }
        else if(turn == 2)
        {
            outtextxy(x_mabda+x*zarib+25, y_mabda+y*zarib+3, "o");
            hole[x+1][y+1] = 2;
        }
        if(turn == 1) turn++;
        else turn--;
    }
    clearmouseclick(WM_LBUTTONDOWN);
    return turn;
}

int win_check(void)
{
    if(hole[1][1] == hole[1][2] && hole[1][1] == hole[1][3]) win = hole[1][1];
    else if(hole[2][1] == hole[2][2] && hole[2][1] == hole[2][3]) win = hole[2][1];
    else if(hole[3][1] == hole[3][2] && hole[3][1] == hole[3][3]) win = hole[3][1];
    //
    else if(hole[1][1] == hole[2][1] && hole[1][1] == hole[3][1]) win = hole[1][1];
    else if(hole[1][2] == hole[2][2] && hole[1][2] == hole[3][2]) win = hole[1][2];
    else if(hole[1][3] == hole[2][3] && hole[1][3] == hole[3][3]) win = hole[1][3];
    //
    else if(hole[1][1] == hole[2][2] && hole[1][1] == hole[3][3]) win = hole[1][1];
    else if(hole[1][3] == hole[2][2] && hole[1][3] == hole[3][1]) win = hole[1][3];
    return win;
}

int full(void)
{
    int _empty = 0;
    for(int i = 1; i <= 3; i++)
            for(int j = 1; j <= 3; j++)
                if(hole[i][j] != 0) _empty++;
    if(_empty == 9) return 1;
    return 0;
}

void show_score(void)
{
    char sx[100] = {} , so[100] = {} ;
    setbkcolor(COLOR(177,50,10));
    settextstyle(6,0,6);
    sprintf(sx,"%d", player_x);
    outtextxy(200,120,sx);
    sprintf(so,"%d", player_o);
    outtextxy(getmaxx()-150,120,so);
}
