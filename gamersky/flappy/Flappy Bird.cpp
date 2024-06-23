#include <cstdio>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <cstring>
using namespace std;
//==================================================================
#define hest 100            //跳的速度(点击到最高点有 (250/hest) 秒) 
#define mo 2000             //跳的高度(每次点击跳到最高多 (((1+hest)*hest+hest)/mo) 格) 
#define hei 20              //屏幕高度 
#define wid 13              //屏幕宽度 
#define det v*2-1
#define gap 5               //柱子间上下的空隙长度 
#define len 3               //柱子的宽度 
#define T  25               //柱子移动时间单位      T t移动一格
#define TT 500/T            //柱子出现频率            TT T出现一个 
//==================================================================
void color(int a)//颜色函数
{
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void gotoxy(int x,int y)//位置函数(列为x 行为y)
{
    COORD pos;
    pos.X=2*x;
    pos.Y=hei-y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

int v,h,hx,hy,t,tt,gg,quit,score,plused,wall[hei+5][wid+len+10];
/*
    t:  时间基本单位          1t=4ms
    tt: 辅助作用                柱子每 移动T格tt++ 
    quit                        记录是否退出游戏 
    plused                      辅助用作计分 
    wall[i][j]  第 i 行第 j 列的柱子情况(0为空 1为有但还没打印 2为打印过了) 
*/ 

void reset(){
    system("cls");
    color(4);
    for (int i=0; i<=wid; i++){gotoxy(i,-1); printf("※");}
    gg=0;
    hx=5;
    hy=hei/2;
    h=hy*mo;
    t=0;
    tt=-5; 
    v=hest;
    score=0;
    memset(wall,0,sizeof(wall));
    color(14); gotoxy(hx,hy); printf("◎");
}

void move_bird(){
    h+=(v*2-1);
    if (h>hei*mo) h=hei*mo;
    if (h/mo!=hy){
        gotoxy(hx,hy); printf("  ");
        hy=h/mo;
        if (hy<0) hy=h=0;//gg=1;
        if (wall[hy][hx]) gg=1;
        gotoxy(hx,hy);
        color(14); printf("◎");
    }
}

void move_wall(){
    for (int i=0; i<=hei; i++){
        int k=0,pp=0;
        while (k<wid+5){
            color(2); 
            for (; k<=wid+5 && !wall[i][k]; k++);
            if (k+len/2==hx){
                if (!plused) plused=1, score++;
                if (!pp) color(15),pp=1;
            }
            if (k>=0 && wall[i][k]) wall[i][k-1]=1;
            k-=2; if (k<-1) k=-1;
            while (wall[i][++k]){
                if (hx==k && hy==i) gg=1;
                if (k<=wid && wall[i][k]==1){wall[i][k]=2; gotoxy(k,i); printf("█");}
            }
            wall[i][k-1]=0; gotoxy(k-1,i); printf("  ");
        }
    }
}

void new_wall(){
    srand(time(NULL));
    int dd=(rand()%(hei-gap-1)+1),uu=dd+gap+1;
    for (int i=1; i<=len; i++) wall[dd][i+wid]=1;
    for (int i=dd-1; i>=0; i--) for (int j=2; j<len; j++) wall[i][j+wid]=1;
    for (int i=1; i<=len; i++) wall[uu][i+wid]=1;
    for (int i=uu+1; i<=hei; i++) for (int j=2; j<len; j++) wall[i][j+wid]=1;
    plused=0;
}

void game(){
    while (!gg){
        v--;
        if(kbhit()) {char ch=getch(); v=hest;}
        Sleep(4); t=(t+1)%T;
        if (tt==TT) tt=0, new_wall();
        if (t==0) tt++, move_wall();
        move_bird();
        color(8);
        gotoxy(wid/2,2*hei/3);
        printf("%d",score);
    }
    gotoxy(wid/2,-3); color(15); printf("GG~");
    gotoxy(wid/2-3,-5); printf("final score: %d",score);
    gotoxy(hx,hy); color(12); printf("◎");
}

int main(){
    char ch;
    while (ch!='*'){
        reset();
        ch=getch();
        game();
        Sleep(1500);
        while (kbhit()) ch=getch();
        Sleep(1000);
        ch=getch();
    }
}
