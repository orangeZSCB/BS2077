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
	cout<<"ע�⣡"<<endl;
	cout<<"����Ϸû�д浵ϵͳ�����Ժ�ٷ�֮�ٻ�д�ģ�������"<<endl;
	cout<<"����㲻�¶�ʧ���ȣ�����Լ�����"<<endl;
	cout<<"���룺\n����֪�����գ����Լ�����\n���ɼ�����\n"; 
	cout<<"���У���Ϸ�ڼ��벻Ҫ�Ұ��س���\n";
	cin>>ans;
	if(ans=="����֪�����գ����Լ�����")
	{
		system("color 0F");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout<<"\n�õģ����ڼ�����Ϸ����\n"; 
	}else{
		return 0;
	}
	Sleep(10000);
	coutsysload();
	mciSendString(TEXT("open .\\ogg\\openedsys.mp3 alias sweettime"), NULL, 0,NULL);
	mciSendString(TEXT("play sweettime repeat"), NULL, 0, NULL);
	cout<<"\n:)\n��ã�������������ܳ���~\n���ʲô��\n";
	string name;
	cin>>name;
	if(name=="Likia"||name=="LikiaBili"||name=="likia")
	{
		cout<<endl<<"Bugkia"<<"......���������֣�\n��ϲ������ɫ��ʲô�����ش��ʽ������+ǰ�� �� 08��\n    0 = ��ɫ       8 = ��ɫ\n    1 = ��ɫ       9 = ����ɫ\n    2 = ��ɫ       A = ����ɫ\n    3 = ǳ��ɫ     B = ��ǳ��ɫ\n    4 = ��ɫ       C = ����ɫ\n    5 = ��ɫ       D = ����ɫ\n    6 = ��ɫ       E = ����ɫ\n    7 = ��ɫ       F = ����ɫ\n";
	}else if(name=="OddGames"||name=="Odd_Games"||name=="odd_games"||name=="Odd_games"
			||name=="odd_Games")
	{
		cout<<endl<<"������OddGames"<<"......���������֣�\n��ϲ������ɫ��ʲô�����ش��ʽ������+ǰ�� �� 08��\n    0 = ��ɫ       8 = ��ɫ\n    1 = ��ɫ       9 = ����ɫ\n    2 = ��ɫ       A = ����ɫ\n    3 = ǳ��ɫ     B = ��ǳ��ɫ\n    4 = ��ɫ       C = ����ɫ\n    5 = ��ɫ       D = ����ɫ\n    6 = ��ɫ       E = ����ɫ\n    7 = ��ɫ       F = ����ɫ\n";
	}else{
		cout<<endl<<name<<"......���������֣�\n��ϲ������ɫ��ʲô�����ش��ʽ������+ǰ�� �� 08��\n    0 = ��ɫ       8 = ��ɫ\n    1 = ��ɫ       9 = ����ɫ\n    2 = ��ɫ       A = ����ɫ\n    3 = ǳ��ɫ     B = ��ǳ��ɫ\n    4 = ��ɫ       C = ����ɫ\n    5 = ��ɫ       D = ����ɫ\n    6 = ��ɫ       E = ����ɫ\n    7 = ��ɫ       F = ����ɫ\n";
	}
	string favcolor;
	cin>>favcolor;
	cout<<"\n�õġ���\n";
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
	cout<<"\n������������ɫ�༭�����ˡ�\n���޷����á�\n";
	sl(4000);
	mciSendString(TEXT("open .\\ogg\\openedsys.mp3 alias sweettime"), NULL, 0,NULL);
	mciSendString(TEXT("play sweettime repeat"), NULL, 0, NULL);
	cout<<"Ҫ��Ȼ�����ҵ��������Ӱɣ�\n";
	sl(4000);
	cout<<"�����д����ָ���Լ��������й��ܡ�\nORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/\n��Ҫд��Ŷ��";
	cout<<"\nҪ��Ȼ��ᶪʧ���ȵģ�������941763�����ҵģ���\nOrange System [�汾 12.941763]\n(c) Orange Game Studio����������Ȩ����"; 
	cout<<"\n!OrangesysTester>>  ";
	string command;
	cin>>command;
	while(command!="ORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/")
	{
		cout<<"!OrangesysTester>>  ";
		cin>>command;
		if(command=="ORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/")
		{
			cout<<"\n�������Ѿ�����Ȩ���ˡ�\n";
			break;
		}else{
			cout<<"command wrong. please retype it after 5 secs.\n";
			sl(5000);
			continue;
		}
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
	mciSendString(TEXT("close sweettime"),NULL,0,NULL);
	mciSendString(TEXT("open .\\ogg\\Funky.mp3 alias gamer"), NULL, 0,NULL);
	mciSendString(TEXT("play gamer"), NULL, 0, NULL);
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
	mciSendString(TEXT("close gamer"),NULL,0,NULL);
	system("cls");
	cout<<"������һ������ֱ���������κ����ݡ�";
	cin>>ans;
	mciSendString(TEXT("open .\\ogg\\openedsys.mp3 alias sweettime"), NULL, 0,NULL);
	mciSendString(TEXT("play sweettime repeat"), NULL, 0, NULL);
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
	sl(1000);
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
	cout<<"Ҫ��Ȼ�����һ���޸����ϵͳ��Ȩ�ްɣ�\n";
	sl(3000);
	cout<<"������ԥ��Ŷ���ҽ���һ�£���ɲ�����"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout<<"�����ϵͳ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<<"���޸�Ȩ��Ŷ��\n"; 
	sl(3000);
	cout<<"OrangeSystemMessage:�Ƿ���ȨELEPET.exe��д�����ȡOrange Game System��(�ش�Yes��No,��Сд����)\n";
	cout<<"(���ڿ����ǲ���Σ��������";
	getOsInfo();
	cout<<"ϵͳ�𣿷��İɣ�Orange Game System����һ������exe�ļ������еģ����������ܲ���һ��û�з�������ļ�������ô��)\n";
	cin>>ans;
	if(ans=="No")
	{
		cout<<"����������������......";
		sl(3000);
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
	}
	cout<<"�ţ������������ҿ��Լ�����write some games����\n";
	sl(3000);
	cout<<"ʲô����������Ϊʲô��д��Ϸ����Ϊ����һ�����˽̹�������\n";
	system("start text1.exe") ;
	sl(3000);
	cout<<"�������Ե�һ�£���Ҫ����һ��RPG MAKER MZ :)\n";
	cout<<"�����������ڴ����¡�������";
	Sleep(10000); 
	return 0; 
}
//941763=Orange=Author 
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
