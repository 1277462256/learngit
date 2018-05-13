#include<stdio.h>
#include<Windows.h>
#include <graphics.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
int initGame();
int drawmap();
int playgame();
int ifwiner();
IMAGE mug[7];
//自定义0为空，2为箱子，1为墙，3为人，4为目的地  7为人与目的地重合，8为箱子与目的地重合
int map[12][8][8] = {
	{ { -1, -1, 1, 1, 1, -1, -1, -1 },
	{ -1, -1, 1, 4, 1, -1, -1, -1 },
	{ -1, -1, 1, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 2, 0, 2, 4, 1 },
	{ 1, 4, 0, 2, 3, 1, 1, 1 },
	{ 1, 1, 1, 0, 2, 1, -1, -1 },
	{ -1, -1, -1, 1, 4, 1, -1, -1 },
	{ -1, -1, -1, 1, 1, 1, -1, -1 } }
};


int main()
{
	initGame();

	while (1)
	{

		
		playgame();
		break;
		
	}
	

	getchar();
	return 0;
}
int initGame()
{
	initgraph(8 * 64, 8 * 64);
	mciSendString(L"open 权御天下.mp3", NULL, NULL, NULL);
	mciSendString(L"play 权御天下.mp3", NULL, NULL, NULL);
	loadimage(&mug[0], L"i/blank.jpg", 64, 64);
	loadimage(&mug[1], L"i/Wall.jpg", 64, 64);
	loadimage(&mug[2], L"i/box.jpg", 64, 64);
	loadimage(&mug[3], L"i/people1.jpg", 64, 64);
	loadimage(&mug[4], L"i/EndPoint.jpg", 64, 64);
	loadimage(&mug[5], L"i/bm.jpg", 64, 64);
	loadimage(&mug[6], L"i/dbox.jpg", 64, 64);
	return 1;

}
int drawmap()
{
	for (int i = 0; i < 8;i++)
	{
		for (int j = 0; j < 8;j++)
	{
			switch (map[0][i][j])
			{
			case 0: putimage(i * 64, j * 64, &mug[0]);break;
			case 1: putimage(i * 64, j * 64, &mug[1]); break;
			case 2: putimage(i * 64, j * 64, &mug[2]); break;
			case 3: putimage(i * 64, j * 64, &mug[3]); break;
			case 4: putimage(i * 64, j * 64, &mug[4]); break;
			case 7: putimage(i * 64, j * 64, &mug[5]); break;
			case 8: putimage(i * 64, j * 64, &mug[6]); break;
			
			}
			
	}
		
	}
	return 1;
}
int playgame()
{
	int x = 4;
	int y = 4;
	char keyboard;
	while (1)
	{
		drawmap();
		if (ifwiner() == 1)
			return 0;
		keyboard = _getch();
		switch (keyboard)
		{		//	int a;
			case 72:                            //上
				//	a = map[0][x][y];
				switch (map[0][x][y - 1])
				{
				case 0:         // 空

					map[0][x][y - 1] = map[0][x][y];
					map[0][x][y] = 0;
					y--;
					break;
				case 1:      //墙
					break;
				case 2:      //箱子

					if (map[0][x][y - 2] == 0)
					{
						map[0][x][y - 2] = map[0][x][y-1];
					}
					else if (map[0][x][y - 2] == 1)
					{
						break;
					}
					else if (map[0][x][y - 2] == 2)
					{
						break;
					}
					else if (map[0][x][y - 2] == 4)
					{
						map[0][x][y - 2] = 8;

					}
					map[0][x][y - 1] = map[0][x][y];
					map[0][x][y] = 0;
					y--;
					break;
				case 4:map[0][x][y - 1] = 7;
					map[0][x][y] = 0;
					y--;
					break;
				default:
					break;
				}
				break;
			case 80:  //下
				switch (map[0][x][y + 1])
				{
				case 0:         // 空
					map[0][x][y+ 1] = map[0][x][y];
					map[0][x][y] = 0;
					y++;
					break;
				case 1:      //墙
					break;
				case 2:      //箱子

					if (map[0][x][y + 2] == 0)
					{
						map[0][x][y+ 2] = map[0][x][y + 1];
					}
					else if (map[0][x][y + 2] == 1)
					{
						break;
					}
					else if (map[0][x][y + 2] == 2)
					{
						break;
					}
					else if (map[0][x][y+ 2] == 4)
					{
						map[0][x][y + 2] = 8;

					}
					map[0][x][y + 1] = map[0][x][y];
					map[0][x][y] = 0;
					y++;
					break;
				case 4:
					map[0][x][y + 1] = 7;
					map[0][x][y] = 0;
					y++;
					break;
				default:
					break;
				}

				break;
			case 75:   //左
				switch (map[0][x-1][y])
				{
				case 0:         // 空
					map[0][x-1][y ] = map[0][x][y];
					map[0][x][y] = 0;
					x--;
					break;
				case 1:      //墙
					break;
				case 2:      //箱子

					if (map[0][x-2][y ] == 0)
					{
						map[0][x-2][y ] = map[0][x-1][y ];
					}
					else if (map[0][x-2][y] == 1)
					{
						break;
					}
					else if (map[0][x-2][y] == 2)
					{
						break;
					}
					else if (map[0][x-2][y] == 4)
					{
						map[0][x-2][y] = 8;

					}
					map[0][x-1][y] = map[0][x][y];
					map[0][x][y] = 0;
					x--;
					break;
				case 4:
					map[0][x- 1][y] = 7;
					map[0][x][y] = 0;
					x--;
					break;
				default:
					break;
				}
				break;
			case 77:   //右
				switch (map[0][x + 1][y])
				{
				case 0:         // 空
					map[0][x + 1][y] = map[0][x][y];
					map[0][x][y] = 0;
					x++;
					break;
				case 1:      //墙
					break;
				case 2:      //箱子

					if (map[0][x + 2][y] == 0)
					{
						map[0][x + 2][y] = map[0][x + 1][y];
					}
					else if (map[0][x + 2][y] == 1)
					{
						break;
					}
					else if (map[0][x + 2][y] == 2)
					{
						break;
					}
					else if (map[0][x + 2][y] == 4)
					{
						map[0][x + 2][y] = 8;

					}
					map[0][x + 1][y] = map[0][x][y];
					map[0][x][y] = 0;
					x++;
					break;
				case 4:
					map[0][x+1][y] = 7;
					map[0][x][y] = 0;
					x++;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		

	}


	return 0;

}
int ifwiner()
{
	int n = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (map[0][i][j] == 8)
				n++;
			if (n == 4)
			{
				while (MessageBox(GetHWnd(), L"你过关了，要在玩一遍吗？", L"chose", MB_YESNO) == IDYES)
				{
					return 1;
				}

			}
	

		}

	}
	return 0;
}