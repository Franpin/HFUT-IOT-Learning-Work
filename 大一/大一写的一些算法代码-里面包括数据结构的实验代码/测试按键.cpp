#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
using namespace std;
int score = 0;
char game_state = 'Y';
int speed = 500;
int ing_state1 = 1;
int ing_state2 = 1;
int map[23][14] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};//地图
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hout;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);			//控制光标位置 
	SetConsoleCursorPosition(hout, pos);
}
void ConsoleCursor() {
	HANDLE hout;
	CONSOLE_CURSOR_INFO cur;
	cur.dwSize = 1;
	cur.bVisible = 0;									//控制光标属性 
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hout, &cur);
}
void drowmap();
int givebirth();
void getchange();
void getdisappear();
void recall(char input);
void judge();
int main()
{
	while (game_state == 'Y')
	{
		givebirth();
		drowmap();
		if (_kbhit())
		{
			char input = _getch();
			recall(input);
			if (input == 'S')
			{
				Sleep(speed / 5);
			}
		}
		else if (!_kbhit())
		{
			recall('U');
			Sleep(speed);
		}
		judge();
	}
	system("cls");
	cout << "游戏结束，你的得分是：" << score;
}
void drowmap()
{
	getchange();
	gotoxy(0, 0);
	ConsoleCursor();
	for (int x = 3; x < 23; x++)
	{
		for (int y = 0; y < 14; y++)
		{
			switch (map[x][y])
			{
			case 0:cout << "  "; break;
			case 1:cout << "□"; break;
			case 2:cout << "■"; break;//中心点
			case 3:cout << "■"; break;//正在进行方块中心点四周
			case 4:cout << "■"; break;//已落下方块
			}
		}
		cout << endl;
	}
	gotoxy(40, 7);
	cout << "你的得分是：" << score;
	ConsoleCursor();
}
int givebirth()
{
	int if_ing = 0;
	for (int x = 0; x < 23; x++)
	{
		for (int y = 0; y < 14; y++)
		{
			if (map[x][y] == 2)
			{
				if_ing = 1;
			}
			else
				continue;
		}
	}
	if (if_ing == 0)
	{
		map[3][6] = 2;
		srand((unsigned)time(NULL));
		ing_state1 = rand() % 7;
		switch (ing_state1)
		{
		case 0:
			ing_state2 = 1 + rand() % 2;
			break;
		case 1:
			ing_state2 = 1 + rand() % 2;
			break;
		case 2:
			ing_state2 = 1 + rand() % 4;
			break;
		case 3:
			ing_state2 = 1 + rand() % 4;
			break;
		case 4:
			ing_state2 = 1;
			break;
		case 5:
			ing_state2 = 1 + rand() % 2;
			break;
		case 6:
			ing_state2 = 1 + rand() % 4;
			break;
		}
	}
	else
		return 0;
}
void getdisappear()
{
	for (int x = 0; x < 23; x++)
	{
		for (int y = 0; y < 14; y++)
		{
			if (map[x][y] == 3)
			{
				map[x][y] = 0;
			}
		}
	}
}
void getchange()
{
	givebirth();
	int m, n;
	for (int x = 0; x < 23; x++)
	{
		for (int y = 0; y < 14; y++)
		{
		    if (map[x][y] == 2)
			{
				m = x; n = y;
			}
			else
				continue;
		}
	}
	switch (ing_state1)
	{
	case 0:
		if (ing_state2 == 1 && map[m - 2][n - 1] == 0 && map[m - 1][n - 1] == 0 && map[m - 1][n] == 0)
		{
			getdisappear();
			map[m - 2][n - 1] = 3;
			map[m - 1][n - 1] = 3;
			map[m - 1][n] = 3;
		}
		else if (ing_state2 == 2 && map[m][n - 1] == 0 && map[m - 1][n] == 0 && map[m - 1][n + 1] == 0)
		{
			getdisappear();
			map[m][n - 1] = 3;
			map[m - 1][n] = 3;
			map[m - 1][n + 1] = 3;
		}
		break;
	case 1:
		if (ing_state2 == 1 && map[m - 2][n + 1] == 0 && map[m - 1][n + 1] == 0 && map[m - 1][n] == 0)
		{
			getdisappear();
			map[m - 2][n + 1] = 3;
			map[m - 1][n + 1] = 3;
			map[m - 1][n] = 3;
		}
		else if (ing_state2 == 2 && map[m - 1][n - 1] == 0 && map[m - 1][n] == 0 && map[m][n + 1] == 0)
		{
			getdisappear();
			map[m - 1][n - 1] = 3;
			map[m - 1][n] = 3;
			map[m][n + 1] = 3;
		}
		break;
	case 2:
		if (ing_state2 == 1 && map[m - 2][n] == 0 && map[m - 1][n] == 0 && map[m][n + 1] == 0)
		{
			getdisappear();
			map[m - 2][n] = 3;
			map[m - 1][n] = 3;
			map[m][n + 1] = 3;
		}
		else if (ing_state2 == 2 && map[m -1][n] == 0 && map[m - 1][n + 1] == 0 && map[m - 1][n + 2] == 0)
		{
			getdisappear();
			map[m - 1][n] = 3;
			map[m - 1][n + 1] = 3;
			map[m - 1][n + 2] = 3;
		}
		else if (ing_state2 == 3 && map[m - 2][n - 1] == 0 && map[m - 2][n] == 0 && map[m - 1][n] == 0)
		{
			getdisappear();
			map[m - 2][n - 1] = 3;
			map[m - 2][n] = 3;
			map[m - 1][n] = 3;
		}
		else if (ing_state2 == 4 && map[m - 1][n] == 0 && map[m][n - 2] == 0 && map[m][n - 1] == 0)
		{
			getdisappear();
			map[m - 1][n] = 3;
			map[m][n - 2] = 3;
			map[m][n - 1] = 3;
		}
		break;
	case 3:
		if (ing_state2 == 1 && map[m - 2][n] == 0 && map[m - 1][n] == 0 && map[m][n - 1] == 0)
		{
			getdisappear();
			map[m - 2][n] = 3;
			map[m - 1][n] = 3;
			map[m][n - 1] = 3;
		}
		else if (ing_state2 == 2 && map[m][n + 1] == 0 && map[m][n + 2] == 0 && map[m - 1][n] == 0)
		{
			getdisappear();
			map[m][n + 1] = 3;
			map[m][n + 2] = 3;
			map[m - 1][n] = 3;
		}
		else if (ing_state2 == 3 && map[m - 2][n - 1] == 0 && map[m - 2][n] == 0 && map[m - 1][n] == 0)
		{
			getdisappear();
			map[m - 2][n - 1] = 3;
			map[m - 2][n] = 3;
			map[m - 1][n] = 3;
		}
		else if (ing_state2 == 4 && map[m - 1][n] == 0 && map[m - 1][n - 2] == 0 && map[m - 1][n - 1] == 0)
		{
			getdisappear();
			map[m - 1][n] = 3;
			map[m - 1][n - 2] = 3;
			map[m - 1][n - 1] = 3;
		}
		break;
	case 4:
		if (ing_state2 == 1 && map[m][n + 1] == 0 && map[m - 1][n] == 0 && map[m - 1][n + 1] == 0)
		{
			getdisappear();
			map[m][n + 1] = 3;
			map[m - 1][n] = 3;
			map[m - 1][n + 1] = 3;
		}
		break;
	case 5:
	     if (ing_state2 == 1 && map[m - 3][n] == 0 && map[m - 2][n] == 0 && map[m - 1][n] == 0)
		{
			getdisappear();
		    map[m - 1][n] = 3;
			map[m - 2][n] = 3;
			map[m - 3][n] = 3;
		}
		else if (ing_state2 == 2 && map[m][n - 1] == 0 && map[m][n + 1] == 0 && map[m][n + 2] == 0)
		{
			getdisappear();
			map[m][n - 1] = 3;
			map[m][n + 2] = 3;
			map[m][n + 1] = 3;
		}
		
		break;
	case 6:
		if (ing_state2 == 1 && map[m - 1][n] == 0 && map[m][n - 1] == 0 && map[m][n + 1] == 0)
		{
			getdisappear();
			map[m - 1][n] = 3;
			map[m][n - 1] = 3;
			map[m][n + 1] = 3;
		}
		else if (ing_state2 == 2 && map[m - 2][n] == 0 && map[m - 1][n + 1] == 0 && map[m - 1][n] == 0)
		{
			getdisappear();
			map[m - 2][n] = 3;
			map[m - 1][n + 1] = 3;
			map[m - 1][n] = 3;
		}
		else if (ing_state2 == 3 && map[m - 1][n - 1] == 0 && map[m - 1][n] == 0 && map[m - 1][n + 1] == 0)
		{
			getdisappear();
			map[m - 1][n - 1] = 3;
			map[m - 1][n + 1] = 3;
			map[m - 1][n] = 3;
		}
		else if (ing_state2 == 4 && map[m - 1][n] == 0 && map[m - 1][n - 1] == 0 && map[m - 2][n] == 0)
		{
			getdisappear();
			map[m - 1][n] = 3;
			map[m - 1][n - 1] = 3;
			map[m - 2][n] = 3;
		}
		break;
	}
}
void recall(char input)
{
	char p = 'T';
	int m, n;
	if (input == 'A')
	{
		for (int x = 0; x <= 23; x++)
		{
			if (map[x][1] == 3 || map[x][1] == 2)
			{
				p = 'F';
			}
		}
		for (int i = 0; i < 4; i++)
		{
             for (int x = 0; x < 23; x++)
		     {
			     for (int y = 0; y < 14; y++)
			     {
				    if (map[x][y] == 3 && map[x][y - 1] == 4)
				    {
					p = 'F';
				    }
			     }
		     }
		}
		
		if (p == 'T')
		{
			for (int i = 0; i < 23; i++)
			{
				for (int k = 0; k < 14; k++)
				{
					if (map[i][k] == 2)
					{
						m = i; n = k;
					}
				}
			}
			map[m][n - 1] = 2;
			map[m][n] = 0;
		}
	}
	else if (input == 'D')
	{
		for (int x = 0; x <= 23; x++)
		{
			if (map[x][12] == 3 || map[x][12] == 2)
			{
				p = 'F';
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int x = 0; x < 23; x++)
			{
				for (int y = 0; y < 14; y++)
				{
					if (map[x][y] == 3 && map[x][y + 1] == 4)
					{
						p = 'F';
					}
				}
			}
		}
		if (p == 'T')
		{
			for (int i = 0; i < 23; i++)
			{
				for (int k = 0; k < 14; k++)
				{
					if (map[i][k] == 2)
					{
						m = i; n = k;
					}
				}
			}
			map[m][n + 1] = 2;
			map[m][n] = 0;
		}
	}
	else if (input == 'W')
	{
		for (int i = 0; i < 23; i++)
		{
			for (int k = 0; k < 14; k++)
			{
				if (map[i][k] == 2)
				{
					m = i; n = k;
				}
			}
		}
		switch (ing_state1)
		{
		case 0:
			if (ing_state2 == 1 && map[m][n - 1] == 0 && map[m - 1][n + 1] == 0)
			{
				ing_state2 = 2;
			}
			else if (ing_state2 == 2 && map[m - 2][n - 1] == 0 && map[m - 1][n - 1] == 0)
			{
				ing_state2 = 1;
			}
			break;
		case 1:
			if (ing_state2 == 1 && map[m - 1][n - 1] == 0 && map[m][n + 1] == 0)
			{
				ing_state2 = 2;
			}
			else if (ing_state2 == 2 && map[m - 2][n + 1] == 0 && map[m - 1][n + 1] == 0)
			{
				ing_state2 = 1;
			}
			break;
		case 2:
			if (ing_state2 == 1 && map[m - 1][n + 1] == 0 && map[m - 1][n + 2] == 0)
			{
				ing_state2 = 2;
			}
			else if (ing_state2 == 2 && map[m - 2][n - 1] == 0 && map[m - 2][n] == 0)
			{
				ing_state2 = 3;
			}
			else if (ing_state2 == 3 && map[m][n - 2] == 0 && map[m][n - 1] == 0)
			{
				ing_state2 = 4;
			}
			else if (ing_state2 == 4 && map[m - 2][n] == 0 && map[m][n + 1] == 0)
			{
				ing_state2 = 1;
			}
			break;
		case 3:
			if (ing_state2 == 1 && map[m][n + 1] == 0 && map[m][n + 2] == 0)
			{
				ing_state2 = 2;
			}
			else if (ing_state2 == 2 && map[m - 2][n - 1] == 0 && map[m - 2][n] == 0)
			{
				ing_state2 = 3;
			}
			else if (ing_state2 == 3 && map[m - 1][n - 2] == 0 && map[m - 1][n - 1] == 0)
			{
				ing_state2 = 4;
			}
			else if (ing_state2 == 4 && map[m - 2][n] == 0 && map[m][n - 1] == 0)
			{
				ing_state2 = 1;
			}
			break;
		case 5:
			if (ing_state2 == 1 && map[m][n - 1] == 0 && map[m][n + 1] == 0 && map[m][n + 2] == 0)
			{
				ing_state2 = 2;
			}
			else if (ing_state2 == 2 && map[m - 3][n] == 0 && map[m - 2][n] == 0 && map[m - 1][n] == 0)
			{
				ing_state2 = 1;
			}
			break;
		case 6:
			if (ing_state2 == 1 && map[m - 2][n] == 0 && map[m - 1][n + 1] == 0)
			{
				ing_state2 = 2;
			}
			else if (ing_state2 == 2 && map[m - 1][n - 1] == 0)
			{
				ing_state2 = 3;
			}
			else if (ing_state2 == 3 && map[m - 2][n] == 0)
			{
				ing_state2 = 4;
			}
			else if (ing_state2 == 4 && map[m][n - 1] == 0 && map[m][n + 1] == 0)
			{
				ing_state2 = 1;
			}
			break;
		}
	}
	else if (input == 'U' || input == 'S')
	{
		for (int i = 0; i < 23; i++)
		{
			for (int k = 0; k < 14; k++)
			{
				if (map[i][k] == 2)
				{
					m = i; n = k;
				}
			}
		}
		switch (ing_state1)
		{
		case 0:
			if (ing_state2 == 1)
			{
				if (map[m + 1][n] == 0 && map[m][n-1]==0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			else if (ing_state2 == 2)
			{
				if (map[m + 1][n] == 0 && map[m + 1][n - 1] == 0 && map[m][n+1]==0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			break;
		case 1:
			if (ing_state2 == 1)
			{
				if (map[m + 1][n] == 0 && map[m][n+1]==0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			else if (ing_state2 == 2)
			{
				if (map[m + 1][n] == 0 && map[m + 1][n + 1] == 0 && map[m][n-1]==0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			break;
		case 2:
			if (ing_state2 == 1)
			{
				if (map[m + 1][n] == 0 && map[m + 1][n + 1] == 0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			else if (ing_state2 == 2)
			{
				if (map[m + 1][n] == 0 && map[m][n+1]==0&& map[m][n+2]==0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			else if (ing_state2 == 3)
			{
				if (map[m + 1][n] == 0 &&map[m-1][n-1]==0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			else if (ing_state2 == 4)
			{
				if (map[m + 1][n] == 0 && map[m + 1][n - 2] == 0 && map[m + 1][n - 1] == 0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			break;
		case 3:
			if (ing_state2 == 1)
			{
				if (map[m + 1][n] == 0 && map[m + 1][n - 1] == 0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			else if (ing_state2 == 2)
			{
				if (map[m + 1][n] == 0 && map[m + 1][n + 1] == 0 && map[m + 1][n + 2] == 0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			else if (ing_state2 == 3)
			{
				if (map[m + 1][n] == 0 && map[m-1][n-1]==0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			else if (ing_state2 == 4)
			{
				if (map[m + 1][n] == 0 && map[m][n-1]==0&& map[m][n-2]==0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			break;
		case 4:
			if (map[m + 1][n] == 0 && map[m + 1][n + 1] == 0)
			{
				map[m][n] = 0;
				map[m + 1][n] = 2;
			}
			else
			{
				for (int x = 0; x <= 23; x++)
				{
					for (int y = 0; y < 14; y++)
					{
						if (map[x][y] == 2 || map[x][y] == 3)
						{
							map[x][y] = 4;
						}
					}
				}
			}
			break;
		case 5:
			if (ing_state2 == 1)
			{
				if (map[m + 1][n] == 0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			else if (ing_state2 == 2)
			{
				if (map[m + 1][n] == 0 && map[m + 1][n - 1] == 0 && map[m + 1][n + 1] == 0 && map[m + 1][n + 2] == 0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			break;
		case 6:
			if (ing_state2 == 1)
			{
				if (map[m + 1][n] == 0 && map[m + 1][n - 1] == 0 && map[m + 1][n + 1] == 0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			else if (ing_state2 == 2)
			{
				if (map[m + 1][n] == 0 && map[m][n+1]==0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			else if (ing_state2 == 3)
			{
				if (map[m + 1][n] == 0 && map[m][n-1]==0&&map[m][n+1]==0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}ing_state2 = 4;
			}
			else if (ing_state2 == 4)
			{
				if (map[m + 1][n] == 0 && map[m][n-1]==0)
				{
					map[m][n] = 0;
					map[m + 1][n] = 2;
				}
				else
				{
					for (int x = 0; x <= 23; x++)
					{
						for (int y = 0; y < 14; y++)
						{
							if (map[x][y] == 2 || map[x][y] == 3)
							{
								map[x][y] = 4;
							}
						}
					}
				}
			}
			break;
		}
	}
	getdisappear();
}
void judge()
{
	for (int x = 21; x > 2; x--)
	{
		char q = 'Y';
		for (int y = 1; y < 13; y++)
		{
			if (map[x][y] != 4)
			{
				q = 'N';
			}
		}
		if (q == 'Y')
		{
			for (int i = x; i > 2; i--)
			{
                  for (int f = 1; f < 13; f++)
			      {
					  map[i][f] = map[i - 1][f];
			      }
			}
			score += 10;
		}
	}
	for (int x = 1; x < 13; x++)
	{
		if (map[2][x] == 4)
		{
			game_state = 'N';
		}
	}
}
