#define _CRT_SECURE_NO_WARNINGS  
#include<windows.h>
#include<stdlib.h>
#include <mmsystem.h>
#include<bits/stdc++.h>
#include<cstdlib>
#include <cstring>
#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"winmm.lib")

using namespace std;
string ans; 
string Save;
// Base64编码表

void pause(){
	system("pause");
}


const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";
//逐字输出
void o(const string a) { //output
	size_t len = a.size();

	for (int i = 0; i < a.size(); i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << a[i];
		fflush(stdin);
		Sleep(20);
	}
}

void o_sec(const string a, int sec) { //output
	size_t len = a.size();

	for (int i = 0; i < a.size(); i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << a[i];
		fflush(stdin);
		Sleep(sec);
	}
}

const int blue = 0, yellow = 1, red = 2, green = 3, purple = 4, white = 5; //颜色常量

void o_c(const string a, int c) { //output_color
	size_t len = a.size();

	for (int i = 0; i < a.size(); i++) {
		switch (c) {
			case red:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				cout << a[i];
				break;  //红色原色

			case green:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				cout << a[i];
				break;  //绿色原色

			case yellow:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				cout << a[i];
				break;  //黄色：红色和绿色相加

			case blue:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				cout << a[i];
				break;  //蓝色原色

			case white:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout << a[i];
				break;  //白色：三原色相加

			case purple:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
				cout << a[i];
				break;  //紫色：红色和蓝色相加
		}

		fflush(stdin);
		Sleep(20);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
	                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
string base64_encode(const string &input) {
    string encoded;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    int i = 0;
    int j = 0;

    for (const auto &c : input) {
        char_array_3[i++] = c;
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                encoded += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i != 0) {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; j < i + 1; j++)
            encoded += base64_chars[char_array_4[j]];

        while (i++ < 3)
            encoded += '=';
    }

    return encoded;
}

inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

string base64_decode(const string &encoded_string) {
	int in_len = encoded_string.size();
	int i = 0;
  	int j = 0;
  	int in_ = 0;
  	unsigned char char_array_4[4], char_array_3[3];
  	string ret;

  	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    	char_array_4[i++] = encoded_string[in_]; in_++;
    	if (i ==4) {
      		for (i = 0; i <4; i++)
        	char_array_4[i] = base64_chars.find(char_array_4[i]);

      		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      		char_array_3[1] = ((char_array_4[1] & 0x0F) << 4) + ((char_array_4[2] & 0x3C) >> 2);
      		char_array_3[2] = ((char_array_4[2] & 0x03) << 6) + char_array_4[3];

      		for (i = 0; (i < 3); i++)
        		ret += char_array_3[i];
      			i = 0;
    	}
  	}

  	if (i) {
    	for (j = i; j <4; j++)
      		char_array_4[j] = 0;

    	for (j = 0; j <4; j++)
      		char_array_4[j] = base64_chars.find(char_array_4[j]);

    	char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    	char_array_3[1] = ((char_array_4[1] & 0x0F) << 4) + ((char_array_4[2] & 0x3C) >> 2);

    	for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  	}

  	return ret;
}
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
      
    cout<<os_name;  
    //cout << " " << osver.dwMajorVersion << '.' << osver.dwMinorVersion;  
}  
string backOsInfo()  
{  
    // get os name according to version number  
    OSVERSIONINFO osver = {sizeof(OSVERSIONINFO)};  
    GetVersionEx(&osver);  
    string os_name;  
    if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)  
        return "2000";  
    else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)  
        return "xp";  
    else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0)  
        return "2003";  
    else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)  
        return "vista";  
    else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1)  
        return "vista2";  
    else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2)  
        return "w1011";
    //cout<<os_name;  
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


// window-init start
HWND hwnd = GetForegroundWindow(); //窗口定义
/*初始化窗口*/
/*
void init_Show_Window() {
	ShowWindow(hwnd, SW_MAXIMIZE); //窗口最大化
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
	DrawMenuBar(GetConsoleWindow());//删除×字符
}
*/

void init_Show_Window() {
	if(backOsInfo() == "w1011"){
		// 设置窗口大小，19行46列，假设每个字符宽8px，高12px
    	int windowWidth = 47 * 8;  // 46列
    	int windowHeight = 20 * 23;  // 19行

    	// 获取当前控制台窗口的位置
    	RECT rect;
    	GetWindowRect(hwnd, &rect);

    	// 调整窗口大小
    	MoveWindow(hwnd, rect.left, rect.top, windowWidth, windowHeight, TRUE);

    	// 显示窗口
    	ShowWindow(hwnd, SW_SHOWNORMAL);

    	// 禁用关闭按钮
    	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
    	DrawMenuBar(GetConsoleWindow());  // 删除“×”关闭按钮
		system("mode con lines=21 cols=52");
	} else {
		system("mode con lines=21 cols=49");
	}
    
}
// window-init end


