// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>
//��½���������
#include<graphics.h>  //ͼ�ν����
#include<string.h>
// C ����ʱͷ�ļ�
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
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);         //�Ӵ��ڻص�����
HRESULT BasicFileOpen();        //���ļ�
void  AddItemsToCommonPlaces(); //�����ļ�

void WinShowMatImage(Mat& img, HDC hdc, const RECT& rect); //ͼƬ��ʾ

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
