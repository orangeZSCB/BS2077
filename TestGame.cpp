#include<iostream>
#include<windows.h> 
using namespace std;
string ans; 
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
	cout<<"-                  itch.io                  -";
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
	cout<<"-                 Publisher                 -";
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
	cout<<"---------------------------------------------";
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
	sl(7000);
}
int main()
{
	system("color 48");
	cout<<"注意！"<<endl;
	cout<<"此游戏没有存档系统。"<<endl;
	cout<<"如果你不怕丢失进度，你可以继续。"<<endl;
	cout<<"输入：\n我已知道风险，可以继续了\n即可继续。\n"; 
	cin>>ans;
	if(ans=="我已知道风险，可以继续了")
	{
		system("color 08");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout<<"\n好的，正在加载游戏……\n"; 
	}else{
		return 0;
	}
	Sleep(10000);
	coutsysload();
	cout<<"\n:)\n\(@^0^@)/\n你好！我是你的新智能宠物~\n你叫什么？\n";
	string name;
	cin>>name;
	cout<<endl<<name<<"......好听的名字！\n你喜欢的颜色是什么？（回答格式：背景+前景 如 08）\n    0 = 黑色       8 = 灰色\n    1 = 蓝色       9 = 淡蓝色\n    2 = 绿色       A = 淡绿色\n    3 = 浅绿色     B = 淡浅绿色\n    4 = 红色       C = 淡红色\n    5 = 紫色       D = 淡紫色\n    6 = 黄色       E = 淡黄色\n    7 = 白色       F = 亮白色\n";
	string favcolor;
	cin>>favcolor;
	cout<<"\n好的……\n";
	sl(3000);
	system("color 48");
	sl(300);
	system("color 08");
	sl(300);
	system("color 48");
	sl(300);
	system("color 08");
	sl(300);
	system("color 48");
	sl(300);
	system("color 08");
	sl(4000);
	cout<<"\nLOG:\nCOLOR_EDITOR.EXE Broked."; 
	cout<<"\n如你所见，颜色编辑器损坏了。\n我无法调用。\n";
	sl(4000);
	cout<<"要不然我们找点其他乐子吧！\n";
	sl(4000);
	cout<<"你可以写以下指令以激活我所有功能。\nORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/\n不要写错哦！";
	cout<<"\n要不然你会丢失进度的！（这是941763告诉我的！）\nOrange System [版本 12.941763]\n(c) Orange Game Studio。保留所有权利。"; 
	cout<<"\n!OrangesysTester>>  ";
	string command;
	cin>>command;
	if(command=="ORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/")
	{
		cout<<"\n看来你已经给我权限了。\n";
	}else{
		cout<<"command wrong.";
		sl(5000);
		return 0;
	}
	sl(3000);
	cout<<"让我找找这个老旧系统里有什么好van的QWQ\n";
	sl(3000);
	cout<<"“杰哥与阿伟的黄色故事.mp4”？让我们看看吧！\n"; 
	sl(3000);
	system("start vidfile1.mp4") ;
	cout<<"我陪你一起看完直到你输入任意内容。\n";
	cin>>ans;
	cout<<"你看完啦？\n" ;
	sl(3000);
	cout<<"由于我看不到你的屏幕内容，能给我讲讲吗？\n";
	sl(5000);
	cout<<"就算你不解释，我也知道这玩意的内容一定是那种涩涩的内容qwq\n因为我看到了“黄色”\n哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈";
	sl(3000);
	cout<<"让我再翻翻……";
	sl(3000);
	cout<<"‘22/October/2022’？打开看看？";
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
	Sleep(10000); 
	return 0; 
}
//941763=Orange=Arthor 
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
*/
