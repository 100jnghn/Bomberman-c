//1971222 백종훈
//crazy arcade
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)

#define STAR '*'
#define Delay 100
// 색상 정의
#define BLACK	0
#define BLUE1	1
#define GREEN1	2
#define CYAN1	3
#define RED1	4
#define MAGENTA1 5
#define YELLOW1	6
#define GRAY1	7
#define GRAY2	8
#define BLUE2	9
#define GREEN2	10
#define CYAN2	11
#define RED2	12
#define MAGENTA2 13
#define YELLOW2	14
#define WHITE	15

//공백
#define BLANK ' '

//ESC
#define ESC 0x1b

#define SPECIAL1 0xe0 // 특수키는 0xe0 + key 값으로 구성된다.
#define SPECIAL2 0x00 // keypad 경우 0x00 + key 로 구성된다.

// Up key는 0xe0 + 0x48 두개의 값이 들어온다.
#define UP  0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
#define UP2		'w'
#define DOWN2	's'
#define LEFT2	'a'
#define RIGHT2	'd'

#define BOMB 'p'

#define HEIGHT 15
#define WIDTH 20

int oldx, oldy, newx, newy;
int userx, usery;
//int distance = 1;
int map1[HEIGHT][WIDTH] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,9,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,6,1},
	{1,0,1,1,1,0,1,1,0,1,0,1,0,0,0,1,1,1,0,1},
	{1,0,1,6,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0,1},
	{1,0,1,0,0,1,1,1,0,1,0,1,0,0,0,1,1,1,0,1},
	{1,0,0,0,0,1,1,1,0,1,0,1,0,1,0,0,0,0,0,1},
	{1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1},
	{1,0,0,0,0,1,1,1,0,1,0,1,0,0,0,0,1,1,0,1},
	{1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,1,1,1,1,0,1,0,1,0,1,0,0,1,0,1,1,0,1},
	{1,0,0,0,0,0,0,1,0,0,6,0,0,0,0,0,0,0,0,1},
	{1,1,1,0,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1},
	{1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,6,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
int map2[HEIGHT][WIDTH] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1},
	{1,0,1,0,9,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
int new_map2[HEIGHT][WIDTH] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1},
	{1,0,1,0,9,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
int new_map1[HEIGHT][WIDTH] ={
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,9,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,6,1},
	{1,0,1,1,1,0,1,1,0,1,0,1,0,0,0,1,1,1,0,1},
	{1,0,1,6,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0,1},
	{1,0,1,0,0,1,1,1,0,1,0,1,0,0,0,1,1,1,0,1},
	{1,0,0,0,0,1,1,1,0,1,0,1,0,1,0,0,0,0,0,1},
	{1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1},
	{1,0,0,0,0,1,1,1,0,1,0,1,0,0,0,0,1,1,0,1},
	{1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,1,1,1,1,0,1,0,1,0,1,0,0,1,0,1,1,0,1},
	{1,0,0,0,0,0,0,1,0,0,6,0,0,0,0,0,0,0,0,1},
	{1,1,1,0,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1},
	{1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,6,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
void init_map1()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			map1[i][j] = new_map1[i][j];
		}
	}
}

void init_map2()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			map2[i][j] = new_map2[i][j];
		}
	}
}

typedef struct enemy
{
	int enemy_x;
	int enemy_y;
	int life;
	int boss_distance;
}enemy;

void gotoxy(int x, int y) //내가 원하는 위치로 커서 이동
{
	COORD pos; // Windows.h 에 정의
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void removeCursor(void) { // 커서를 안보이게 한다
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void showCursor(void) { // 커서를 보이게 한다
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

// 화면 지우기고 원하는 배경색으로 설정한다.
void cls(int text_color, int bg_color)
{
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);
}

int hidden_index; // Hidden 화면 번호 0 or 1
HANDLE scr_handle[2]; // 화면 버퍼 변수
void scr_clear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(scr_handle[hidden_index], ' ', WIDTH * 2 * HEIGHT, Coor, &dw);
}

// 정의된 맵 배열을 이용하여 맵을 그린다
void create_map1()
{
	int x, y;
	//scr_clear();

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			if (map1[y][x] == 0) //0=빈칸
			{
				textcolor(14, 14);
				printf("■");
				textcolor(0, 15);
			}
			else if (map1[y][x] == 1) //1=벽
			{
				textcolor(8, 8);
				printf("■");
				textcolor(1, 15);
			} //■
			else if (map1[y][x] == 9) //9=user
			{
				textcolor(6, 14);
				printf("★"); //★
				textcolor(0, 15);
			}
			else if (map1[y][x] == 2) //2=bomb
			{
				textcolor(9, 14);
				printf("●");
				textcolor(0, 15);
			}
			else if (map1[y][x] == 3) //3=bomb_range
			{
				textcolor(1, 14);
				printf("▒");
				textcolor(0, 15);
			}
			else if (map1[y][x] == 4) //4=item
			{
				textcolor(15, 9);
				printf("Д"); //▣Д
				textcolor(0, 15);
			}
			else if (map1[y][x] == 6) //6=monster
			{
				textcolor(4, 14);
				printf("ⓜ");
				textcolor(0, 15);
			}
		}
		printf("\n");
	}
}
void create_map2()
{
	int x, y;
	//scr_clear();

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			if (map2[y][x] == 0) //0=빈칸
			{
				textcolor(14, 14);
				printf("■");
				textcolor(0, 15);
			}
			else if (map2[y][x] == 1) //1=벽
			{
				textcolor(8, 8);
				printf("■");
				textcolor(0, 15);
			} //■
			else if (map2[y][x] == 9) //9=user
			{
				textcolor(2, 14);
				printf("★"); //★
				textcolor(0, 15);
			}
			else if (map2[y][x] == 2) //2=bomb
			{
				textcolor(9, 14);
				printf("●");
				textcolor(0, 15);
			}
			else if (map2[y][x] == 3) //3=bomb_range
			{
				textcolor(1, 14);
				printf("▒");
				textcolor(0, 15);
			}
			else if (map2[y][x] == 4) //4=item
			{
				textcolor(15, 9);
				printf("Д"); //▣Д
				textcolor(0, 15);
			}
			else if (map2[y][x] == 5)
			{
				textcolor(12, 14);
				printf("♥");
				textcolor(0, 15);
			}
			else if (map2[y][x] == 6) //6=monster
			{
				textcolor(4, 14);
				printf("★");
				textcolor(0, 15);
			}
			else if (map2[y][x] == 7)
			{
				textcolor(4, 14);
				printf("●");
				textcolor(0, 15);
			}
			else if (map2[y][x] == 8)
			{
				textcolor(4, 14);
				printf("▒");
				textcolor(0, 15);
			}

		}
		printf("\n");
	}
}

