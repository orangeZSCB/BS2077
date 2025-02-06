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
// Base64�����

void pause(){
	system("pause");
}


const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";
//�������
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

const int blue = 0, yellow = 1, red = 2, green = 3, purple = 4, white = 5; //��ɫ����

void o_c(const string a, int c) { //output_color
	size_t len = a.size();

	for (int i = 0; i < a.size(); i++) {
		switch (c) {
			case red:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				cout << a[i];
				break;  //��ɫԭɫ

			case green:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				cout << a[i];
				break;  //��ɫԭɫ

			case yellow:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				cout << a[i];
				break;  //��ɫ����ɫ����ɫ���

			case blue:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				cout << a[i];
				break;  //��ɫԭɫ

			case white:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout << a[i];
				break;  //��ɫ����ԭɫ���

			case purple:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
				cout << a[i];
				break;  //��ɫ����ɫ����ɫ���
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
HWND hwnd = GetForegroundWindow(); //���ڶ���
/*��ʼ������*/
/*
void init_Show_Window() {
	ShowWindow(hwnd, SW_MAXIMIZE); //�������
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
	DrawMenuBar(GetConsoleWindow());//ɾ�����ַ�
}
*/

void init_Show_Window() {
	if(backOsInfo() == "w1011"){
		// ���ô��ڴ�С��19��46�У�����ÿ���ַ���8px����12px
    	int windowWidth = 47 * 8;  // 46��
    	int windowHeight = 20 * 23;  // 19��

    	// ��ȡ��ǰ����̨���ڵ�λ��
    	RECT rect;
    	GetWindowRect(hwnd, &rect);

    	// �������ڴ�С
    	MoveWindow(hwnd, rect.left, rect.top, windowWidth, windowHeight, TRUE);

    	// ��ʾ����
    	ShowWindow(hwnd, SW_SHOWNORMAL);

    	// ���ùرհ�ť
    	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
    	DrawMenuBar(GetConsoleWindow());  // ɾ���������رհ�ť
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
    // ���ļ�����������ļ�
    ofstream outfile("save.dat");
    // ������ļ�
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
	printf("Ҫ��Ȼ�����һ���޸����ϵͳ��Ȩ�ްɣ�\n");
	sl(3000);
	printf("������ԥ��Ŷ���ҽ���һ�£���ɲ�����"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout<<"�����ϵͳ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<<"���޸�Ȩ��Ŷ��\n"; 
	sl(3000);
	cout<<"\n------ϵͳ��Ϣ��ʼ------\n";
	cout<<"OrangeSystemMessage:�Ƿ���ȨELEPET.exe��д�����ȡOrange Game System��(�ش�Yes��No,��Сд����)\n";
	cout<<"(���ڿ����ǲ���Σ��������";
	getOsInfo();
	cout<<"ϵͳ�����İɣ�Orange Game System ����һ������exe �ļ������еģ������ܲ���һ��û�з�������ļ�������ô��)\n";
	cin>>ans;
	if(ans=="No")
	{
		cout<<"����������������......";
		sl(3000);
		cout<<"\n------ϵͳ��Ϣ����------\n";
		return 0;
	}else{
		cout<<"����ע��Orange Game System��ע���......\n";
		sl(1000);
		cout<<"ע��ɹ���";
		cout<<"��������һЩ��ϵͳ�ı༭����......\n";
		sl(1000);
		system("start dledit.exe");
		sl(15000); 
		cout<<"���سɹ���\n";
		cout<<"���ڼ�����......\n";
		cout<<"����һǿ���Բ�����\n�������ƣ������������\n�ļ�����putseach.orzfp\n��������...\n";
		cout<<"ע�⣺����Ȩ������Ͳ������ƣ������ļ�ֻ����������������������ķ�������ѯ�����Ƿ����أ���ѡ��\"��\"\n";
		if(backOsInfo() == "w1011"){
			system("powershell -Command \"Invoke-WebRequest -Uri 'https://visitthis.orangestd.cn/static/putseach.orzfp' -OutFile 'putseach.orzfp'\"");
		} else {
			system("certutil -urlcache -split -f https://visitthis.orangestd.cn/static/putseach.orzfp putseach.orzfp");
		}
		
		
		cout<<"������ɣ�\n";
	}
	system("cls");
	o_sec("�ţ�˵��˳���˺ܶ�",10);
	system("cls");
	cout<<"�ţ�";
	o("�����������ҿ��Լ���������Ϸ����\n");
	sl(3000);
	o("���ǲ��ǻ��ɻ���Ϊʲô��д��Ϸ����Ϊ����һ�����˽̹�������\n");
	sl(3000);
	o("�������Ե�һ�£���Ҫ����һ����Ϸ�������� :)\n");
	cout<<"�����������ڴ����¡�������";
	Sleep(10000);
}
int ggamersky(){
	cout<<"��ӭ���������ǿ���������"<<endl;
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
	cout<<"�����ǿվ��ֲ�\n";
	mciSendString(TEXT("stop swt"), NULL, 0, NULL);
	mciSendString(TEXT("play gamer repeat"), NULL, 0, NULL);
	cout<<"��ѡ����Ϸ��\n1.��������ŷ\n2.̰����\n��������Դ���Ϸ\n";
	cin>>ans;
	if(ans=="1")
	{
		int a;
		a=MessageBox(0,"ELEPET.exe��������ϵͳ��д��Ȩ�ޣ�������ϷĿ¼���ҵ�gamersky/supermario/Mario.exe�򿪡�","OrangeGameSystem-Tips",MB_OK);
	}
	if(ans=="2")
	{
		int a;
		a=MessageBox(0,"ELEPET.exe��������ϵͳ��д��Ȩ�ޣ�������ϷĿ¼���ҵ�gamersky/Snake/Snake.exe�򿪡�","OrangeGameSystem-Tips",MB_OK);
	}
	system("cls");
	mciSendString(TEXT("stop gamer"), NULL, 0, NULL);
	cout<<"������һ������ֱ���������κ����ݡ�";
	cin>>ans;
	mciSendString(TEXT("play swt repeat"), NULL, 0, NULL);
	cout<<"�׵ȵȣ����ַ����������ӣ��������ֶ��ǡ��ܸ��밢ΰ�Ļ�ɫ���¡���������һ����Bilibili�ģ���һ����YouTube��\n";
	sl(3000);
	cout<<"˳��˵�£������ڿ��Է���YouTube��(�ش�Yes����No)\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout<<"�����ڣ�����֮��\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
	cin>>ans;
	if(ans=="Yes")
	{
		cout<<"���У������ǿ����ɣ�\n"; 
		sl(3000);
		system("start https://www.youtube.com/watch?v=vZ9MbIJ3MzY") ;
	}else{
		cout<<"���У����ǿ�bilibili�ϵİɣ�����������Ӧ�ö�...һ����...��";
		sl(3000);
		system("start https://www.bilibili.com/video/BV1rA411g7q8") ;
	} 
	cout<<"������һ����ֱ���������������ݡ�\n";
	cin>>ans;
	cout<<"�㿴������\n" ;
	sl(3000);
	cout<<"�����ҿ����������Ļ���ݣ��ܸ��ҽ�����\n";
	sl(5000);
	cout<<"�����㲻���ͣ���Ҳ֪�������������һ��������ɬɬ������qwq\n��Ϊ�ҿ����ˡ���ɫ��\n������������������������������";
	sl(3000);
	cout<<"\n�����ٷ�������\n";
	sl(3000);
	cout<<"��22/October/2022�����򿪿�����\n";
	sl(3000);
	system("start excfile.xlsx") ; 
	cout<<"������һ������ֱ���������������ݡ�\n";
	cin>>ans;
	cout<<"������(�� �� һ�㶼������)\n";
	cin>>ans;
	if(ans=="��") 
	{
		cout<<"Ү!����ɣ�\n"; 
	}else if(ans=="һ�㶼������"){
		cout<<"�ðɣ�����û��ϵ��\n";
	} else{
		cout<<"�Ҳ�������˵Щʲôqwq\n"; 
	} 
	save ("ggiveperoforzsys");
	ggiveperoforzsys();
}
int gstart(){
	cout<<"ע�⣡"<<endl;
	cout<<"����Ϸ�д浵ϵͳ��"<<endl;
	cout<<"���㿴������ͼ����ʱ�������˳���Ϸ��"<<endl<<endl;
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
	cout<<"\n:)\n��ã�������������ܳ���~\n���ʲô��\n";
	string name;
	cin>>name;
	if(name=="Lyas183"||name=="lyas183"||name=="sunruicheng"||name=="src"||name=="sun")
	{
		cout<<endl<<"���"<<"......�ţ�941753���㿪�ˣ��������������������ʱ����������������������������ˣ������Ǽ�����\n��ϲ������ɫ��ʲô�����ش��ʽ������+ǰ�� �� 08��\n    0 = ��ɫ       8 = ��ɫ\n    1 = ��ɫ       9 = ����ɫ\n    2 = ��ɫ       A = ����ɫ\n    3 = ǳ��ɫ     B = ��ǳ��ɫ\n    4 = ��ɫ       C = ����ɫ\n    5 = ��ɫ       D = ����ɫ\n    6 = ��ɫ       E = ����ɫ\n    7 = ��ɫ       F = ����ɫ\n";
	}else{
		cout<<endl<<name<<"......���������֣�\n��ϲ������ɫ��ʲô�����ش��ʽ������+ǰ�� �� 08��\n    0 = ��ɫ       8 = ��ɫ\n    1 = ��ɫ       9 = ����ɫ\n    2 = ��ɫ       A = ����ɫ\n    3 = ǳ��ɫ     B = ��ǳ��ɫ\n    4 = ��ɫ       C = ����ɫ\n    5 = ��ɫ       D = ����ɫ\n    6 = ��ɫ       E = ����ɫ\n    7 = ��ɫ       F = ����ɫ\n";
	}
	string favcolor;
	cin>>favcolor;
	cout<<"\n�õġ���\n";
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
	cout<<"\n����ɫ�༭�����ˡ�\n���޷����á�\n";
	sl(4000);
	mciSendString(TEXT("open .\\ogg\\sweettime.mp3 alias swt"), NULL, 0,NULL);
	mciSendString(TEXT("play swt repeat"), NULL, 0, NULL);
	cout<<"Ҫ��Ȼ�����ҵ��������Ӱɣ�\n";
	sl(4000);
	cout<<"�����д����ָ���Լ��������й��ܡ�\nORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/\n��Ҫд��Ŷ��";
	cout<<"\nҪ��Ȼ��ᶪʧ���ȵģ�������941753�����ҵģ���\n\n------ϵͳ��Ϣ��ʼ------\nOrange System [�汾 12.941753]\n(c) Orange Game Studio����������Ȩ����"; 
	cout<<"\n!OrangesysTester>>  ";
	string command;
	cin>>command;
	if(command=="ORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/")
	{
		cout<<"------ϵͳ��Ϣ����------\n";
		cout<<"\n�������Ѿ�����Ȩ���ˡ�\n";
	}else{
		cout<<"command wrong.";
		sl(5000);
		return 0;
	}
	sl(3000);
	cout<<"������������Ͼ�ϵͳ����ʲô��van��QWQ\n";
	sl(3000);
	cout<<"Ӵ��������һ����GamerSkyHub��App\n";
	sl(3000);
	cout<<"��������ĳ����Ϸ��վ��\n";
	sl(3000);
	cout<<"���Ҵ򿪿�����\n";
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
    // ����ϵͳ�� ping ����
    std::string command = "ping " + std::string(website) + " -n 1";
    int result = system(command.c_str());
    if (result == 0) {
        system("cls");
    } else {
    	system("cls");
        std::cout << "���ĵ���δ��������Ϸ�п��ܻ������뻥����ͨ�ŵĻ��ڡ������������档" << std::endl;
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
		for(int i=1;i<=300;i++)cout << "ΪʲôҪ��������������ô���ŵ�ϵͳ����Ϸ��"<<endl;
		for(int i=1;i<=300;i++)cout << "�Բ�����ʲô���������벻Ҫ��������"<<endl;
		for(int i=1;i<=50;i++)cout << "��������ʲô��������"<<endl;
		for(int i=1;i<=300;i++)cout << "��������������������";
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

  attr        ָ������̨�������ɫ���ԡ�

��ɫ����������ʮ����������ָ�� -- ��һ��
��Ӧ�ڱ������ڶ�����Ӧ��ǰ����ÿ������
����Ϊ�����κ�ֵ:

    0 = ��ɫ       8 = ��ɫ
    1 = ��ɫ       9 = ����ɫ
    2 = ��ɫ       A = ����ɫ
    3 = ǳ��ɫ     B = ��ǳ��ɫ
    4 = ��ɫ       C = ����ɫ
    5 = ��ɫ       D = ����ɫ
    6 = ��ɫ       E = ����ɫ
    7 = ��ɫ       F = ����ɫ

���û�и����κβ�����������Ὣ��ɫ��ԭ�� CMD.EXE ����ʱ
����ɫ�����ֵ���Ե�ǰ����̨
���ڡ�/T �����п��ػ� DefaultColor ע���
ֵ��

�������ʹ����ͬ��
ǰ���ͱ�����ɫ��ִ��
 COLOR ���COLOR ����Ὣ ERRORLEVEL ����Ϊ 1��

ʾ��: "COLOR fc" ������ɫ�ϲ�������ɫ
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
