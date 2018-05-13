/*项目民称：卿亮毕业设计
  最后修改人：卿亮
  最后修改时间：2018-4-22
  修改内容;加振动
*/



// Win32Project1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING]="信号处理软件";					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND temphwnd;
HINSTANCE imagehInstance;
int       imagenCmdShow;
char *pChar = NULL;
Mat img1;
IplImage *img2;
//登陆界面函数
void encryption();   //加密文件方法
void Init();         //初始化
void getmous();      //获取鼠标当前位置 ，测试用
int signaccount();    //注册按钮操作
int signinterface();  //注册界面
int confirmation();  //用户登录
IMAGE map[10];
MOUSEMSG  msg;
// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);        //注册窗口类
                
BOOL				InitInstance(HINSTANCE, int);           //初始化窗口
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);     //主窗口回调函数


struct  passworld
{
	int a;
	double b;
	char c;
	float f;

}encrypt, decode;

//LPITEMIDLIST PidlBrowse(HWND hwnd, int nCSIDL, LPSTR pszDisplayName);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  在此放置代码。
	MSG msg1;
	HACCEL hAccelTable;
	/*imagehInstance = hInstance;*/
	imagenCmdShow = nCmdShow;
	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	while (1)
	{
	a:	Init();
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
							closegraph();
							MyRegisterClass(hInstance);
							// 执行应用程序初始化: 
							if (!InitInstance(hInstance, nCmdShow))
							{
								return FALSE;
							}
							img1 = imread("zhd.jpg");
							RECT rect;
							GetWindowRect(temphwnd, &rect);
							WinShowMatImage(img1, GetWindowDC(temphwnd), rect);

							hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

							// 主消息循环: 
							while (GetMessage(&msg1, NULL, 0, 0))
							{
								if (!TranslateAccelerator(msg1.hwnd, hAccelTable, &msg1))
								{
									TranslateMessage(&msg1);
									DispatchMessage(&msg1);
								}
							}

							return (int)msg1.wParam;

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
						goto a;
					}
					break;
				}
				break;
			}
		}
	}
	

}



//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JCT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_JCT1));

	return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass,"信号处理软件", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 700, 500, NULL, NULL, hInstance, NULL);
   temphwnd = hWnd;
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_image:
			imageloop(imagehInstance, imagenCmdShow,img1,img2);
			break;
		case ID_32772:
			MessageBox(NULL, "PCI8510未找到", "提示", NULL);
			break;
		case ID_openfile:
			BasicFileOpen();
			break;
		case ID_savefile:
			AddItemsToCommonPlaces();
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


HRESULT BasicFileOpen()
{
	// CoCreate the File Open Dialog object.
	IFileDialog *pfd = NULL;
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pfd));
	if (SUCCEEDED(hr))
	{
		LPWSTR filePath;
		LPWSTR fileName;
		DWORD dwFlags;
		hr = pfd->GetOptions(&dwFlags);
		hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
		COMDLG_FILTERSPEC rgSpec[] ={ L"All", L"*.*" };  //设置文件类型就是对对话框的要打开的文件类型做过滤,第一个成员是文件类型，第二个成员是文件的扩展名
		hr = pfd->SetFileTypes(1, rgSpec);    //这个方法的第一个参数后面那个参数中元素的个数
		hr = pfd->SetFileTypeIndex(1);    //通过设置这个，就可以设置默认选中的文件类型项目上面。
		hr = pfd->Show(NULL);        //展示
		IShellItem *psiResult;
		hr = pfd->GetResult(&psiResult);
		if (SUCCEEDED(hr))
		{
			
			hr = psiResult->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &filePath);
			hr = psiResult->GetDisplayName(SIGDN_NORMALDISPLAY, &fileName);
			//计算需要多少个字节才能表示对应的多字节字符串  
			DWORD num = WideCharToMultiByte(CP_ACP, 0, filePath, -1, NULL, 0, NULL, 0);

			//开辟空间  
			
			pChar = (char*)malloc(num*sizeof(char));
			if (pChar == NULL)
			{
				free(pChar);
			}
			memset(pChar, 0, num*sizeof(char));

			//将宽字节字符串转换为多字节字符串  
			WideCharToMultiByte(CP_ACP, 0, filePath, -1, pChar, num, NULL, 0);
			//MessageBox(temphwnd,pChar, "显示", NULL);
			
			//opencv加载图片并显示
			/*	cvNamedWindow("原图像");
				IplImage *image = imread((const char *)pChar);
				cvShowImage("原图像", image);*/
			 img1 = imread((const char *)pChar);
			 //img2 = cvLoadImage((const char *)pChar);
			RECT rect;
			GetWindowRect(temphwnd, &rect);
			WinShowMatImage(img1, GetWindowDC(temphwnd), rect);


			CoTaskMemFree(filePath);
			CoTaskMemFree(fileName);
			psiResult->Release();
		}
		pfd->Release();
	
	}
	return hr;
}
//保存文件功能暂时无法实现h

