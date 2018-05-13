#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>

int play(int map[][3], int width, int height);
void initgame();
void drawgame();

IMAGE pic[3][3];
IMAGE img;
int map[3][3];
int main()
{
	loadimage(&img, L"0.jpg");
	initgraph(img.getwidth(), img.getheight());
	
	initgame();
	
	while (1)
	{
		drawgame();
		while (play(map, img.getwidth() / 3, img.getheight()/3) == 0);
		cleardevice();
	}
	getchar();
	return 0;

}
int play(int map[][3],int width,int height)
{
	MOUSEMSG msg;
		int m=0, n=0;
		for (int i = 0; i < 3;i++)
		{
			for (int j = 0; j < 3;j++)
			{
				if (map[i][j] == 8)
				{
					m = i;
					n = j;
					break;
				}
			}
			if (map[m][n] == 8)break;
		}
		while (1)
		{
			msg = GetMouseMsg();
			while (msg.uMsg == WM_LBUTTONDOWN)
			{
				int t;
				if (m == msg.x / width  + 1 && n == msg.y / height)
				{
					t = map[m][n];
					map[m][n] = map[m - 1][n];
					map[m - 1][n] = t;
				}
				else if (m == msg.x / width  - 1 && n == msg.y / height)
				{
					t = map[m][n];
					map[m][n] = map[m + 1][n];
					map[m + 1][n] = t;
				}
				else if (m == msg.x / width && n == msg.y / height  - 1)
				{
					int t;
					t = map[m][n];
					map[m][n] = map[m][n + 1];
					map[m][n + 1] = t;

				}
				else if (m == msg.x / width  && n == msg.y / height  + 1)
				{

					t = map[m][n];
					map[m][n] = map[m][n - 1];
					map[m][n - 1] = t;
				}
				else return 0;
				return 1;
			}
		}
		return 0;
}
void initgame()
{
	
	
	SetWorkingImage(&img);
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 2 && j == 2)break;
			getimage(&pic[i][j], i*img.getwidth() / 3, j* img.getheight() / 3, img.getwidth() / 3, img.getheight() / 3);
		}
	}
	SetWorkingImage(NULL);


	srand((unsigned)time(NULL));
	int a[9], size = 9;
	for (int i = 0; i < 9; i++)
	{
		a[i] = i;
	}

	for (int i = 0; i <3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int  k = rand() % size;
			map[i][j] = a[k];
			for (int x = k; x < size; x++)
			{
				a[x] = a[x + 1];
			}
			size--;
		}
	}
}
void drawgame()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			putimage(i*img.getwidth() / 3, j* img.getheight() / 3, &pic[0][map[i][j]]);
			Sleep(20);
		}
	}

}