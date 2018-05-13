#pragma  once
#include "stdafx.h"
#include <vector>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
using namespace cv;
using namespace std;
ATOM imageRegisterClass(HINSTANCE hInstance);     //注册图像窗口类
BOOL imageInitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK imageWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);     //消息回掉函数
int imageloop(HINSTANCE hInstance, int  nCmdShow,Mat img,IplImage *img3);            //图像信号主函数
Mat blurimage(Mat img);
Mat gosiimage(Mat img);
Mat medianimage(Mat img);
Mat bilateralimage(Mat img);
void Erosion(int, void*);
void Dilation(int, void*);
void more_dst(int, void*);
Mat imageup(Mat map);
Mat imagedown(Mat map);
Mat cannyimage(Mat map);
Mat sobelimage(Mat map);
Mat laplaceimage(Mat src);
Mat changgeimage(Mat src);
Mat splitimage(Mat src);
Mat faceselectimage(Mat img);

