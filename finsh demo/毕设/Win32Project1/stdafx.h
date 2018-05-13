// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>
//登陆界面所需库
#include<graphics.h>  //图形界面库
#include<string.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<Shobjidl.h>
#include <Shlobj.h>
#include<Commdlg.h>  
#include "Win32Project1.h"
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/core/core.hpp> 
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "image.h"
using namespace cv;
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);         //子窗口回调函数
HRESULT BasicFileOpen();        //打开文件
void  AddItemsToCommonPlaces(); //保存文件

void WinShowMatImage(Mat& img, HDC hdc, const RECT& rect); //图片显示

// TODO:  在此处引用程序需要的其他头文件
