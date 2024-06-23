#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#pragma comment(lib,"winmm.lib")
#include <mmsystem.h>
using namespace std;

/*** ��궨λ ***/
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

void locate(int x, int y) {
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};

/*** ���ع�� ***/
void hide() {
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(hout, &cursor_info);
}

/*** ��������� ***/
double random(double start, double end) {
	return start + (end - start) * rand() / (RAND_MAX + 1.0);
}

/*** �����ͼ�ĳ����ߵ����꣬���ȣ�����ʳ���λ�� ***/
int m, n;

struct node {
	int x, y;
} snake[1000];

int snake_length, dir;
node food;
int direct[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

/*** ���ǽ ***/
void print_wall() {
	cout << " ";

	for (int i = 1; i <= n; i++)
		cout << "-";

	cout << endl;

	for (int j = 0; j <= m - 1; j++) {
		cout << "|";

		for (int i = 1; i <= n; i++)
			cout << " ";

		cout << "|" << endl;
	}

	cout << " ";

	for (int i = 1; i <= n; i++)
		cout << "-";
}

/*** �״�����ߣ�����snake[0]����ͷ ***/
void print_snake() {
	locate(snake[0].x, snake[0].y);
	cout << "@";

	for (int i = 1; i <= snake_length - 1; i++) {
		locate(snake[i].x, snake[i].y);
		cout << "*";
	}
}

/*** �ж��Ƿ�ײǽ������ײ ***/
bool is_correct() {
	if (snake[0].x == 0 || snake[0].y == 0 || snake[0].x == m + 1 || snake[0].y == n + 1)
		return false;

	for (int i = 1; i <= snake_length - 1; i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			return false;
	}

	return true;
}

/*** ������ɲ����ʳ��λ�� ***/
bool print_food() {
	srand((unsigned)time(0));
	bool e;

	while (1) {
		e = true;
		int i = (int) random(0, m) + 1, j = (int) random(0, n) + 1;
		food.x = i;
		food.y = j;

		for (int k = 0; k <= snake_length - 1; k++) {
			if (snake[k].x == food.x && snake[k].y == food.y) {
				e = false;
				break;
			}
		}

		if (e)
			break;
	}

	locate(food.x, food.y);
	cout << "$";
	return true;
}

/*** �ߵ�ǰ�� ***/
bool go_ahead() {
	node temp;
	bool e = false;
	temp = snake[snake_length - 1];

	for (int i = snake_length - 1; i >= 1; i--)
		snake[i] = snake[i - 1];

	snake[0].x += direct[dir][0];
	snake[0].y += direct[dir][1];
	locate(snake[1].x, snake[1].y);
	cout << "*";

	/*** �Ե���ʳ�� ***/
	if (snake[0].x == food.x && snake[0].y == food.y) {
		snake_length++;
		e = true;
		snake[snake_length - 1] = temp;
	}

	/*** �����ʱ��״̬ ***/
	if (!e) {
		locate(temp.x, temp.y);
		cout << " ";
	} else
		print_food();

	locate(snake[0].x, snake[0].y);
	cout << "@";

	/*** �����ײ ***/
	if (!is_correct()) {
		system("cls");
		mciSendString(TEXT("close s1"),NULL,0,NULL);
		mciSendString(TEXT("open .\\sounds\\lose.mp3 alias s2"),NULL,0,NULL);
		mciSendString(TEXT("play s2"),NULL,0,NULL);
		cout << "��������" << endl << "���ճ���: " << snake_length << endl;
		Sleep(3000);
		mciSendString(TEXT("close s2"),NULL,0,NULL);
		return false;
	}

	return true;
}

/*** ������ ***/
int main() {
	cout << "--------------------̰����---------------------" << endl;
	cout << "��ע�ⴰ�ڴ�С,���ⷢ����λ.���齫���ڵ�Ϊ���." << endl;
	cout << "��ѡ���Ѷ�.����1-10������1����,1���,10������" << endl;
	cout << "Ȼ�������Ϸ����,�Է�������Ʒ���.ף����Ϸ���!" << endl;
	cout << "-----------------------------------------------" << endl;
	m = 25;
	n = 40;

	if (m < 10 || n < 10 || m > 25 || n > 40) {
		cout << "ERROR" << endl;
		system("pause");
		return 0;
	}

	int hard;
	cin >> hard;

	if (hard <= 0 || hard > 100) {
		cout << "ERROR" << endl;
		system("pause");
		return 0;
	}

	/*** ����ȫ����ʼ���������߳���λ�ã����� ���� ***/
	mciSendString(TEXT("open .\\sounds\\bgm.mp3 alias s1"),NULL,0,NULL);
	mciSendString(TEXT("play s1"),NULL,0,NULL);
	snake_length = 5;
	clock_t a, b;
	char ch;
	double hard_len;

	for (int i = 0; i <= 4; i++) {
		snake[i].x = 1;
		snake[i].y = 5 - i;
	}

	dir = 3;
	/*** �����ʼ��ͼ������ʳ�� ***/
	system("cls");
	hide();
	print_wall();
	print_food();
	print_snake();
	locate(m + 2, 0);
	cout << "���ڳ���: ";

	/*** ��ʼ��Ϸ ***/
	while (1) {
		/*** �Ѷ��泤�����Ӷ���� ***/
		hard_len = (double)snake_length / (double) (m * n);
		/*** ����ʱ�䣬��λ��ms ***/
		a = clock();

		while (1) {
			b = clock();

			if (b - a >= (int)(400 - 30 * hard) * (1 - sqrt(hard_len)))
				break;
		}

		/*** ���ܼ���������������ң����Դ˸ı䷽�� ***/
		if (kbhit()) {
			ch = getch();

			if (ch == -32) {
				ch = getch();

				switch (ch) {
					case 72:
						if (dir == 2 || dir == 3)
							dir = 0;

						break;

					case 80:
						if (dir == 2 || dir == 3)
							dir = 1;

						break;

					case 75:
						if (dir == 0 || dir == 1)
							dir = 2;

						break;

					case 77:
						if (dir == 0 || dir == 1)
							dir = 3;

						break;
				}
			}
		}

		/*** ǰ�� ***/
		if (!go_ahead())
			break;

		/*** ����������ʱ���� ***/
		locate(m + 2, 12);
		cout << snake_length;
	}

	system("pause");
	return 0;
}