//显示图片
void WinShowMatImage(Mat& img, HDC hdc, const RECT& rect)
{
	CvMat _img = img;
	const CvArr* arr = &_img;
	CvMat stub;
	CvMat* image = cvGetMat(arr, &stub);
	// 构造BITMAPINFO头   
	SIZE size = { image->width, image->height };
	int channels = 3;
	BITMAPINFO binfo;
	memset(&binfo, 0, sizeof(binfo));
	BITMAPINFOHEADER& bmih = binfo.bmiHeader;
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = size.cx;
	bmih.biHeight = abs(size.cy);
	bmih.biPlanes = 1;
	bmih.biBitCount = (unsigned short)(channels *8);
	bmih.biCompression = BI_RGB;

	void* dst_ptr = 0;
	HBITMAP hb = CreateDIBSection(hdc, &binfo, DIB_PAL_COLORS, &dst_ptr, 0, 0);
	HDC windowdc = CreateCompatibleDC(hdc);
	SelectObject(windowdc, hb);
	CvMat dst;
	cvInitMatHeader(&dst, size.cy, size.cx, CV_8UC3, dst_ptr, (size.cx*channels + 3)&-4);

	int origin = ((IplImage*)arr)->origin;
	cvConvertImage(image, &dst,  1);
	// 显示  
	SetStretchBltMode(hdc, COLORONCOLOR); 
	//BitBlt( hdc, 0, 0, size.cx, size.cy, windowdc, 0, 0, SRCCOPY );  
	//StretchDIBits(hdc,0,0,rect.right - rect.left, rect.bottom - rect.top,0,	0,size.cx,  size.cy,   img.data,&binfo,DIB_RGB_COLORS,SRCCOPY);
	StretchBlt(hdc, 0, 50, rect.right - rect.left, rect.bottom - rect.top, windowdc,0,0, size.cx, size.cy+30, SRCCOPY);
}

void Init()
{
	initgraph(640, 480);
	loadimage(&map[0], "0-8.jpg", 640, 480);
	loadimage(&map[1], "0-9.jpg", 640, 480);
	loadimage(&map[2], "3.bmp", 70, 40);
	loadimage(&map[3], "4.bmp", 229, 38);
	loadimage(&map[4], "5.bmp", 229, 38);
	loadimage(&map[5], "0.bmp", 70, 40);
	loadimage(&map[6], "6.bmp", 70, 40);
	loadimage(&map[7], "7.bmp", 195, 35);
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
	while (msg.uMsg == WM_LBUTTONDOWN)
	{
		TCHAR arr[5];
		_stprintf_s(arr, _T("%d"), msg.x);
		outtextxy(120, 240, arr);
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
					while (InputBox(arr, 10, "输入账号", 0, 0, true) == TRUE)
					{
						if (arr == NULL)
						{
							MessageBox(GetHWnd(), TEXT("请输入账号"), TEXT("提示"), 1);
							break;
						}
						FILE *p;
						p = fopen(arr, "wb+");
						fclose(p);
						outtextxy(210, 130, arr);
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
						if (brr == NULL)
						{
							MessageBox(GetHWnd(), TEXT("请输入账号"), TEXT("提示"), 1);
							break;
						}
						FILE *p;
						p = fopen(arr, "wb+");
						fwrite(brr, 10, 1, p);
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
