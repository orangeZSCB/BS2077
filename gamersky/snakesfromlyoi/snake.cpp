#include <cstdio>
#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>       //停顿:Sleep(); 
#include <cstdlib>         //清屏:system("cls");
#include <cstring>         //1:'◎' 2:'⊙' 3:'▲' 4:'◆' 5:'■'
using namespace std;
int a[100][100],dir[100][100];
//string guo[5]={'▲','◆','■','▼','★'};
int fx[4][2]={{0,-1},{1,0},{0,1},{-1,0}}; //ap来记录奖励块的分   
int n,m,ff,f=1,t=55,T=55,ap=10,egg[2],danshu,headx,heady,endx,endy,point=0,apple=0,fangx,stopp=0,panduan=0;  //ff用来判断  panduan 0:中途退出;1:咬到自己;2:重置  
int lastfx;
int zuobi=0;
int fff[110][110];
string print[4][4]={{"═","╔"," ","╚"},{"╝","║","╚"," "},{" ","╗","═","╝"},{"╗"," ","╔","║"}};

void color(int a)//颜色函数
{
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

void gotoxy(int x,int y)//位置函数(行为x 列为y)
{
COORD pos;
pos.X=2*y;
pos.Y=x;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void reset(){
    system("cls");
    color(7); printf("                   ★"); color(10); printf("贪吃蛇"); color(11); printf("★\n\n"); color(7);
    printf("⊙打印若有错位请调整窗口大小或按r重输小点的数⊙\n\n  请输入场地大小(格式:行数 列数) 推荐(20 20) \n\n>>");
    scanf("%d%d",&n,&m);
    system("cls");
    color(14);
    for (int i=1; i<=m; i++){gotoxy(0,i);printf("※");gotoxy(n+1,i);printf("※");}
    for (int i=1; i<=n; i++){gotoxy(i,0);printf("※");gotoxy(i,m+1);printf("※");}
    color(10);
    memset(fff,0,sizeof(fff));
    gotoxy(0,0); printf("┍");
    gotoxy(n+1,0); printf("┕");
    gotoxy(0,m+1); printf("┑");
    gotoxy(n+1,m+1); printf("┙");
    color(7);
    gotoxy(0,m+5); printf("方向：a/s/d/w | 1/2/3/5");
    gotoxy(1,m+5); printf("暂停：p       |       0");
    gotoxy(2,m+5); printf("减速：q/j     |     4/7");
    gotoxy(3,m+5); printf("加速：e/k     |     6/9"); 
    gotoxy(4,m+5); printf("重置：r       |       .");
    gotoxy(5,m+5); printf("地图：g       |       +");
    headx=endx=endy=1; heady=3;
    f=1; ff=3;
    memset(a,1,sizeof(a));
    memset(dir,0,sizeof(dir));
    a[1][1]=a[1][2]=a[1][3]=0;
    gotoxy(1,1); printf("⊙");
    gotoxy(1,2); printf("⊙");
    gotoxy(1,3); printf("◎");
    dir[1][1]=dir[1][2]=dir[1][3]=2;
    apple=0; fangx=2; point=0; danshu=0; lastfx=2; stopp=0;
    if (zuobi) {color(12); gotoxy(12,m+5); printf("作弊可耻！"); gotoxy(n+4,0); printf("做了弊还没路走那就救不了你了，乖乖重来吧......"); color(7);} 
}

void haha(){
    char ch=getch();
    if ((ch=='a' | ch=='1') && dir[headx][heady]!=2){fangx=0; return;}
    if ((ch=='s' | ch=='2') && dir[headx][heady]!=3){fangx=1; return;} 
    if ((ch=='d' | ch=='3') && dir[headx][heady]!=0){fangx=2; return;}
    if ((ch=='w' | ch=='5') && dir[headx][heady]!=1){fangx=3; return;}
    if (ch=='p' | ch=='0'){stopp=(stopp+1)%2; return;}
    if (ch=='q' | ch=='4'){T+=10; if (T>=1005) T=1005; return;}
    if (ch=='e' | ch=='6'){T-=10; if (T<=1) T=2; return;} 
    if (ch=='j' | ch=='7'){T+=1; if (T>=1005) T=1005; return;}
    if (ch=='k' | ch=='9'){T-=1; if (T<=1) T=2; return;}
    if (ch=='r' | ch=='.'){ff=2; f=0; panduan=0; return;}
    if (ch=='h' | ch=='8'){
        zuobi+=1; zuobi%=2;
        if (zuobi) {color(12); gotoxy(12,m+5); printf("作弊可耻！"); gotoxy(n+4,0); printf("做了弊还没路走那就救不了你了，乖乖重来吧......"); color(7);} 
        else {printf("                "); gotoxy(m+4,0); printf("                                                   ");}
    }
    if (ch=='g' |ch=='+'){
        gotoxy(n+50,0);
        printf("现在切换到地图编辑模式\n\nq/4 为开始放置模式(光标移动过的痕迹会留下障碍物)\n\ne/6 为取消放置障碍物模式\n\nj/0 为橡皮模式(再按一次退出橡皮模式)\n\n按 h/+ 继续游戏\n\n"); 
        printf("\n按任意键开始编辑地图"); 
        color(13); 
        int x=1,y=1, dfx, moshi=0;
        ch=getch(); gotoxy(0,0); gotoxy(1,1);
        while (ch!='h' && ch!='+'){
            if (ch=='a' | ch=='1') dfx=0;
            else if (ch=='s' | ch=='2') dfx=1;
            else if (ch=='d' | ch=='3') dfx=2;
            else if (ch=='w' | ch=='5') dfx=3;
            else dfx=5;
            if (ch=='q' | ch=='4') moshi=1;
            if (ch=='e' | ch=='6') moshi=0;
            if (ch=='j' | ch=='0') if (moshi-2) moshi=2; else moshi=0;
            if (dfx<=4){
                if (x+fx[dfx][0]>0 && x+fx[dfx][0]<=n && y+fx[dfx][1]>0 && y+fx[dfx][1]<=m){x+=fx[dfx][0]; y+=fx[dfx][1];}
                if (x>0 && x<=n && y>0 && y<=m){
                    gotoxy(x,y);
                    if (moshi==1 && a[x][y] && !fff[x][y]){a[x][y]=0; fff[x][y]=1; printf("□");}
                    if (moshi==2 && fff[x][y]){a[x][y]=1; fff[x][y]=0; printf("  ");} 
                    gotoxy(x,y);
                }
            }
            ch=getch();
        }
        color(7);
    }
}   

void findegg(){
    srand(time(NULL));
    int aa=1;
    while (!a[egg[0]][egg[1]]){egg[0]=(rand()%(n))+1; egg[1]=(rand()%m)+1;}
    a[egg[0]][egg[1]]=0;
    point+=ap;
    gotoxy(egg[0],egg[1]); if (!apple){printf("★"); ap=8000/T; if (ap>=200) ap=200;}else {printf("●"); ap=10;}
    apple++; apple=apple%10;  
    gotoxy(n+2,0); printf("距离下一个奖励蛋还有 "); color(11); cout <<9-(8+apple)%10; color(7); printf(" 个"); 
    danshu++;
    return;
}

int gg(){

    if (ff==0) return(0);
    if (ff==1) {gotoxy(n+2,1); Sleep(3000); gotoxy(n+26,1); gotoxy(n+10,0); printf("哦豁~ 你咬到自己了o(￣▽￣)d\n\n\n你共吃蛋 %d 个\n\n\n你共得分 %d 分，恭喜！\n\n\n等一下就继续",danshu,point); while (kbhit()) char ch=getch(); Sleep(5000); if (kbhit) return(1);}
    if (ff==2) return(1);
}

void dong(){
    gotoxy(11,m+3); printf("当前的蛋有 %d 分            ",ap);
    if (ap-3>10) ap-=3;
    if (ap!=10){
            gotoxy(egg[0],egg[1]);
            color(ap%10);
            printf("★");
            color(7);
    }

    int x,y;
    x=(headx+fx[fangx][0]-1+n)%(n)+1; y=(heady+fx[fangx][1]-1+m)%(m)+1;
    dir[headx][heady]=fangx; 
    if(x==egg[0] && y==egg[1]){
        gotoxy(headx,heady); cout <<print[lastfx][fangx]; 
        dir[headx][heady]=fangx;
        headx=x; heady=y; a[x][y]=0;
        gotoxy(headx,heady); printf("◎");
        findegg();
    }
    else if (a[x][y]){
        gotoxy(headx,heady); cout <<print[lastfx][fangx]; 
        headx=x; heady=y; a[x][y]=0;
        gotoxy(headx,heady); printf("◎");
        gotoxy(endx,endy); printf("  "); a[endx][endy]=1; 
        x=endx; y=endy; 
        endx+=fx[dir[x][y]][0]; endx=(endx-1+n)%(n)+1;
        endy+=fx[dir[x][y]][1]; endy=(endy-1+m)%(m)+1;
        dir[x][y]=-1;
    }
    else if(!zuobi){f=0; ff=1;}

    dir[headx][heady]=fangx;
    lastfx=fangx;
    return;
}

int main(){
    while (1){
        srand(time(NULL));
        reset();
        egg[0]=(rand()%n-1)+2; egg[1]=(rand()%m)+1; 
        a[egg[0]][egg[1]]=0;
        gotoxy(egg[0],egg[1]); if (apple){printf("★"); ap=100;}else printf("●");
        while (f){
            if (kbhit()) haha();
            gotoxy(9,m+5); printf("吃蛋：%d 个",danshu);
            gotoxy(8,m+5); printf("速度: %d   ",1005-T);
            //while (stopp) {Sleep(10); if (kbhit()) haha();}
            Sleep(1); t=(t-1+T)%T;  
            if (t==0 && !stopp) dong();
            gotoxy(7,m+5); printf("得分：%d 分",point);
            gotoxy(12,m+5);
        }
        if (!gg()) return 0;
    }
    return 0;
}