void putstar(int x, int y)
{
	map1[y][x] = 4;
}
void erasestar(int x, int y)
{
	gotoxy(x, y);
	putchar(BLANK);
}
void bomb(int bomb_start) //폭탄 설치되고 시간 지나면 터지는 함수
{
	int bomb_end;
	bomb_end = time(NULL);
	if (bomb_end - bomb_start >= 2)
	{
		map1[newx][newy] == 3;
		map1[newx + 1][newy] == 3;
		map1[newx - 1][newy] == 3;
		map1[newx][newy + 1] == 3;
		map1[newx][newy - 1] == 3;
	}
}
void show_time(int remain_time)
{
	if (remain_time >= 15)
	{
		textcolor(YELLOW2, GRAY2);
		gotoxy(47, 1);
		printf("시간 : %03d\r", remain_time);
		printf("\n");
		textcolor(BLACK, WHITE);
	}
	else
	{
		if (remain_time % 2 == 0)
		{
			textcolor(4, 8);
			gotoxy(47, 1);
			printf("시간 : %03d\r", remain_time);
			printf("\n");
			textcolor(BLACK, WHITE);
		}
		else
		{
			textcolor(YELLOW2, GRAY2);
			gotoxy(47, 1);
			printf("시간 : %03d\r", remain_time);
			printf("\n");
			textcolor(BLACK, WHITE);
		}
	}
}
int getTime()
{
	int flowtime = time(NULL);
	return flowtime;
}
void bomb_s(int i, int j, int distance)
{

	int n = 0;
	map1[i][j] = 3;
	while (n <= distance)
	{
		if (map1[i + n][j] == 1)
			break;
		map1[i + n][j] = 3;
		n++;
	}
	n = 0;
	while (n <= distance)
	{
		if (map1[i - n][j] == 1)
			break;
		map1[i - n][j] = 3;
		n++;
	}
	n = 0;
	while (n <= distance)
	{
		if (map1[i][j + n] == 1)
			break;
		map1[i][j + n] = 3;
		n++;
	}
	n = 0;
	while (n <= distance)
	{
		if (map1[i][j - n] == 1)
			break;
		map1[i][j - n] = 3;
		n++;
	}
}
void bomb_s2(int i, int j, int distance)
{

	int n = 0;
	map2[i][j] = 3;
	while (n <= distance)
	{
		if (map2[i + n][j] == 1)
			break;
		map2[i + n][j] = 3;
		n++;
	}
	n = 0;
	while (n <= distance)
	{
		if (map2[i - n][j] == 1)
			break;
		map2[i - n][j] = 3;
		n++;
	}
	n = 0;
	while (n <= distance)
	{
		if (map2[i][j + n] == 1)
			break;
		map2[i][j + n] = 3;
		n++;
	}
	n = 0;
	while (n <= distance)
	{
		if (map2[i][j - n] == 1)
			break;
		map2[i][j - n] = 3;
		n++;
	}
}
void bomb_boss(int i, int j, int distance)
{

	int n = 0;
	map2[i][j] = 8;
	while (n <= distance)
	{
		if (map2[i + n][j] == 7)
			if(map2[i + n + n][j])map2[i + n+n][j] = 7;
		if (map2[i + n][j] == 1)
			break;
		map2[i + n][j] = 8;
		n++;
	}
	n = 0;
	while (n <= distance)
	{
		if (map2[i - n][j] == 7)
			if(map2[i-n-n][j]!=1) map2[i - n - n][j] = 7;
		if (map2[i - n][j] == 1)
			break;
		map2[i - n][j] = 8;
		n++;
	}
	n = 0;
	while (n <= distance)
	{
		if (map2[i][j + n] == 7)
			if(map2[i][j + n + n]!=1)map2[i][j + n+n] = 7;
		if (map2[i][j + n] == 1)
			break;
		map2[i][j + n] = 8;
		n++;
	}
	n = 0;
	while (n <= distance)
	{
		if (map2[i][j - n] == 7)
			if(map2[i][j - n - n]!=1)map2[i][j - n-n] = 7;
		if (map2[i][j - n] == 1)
			break;
		map2[i][j - n] = 8;
		n++;
	}
}
void bomb_e(int i, int j, int distance)
{

	map1[i][j] = 0;
}
void bomb_e2(int i, int j, int distance)
{

	map2[i][j] = 0;
}

int find_monster()
{
	int result = 0;
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (map1[i][j] == 6)
				result = 1;
		}
	}
	return result;
}

void attack(int n)
{
	if (n == 0)
	{
		if (map2[4][6] == 0 || map2[4][6] == 4 || map2[4][6] == 5)
			map2[4][6] = 7;
		if (map2[4][13] == 0 || map2[4][13] == 4 || map2[4][13] == 5)
			map2[4][13] = 7;
		if (map2[10][6] == 0 || map2[10][6] == 4 || map2[10][6] == 5)
			map2[10][6] = 7;
		if (map2[10][13] == 0 || map2[10][13] == 4 || map2[10][13] == 5)
			map2[10][13] = 7;
	}
	else if (n == 1)
	{
		if (map2[3][3] == 0 || map2[3][3] == 4 || map2[3][3] == 5)
			map2[3][3] = 7;
		if (map2[11][3] == 0 || map2[11][3] == 4 || map2[11][3] == 5)
			map2[11][3] = 7;
		if (map2[3][16] == 0 || map2[3][16] == 4 || map2[3][16] == 5)
			map2[3][16] = 7;
		if (map2[11][16] == 0 || map2[11][16] == 4 || map2[11][16] == 5)
			map2[11][16] = 7;
	}
	else if (n == 2)
	{
		if (map2[6][5] == 0 || map2[6][5] == 4 || map2[6][5] == 5)
			map2[6][5] = 7;
		if (map2[8][5] == 0 || map2[8][5] == 4 || map2[8][5] == 5)
			map2[8][5] = 7;
		if (map2[6][14] == 0 || map2[6][14] == 4 || map2[6][14] == 5)
			map2[6][14] = 7;
		if (map2[8][14] == 0 || map2[8][14] == 4 || map2[8][14] == 5)
			map2[8][14] = 7;
		if (map2[7][8] == 0 || map2[7][8] == 4 || map2[7][8] == 5)
			map2[7][8] = 7;
		if (map2[7][11] == 0 || map2[7][11] == 4 || map2[7][11] == 5)
			map2[7][11] = 7;
	}

}

