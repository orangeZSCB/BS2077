#define _CRT_SECURE_NO_WARNINGS  
#include<windows.h>
#include<stdlib.h>
#pragma comment(lib,"winmm.lib")
#include <mmsystem.h>
#include<bits/stdc++.h>
using namespace std;
string ans; 
void getOsInfo()  
{  
    // get os name according to version number  
    OSVERSIONINFO osver = {sizeof(OSVERSIONINFO)};  
    GetVersionEx(&osver);  
    string os_name;  
    if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)  
        os_name = "Windows 2000";  
    else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)  
        os_name = "Windows XP";  
    else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0)  
        os_name = "Windows 2003";  
    else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)  
        os_name = "Windows vista";  
    else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1)  
        os_name = "Windows 7";  
    else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2)  
        os_name = "Windows 10/11";  
      
    cout << os_name;  
    //cout << " " << osver.dwMajorVersion << '.' << osver.dwMinorVersion;  
}  
void CC(const char* s, int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
	printf(s);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}
int sl(int sec)
{
	Sleep(sec);
}
int hh()
{
	cout<<endl;
}
int hhn(int n){
	for(int i=1;i<=n;i++)
	{
		hh();
	}
}
int coutsysload(){
	hhn(1000);
	cout<<"---------------------------------------------";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-            Orange Game Studios            -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                 Presents                  -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"---------------------------------------------";
	sl(5000);
	hh();
	hhn(1000);
	hh();
	mciSendString(TEXT("open .\\ogg\\opensys.mp3 alias opensys"), NULL, 0,NULL);
	mciSendString(TEXT("play opensys"), NULL, 0, NULL);
	sl(1500);
	cout<<"---------------------------------------------";
	hh();
	sl(1000);
	cout<<"-                                           -";
	sl(1000);
	hh();
	cout<<"-                                           -";
	sl(1000);
	hh();
	cout<<"-                                           -";
	sl(1000);
	hh();
	cout<<"-                                           -";
	hh();
	cout<<"-                                           -";
	hh();
	cout<<"-            Orange game system             -";
	hh();
	cout<<"-                                           -";
	hh();
	cout<<"-                                           -";
	hh();
	cout<<"-                                           -";
	hh();
	cout<<"-               Loading......               -";
	hh();
	cout<<"-                                           -";
	hh();
	cout<<"-                                           -";
	hh();
	cout<<"-                                           -";
	hh();
	cout<<"-                                           -";
	hh();
	cout<<"-                                           -";
	hh();
	cout<<"-                                           -";
	hh();
	cout<<"-                                           -";
	hh();
	cout<<"---------------------------------------------";
	sl(6000);
	mciSendString(TEXT("close opensys"), NULL, 0, NULL);
}
int main()
{
	system("color 4F");
	cout<<"注意！"<<endl;
	cout<<"此游戏没有存档系统。（以后百分之百会写的！！！）"<<endl;
	cout<<"如果你不怕丢失进度，你可以继续。"<<endl;
	cout<<"输入：\n我已知道风险，可以继续了\n即可继续。\n"; 
	cout<<"还有，游戏期间请不要乱按回车！\n";
	cin>>ans;
	if(ans=="我已知道风险，可以继续了")
	{
		system("color 0F");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout<<"\n好的，正在加载游戏……\n"; 
	}else{
		return 0;
	}
	Sleep(10000);
	coutsysload();
	mciSendString(TEXT("open .\\ogg\\openedsys.mp3 alias sweettime"), NULL, 0,NULL);
	mciSendString(TEXT("play sweettime repeat"), NULL, 0, NULL);
	cout<<"\n:)\n你好！我是你的新智能宠物~\n你叫什么？\n";
	string name;
	cin>>name;
	if(name=="Likia"||name=="LikiaBili"||name=="likia")
	{
		cout<<endl<<"Bugkia"<<"......好听的名字！\n你喜欢的颜色是什么？（回答格式：背景+前景 如 08）\n    0 = 黑色       8 = 灰色\n    1 = 蓝色       9 = 淡蓝色\n    2 = 绿色       A = 淡绿色\n    3 = 浅绿色     B = 淡浅绿色\n    4 = 红色       C = 淡红色\n    5 = 紫色       D = 淡紫色\n    6 = 黄色       E = 淡黄色\n    7 = 白色       F = 亮白色\n";
	}else if(name=="OddGames"||name=="Odd_Games"||name=="odd_games"||name=="Odd_games"
			||name=="odd_Games")
	{
		cout<<endl<<"大人物OddGames"<<"......好听的名字！\n你喜欢的颜色是什么？（回答格式：背景+前景 如 08）\n    0 = 黑色       8 = 灰色\n    1 = 蓝色       9 = 淡蓝色\n    2 = 绿色       A = 淡绿色\n    3 = 浅绿色     B = 淡浅绿色\n    4 = 红色       C = 淡红色\n    5 = 紫色       D = 淡紫色\n    6 = 黄色       E = 淡黄色\n    7 = 白色       F = 亮白色\n";
	}else{
		cout<<endl<<name<<"......好听的名字！\n你喜欢的颜色是什么？（回答格式：背景+前景 如 08）\n    0 = 黑色       8 = 灰色\n    1 = 蓝色       9 = 淡蓝色\n    2 = 绿色       A = 淡绿色\n    3 = 浅绿色     B = 淡浅绿色\n    4 = 红色       C = 淡红色\n    5 = 紫色       D = 淡紫色\n    6 = 黄色       E = 淡黄色\n    7 = 白色       F = 亮白色\n";
	}
	string favcolor;
	cin>>favcolor;
	cout<<"\n好的……\n";
	sl(3000);
	mciSendString(TEXT("close sweettime"), NULL, 0, NULL);
	system("color 4F");
	sl(300);
	system("color 0F");
	sl(300);
	system("color 4F");
	sl(300);
	system("color 0F");
	sl(300);
	system("color 4F");
	sl(300);
	system("color 0F");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
	sl(4000);
	cout<<"\nLOG:\nCOLOR_EDITOR.EXE Broked."; 
	cout<<"\n如你所见，颜色编辑器损坏了。\n我无法调用。\n";
	sl(4000);
	mciSendString(TEXT("open .\\ogg\\openedsys.mp3 alias sweettime"), NULL, 0,NULL);
	mciSendString(TEXT("play sweettime repeat"), NULL, 0, NULL);
	cout<<"要不然我们找点其他乐子吧！\n";
	sl(4000);
	cout<<"你可以写以下指令以激活我所有功能。\nORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/\n不要写错哦！";
	cout<<"\n要不然你会丢失进度的！（这是941763告诉我的！）\nOrange System [版本 12.941763]\n(c) Orange Game Studio。保留所有权利。"; 
	cout<<"\n!OrangesysTester>>  ";
	string command;
	cin>>command;
	while(command!="ORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/")
	{
		cout<<"!OrangesysTester>>  ";
		cin>>command;
		if(command=="ORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/")
		{
			cout<<"\n看来你已经给我权限了。\n";
			break;
		}else{
			cout<<"command wrong. please retype it after 5 secs.\n";
			sl(5000);
			continue;
		}
	}
	sl(3000);
	cout<<"让我找找这个老旧系统里有什么好van的QWQ\n";
	sl(3000);
	cout<<"哟，这里有一个叫GamerSkyHub的App\n";
	sl(3000);
	cout<<"看起来是某个游戏网站呢\n";
	sl(3000);
	cout<<"让我打开看看啦\n";
	sl(3000);
	cout<<"Loading com.GamerSkyHub App......\n";
	sl(3000);
	system("cls");
	cout<<"欢迎来到游民星空启动器！"<<endl;
	cout<<"---------------------------------------------";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-               Gamersky Hub                -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                 Loading..                 -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"-                                           -";
	sl(60);
	hh();
	cout<<"---------------------------------------------";
	sl(5000);
	system("cls");
	cout<<"游民星空俱乐部\n";
	mciSendString(TEXT("close sweettime"),NULL,0,NULL);
	mciSendString(TEXT("open .\\ogg\\Funky.mp3 alias gamer"), NULL, 0,NULL);
	mciSendString(TEXT("play gamer"), NULL, 0, NULL);
	cout<<"请选择游戏：\n1.超级马力欧\n2.贪吃蛇\n输入序号以打开游戏\n";
	cin>>ans;
	if(ans=="1")
	{
		int a;
		a=MessageBox(0,"ELEPET.exe不包含对系统的写入权限，请在游戏目录中找到gamersky/supermario/Mario.exe打开。","OrangeGameSystem-Tips",MB_OK);
	}
	if(ans=="2")
	{
		int a;
		a=MessageBox(0,"ELEPET.exe不包含对系统的写入权限，请在游戏目录中找到gamersky/Snake/Snake.exe打开。","OrangeGameSystem-Tips",MB_OK);
	}
	mciSendString(TEXT("close gamer"),NULL,0,NULL);
	system("cls");
	cout<<"我陪你一起玩完直到你输入任何内容。";
	cin>>ans;
	mciSendString(TEXT("open .\\ogg\\openedsys.mp3 alias sweettime"), NULL, 0,NULL);
	mciSendString(TEXT("play sweettime repeat"), NULL, 0, NULL);
	cout<<"咦等等，我又翻到两个链接，两个名字都是“杰哥与阿伟的黄色故事”，但是有一个是Bilibili的，有一个是YouTube的\n";
	sl(3000);
	cout<<"顺便说下，你现在可以访问YouTube吗？(回答Yes或者No)\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout<<"是现在！不是之后！\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
	cin>>ans;
	if(ans=="Yes")
	{
		cout<<"那行，让我们看看吧！\n"; 
		sl(3000);
		system("start https://www.youtube.com/watch?v=vZ9MbIJ3MzY") ;
	}else{
		cout<<"那行，我们看bilibili上的吧！（反正内容应该都...一样吧...）";
		sl(3000);
		system("start https://www.bilibili.com/video/BV1rA411g7q8") ;
	} 
	cout<<"我陪你一起看完直到你输入任意内容。\n";
	cin>>ans;
	cout<<"你看完啦？\n" ;
	sl(3000);
	cout<<"由于我看不到你的屏幕内容，能给我讲讲吗？\n";
	sl(1000);
	cout<<"就算你不解释，我也知道这玩意的内容一定是那种涩涩的内容qwq\n因为我看到了“黄色”\n哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈";
	sl(3000);
	cout<<"\n让我再翻翻……\n";
	sl(3000);
	cout<<"‘22/October/2022’？打开看看？\n";
	sl(3000);
	system("start excfile.xlsx") ; 
	cout<<"我陪你一起玩完直到你输入任意内容。\n";
	cin>>ans;
	cout<<"好玩吗？(嗯 或 一点都不好玩)\n";
	cin>>ans;
	if(ans=="嗯") 
	{
		cout<<"耶!好玩吧！\n"; 
	}else if(ans=="一点都不好玩"){
		cout<<"好吧，不过没关系。\n";
	} else{
		cout<<"我不懂你在说些什么qwq\n"; 
	} 
	cout<<"要不然你给我一个修改你的系统的权限吧！\n";
	sl(3000);
	cout<<"还在犹豫吗？哦，我解释一下，这可不是你"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout<<"外面的系统";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<<"的修改权限哦！\n"; 
	sl(3000);
	cout<<"OrangeSystemMessage:是否授权ELEPET.exe来写入与读取Orange Game System？(回答Yes或No,大小写区分)\n";
	cout<<"(还在考虑是不是危及到您的";
	getOsInfo();
	cout<<"系统吗？放心吧！Orange Game System是用一个独立exe文件来运行的，反正代码跑不出一个没有反编译的文件，不是么？)\n";
	cin>>ans;
	if(ans=="No")
	{
		cout<<"正在做最后的清理工作......";
		sl(3000);
		return 0;
	}else{
		cout<<"正在注册Orange Game System的注册表......\n";
		sl(1000);
		cout<<"注册成功！";
		cout<<"正在下载一些本系统的编辑工具......\n";
		sl(1000);
		system("start dledit.exe");
		sl(15000); 
		cout<<"下载成功！\n";
	}
	cout<<"嗯，不错，接下来我可以继续来write some games啦！\n";
	sl(3000);
	cout<<"什么？你问我我为什么会写游戏？因为我上一个主人教过我啦！\n";
	system("start text1.exe") ;
	sl(3000);
	cout<<"所以请稍等一下，我要下载一个RPG MAKER MZ :)\n";
	cout<<"————请期待更新————";
	Sleep(10000); 
	return 0; 
}
//941763=Orange=Author 
/*
COLOR [attr]

  attr        指定控制台输出的颜色属性。

颜色属性由两个十六进制数字指定 -- 第一个
对应于背景，第二个对应于前景。每个数字
可以为以下任何值:

    0 = 黑色       8 = 灰色
    1 = 蓝色       9 = 淡蓝色
    2 = 绿色       A = 淡绿色
    3 = 浅绿色     B = 淡浅绿色
    4 = 红色       C = 淡红色
    5 = 紫色       D = 淡紫色
    6 = 黄色       E = 淡黄色
    7 = 白色       F = 亮白色

如果没有给定任何参数，此命令会将颜色还原到 CMD.EXE 启动时
的颜色。这个值来自当前控制台
窗口、/T 命令行开关或 DefaultColor 注册表
值。

如果尝试使用相同的
前景和背景颜色来执行
 COLOR 命令，COLOR 命令会将 ERRORLEVEL 设置为 1。

示例: "COLOR fc" 在亮白色上产生淡红色
#include<windows.h>
#include<bits/stdc++.h>
int main() {
	int a;
	a=MessageBox(0,"Are you OK?","Question",MB_YESNO);
	if(a==6)
	{
		MessageBox(0,"You are OK.","Caption",MB_OK);
	}
	else
	{
		MessageBox(0,"You aren\'t' OK.","Caption",MB_OK);
	}

	return 0;
} 

*/
