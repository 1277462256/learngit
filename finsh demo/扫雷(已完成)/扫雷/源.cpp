#include<stdio.h>
#include<graphics.h>
#include<time.h>   //随机数种子
#include <stdlib.h>
#include<mmsystem.h>
#pragma  comment(lib,"winmm.lib")


#define Row 10
#define Col 10
void jdExtend(int map[Row + 2][Col + 2], int x, int y);
int  game();
void randomGame();
void draMap();


IMAGE img[12];

int map[Row + 2][Col + 2] ;
int a, b;
int diffcult =10;
int win;

 int main()
{   
	//	扫描过程
	//  找到一个雷周围全部加1
	//找一个不是雷的地方统计不是雷的地方
	 mciSendString(L"open 权御天下.mp3",NULL,NULL,NULL);
	
 	
 PLAY:    win = 0;
	if (MessageBox(GetHWnd(), L"要增加难度吗", L"chose", MB_YESNO) == IDYES)
 {
			diffcult+=5; 
 }
	 mciSendString(L"play 权御天下.mp3", NULL, NULL, NULL);
	 randomGame();  //随机数选取，加载图片
	 BeginBatchDraw();
	 while (game()==1)
	 {
		 draMap();   //刷新图片
		 FlushBatchDraw();
		 if (win==Row*Col)
		 {
			 if (MessageBox(GetHWnd(), L"你赢了，要在玩一遍吗？", L"chose", MB_YESNO) == IDYES)
				  {
				 mciSendString(L"pause 权御天下.mp3", NULL, NULL, NULL);
				 	 goto PLAY;
				 }
			 return 0;
		 }
	 }
	 EndBatchDraw();
	 if (MessageBox(GetHWnd(), L"要在玩一遍吗？", L"chose", MB_YESNO) == IDYES)
	{
		 goto PLAY;
	}
	 return 0;
}
int game()
{
	MOUSEMSG	msg;
	while (1)
	{
		msg = GetMouseMsg();
		
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
			a = (int)msg.x / 64 + 1;
			b = (int)msg.y / 64 + 1;
			if (map[a][b] <= 8)
			{
				if (map[a][b] == 0)
				{ //递归函数
					jdExtend(map, a, b);
				}
				else if (map[a][b] == -1)
				{ //踩到雷
					map[a][b] += 10;
					draMap();
					mciSendString(L"pause 权御天下.mp3", NULL, NULL, NULL);
					MessageBox(GetHWnd(), L"你输了", L"lose", MB_OK);
					return 0;
				}
				else
				{
					map[a][b] += 10;
					win++;

				}

			}
			break;
		case WM_RBUTTONDOWN:
			a = msg.x / 64 + 1;
			b = msg.y / 64 + 1;
			if (map[a][b] >=-2)
			{

				if (map[a][b] >= 8)
				{
					break;
				}
				else
				{
					map[a][b] -= 20;
					win++;

				}
				break;
			}
			break;
		}
		
		//printf("%d,%d",x, y);
		return 1;
	}
}
void  jdExtend(int map[][Col + 2],int x,int y)     //判断周围是否能扩展开吗？
//需要一个坐标，数组
{
	map[x][y] += 10;
	win++;

	for (int i = x - 1; i <= x + 1&&i!=0&&i!=11;i++)
		{
		for (int j = y - 1; j <= y + 1 && j != 0 && j != 11; j++)
		{
			if (map[i][j] <= 8 && map[i][j] > 0)
				
				{
				map[i][j] += 10;
				win++;
				}
		      	else if (map[i][j] == 0) 
				{
					jdExtend(map, i, j);
				}
				else;
			
			
		}
		}

	

}
void  randomGame()
{

	srand((unsigned)time(NULL));  //生成一个随机数种子
	
	//initgraph(500, 500);
	
	loadimage(&img[0], L"res/0.jpg", 64, 64);
	loadimage(&img[1], L"res/1.j pg", 64, 64);
	loadimage(&img[2], L"res/2.j pg", 64, 64);
	loadimage(&img[3], L"res/3.j pg", 64, 64);
	loadimage(&img[4], L"res/4.j pg", 64, 64);
	loadimage(&img[5], L"res/5.j pg", 64, 64);
	loadimage(&img[6], L"res/6.j pg", 64, 64);
	loadimage(&img[7], L"res/7.j pg", 64, 64);
	loadimage(&img[8], L"res/8.j pg", 64, 64);
	loadimage(&img[9], L"res/标记.jpg", 64, 64);
	loadimage(&img[10], L"res/地图.jpg", 64, 64);
	loadimage(&img[11], L"res/雷.jpg", 64, 64);
	//加载完成，
	initgraph(Col * 64, Row * 64);
	for (int x = 1; x <= 10; x++)
	{
		for (int y = 1; y <= 10; y++)
		{
			map[x][y] = 0;

		}
	}
	for (int n = 0; n < diffcult;)
	{
		int x, y;
		x = rand() % Row + 1;
		y = rand() % Col + 1;
		//有没有重复的问题
		if (map[x][y] == 0)
		{
			map[x][y] = -1;
			n++;
			//周围八个数字加一
			for (int m = x - 1; m <= x + 1; m++){
				for (int n = y - 1; n <= y + 1; n++){
					if (map[m][n] != -1)
					{
						map[m][n]++;
					}
				}
			}
		}
	}
	
}
void draMap()
{

	//准备图片
	FlushBatchDraw();
	for (int i = 1; i < Row+1; i++)	{
		for (int j = 1; j < Col + 1; j++){
			if (map[i][j]>-2 && map[i][j]<9)
			{
				putimage((i - 1) * 64, (j - 1) * 64, &img[10]);
			}
			if (map[i][j] <-2)
			{
				putimage((i - 1) * 64, (j - 1) * 64, &img[9]);
			}
			else
			{

				switch (map[i][j])
				{
				case 9: putimage((i - 1) * 64, (j - 1) * 64, &img[11]); break;
				case 10: putimage((i - 1) * 64, (j - 1) * 64, &img[0]); break;
				case 11: putimage((i - 1) * 64, (j - 1) * 64, &img[1]); break;
				case 12:  putimage((i - 1) * 64, (j - 1) * 64, &img[2]); break;
				case 13: putimage((i - 1) * 64, (j - 1) * 64, &img[3]); break;
				case 14: putimage((i - 1) * 64, (j - 1) * 64, &img[4]); break;
				case 15: putimage((i - 1) * 64, (j - 1) * 64, &img[5]); break;
				case 16: putimage((i - 1) * 64, (j - 1) * 64, &img[6]); break;
				case 17: putimage((i - 1) * 64, (j - 1) * 64, &img[7]); break;
				case 18: putimage((i - 1) * 64, (j - 1) * 64, &img[8]); break;
				}
			}
		}
		//printf("\n");
	}

}