void show_life(int count,int obj) // obj가 0이면 user, obj가 1이면 boss
{
	if (obj == 0)
	{
		for (int i = 0; i < count; i++)
		{

			textcolor(12, 12);
			printf("■");
			textcolor(0, 15);
		}
	}
	else if(obj == 1)
	{
		for (int i = 0; i < count; i++)
		{
			textcolor(5, 5);
			printf("■");
			textcolor(0, 15);
		}
	}
}
//////////////////////////게임 종료 애니메이션 구현
void win()
{
	cls(15, 0);
	int timer = time(NULL);
	int c = 1;
	while (1)
	{
		c++;
		int runtime = time(NULL);
		int duration = runtime - timer;
		gotoxy(70, 0);
		if (duration >= 12) break;
		if (duration < 2)
		{
			textcolor(12, 0);
			gotoxy(30, 14); printf("        ####### \n");
			gotoxy(30, 15); printf("       ##◑#####\n");
			gotoxy(30, 16); printf("       #########\n");
			gotoxy(30, 17); printf("#      ###      \n");
			gotoxy(30, 18); printf("##     #######  \n");
			gotoxy(30, 19); printf("###   #####     \n");
			gotoxy(30, 20); printf(" ##  #######▶  \n");
			gotoxy(30, 21); printf("  #########     \n");
			gotoxy(30, 22); printf("    #######     \n");
			gotoxy(30, 23); printf("     #   #      \n");
			gotoxy(30, 24); printf("     ##  ##      ");
			//textcolor(0, 15);
			textcolor(6, 6);
			gotoxy(23, 25); printf("■■■■■■■■■■■■■■■");
			gotoxy(23, 26); printf("■■■■■■■■■■■■■■■");
			gotoxy(23, 27); printf("■■■■■■■■■■■■■■■");
			textcolor(0, 15);
		}
		else if (duration >= 2 && duration < 4)
		{
			textcolor(9, 9);
			for (int i = 0; i <= 6; i++)
			{
				gotoxy(30, i);
				printf("■■■■■■■■■");
			}
			textcolor(12, 0);
			gotoxy(30, 14); printf("        ####### \n");
			gotoxy(30, 15); printf("       ##◑#####\n");
			gotoxy(30, 16); printf("       #########\n");
			gotoxy(30, 17); printf("#      ###      \n");
			gotoxy(30, 18); printf("##     #######  \n");
			gotoxy(30, 19); printf("###   #####     \n");
			gotoxy(30, 20); printf(" ##  #######▶  \n");
			gotoxy(30, 21); printf("  #########     \n");
			gotoxy(30, 22); printf("    #######     \n");
			gotoxy(30, 23); printf("     #   #     \n");
			gotoxy(30, 24); printf("     ##  ##      ");
			textcolor(0, 15);
		}
		else if (duration >= 4 && duration < 6)
		{
			for (int i = 0; i < 3; i++)
			{
				gotoxy(30, i);
				textcolor(0, 0);
				printf("                            ");
			}
			for (int i = 6; i <= 13; i++)
			{

				textcolor(9, 9);

				gotoxy(30, i);
				printf("■■■■■■■■■");
			}
			textcolor(12, 0);
			gotoxy(30, 14); printf("        ####### \n");
			gotoxy(30, 15); printf("       ##◑#####\n");
			gotoxy(30, 16); printf("       #########\n");
			gotoxy(30, 17); printf("#      ###      \n");
			gotoxy(30, 18); printf("##     #######  \n");
			gotoxy(30, 19); printf("###   #####     \n");
			gotoxy(30, 20); printf(" ##  #######▶  \n");
			gotoxy(30, 21); printf("  #########     \n");
			gotoxy(30, 22); printf("    #######     \n");
			gotoxy(30, 23); printf("     #   #     \n");
			gotoxy(30, 24); printf("     ##  ##      ");
			textcolor(0, 15);
		}
		else if (duration >= 6 && duration <= 7)
		{
			for (int i = 0; i < 12; i++)
			{
				textcolor(0, 0);
				gotoxy(30, i);
				printf("                            ");
			}
			textcolor(9, 9);
			for (int i = 12; i <= 13; i++)
			{
				textcolor(0, 0);
				gotoxy(30, i);
				printf("■■■■■■■■■");
			}
			textcolor(12, 9);
			gotoxy(30, 14); printf("         #######  \n");
			gotoxy(30, 15); printf("        ##◑##### \n");
			gotoxy(30, 16); printf("        ######### \n");
			gotoxy(30, 17); printf(" #      ###       \n");
			gotoxy(30, 18); printf(" ##     #######   \n");
			gotoxy(30, 19); printf(" ###   #####      \n");
			gotoxy(30, 20); printf("  ##  #######▶   \n");
			gotoxy(30, 21); printf("   #########      \n");
			gotoxy(30, 22); printf("     #######      \n");
			gotoxy(30, 23); printf("      #   #       \n");
			gotoxy(30, 24); printf("      ##  ##      ");
			textcolor(0, 15);
		}
		else if (duration>7)
		{
		for (int i = 0; i < 12; i++)
		{
			textcolor(0, 0);
			gotoxy(30, i);
			printf("                            ");
		}
		textcolor(9, 9);
		for (int i = 12; i <= 13; i++)
		{
			textcolor(0, 0);
			gotoxy(30, i);
			printf("■■■■■■■■■");
		}
		textcolor(12, 9);
		gotoxy(30, 14); printf("         #######  \n");
		gotoxy(30, 15); printf("        ##Χ##### \n");
		gotoxy(30, 16); printf("        ######### \n");
		gotoxy(30, 17); printf(" #      ###       \n");
		gotoxy(30, 18); printf(" ##     #######   \n");
		gotoxy(30, 19); printf(" ###   #####      \n");
		gotoxy(30, 20); printf("  ##  #######▶   \n");
		gotoxy(30, 21); printf("   #########      \n");
		gotoxy(30, 22); printf("     #######      \n");
		gotoxy(30, 23); printf("      #   #       \n");
		gotoxy(30, 24); printf("      ##  ##      ");
		textcolor(0, 15);
				
		textcolor(14, 8);
		gotoxy(70, 10); printf("  The Winner is  \n");
		gotoxy(70, 11); printf("      Player     \n");
		gotoxy(70, 12); printf("  Congratuation! \n");
		textcolor(0, 15);
		}		
	}
	gotoxy(70, 20);
}
void die_bomb()
{
	cls(15, 0);
	int timer = time(NULL);
	int c = 0; int d = 0;
	while (1)
	{

		int runtime = time(NULL);
		int duration = runtime - timer;
		gotoxy(70, 0);
		if (duration >= 15) break;
		if (duration < 2)
		{
			textcolor(2, 0);
			gotoxy(51, 20);	printf("★");
			textcolor(6, 6);
			gotoxy(39, 21);	printf("■■■■■■■■■■■■■");
			gotoxy(39, 22);	printf("■■■■■■■■■■■■■");
			gotoxy(39, 23);	printf("■■■■■■■■■■■■■");
			textcolor(0, 15);
		}
		else if (duration >= 1 && duration<4)
		{
			textcolor(3, 3);
			gotoxy(45, 10);	printf("■■■■■■■");
			gotoxy(45, 11);	printf("■■■■■■■");
			gotoxy(45, 12);	printf("■■■■■■■");
			textcolor(0, 15);
		}
		else if (duration >= 4 && duration < 6)
		{
			textcolor(3, 3);
			gotoxy(45, 13);	printf("■■■■■■■");
			gotoxy(45, 14);	printf("■■■■■■■");
			gotoxy(45, 15);	printf("■■■■■■■");
			textcolor(0, 15);
			
			if (duration % 2 == 0)
			{
				textcolor(2, 0);
				gotoxy(51, 19);	printf("★");
				textcolor(0, 0);
				gotoxy(51, 20); printf("  ");
				textcolor(0, 15);
			}
			else if (duration % 2 == 1)
			{
				textcolor(2, 0);
				gotoxy(51, 20);	printf("★");
				textcolor(0, 0);
				gotoxy(51, 19); printf("  ");
				textcolor(0, 15);
			}
		}
		else if (duration >= 6 && duration < 9)
		{
			textcolor(0, 0);
			gotoxy(45, 10);	printf("              ");
			gotoxy(45, 11);	printf("              ");
			gotoxy(45, 12);	printf("              ");
			textcolor(3, 3);
			gotoxy(45, 16);	printf("■■■■■■■");
			gotoxy(45, 17);	printf("■■■■■■■");
			gotoxy(45, 18);	printf("■■■■■■■");
			textcolor(0, 15);
			if (duration % 2 == 0)
			{
				textcolor(2, 0);
				gotoxy(51, 19);	printf("★");
				textcolor(0, 0);
				gotoxy(51, 20); printf("  ");
				textcolor(0, 15);
			}
			else if (duration % 2 == 1)
			{
				textcolor(2, 0);
				gotoxy(51, 20);	printf("★");
				textcolor(0, 0);
				gotoxy(51, 19); printf("  ");
				textcolor(0, 15);
			}
		}
		else if (duration >= 9 && duration < 12)
		{
			textcolor(3, 3);
			gotoxy(45, 19);	printf("■■■★■■■");
			gotoxy(45, 20);	printf("■■■■■■■");
			textcolor(1, 3);
			gotoxy(51, 19);	printf("★");
		}
		else
		{
			textcolor(4, 3);
			gotoxy(51, 19);	printf("★");
			textcolor(14, 8);
			gotoxy(70, 10); printf("  The Winner is  \n");
			gotoxy(70, 11); printf("     Monster..   \n");
			gotoxy(70, 12); printf("     You Lose    \n");
			gotoxy(70, 13); printf("      ㅠㅡㅠ     \n");
			textcolor(0, 15);
		}

	}
	gotoxy(70, 20);
}
void die_boss()
{
	cls(WHITE, BLACK);
	int timer = time(NULL);
	int c = 0;
	while (1)
	{
		int runtime = time(NULL);
		int duration = runtime - timer;
		gotoxy(70, 0);
		if (duration >= 17) break;
		if (duration < 2)
		{
			textcolor(6, 6);
			gotoxy(23, 25); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
			gotoxy(23, 26); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
			gotoxy(23, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
			textcolor(0, 15);
		}
		else if (duration >= 2 && duration < 4)
		{
			textcolor(12, 0);
			gotoxy(30, 14); printf("        ####### \n");
			gotoxy(30, 15); printf("       ##◑#####\n");
			gotoxy(30, 16); printf("       #########\n");
			gotoxy(30, 17); printf("#      ###      \n");
			gotoxy(30, 18); printf("##     #######  \n");
			gotoxy(30, 19); printf("###   #####     \n");
			gotoxy(30, 20); printf(" ##  #######▶  \n");
			gotoxy(30, 21); printf("  #########     \n");
			gotoxy(30, 22); printf("    #######     \n");
			gotoxy(30, 23); printf("     #   #      \n");
			gotoxy(30, 24); printf("     ##  ##      ");
			textcolor(2, 0);
			gotoxy(60, 17); printf("★");
			textcolor(0, 15);
		}
		else if (duration >= 4&& duration<5)
		{
			textcolor(12, 0);
			gotoxy(41, 17); printf("∈■■■≫");
			textcolor(0, 15);
		}
		else if (duration >= 5 && duration <14)
		{
			{
				textcolor(0, 0);
				gotoxy(duration + 36, 17); printf(" ");
				textcolor(12, 0);
				gotoxy(duration + 37, 17); printf("∈■■■≫");
				textcolor(0, 15);
			}
		}
		else if (duration >= 14)
		{
			textcolor(0, 0);
			gotoxy(50, 17); printf("         ");
			textcolor(4, 0);
			gotoxy(60, 17); printf("★");
			textcolor(12, 0);
			gotoxy(39, 15); printf("＾");

			textcolor(14, 8);
			gotoxy(70, 10); printf("      Player became      \n");
			gotoxy(70, 11); printf("     Monster's dinner..  \n");
			gotoxy(70, 12); printf("        You lose         \n");
			textcolor(0, 15);
		}

	}
}
void game_rule()
{
	//cls(15, 0);
	PlaySound(TEXT("rule.wav"), NULL, SND_ASYNC | SND_LOOP);
	char ch;
	while (1)
	{
		if (kbhit() == 1)
		{
			ch = getch();
			if (ch == 13)
				break;
		}
		

		textcolor(6, 0);
		gotoxy(31, 4);	printf("◀◀◀◀◀G A M E  G U I D E▶▶▶▶▶");

		textcolor(15, 0);
		gotoxy(5, 10);	printf("물풍선 폭발에 맞으면 life가 감소합니다.");
		gotoxy(5, 11);	printf("life가 다 떨어지면 패배 합니다.");
		textcolor(12, 0);
		gotoxy(5, 14);	printf("♥");
		textcolor(15, 0);
		gotoxy(7, 14);	printf("아이템을 먹으면 life가 증가합니다.");
		textcolor(12, 0);
		gotoxy(5, 18);	printf("♥");
		textcolor(15, 0);
		gotoxy(7, 18);	printf("life는 최대 3을 넘길 수 없습니다.");

		gotoxy(55, 10);	printf("P를 눌러 물풍선을 설치할 수 있습니다.");
		textcolor(15, 9);
		gotoxy(55, 14);	printf("Д");
		textcolor(15, 0);
		gotoxy(57, 14);	printf("아이템을 먹으면 폭탄의 범위가 증가합니다.");
		gotoxy(55, 18);	printf("폭탄의 범위는 4를 넘길 수 없습니다.");
		
		gotoxy(20, 22);	printf("폭탄으로 Boss를 공격해 Boss의 체력을 다 떨어트리면 승리합니다!");
		gotoxy(20, 23);	printf("Boss는 "); textcolor(4, 0); 
		gotoxy(27, 23); printf("●"); textcolor(15, 0);  printf("로 플레이어를 공격할 수 있습니다.");
		gotoxy(20, 24);	printf("Boss의 공격은 플레이어의 공격을 무력화 시킬 수 있습니다.");
		textcolor(4, 0);
		gotoxy(20, 25);	printf("※Boss와 부딪히면 Boss에게 잡아먹혀 바로 죽게됩니다...");

		textcolor(8, 0);
		gotoxy(78, 28);	printf("(press ENTER to out)");

		Sleep(Delay);
	}

}
int start_menu()
{
	textcolor(1, 0);
	gotoxy(18, 3);	printf(" ■■■■    ■■■■         ■        ■■■■■    ■      ■");
	gotoxy(18, 4);	printf("■           ■     ■      ■  ■             ■      ■    ■ ");
	gotoxy(18, 5);	printf("■           ■■■■      ■    ■          ■         ■  ■  ");
	gotoxy(18, 6);	printf("■           ■   ■      ■■■■■       ■             ■    ");
	gotoxy(18, 7);	printf("■           ■    ■     ■      ■     ■               ■    ");
	gotoxy(18, 8);	printf(" ■■■■    ■     ■    ■      ■    ■■■■■        ■    ");

	gotoxy(12, 10);	printf("    ■         ■■■■      ■■■■        ■        ■■■■      ■■■■");
	gotoxy(12, 11); printf("  ■  ■       ■     ■    ■             ■  ■      ■      ■    ■      ");
	gotoxy(12, 12); printf(" ■    ■      ■■■■     ■            ■    ■     ■      ■    ■■■■");
	gotoxy(12, 13); printf("■■■■■     ■   ■      ■           ■■■■■    ■      ■    ■      ");
	gotoxy(12, 14); printf("■      ■     ■    ■     ■           ■      ■    ■      ■    ■      ");
	gotoxy(12, 15); printf("■      ■     ■     ■     ■■■■    ■      ■    ■■■■      ■■■■");

	textcolor(15, 0);
	gotoxy(45, 20);	printf("게임 설명");
	gotoxy(45, 21); printf("연습 모드");
	gotoxy(45, 22);	printf("보스 모드");
	gotoxy(45, 23);	printf("게임 종료");
	gotoxy(43, 20); printf("▶");
	PlaySound(TEXT("login.wav"), NULL, SND_ASYNC | SND_LOOP);

	int x=43, y=20;
	while(1)
	{
		int timer = time(NULL); char n = getch();

		switch (n)
		{
		case UP:
			if (y > 20)
			{
				gotoxy(x, y);	printf("  ");
				gotoxy(x, --y);	printf("▶");
			}
			else
			{
				break;
			}
			break;

		case DOWN:
			if (y < 23)
			{
				gotoxy(x, y);	printf("  ");
				gotoxy(x, ++y);	printf("▶");
			}
			else
			{
				break;
			}
			break;
		case 13:
			return y;
		}
	}
}
void game_end()
{
	PlaySound(TEXT("Everything we talked about"), NULL, SND_ASYNC | SND_LOOP);
	cls(15, 0);
	textcolor(1, 0);
	int timer = time(NULL);
	while (1)
	{
		int time_now = time(NULL);
		int duration = time_now - timer;
		if (duration % 4 == 0) textcolor(1, 0);		//blue1
		if (duration % 4 == 1) textcolor(2, 0);		//green1
		if (duration % 4 == 2) textcolor(6, 0);		//yellow1
		if (duration % 4 == 3) textcolor(12, 0);	//red2
		if (duration>=1 && duration < 2)
		{
			gotoxy(13, 5);	printf("■■■■    ■■■■    ■■■■");
			gotoxy(13, 6);	printf("■          ■          ■      ");
			gotoxy(13, 7);	printf("■■■■    ■■■■    ■■■■");
			gotoxy(13, 8);	printf("      ■    ■          ■		");
			gotoxy(13, 9);	printf("■■■■    ■■■■    ■■■■");
		}
		else if (duration >= 2 && duration < 3)
		{
			gotoxy(13, 5);	printf("■■■■    ■■■■    ■■■■");
			gotoxy(13, 6);	printf("■          ■          ■      ");
			gotoxy(13, 7);	printf("■■■■    ■■■■    ■■■■");
			gotoxy(13, 8);	printf("      ■    ■          ■		");
			gotoxy(13, 9);	printf("■■■■    ■■■■    ■■■■");

			gotoxy(56, 5);	printf("■    ■     ■■■     ■    ■");
			gotoxy(56, 6);	printf(" ■  ■     ■    ■    ■    ■");
			gotoxy(56, 7);	printf("  ■■      ■    ■    ■    ■");
			gotoxy(56, 8);	printf("   ■       ■    ■    ■    ■");
			gotoxy(56, 9);	printf("   ■        ■■■      ■■■ ");
		}
		else if (duration >= 3)
		{
			gotoxy(13, 5);	printf("■■■■    ■■■■    ■■■■");
			gotoxy(13, 6);	printf("■          ■          ■      ");
			gotoxy(13, 7);	printf("■■■■    ■■■■    ■■■■");
			gotoxy(13, 8);	printf("      ■    ■          ■		");
			gotoxy(13, 9);	printf("■■■■    ■■■■    ■■■■");

			gotoxy(56, 5);	printf("■    ■     ■■■     ■    ■");
			gotoxy(56, 6);	printf(" ■  ■     ■    ■    ■    ■");
			gotoxy(56, 7);	printf("  ■■      ■    ■    ■    ■");
			gotoxy(56, 8);	printf("   ■       ■    ■    ■    ■");
			gotoxy(56, 9);	printf("   ■        ■■■      ■■■ ");

			if (duration % 4 == 0) textcolor(6, 0);	//blue1
			if (duration % 4 == 1) textcolor(12, 0);		//green1
			if (duration % 4 == 2) textcolor(1, 0);		//yellow1
			if (duration % 4 == 3) textcolor(2, 0);		//red2

			gotoxy(12, 15);	printf("     ■          ■■■■        ■        ■■■■■    ■■      ■      ■");
			gotoxy(12, 16);	printf("   ■  ■      ■              ■  ■          ■        ■ ■     ■      ■");
			gotoxy(12, 17); printf("  ■    ■     ■             ■    ■         ■        ■  ■    ■      ■");
			gotoxy(12, 18);	printf(" ■      ■    ■  ■■■    ■      ■        ■        ■   ■   ■      ■");
			gotoxy(12, 19);	printf(" ■■■■■    ■  ■  ■    ■■■■■        ■        ■    ■  ■      ■");
			gotoxy(12, 20);	printf(" ■      ■    ■      ■    ■      ■        ■        ■     ■ ■        ");
			gotoxy(12, 21);	printf(" ■      ■      ■■■■    ■      ■    ■■■■■    ■      ■■      ■");

		}
		if (duration > 10)
		{
			textcolor(15, 0);
			gotoxy(45, 25);
			printf("Thanks To Play!\n");
			gotoxy(70, 26);
			printf("Prees any key to quit\n");
			textcolor(7, 0);
			gotoxy(70, 28);
			if (kbhit() == 1)
				break;
		}
	}
}

void gamestart1()
{
	PlaySound(TEXT("start1.wav"), NULL, SND_ASYNC | SND_LOOP);
	init_map1();
	srand((unsigned)time(NULL));
	unsigned char ch;
	int keep_moving = 0;
	int start_time, run_time, bomb_end, duration;
	int bomb_start[100];
	int bomb_count = 0;

	int bomb_on_off = 0;
	start_time = time(NULL);
	int item, item1_x, item1_y;
	item1_x = 8; item1_y = 10;
	map1[item1_x][item1_y] = 4;

	newx = oldx = userx = 1;	newy = oldy = usery = 1;
	ch = 0;
	unsigned char pastch = 0;
	int life_count = 1;
	int distance = 1;
	// 몬스터 생성
	int testmonster = 1;
	int monster_count = 0;
	//map1[3][3] = 6;
	while (life_count != 0)
	{
		gotoxy(0, 0);
		create_map1(); //맵 그리기

		run_time = time(NULL);
		duration = run_time - start_time; //duration=시작 후 흐른 시간
		show_time(999-duration);
		if (duration >= 999)
			break;

		if (kbhit() == 1) {  // 키보드가 눌려져 있으면
			ch = getch(); // key 값을 읽는다
			if (ch == ESC) //ESC 누르면 프로그램 종료
				break;

			//방향키로 움직임, 벽은 이동 불가
			if (ch == SPECIAL1 || ch == SPECIAL2)
			{
				ch = getch();
				switch (ch)
				{
				case UP:
					if (map1[oldx - 1][oldy] == 1) //가려고 하는 곳이 벽이면
					{
						pastch = map1[oldx - 1][oldy];
						map1[oldx - 1][oldy] = pastch;
						map1[oldx][oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
					else if (map1[oldx - 1][oldy] == 6) //몬스터에 닿으면
					{
						life_count = 0;
						break;
					}
					else if (map1[oldx - 1][oldy] == 3) //물줄기에 닿으면
					{
						life_count = 0;
						break;
					}
					else if (map1[oldx - 1][oldy] == 4) //물줄기 증가 아이템 먹으면
					{
						pastch = map1[oldx][oldy];
						map1[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map1[oldx][oldy] = 0;
						}
						oldx -= 1;
						map1[oldx][oldy] = 9;
						userx = oldx; usery = oldy;

						distance += 1;
						break;
					}
					else
					{
						pastch = map1[oldx][oldy];
						map1[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map1[oldx][oldy] = 0;
						}
						oldx -= 1;
						map1[oldx][oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
				case DOWN:
					if (map1[oldx + 1][oldy] == 1)
					{
						pastch = map1[oldx + 1][oldy];
						map1[oldx + 1][oldy] = pastch;
						map1[oldx][oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
					else if (map1[oldx + 1][oldy] == 6)
					{

						life_count = 0;
						break;
					}
					else if (map1[oldx + 1][oldy] == 3)
					{
						life_count = 0;
						break;
					}
					else if (map1[oldx + 1][oldy] == 4)
					{
						pastch = map1[oldx][oldy];
						map1[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map1[oldx][oldy] = 0;
						}
						map1[++oldx][oldy] = 9;
						userx = oldx; usery = oldy;

						distance += 1;
						break;
					}
					else
					{
						pastch = map1[oldx][oldy];
						map1[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map1[oldx][oldy] = 0;
						}
						map1[++oldx][oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
				case LEFT:
					if (map1[oldx][oldy - 1] == 1)
					{
						pastch = map1[oldx][oldy - 1];
						map1[oldx][oldy - 1] == pastch;
						map1[oldx][oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
					else if (map1[oldx][oldy - 1] == 6)
					{
						life_count = 0;
						break;
					}
					else if (map1[oldx][oldy - 1] == 3)
					{
						life_count = 0;
						break;
					}
					else if (map1[oldx][oldy - 1] == 4)
					{
						pastch = map1[oldx][oldy];
						map1[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map1[oldx][oldy] = 0;
						}
						map1[oldx][--oldy] = 9;
						userx = oldx; usery = oldy;

						distance += 1;
						break;
					}
					else
					{
						pastch = map1[oldx][oldy];
						map1[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map1[oldx][oldy] = 0;
						}
						map1[oldx][--oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
				case RIGHT:
					if (map1[oldx][oldy + 1] == 1)
					{
						pastch = map1[oldx][oldy + 1];
						map1[oldx][oldy + 1] == pastch;
						map1[oldx][oldy] == 9;
						userx = oldx; usery = oldy;
						break;
					}
					else if (map1[oldx][oldy + 1] == 6)
					{
						life_count = 0;
						break;
					}
					else if (map1[oldx][oldy + 1] == 3)
					{
						life_count = 0;
						break;
					}
					else if (map1[oldx][oldy + 1] == 4)
					{
						pastch = map1[oldx][oldy];
						map1[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map1[oldx][oldy] = 0;
						}
						map1[oldx][++oldy] = 9;
						userx = oldx; usery = oldy;

						distance += 1;
						break;
					}
					else
					{
						pastch = map1[oldx][oldy];
						map1[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map1[oldx][oldy] = 0;
						}
						map1[oldx][++oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
				}

			}//방향키로 움직이기

			switch (ch)
			{
			case BOMB:
				map1[oldx][oldy] = 2;
				newx = oldx; newy = oldy;

				bomb_on_off = 1;
				bomb_start[++bomb_count] = duration;
				break;
			}

		} //player 동작 구현 끝

		bomb_end = time(NULL);

		//맵1에서 폭탄을 찾는다
		for (int j = 1; j < HEIGHT; j++)
		{
			for (int i = 1; i < WIDTH; i++)
			{
				if (map1[j][i] == 2 && duration>=bomb_start[bomb_count]+3) //map[j][i]가 폭탄이면 4초 후 터트림
				{
					bomb_s(j, i, distance);
				}
				if (map1[j][i] == 3 &&duration>=bomb_start[bomb_count]+4) //map[j][i]가 물줄기면 폭탄 터지고 2초 후 사라짐
				{
					bomb_e(j, i, distance);
				}
			}
		}
		////////////////////////find_monster();
		int op = 0;
		int result = find_monster();

		//몬스터 다 잡고 끝남
		if (map1[3][3] == 0 && map1[13][1] == 0 && map1[11][10] == 0 && map1[13][18] == 0 && map1[1][18] == 0)
		{
			break;
		}
		/////////////////////

		//폭탄 맞고 끝남
		if (map1[userx][usery] == 3)
		{
			break;
		}
		/////////////////////

		Sleep(Delay); // Delay를 줄이면 속도가 빨라진다.
	}
	cls(15, 0);
	while (1)
	{
		gotoxy(40, 11);
		printf("It Was Just Test!\n");
		gotoxy(36, 15);
		printf("Press ENTER to back to menu\n");
		char ch = getch();
		if (ch == 13)
			break;
	}
}

void gamestart2()//////////////////////////////////////////////////////////////////////////////////////////
{
	PlaySound(TEXT("start2.wav"), NULL, SND_ASYNC | SND_LOOP);
	cls(15, 0);
	init_map2();

	srand((unsigned)time(NULL));
	unsigned char ch;
	int keep_moving = 0;
	int start_time, run_time, bomb_end, duration;
	int bomb_start[100];
	int bomb_count = 0;
	int boss_bomb;

	int bomb_on_off = 0;
	start_time = time(NULL);
	int item, item1_x, item1_y;
	item1_x = 9; item1_y = 10;

	newx = oldx = userx = 7;	newy = oldy = usery = 4;
	ch = 0;
	unsigned char pastch = 0;
	unsigned char boss_pastch = 0;
	int life_count = 1; //user life
	int distance = 1; //user bomb distance

	// 몬스터 생성
	enemy boss;
	boss.enemy_x = 7;
	boss.enemy_y = 10;
	map2[boss.enemy_x][boss.enemy_y] = 6;
	boss.life = 10;
	boss.boss_distance = 1;

	int by = 0;

	while (life_count != 0)
	{
		run_time = time(NULL);
		duration = run_time - start_time; //duration=시작 후 흐른 시간
		
		show_time(90-duration);
		if (duration >= 90)
			break;

		if (distance > 4) //distance 범위는 최대 4
			distance = 4;
		if (life_count > 3) //life는 최대 3
			life_count = 3;
		
		

		///////////////////////////////// 아이템 랜덤 생성if(duration%15==14)/////////////////////////////////////////////////////////////////////////
		if (duration % 7 == 6)
		{
			int item_rand_make;
			item_rand_make = rand() % 6; //distance증가0 life증가1
			int item_x = rand() % 18 + 1;
			int item_y = rand() % 13 + 1;
			if (item_rand_make == 0 && distance < 5 && map2[item_x][item_y] == 0) //랜덤값0 distance<5 생성하려는 곳이 빈칸
			{
				map2[item_x][item_y] = 4;
			}
			if (item_rand_make == 1 && life_count < 3 && map2[item_x][item_y] == 0)
			{
				map2[item_x][item_y] = 5;
			}
		}
		//////////////////////////////////몬스터 움직임 구현
		if (duration % 2 == 1)
		{
			int boss_rand_move;
			boss_rand_move = rand() % 6; //상0 하1 좌2 우3 가운데4~5
			switch (boss_rand_move)
			{
			case 0: //상
				if (map2[boss.enemy_x - 1][boss.enemy_y] == 1 || map2[boss.enemy_x - 1][boss.enemy_y] == 2 || map2[boss.enemy_x-1][boss.enemy_y]==7) //가려는 곳이 벽
				{
					break;
				}
				else if (map2[boss.enemy_x - 1][boss.enemy_y] == 3) //물줄기에 닿으면
				{
					boss.life--;
					break;
				}
				else
				{
					boss_pastch = map2[boss.enemy_x][boss.enemy_y];
					map2[boss.enemy_x][boss.enemy_y] = boss_pastch;
					if (boss_pastch == 6)
					{
						map2[boss.enemy_x][boss.enemy_y] = 0;
					}
					boss.enemy_x -= 1;
					map2[boss.enemy_x][boss.enemy_y] = 6;
					break;
				}
			case 1: //하
				if (map2[boss.enemy_x + 1][boss.enemy_y] == 1 || map2[boss.enemy_x + 1][boss.enemy_y] == 2 || map2[boss.enemy_x + 1][boss.enemy_y] == 7) //가려는 곳이 벽
				{
					break;
				}
				else if (map2[boss.enemy_x + 1][boss.enemy_y] == 3) //물줄기에 닿으면
				{
					boss.life--;
					break;
				}
				else
				{
					boss_pastch = map2[boss.enemy_x][boss.enemy_y];
					map2[boss.enemy_x][boss.enemy_y] = boss_pastch;
					if (boss_pastch == 6)
					{
						map2[boss.enemy_x][boss.enemy_y] = 0;
					}
					boss.enemy_x += 1;
					map2[boss.enemy_x][boss.enemy_y] = 6;
					break;
				}
			case 2: //좌
				if (map2[boss.enemy_x][boss.enemy_y - 1] == 1 || map2[boss.enemy_x][boss.enemy_y - 1] == 2 || map2[boss.enemy_x][boss.enemy_y - 1] == 7) //가려는 곳이 벽
				{
					break;
				}
				else if (map2[boss.enemy_x][boss.enemy_y - 1] == 3) //물줄기에 닿으면
				{
					boss.life--;
					break;
				}
				else
				{
					boss_pastch = map2[boss.enemy_x][boss.enemy_y];
					map2[boss.enemy_x][boss.enemy_y] = boss_pastch;
					if (boss_pastch == 6)
					{
						map2[boss.enemy_x][boss.enemy_y] = 0;
					}
					boss.enemy_y -= 1;
					map2[boss.enemy_x][boss.enemy_y] = 6;
					break;
				}
			case 3: //우
				if (map2[boss.enemy_x][boss.enemy_y + 1] == 1 || map2[boss.enemy_x][boss.enemy_y + 1] == 2 || map2[boss.enemy_x][boss.enemy_y + 1] == 7) //가려는 곳이 벽
				{
					break;
				}
				else if (map2[boss.enemy_x][boss.enemy_y + 1] == 3) //물줄기에 닿으면
				{
					boss.life--;
					break;
				}
				else
				{
					boss_pastch = map2[boss.enemy_x][boss.enemy_y];
					map2[boss.enemy_x][boss.enemy_y] = boss_pastch;
					if (boss_pastch == 6)
					{
						map2[boss.enemy_x][boss.enemy_y] = 0;
					}
					boss.enemy_y += 1;
					map2[boss.enemy_x][boss.enemy_y] = 6;
					break;
				}
			case 4: //가운데
			case 5:
				//case 6:
				break;
			}
		}


		//////////////////////////////////////몬스터가 물줄기에 맞는거 구현
		if (map2[boss.enemy_x][boss.enemy_y] == 3)
		{
			Sleep(1000);
			boss.life--;
		}

		/////////////////////////////////////////boss.life=0이면 user 승리
		if (boss.life <= 0)
		{
			cls(0, 0);
			win();
			break;
		}

		/////////////////////////////////////////boss가 user에 부딪히면 종료
		if (boss.enemy_x == userx && boss.enemy_y == usery)
		{
			life_count = 0;
			cls(0, 0);
			die_boss();
			break;
		}

		if (kbhit() == 1) {  // 키보드가 눌려져 있으면
			ch = getch(); // key 값을 읽는다
			if (ch == ESC) //ESC 누르면 프로그램 종료
				break;

			//방향키로 움직임, 벽은 이동 불가
			if (ch == SPECIAL1 || ch == SPECIAL2)
			{
				ch = getch();
				switch (ch)
				{
				case UP:
					if (map2[oldx - 1][oldy] == 1 || map2[oldx - 1][oldy] == 2 || map2[oldx - 1][oldy] == 7) //가려고 하는 곳이 벽이나 폭탄이면
					{
						pastch = map2[oldx - 1][oldy];
						map2[oldx - 1][oldy] = pastch;
						map2[oldx][oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
					else if (map2[oldx - 1][oldy] == 6) //몬스터에 닿으면
					{
						by = 1;
						life_count = 0;
						break;
					}
					else if (map2[oldx - 1][oldy] == 3 || map2[oldx - 1][oldy] == 8) //물줄기에 닿으면
					{
						life_count -= 1;
						break;
					}
					else if (map2[oldx - 1][oldy] == 4) //물줄기 증가 아이템 먹으면
					{
						pastch = map2[oldx][oldy];
						map2[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map2[oldx][oldy] = 0;
						}
						oldx -= 1;
						map2[oldx][oldy] = 9;
						userx = oldx; usery = oldy;

						distance += 1;
						break;
					}
					else if (map2[oldx - 1][oldy] == 5) //생명 증가 아이템 먹으면
					{
						pastch = map2[oldx][oldy];
						map2[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map2[oldx][oldy] = 0;
						}
						oldx -= 1;
						map2[oldx][oldy] = 9;
						userx = oldx; usery = oldy;

						life_count += 1;
						break;
					}
					else
					{
						pastch = map2[oldx][oldy];
						map2[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map2[oldx][oldy] = 0;
						}
						oldx -= 1;
						map2[oldx][oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
				case DOWN:
					if (map2[oldx + 1][oldy] == 1 || map2[oldx + 1][oldy] == 2 || map2[oldx + 1][oldy] == 7)
					{
						pastch = map2[oldx + 1][oldy];
						map2[oldx + 1][oldy] = pastch;
						map2[oldx][oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
					else if (map2[oldx + 1][oldy] == 6)
					{
						by = 1;
						life_count = 0;
						break;
					}
					else if (map2[oldx + 1][oldy] == 3 || map2[oldx + 1][oldy] == 8)
					{
						life_count -= 1;
						break;
					}
					else if (map2[oldx + 1][oldy] == 4)
					{
						pastch = map2[oldx][oldy];
						map2[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map2[oldx][oldy] = 0;
						}
						map2[++oldx][oldy] = 9;
						userx = oldx; usery = oldy;

						distance += 1;
						break;
					}
					else if (map2[oldx + 1][oldy] == 5)
					{
						pastch = map2[oldx][oldy];
						map2[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map2[oldx][oldy] = 0;
						}
						map2[++oldx][oldy] = 9;
						userx = oldx; usery = oldy;

						life_count += 1;
						break;
					}
					else
					{
						pastch = map2[oldx][oldy];
						map2[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map2[oldx][oldy] = 0;
						}
						map2[++oldx][oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
				case LEFT:
					if (map2[oldx][oldy - 1] == 1 || map2[oldx][oldy - 1] == 2 || map2[oldx][oldy - 1] == 7)
					{
						pastch = map2[oldx][oldy - 1];
						map2[oldx][oldy - 1] == pastch;
						map2[oldx][oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
					else if (map2[oldx][oldy - 1] == 6)
					{
						by = 1;
						life_count = 0;
						break;
					}
					else if (map2[oldx][oldy - 1] == 3 || map2[oldx][oldy - 1] == 8)
					{
						life_count -= 1;
						break;
					}
					else if (map2[oldx][oldy - 1] == 4)
					{
						pastch = map2[oldx][oldy];
						map2[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map2[oldx][oldy] = 0;
						}
						map2[oldx][--oldy] = 9;
						userx = oldx; usery = oldy;

						distance += 1;
						break;
					}
					else if (map2[oldx][oldy - 1] == 5)
					{
						pastch = map2[oldx][oldy];
						map2[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map2[oldx][oldy] = 0;
						}
						map2[oldx][--oldy] = 9;
						userx = oldx; usery = oldy;

						life_count += 1;
						break;
					}
					else
					{
						pastch = map2[oldx][oldy];
						map2[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map2[oldx][oldy] = 0;
						}
						map2[oldx][--oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
				case RIGHT:
					if (map2[oldx][oldy + 1] == 1 || map2[oldx][oldy + 1] == 2 || map2[oldx][oldy + 1] == 7)
					{
						pastch = map2[oldx][oldy + 1];
						map2[oldx][oldy + 1] == pastch;
						map2[oldx][oldy] == 9;
						userx = oldx; usery = oldy;
						break;
					}
					else if (map2[oldx][oldy + 1] == 6)
					{
						by = 1;
						life_count = 0;
						break;
					}
					else if (map2[oldx][oldy + 1] == 3 || map2[oldx][oldy + 1] == 8)
					{
						life_count -= 1;
						break;
					}
					else if (map2[oldx][oldy + 1] == 4)
					{
						pastch = map2[oldx][oldy];
						map2[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map2[oldx][oldy] = 0;
						}
						map2[oldx][++oldy] = 9;
						userx = oldx; usery = oldy;

						distance += 1;
						break;
					}
					else if (map2[oldx][oldy + 1] == 5)
					{
						pastch = map2[oldx][oldy];
						map2[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map2[oldx][oldy] = 0;
						}
						map2[oldx][++oldy] = 9;
						userx = oldx; usery = oldy;

						life_count += 1;
						break;
					}
					else
					{
						pastch = map2[oldx][oldy];
						map2[oldx][oldy] = pastch;
						if (pastch == 9)
						{
							map2[oldx][oldy] = 0;
						}
						map2[oldx][++oldy] = 9;
						userx = oldx; usery = oldy;
						break;
					}
				}

			}//방향키로 움직이기

			switch (ch)
			{
			case BOMB:
				map2[oldx][oldy] = 2;
				newx = oldx; newy = oldy;

				bomb_on_off = 1;
				bomb_start[++bomb_count] = duration;
				break;
			}

		} //player 동작 구현 끝
		/////////////////////////boss에 부딪혀 사망
		if (by == 1)
		{
			die_boss();
			break;
		}

		bomb_end = time(NULL);

		if (duration % 5 == 4) // 5초에 1번 보스 공격 할 수도 있고 안할 수도 있고...
		{
			int boss_attack_rand = rand() % 100;
			
			if (boss_attack_rand < 30)
			{
				int boss_attack_123 = rand() % 6; // 0~2 공격패턴
				switch (boss_attack_123)
				{
				case 0:
					boss.boss_distance = 5;
					attack(0);
					break;
				case 1:
					boss.boss_distance = 6;
					attack(1);
					break;
				case 2:
					boss.boss_distance = 2;
					attack(2);
					break;
				case 3:
				case 4:
				case 5:
					break;
				}
			}
		}

		//맵1에서 폭탄을 찾는다
		for (int j = 1; j < HEIGHT; j++)
		{
			for (int i = 1; i < WIDTH; i++)
			{
				if (map2[j][i] == 2 && duration>=bomb_start[bomb_count]+3) //map[j][i]가 폭탄이면 3초 후 터트림
				{
					bomb_s2(j, i, distance);
				}
				else if (map2[j][i] == 7)
				{
					if (duration % 5 == 1)
					{
						bomb_boss(j, i, boss.boss_distance);
					}
				}
				if (map2[j][i] == 3 && (double)duration >= (double)bomb_start[bomb_count] + 3.5) //map[j][i]가 물줄기면 폭탄 터지고 1초 후 사라짐
				{
					bomb_e2(j, i, distance);
				}
				if (map2[j][i] == 8)
				{
					if (duration % 5 == 2)
					{
						bomb_e2(j, i, boss.boss_distance);
					}
				}
			}
		}


		////////////////////////find_monster();
		int op = 0;
		int result = find_monster();

		/////////////////////
		gotoxy(0, 0);
		create_map2(); //맵 그리기

		///////////////////////////life count 표시
		gotoxy(47, 9);
		textcolor(1, 7);
		printf("※※남은 H P※※");

		gotoxy(47, 11);
		textcolor(2, 7);
		printf("★ ");
		textcolor(0, 0);
		gotoxy(50, 11);
		for (int x = 0; x < 10; x++)
			printf("  ");
		gotoxy(50, 11);
		show_life(life_count, 0); // user의 life 표시 끝

		gotoxy(47, 13);
		textcolor(4, 7);
		printf("★ ");
		textcolor(0, 0);
		gotoxy(50, 13);
		for (int x = 0; x < 10; x++)
			printf("  ");
		gotoxy(50, 13);
		show_life(boss.life, 1); //boss의 life 표시 끝
		//////////////////////////////////////////////

		//폭탄 맞고 끝남/////////////////////////////////////////////////////////////////////////////////////////////////////////////////수정
		if (map2[userx][usery] == 3 || map2[userx][usery]==8)
		{
			Sleep(Delay);
			int life_tmp = life_count - 1;
			life_count = life_tmp;
			Sleep(Delay);
			
		}
		/////////////////////
		if (life_count == 0)
		{
			cls(0, 0);
			die_bomb();
			break;
		}

		Sleep(Delay); // Delay를 줄이면 속도가 빨라진다.
	}
	cls(15, 0);
}
int main()
{
	system("mode con cols=100 lines=30 | title Crazy Arcade");
	removeCursor();
	int menu_num;
	cls(BLACK, WHITE);
	while (1)
	{
		cls(15, 0);
		menu_num = start_menu();
		if (menu_num == 20)
		{
			cls(15, 0);
			game_rule();
			cls(15, 0);
		}
		else if (menu_num == 21)
		{
			cls(15, 0);
			gamestart1();
			cls(15, 0);
		}
		else if (menu_num == 22)
		{
			cls(15, 0);
			gamestart2();
			cls(15, 0);
		}
		else if (menu_num == 23)
		{
			cls(15, 0);
			game_end();
			//cls(15, 0); //작동시키면 see you again 문구 삭제 후 검은 화면에 종료
			break;
		}
	}
	
	// 종료
	textcolor(0, 0);
	gotoxy(60, 27);
	return 0;
}