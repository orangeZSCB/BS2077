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
        os_name = "Windows 10";  
      
    cout << os_name;  
    cout << " " << osver.dwMajorVersion << '.' << osver.dwMinorVersion;  
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
	cout<<"\nAlthough idk whether the original author of BuddySim1984 will accept my work, I am willing to die for this work!\nThanks for the inspiration provided by ??Not a Sailor Studio??!";
	sl(5000);
	cout<<"\n????????????BuddySim1984??????????????????????????????????????????????????????????????\n????????????????????????????????????" ;
	sl(5000);
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
	system("color 48");
	cout<<"??????"<<endl;
	cout<<"????????????????????"<<endl;
	cout<<"????????????????????????????????"<<endl;
	cout<<"??????\n????????????????????????\n??????????\n"; 
	cout<<"??????????????????????????????\n????????????????????????txt??????????????????\n";
	cin>>ans;
	if(ans=="????????????????????????")
	{
		system("color 08");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout<<"\n??????????????????????\n"; 
	}else{
		return 0;
	}
	Sleep(10000);
	coutsysload();
	mciSendString(TEXT("open .\\ogg\\openedsys.mp3 alias sweettime"), NULL, 0,NULL);
	mciSendString(TEXT("play sweettime repeat"), NULL, 0, NULL);
	cout<<"\n:)\n\(@^0^@)/\n????????????????????????~\n??????????\n";
	string name;
	cin>>name;
	if(name=="Likia"||name=="LikiaBili"||name=="likia")
	{
		cout<<endl<<"Bugkia"<<"......????????????\n????????????????????????????????????+???? ?? 08??\n    0 = ????       8 = ????\n    1 = ????       9 = ??????\n    2 = ????       A = ??????\n    3 = ??????     B = ????????\n    4 = ????       C = ??????\n    5 = ????       D = ??????\n    6 = ????       E = ??????\n    7 = ????       F = ??????\n";
	}else{
		cout<<endl<<name<<"......????????????\n????????????????????????????????????+???? ?? 08??\n    0 = ????       8 = ????\n    1 = ????       9 = ??????\n    2 = ????       A = ??????\n    3 = ??????     B = ????????\n    4 = ????       C = ??????\n    5 = ????       D = ??????\n    6 = ????       E = ??????\n    7 = ????       F = ??????\n";
	}
	string favcolor;
	cin>>favcolor;
	cout<<"\n????????\n";
	sl(3000);
	mciSendString(TEXT("close sweettime"), NULL, 0, NULL);
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
	sl(4000);
	cout<<"\nLOG:\nCOLOR_EDITOR.EXE Broked."; 
	cout<<"\n????????????????????????????\n????????????\n";
	sl(4000);
	mciSendString(TEXT("open .\\ogg\\openedsys.mp3 alias sweettime"), NULL, 0,NULL);
	mciSendString(TEXT("play sweettime repeat"), NULL, 0, NULL);
	cout<<"??????????????????????????\n";
	sl(4000);
	cout<<"??????????????????????????????????\nORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/\n????????????";
	cout<<"\n????????????????????????????941763????????????\nOrange System [???? 12.941763]\n(c) Orange Game Studio????????????????"; 
	cout<<"\n!OrangesysTester>>  ";
	string command;
	cin>>command;
	if(command=="ORZGAMESYSCOMMAND:/GIVE_ELEPET.EXE_SYSTEM_OP/")
	{
		cout<<"\n??????????????????????\n";
	}else{
		cout<<"command wrong.";
		sl(5000);
		return 0;
	}
	sl(3000);
	cout<<"??????????????????????????????van??QWQ\n";
	sl(3000);
	cout<<"??????????????????????????????????????????????????????????????????????????Bilibili????????????YouTube??\n";
	sl(3000);
	cout<<"????????????????????????YouTube????(????Yes????No)\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout<<"??????????????????\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
	cin>>ans;
	if(ans=="Yes")
	{
		cout<<"????????????????????\n"; 
		sl(3000);
		system("start https://www.youtube.com/watch?v=vZ9MbIJ3MzY") ;
	}else{
		cout<<"????????????bilibili????????????????????????...??????...??";
		sl(3000);
		system("start https://www.bilibili.com/video/BV1rA411g7q8") ;
	} 
	cout<<"??????????????????????????????????\n";
	cin>>ans;
	cout<<"??????????\n" ;
	sl(3000);
	cout<<"????????????????????????????????????????\n";
	sl(5000);
	cout<<"??????????????????????????????????????????????????????qwq\n????????????????????\n??????????????????????????????";
	sl(3000);
	cout<<"\n??????????????\n";
	sl(3000);
	cout<<"??22/October/2022??????????????\n";
	sl(3000);
	system("start excfile.xlsx") ; 
	cout<<"??????????????????????????????????\n";
	cin>>ans;
	cout<<"????????(?? ?? ????????????)\n";
	cin>>ans;
	if(ans=="??") 
	{
		cout<<"??!????????\n"; 
	}else if(ans=="????????????"){
		cout<<"??????????????????\n";
	} else{
		cout<<"??????????????????qwq\n"; 
	} 
	cout<<"??????????????????????????????????????\n";
	sl(3000);
	cout<<"??????????????????????????????????????"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout<<"??????????";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<<"??????????????\n"; 
	sl(3000);
	cout<<"OrangeSystemMessage:????????ELEPET.exe????????????Orange Game System??(????Yes??No,??????????)\n";
	cout<<"(????????????????????????";
	getOsInfo();
	cout<<"????????????????Orange Game System????????????exe??????????????????????????????????????????????????????????)\n";
	cin>>ans;
	if(ans=="No")
	{
		cout<<"????????????????????......";
		sl(3000);
		return 0;
	}else{
		cout<<"????????Orange Game System????????......\n";
		sl(1000);
		cout<<"??????????";
		cout<<"????????????????????????????......\n";
		sl(1000);
		system("start dledit.exe");
		sl(15000); 
		cout<<"??????????\n";
	}
	cout<<"????????????????????????????write some games????\n";
	sl(3000);
	cout<<"????????????????????????????????????????????????????????\n";
	system("start text1.exe") ;
	sl(3000);
	cout<<"????????????????????????????RPG MAKER MZ :)\n";
	cout<<"??????????????????????????";
	Sleep(10000); 
	return 0; 
}
//941763=Orange=Arthor 
/*
COLOR [attr]

  attr        ??????????????????????????

?????????????????????????????? -- ??????
??????????????????????????????????????
????????????????:

    0 = ????       8 = ????
    1 = ????       9 = ??????
    2 = ????       A = ??????
    3 = ??????     B = ????????
    4 = ????       C = ??????
    5 = ????       D = ??????
    6 = ????       E = ??????
    7 = ????       F = ??????

?????????????????????????????????????????? CMD.EXE ??????
????????????????????????????
??????/T ???????????? DefaultColor ??????
????

??????????????????
????????????????????
 COLOR ??????COLOR ???????? ERRORLEVEL ?????? 1??

????: "COLOR fc" ????????????????????
*/
