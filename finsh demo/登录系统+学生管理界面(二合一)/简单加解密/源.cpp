
#include"student.h"
struct  passworld
{
	int a;
	double b;
	char c;
	float f;

}encrypt, decode;
IMAGE map[10];
MOUSEMSG  msg;
int main()
{
	while (1)
	{
	Init();
// 	while (1)
// 	getmous();    //获取鼠标当前坐标
		confirmation();
	}
	getchar();
	return 0;
}
void Init()
{   initgraph(640, 480);
	loadimage(&map[0], "0-8.jpg", 640, 480);
	loadimage(&map[1], "0-9.jpg", 640, 480);
	loadimage(&map[2], "3.bmp",70, 40);
	loadimage(&map[3], "4.bmp", 229, 38);
	loadimage(&map[4], "5.bmp", 229, 38);
	loadimage(&map[5], "0.bmp", 70, 40);
	loadimage(&map[6], "6.bmp", 70, 40);
	loadimage(&map[7], "7.bmp", 195,35);
	putimage(0, 0, &map[0]);
	putimage(400, 350, &map[2]);  //注册按钮
	putimage(200, 120, &map[3]);  //输入账号
	putimage(200, 158, &map[4]);  //输入密码
	putimage(220, 200, &map[7]);   //登录按钮
}
void encryption()
{ 
	FILE *fp = fopen("1.txt", "wb+");
	encrypt = { 1, 3.2, 5, 6 };
	fwrite(&encrypt, sizeof(struct  passworld), 1, fp);
	fclose(fp);
	fp = fopen("1.pbb", "rb+");
	fread(&decode, sizeof(struct  passworld), 1, fp);
	printf("aΪ%d,b=%lf,c=%d,f=%f", decode.a, decode.b, decode.c, decode.f);
	fclose(fp);
	
}
void getmous()
{
	
	msg = GetMouseMsg();
	while (msg.uMsg==WM_LBUTTONDOWN)
	{
		TCHAR arr[5];
		_stprintf_s(arr,_T("%d"),msg.x);
		outtextxy(120,240,arr);
		break;
	}


}
int signaccount()
{
	//TCHAR arr[] =_T("dssd");
	while (1)
	{

		msg = GetMouseMsg();
		while (msg.uMsg == WM_LBUTTONDOWN)
		{
			while (msg.x >= 400 && msg.x <= 470)
			{
				while (msg.y >= 350 && msg.y <= 390)
				{
					//outtextxy(30,40,arr);
					cleardevice();
					signinterface();
					return 0;
				}
				break;
			}
			break;
		}
		

	}
}
int signinterface()
{
	putimage(0, 0, &map[1]);
	putimage(400, 350, &map[5]);   //注册
	putimage(200, 120, &map[3]);  //输入账号
	putimage(200, 158, &map[4]);  //输入密码
	putimage(200, 350, &map[6]);     //返回
	while (1)
	{
		char arr[10];
		char brr[10];
		
		msg = GetMouseMsg();
		while (msg.uMsg == WM_LBUTTONDOWN)
		{
			while (msg.x >= 200 && msg.x <= 270)           //返回键
			{
				while (msg.y >= 350 && msg.y <= 390)
				{
					return 0;
				}
				break;
			}
				
				while (msg.x >= 200 && msg.x <= 429)           //账号键
				{
					while (msg.y >= 120 && msg.y <= 158)
					{
						while (InputBox(arr, 10, "输入账号",0,0,true) == TRUE)
						{
							if (arr == NULL)
							{
								MessageBox(GetHWnd(), TEXT("请输入账号"), TEXT("提示"), 1);
								break;
							}
							FILE *p;
							p=fopen(arr,"wb+");
							fclose(p);
							outtextxy(210, 130, arr);
							break;
						}
						break;
					}
					break;
				}
				while (msg.x >= 200 && msg.x <=429)           //密码键
				{
					while (msg.y >158 && msg.y <= 196)
					{
					
						while (InputBox(brr, 10, "输入密码", 0, 0, true) == TRUE)
						{
							if (brr == NULL)
							{
								MessageBox(GetHWnd(), TEXT("请输入账号"), TEXT("提示"), 1);
								break;
							}
							FILE *p;
							p = fopen(arr, "wb+");
							fwrite(brr,10,1,p);
							fclose(p);
							outtextxy(210, 168, "**********");
							break;
						}
						break;
					}
					break;
				}
				while (msg.x >= 400 && msg.x <= 470)           //注册键
				{
					while (msg.y >= 350 && msg.y <= 390)
					{
						char crr[10];
						FILE *p;
						p = fopen(arr, "rb+");

						if (p == NULL)
						{
							MessageBox(GetHWnd(), TEXT("请输入账号"), TEXT("提示"), 1);
							break;
						}
						if (fread(crr, 10, 1, p) != 0)
						{
							MessageBox(GetHWnd(), TEXT("注册完成"), TEXT("提示"), 1);
						}
						else
							MessageBox(GetHWnd(), TEXT("请输入密码"), TEXT("提示"), 1);
						return 0;
					}
					break;
				}
				break;
		}
	}
}
int confirmation()
{
	while (1)
	{
		char arr[10];
		char brr[10];

		msg = GetMouseMsg();
		while (msg.uMsg == WM_LBUTTONDOWN)
		{
			while (msg.x >= 200 && msg.x <= 429)           //账号键
			{
				while (msg.y >= 120 && msg.y <= 158)
				{
					while (InputBox(arr, 10, "输入账号", 0, 0, true) == TRUE)
					{
						FILE *p;
						p = fopen(arr, "rb+");
						if (p == NULL)
						{
							MessageBox(GetHWnd(), TEXT("此账号尚未注册"), TEXT("错误"), 1);
							break;
						}
						else
						{
							outtextxy(210, 130, arr);
						}
						break;
					}
					break;
				}
				break;
			}
			while (msg.x >= 200 && msg.x <= 429)           //密码键
			{
				while (msg.y > 158 && msg.y <= 196)
				{

					while (InputBox(brr, 10, "输入密码", 0, 0, true) == TRUE)
					{
						outtextxy(210, 168, "**********");
						break;
					}
					break;
				}
				break;
			}
			while (msg.x >= 220 && msg.x <= 415)           //登录键
			{
				while (msg.y >= 200 && msg.y <= 235)
				{
					char crr[10];
					FILE *p;
					p = fopen(arr, "rb+");
					if (p == NULL)
					{
						MessageBox(GetHWnd(), TEXT("请输入正确账号"), TEXT("提示"), 1);
						break;
					}
					fread(crr, 10, 1, p);
					fclose(p);
					if (strcmp(brr, crr) == 0)
					{
						MessageBox(GetHWnd(), TEXT("登录完成"), TEXT("提示"), 1);
						loop();
						return 0;
					}
					else
					{
						MessageBox(GetHWnd(), TEXT("密码错误"), TEXT("提示"), 1);
						break;
					}
					break;
				}
				break;
			}
			while (msg.x >= 400 && msg.x <= 470)                 //注册建
			{
				while (msg.y >= 350 && msg.y <= 390)
				{
					cleardevice();
					signinterface();
					return 0;
				}
				break;
			}
			break;
		}
	}
} 