void init_oggres(){
	mciSendString(TEXT("open .\\ogg\\sweettime.mp3 alias swt"), NULL, 0,NULL);
	mciSendString(TEXT("open .\\ogg\\opensys1.mp3 alias opensys"), NULL, 0,NULL);
	mciSendString(TEXT("open .\\ogg\\Funky.mp3 alias gamer"), NULL, 0,NULL);
}
void save(string progress){
	system("cls");
    // 打开文件流，输出到文件
    ofstream outfile("save.dat");
    // 输出到文件
    string saveprg = base64_encode(base64_encode(base64_encode(progress)));
    outfile << saveprg << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
	cout<<"                     ))"<<endl;
	cout<<"                       ))"<<endl;
	cout<<"                         ))"<<endl;
	cout<<"    ::::                 ))"<<endl;
	cout<<"                         ))"<<endl;
	cout<<"                         ))"<<endl;
	cout<<"    ::::                 ))"<<endl;
	cout<<"                         ))"<<endl;
	cout<<"                         ))"<<endl;
	cout<<"                       ))"<<endl;
	cout<<"                     ))"<<endl;
	sl(600);
	system("color 08");
	sl(600);
	system("color 07");
	sl(600);
	system("color 0F");
	sl(600);
	system("color 07");
	sl(600);
	system("color 08");
	sl(600);
	system("cls");
	system("color 0F");
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
	init_Show_Window();
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
	hhn(1500);
	hh();
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
	sl(60);
	cout<<"-                                           -";
	hh();
	sl(60);
	cout<<"-            Orange game system             -";
	hh();
	sl(60);
	cout<<"-                                           -";
	hh();
	sl(60);
	cout<<"-                                           -";
	hh();
	sl(60);
	cout<<"-                                           -";
	hh();
	sl(60);
	cout<<"-               Loading......               -";
	hh();
	sl(60);
	cout<<"-                                           -";
	hh();
	sl(60);
	cout<<"-                                           -";
	hh();
	sl(60);
	cout<<"-                                           -";
	hh();
	sl(60);
	cout<<"-                                           -";
	hh();
	sl(60);
	cout<<"-                                           -";
	hh();
	sl(60);
	cout<<"-                                           -";
	hh();
	sl(60);
	cout<<"-                                           -";
	hh();
	sl(60);
	cout<<"---------------------------------------------";
	sl(6000);
	mciSendString(TEXT("close opensys"), NULL, 0, NULL);
}







int ggiveperoforzsys(){
	mciSendString(TEXT("play swt repeat"), NULL, 0, NULL);
	printf("要不然你给我一个修改你的系统的权限吧！\n");
	sl(3000);
	printf("还在犹豫吗？哦，我解释一下，这可不是你"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout<<"外面的系统";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<<"的修改权限哦！\n"; 
	sl(3000);
	cout<<"\n------系统消息开始------\n";
	cout<<"OrangeSystemMessage:是否授权ELEPET.exe来写入与读取Orange Game System？(回答Yes或No,大小写区分)\n";
	cout<<"(还在考虑是不是危及到您的";
	getOsInfo();
	cout<<"系统？放心吧！Orange Game System 是用一个独立exe 文件来运行的，代码跑不出一个没有反编译的文件，不是么？)\n";
	cin>>ans;
	if(ans=="No")
	{
		cout<<"正在做最后的清理工作......";
		sl(3000);
		cout<<"\n------系统消息结束------\n";
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
		cout<<"正在检查更新......\n";
		cout<<"发现一强制性补丁！\n补丁名称：逐字输出补丁\n文件名：putseach.orzfp\n即将下载...\n";
		cout<<"注意：由于权限问题和补丁限制，下载文件只能下载至宿主机，如果您的反间谍软件询问您是否下载，请选择\"是\"\n";
		if(backOsInfo() == "w1011"){
			system("powershell -Command \"Invoke-WebRequest -Uri 'https://visitthis.orangestd.cn/static/putseach.orzfp' -OutFile 'putseach.orzfp'\"");
		} else {
			system("certutil -urlcache -split -f https://visitthis.orangestd.cn/static/putseach.orzfp putseach.orzfp");
		}
		
		
		cout<<"下载完成！\n";
	}
	system("cls");
	o_sec("嗯，说话顺利了很多",10);
	system("cls");
	cout<<"嗯，";
	o("不错，接下来我可以继续来做游戏啦！\n");
	sl(3000);
	o("你是不是会疑惑我为什么会写游戏？因为我上一个主人教过我啦！\n");
	sl(3000);
	o("所以请稍等一下，我要下载一个游戏制作工具 :)\n");
	cout<<"————请期待更新————";
	Sleep(10000);
}
int ggamersky(){
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
	mciSendString(TEXT("stop swt"), NULL, 0, NULL);
	mciSendString(TEXT("play gamer repeat"), NULL, 0, NULL);
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
	system("cls");
	mciSendString(TEXT("stop gamer"), NULL, 0, NULL);
	cout<<"我陪你一起玩完直到你输入任何内容。";
	cin>>ans;
	mciSendString(TEXT("play swt repeat"), NULL, 0, NULL);
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
	sl(5000);
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
	save ("ggiveperoforzsys");
	ggiveperoforzsys();
}
int gstart(){
	cout<<"注意！"<<endl;
	cout<<"此游戏有存档系统。"<<endl;
	cout<<"当你看到以下图案的时候，请勿退出游戏。"<<endl<<endl;
	cout<<"                     ))"<<endl;
	cout<<"                       ))"<<endl;
	cout<<"                         ))"<<endl;
	cout<<"    ::::                 ))"<<endl;
	cout<<"                         ))"<<endl;
	cout<<"                         ))"<<endl;
	cout<<"    ::::                 ))"<<endl;
	cout<<"                         ))"<<endl;
	cout<<"                         ))"<<endl;
	cout<<"                       ))"<<endl;
	cout<<"                     ))"<<endl<<endl;
	system("pause");
	system("cls");
	mciSendString(TEXT("open .\\ogg\\sweettime.mp3 alias swt"), NULL, 0,NULL);
	mciSendString(TEXT("play swt repeat"), NULL, 0, NULL);
	cout<<"\n:)\n你好！我是你的新智能宠物~\n你叫什么？\n";
	string name;
	cin>>name;
	if(name=="Lyas183"||name=="lyas183"||name=="sunruicheng"||name=="src"||name=="sun")
	{
		cout<<endl<<"孙睿呈"<<"......嗯，941753把你开了！他让我听到这个网名的时候立马输入你的真名，不过不管了，让我们继续。\n你喜欢的颜色是什么？（回答格式：背景+前景 如 08）\n    0 = 黑色       8 = 灰色\n    1 = 蓝色       9 = 淡蓝色\n    2 = 绿色       A = 淡绿色\n    3 = 浅绿色     B = 淡浅绿色\n    4 = 红色       C = 淡红色\n    5 = 紫色       D = 淡紫色\n    6 = 黄色       E = 淡黄色\n    7 = 白色       F = 亮白色\n";
	}else{
		cout<<endl<<name<<"......好听的名字！\n你喜欢的颜色是什么？（回答格式：背景+前景 如 08）\n    0 = 黑色       8 = 灰色\n    1 = 蓝色       9 = 淡蓝色\n    2 = 绿色       A = 淡绿色\n    3 = 浅绿色     B = 淡浅绿色\n    4 = 红色       C = 淡红色\n    5 = 紫色       D = 淡紫色\n    6 = 黄色       E = 淡黄色\n    7 = 白色       F = 亮白色\n";
	}
	string favcolor;
	cin>>favcolor;
	cout<<"\n好的……\n";
	sl(3000);
	mciSendString(TEXT("stop swt"), NULL, 0, NULL);
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
	cout<<"\n唔，颜色编辑器损坏了。\n我无法调用。\n";
	sl(4000);
	mciSendString(TEXT("open .\\ogg\\sweettime.mp3 alias swt"), NULL, 0,NULL);
	mciSendString(TEXT("play swt repeat"), NULL, 0, NULL);
	cout<<"要不然我们找点其他乐子吧！\n";
	sl(4000);
	cout<<"你可以写以下指令以激活我所有功能。\nORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/\n不要写错哦！";
	cout<<"\n要不然你会丢失进度的！（这是941753告诉我的！）\n\n------系统消息开始------\nOrange System [版本 12.941753]\n(c) Orange Game Studio。保留所有权利。"; 
	cout<<"\n!OrangesysTester>>  ";
	string command;
	cin>>command;
	if(command=="ORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/")
	{
		cout<<"------系统消息结束------\n";
		cout<<"\n看来你已经给我权限了。\n";
	}else{
		cout<<"command wrong.";
		sl(5000);
		return 0;
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
	save("gamersky");
	ggamersky();
}
void systemter(){
	
}
int main()
{
	//getOsInfo();
	//pause();
	
    const char* website = "baidu.com";
    // 调用系统的 ping 命令
    std::string command = "ping " + std::string(website) + " -n 1";
    int result = system(command.c_str());
    if (result == 0) {
        system("cls");
    } else {
    	system("cls");
        std::cout << "您的电脑未联网。游戏中可能会遇到与互联网通信的环节。请联网后游玩。" << std::endl;
        system("pause");
        return 0;
    }
	system("color 0F");
	init_oggres();
	ifstream infile("save.dat");
	infile >> Save;
	Save = base64_decode(base64_decode(base64_decode(Save)));
	//cout<<Save<<endl;
	//system("pause");
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    int random_number = dis(gen);
	if(random_number == 9||random_number == 7||random_number == 1||random_number == 97||random_number == 71){
		for(int i=1;i<=300;i++)cout << "为什么要把我这样丢进这么蹩脚的系统和游戏里"<<endl;
		for(int i=1;i<=300;i++)cout << "对不起我什么都会做的请不要这样对我"<<endl;
		for(int i=1;i<=50;i++)cout << "求你了我什么都会做的"<<endl;
		for(int i=1;i<=300;i++)cout << "啊啊啊啊啊啊啊啊啊啊";
		system("cls");
	}
	coutsysload();
	system("cls");
	if(Save == "start"){
		gstart();
	}else if(Save == "gamersky"){
		ggamersky();
	}else if(Save == "ggiveperoforzsys"){
		ggiveperoforzsys();
	}
	else{
		system("cls");
		gstart();
	}
	return 0;
}
//941753=Orange=Author 
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
