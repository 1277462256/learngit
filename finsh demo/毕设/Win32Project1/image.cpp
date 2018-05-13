#pragma  once
#include "image.h"
#define MAX_LOADSTRING 100

HINSTANCE imagehInst;								// 当前实例
TCHAR imageszTitle[MAX_LOADSTRING]="图像变换显示";					// 标题栏文本
TCHAR imageszWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND imagetemphwnd;
Mat changeimage, originalimage;
TCHAR strFilename[100];
RECT rect;
//膨胀与腐蚀
int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;
//开运算以及其他形态变化
int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;

//LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);

int  imageloop(HINSTANCE ihInstance, int  nCmdShow,Mat img,IplImage *img3)
{
	MSG msg;
	HACCEL hAccelTable;
	if (img.empty() == TRUE)
	{
		MessageBox(imagetemphwnd, "未选择文件", "提示",NULL);
		return  0;
	}
	originalimage = img;
	// 初始化全局字符串
	LoadString(ihInstance, IDS_APP_TITLE, imageszTitle, MAX_LOADSTRING);
	/*LoadString(ihInstance, IDC_WIN32PROJECT1, imageszWindowClass, MAX_LOADSTRING);*/
	imageRegisterClass(ihInstance);

	// 执行应用程序初始化: 
	if (!imageInitInstance(ihInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(ihInstance, MAKEINTRESOURCE(IDR_image));

	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM imageRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX imageS;
	imageS.cbSize = sizeof(WNDCLASSEX);
	imageS.style = CS_HREDRAW | CS_VREDRAW;
	imageS.lpfnWndProc = imageWndProc;
	imageS.cbClsExtra = 0;
	imageS.cbWndExtra = 0;
	imageS.hInstance = hInstance;
	imageS.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JCT1));
	imageS.hCursor = LoadCursor(NULL, IDC_ARROW);
	imageS.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	imageS.lpszMenuName = MAKEINTRESOURCE(IDR_image);
	imageS.lpszClassName = "test";
	imageS.hIconSm = LoadIcon(imageS.hInstance, MAKEINTRESOURCE(IDI_JCT1));
	return RegisterClassEx(&imageS);
}
BOOL imageInitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND ihWnd;

	imagehInst = hInstance; // 将实例句柄存储在全局变量中00

	ihWnd = CreateWindow("test","图像处理" , WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0,500, 500, NULL, NULL, hInstance, NULL);
	imagetemphwnd = ihWnd;
	if (!ihWnd)
	{
		return FALSE;
	}
	ShowWindow(ihWnd, nCmdShow);
	UpdateWindow(ihWnd);
	return TRUE;
}


LRESULT CALLBACK imageWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	Mat  tempimage = originalimage;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		
		switch (wmId)
		{
		case ID_32791:      //腐蚀操作
			namedWindow("腐蚀滑动选择");
			createTrackbar("腐蚀方式","腐蚀滑动选择",
				&erosion_elem, max_elem,
				Erosion);

			createTrackbar("腐蚀度", "腐蚀滑动选择",
				&erosion_size, max_kernel_size,
				Erosion);

			break;
		case ID_32807:       //膨胀操作
			namedWindow("膨胀滑动选择");
			createTrackbar("膨胀方式", "膨胀滑动选择",
				&dilation_elem, max_elem,
				Dilation);

			createTrackbar("膨胀度", "膨胀滑动选择",
				&dilation_size, max_kernel_size,
				Dilation);

			break;
		case ID_32792:
			namedWindow("开运算滑动选择");
			morph_operator = 2;
			createTrackbar("开运算方式", "开运算滑动选择",
				&morph_elem, max_elem,
				more_dst);

			createTrackbar("开运算度", "开运算滑动选择",
				&morph_size, max_kernel_size,
				more_dst);
			break;
		case ID_32793:
			namedWindow("闭运算滑动选择");
			morph_operator = 3;
			createTrackbar("闭运算方式", "闭运算滑动选择",
				&morph_elem, max_elem,
				more_dst);

			createTrackbar("闭运算度", "闭运算滑动选择",
				&morph_size, max_kernel_size,
				more_dst);
			break;
		case ID_32794:
			namedWindow("形态梯度滑动选择");
			morph_operator = 4;
			createTrackbar("形态梯度运算方式", "形态梯度滑动选择",
				&morph_elem, max_elem,
				more_dst);

			createTrackbar("形态梯度运算度", "形态梯度滑动选择",
				&morph_size, max_kernel_size,
				more_dst);
			break;
		case ID_32795:
			namedWindow("顶帽滑动选择");
			morph_operator = 5;
			createTrackbar("顶帽运算方式", "顶帽滑动选择",
				&morph_elem, max_elem,
				more_dst);

			createTrackbar("顶帽运算度", "顶帽滑动选择",
				&morph_size, max_kernel_size,
				more_dst);
			break;
		case ID_32796:
			namedWindow("黑帽滑动选择");
			morph_operator = 6;
			createTrackbar("黑帽运算方式", "黑帽滑动选择",
				&morph_elem, max_elem,
				more_dst);

			createTrackbar("黑帽运算度", "黑帽滑动选择",
				&morph_size, max_kernel_size,
				more_dst);
			break;
		case ID_32797:                     //图像放大
			changeimage = imageup(tempimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			tempimage = changeimage;
			break;
		case ID_32798:                     //图像缩小
			changeimage = imagedown(tempimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			tempimage = changeimage;
			break;
		case ID_32803:                     //均值滤波
			changeimage =blurimage(originalimage);
			
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case ID_32804:             //高斯滤波
			changeimage =gosiimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case ID_32805:           //中指滤波
			changeimage = medianimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case ID_32806:             //双边滤波
			changeimage = bilateralimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case  ID_32799:            //canny边缘检测
			changeimage = cannyimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case  ID_32800:            //sobel边缘检测
			changeimage = sobelimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case  ID_32801:            //sobel边缘检测
			changeimage = laplaceimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case  ID_32786:            //图像旋转
			changeimage = changgeimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case  ID_32802:            //图像旋转
			changeimage = faceselectimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case  ID_Menu:            //产生直方图
			changeimage = splitimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			destroyAllWindows();
			break;
		case ID_openfile:
			break;
		case ID_savefile:
			if (changeimage.data != NULL)
			{
				AddItemsToCommonPlaces();


				imwrite(strFilename, changeimage);
				/*int a = changeimage.channels();
				char s[10] = { 0 };
				sprintf(s, "%d", a);
				MessageBox(NULL,s , TEXT("提示"), 0);*/

			}
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

Mat blurimage(Mat img)
{
	Mat tempimg;
	blur(img, tempimg, Size(3, 3), Point(-1, -1));
	return tempimg;
}

Mat gosiimage(Mat img)
{
	Mat tempimg;
	GaussianBlur(img, tempimg, Size(3, 3), 0, 0);
	return tempimg;
}
Mat medianimage(Mat img)
{
	Mat tempimg;
	medianBlur(img, tempimg,3);
	return tempimg;
}
Mat bilateralimage(Mat img)
{
	Mat tempimg;
	bilateralFilter(img, tempimg, 25, 25 * 2, 25 / 2);
	return tempimg;
}

void Erosion(int, void*)
{
	Mat src, erosion_dst;
	int erosion_type;
	src = originalimage;
	if (erosion_elem == 0){ erosion_type = MORPH_RECT; }
	else if (erosion_elem == 1){ erosion_type = MORPH_CROSS; }
	else if (erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement(erosion_type,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));

	/// 腐蚀操作
	erode(src, erosion_dst, element);
	GetWindowRect(imagetemphwnd, &rect);
	WinShowMatImage(erosion_dst, GetWindowDC(imagetemphwnd), rect);
}
void Dilation(int, void*)
{
	Mat src, dilation_dst;
	src = originalimage;
	int dilation_type;
	if (dilation_elem == 0){ dilation_type = MORPH_RECT; }
	else if (dilation_elem == 1){ dilation_type = MORPH_CROSS; }
	else if (dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));
	/// 膨胀操作
	dilate(src, dilation_dst, element);
	GetWindowRect(imagetemphwnd, &rect);
	WinShowMatImage(dilation_dst, GetWindowDC(imagetemphwnd), rect);
	
}

void more_dst(int, void*)
{
	Mat src, dst;
	src = originalimage;
	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	morphologyEx(src, dst, morph_operator, element);
	GetWindowRect(imagetemphwnd, &rect);
	WinShowMatImage(dst, GetWindowDC(imagetemphwnd), rect);
}

Mat imageup(Mat map)
{
	Mat dst, tmp;
	tmp = map;
	pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
	return dst;
}
Mat imagedown(Mat map)
{
	Mat dst, tmp;
	tmp = map;
	pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
	return dst;
}

Mat cannyimage(Mat map)
{
	cvtColor(map, map, CV_BGR2GRAY);
	Mat contours;
	Canny(map, contours, 20, 255);
	return contours;
}

Mat sobelimage(Mat map)
{
	Mat grad, src_gray;
	cvtColor(map, src_gray, CV_RGB2GRAY);
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	Sobel(src_gray, grad_x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	Sobel(src_gray, grad_y, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	return grad;
}

Mat laplaceimage(Mat src)
{
	Mat  src_gray, dst;
	cvtColor(src, src_gray, CV_RGB2GRAY);
	Mat abs_dst;
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	return abs_dst;

}

Mat changgeimage(Mat src)
{
	Point2f srcTri[3];
	Point2f dstTri[3];

	Mat rot_mat(2, 3, CV_32FC1);
	Mat warp_mat(2, 3, CV_32FC1);
	Mat warp_dst, warp_rotate_dst;
	warp_dst = Mat::zeros(src.rows, src.cols, src.type());
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);

	dstTri[0] = Point2f(src.cols*0.0, src.rows*0.33);
	dstTri[1] = Point2f(src.cols*0.85, src.rows*0.25);
	dstTri[2] = Point2f(src.cols*0.15, src.rows*0.7);
	/// 求得仿射变换
	warp_mat = getAffineTransform(srcTri, dstTri);

	/// 对源图像应用上面求得的仿射变换
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	/** 对图像扭曲后再旋转 */

	/// 计算绕图像中点顺时针旋转50度缩放因子为0.6的旋转矩阵
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;

	/// 通过上面的旋转细节信息求得旋转矩阵
	rot_mat = getRotationMatrix2D(center, angle, scale);

	/// 旋转已扭曲图像
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());

	return warp_dst;
}
Mat splitimage(Mat src)
{
	Mat dst;
	Mat  rgb_planes[3];

	split(src, rgb_planes);
	/// 设定bin数目
	int histSize = 255;

	/// 设定取值范围 ( R,G,B) )
	float range[] = { 0, 255 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat r_hist, g_hist, b_hist;

	/// 计算直方图:
	calcHist(&rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

	// 创建直方图画布
	int hist_w = 400; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));

	/// 将直方图归一化到范围 [ 0, histImage.rows ]
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// 在直方图画布上画出直方图
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}
	return  histImage;
}

Mat faceselectimage(Mat img)    //人脸识别
{  
	const char* cascade_name ="haarcascade_frontalface_alt.xml";
	CascadeClassifier faceCascade;
	
	if (!img.data)
	{
		while (1);
	}
	if(!faceCascade.load("haarcascade_frontalface_alt2.xml"))
	{
		while (1);
		
	}
		  //加载分类器，注意文件路径  
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(img, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	faceCascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (int i = 0; i < faces.size(); i++) {
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(img, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	}

	return img;
	
}
void AddItemsToCommonPlaces()   //文件保存
{
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(OPENFILENAME);//结构体大小  
	ofn.hwndOwner = NULL;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄  
	ofn.lpstrFilter = TEXT("*_*.bmp");//设置过滤  
	ofn.nFilterIndex = 1;//过滤器索引  
	ofn.lpstrFile = strFilename;//接收返回的文件名，注意第一个字符需要为NULL  
	ofn.nMaxFile = sizeof(strFilename);//缓冲区长度  
	ofn.lpstrInitialDir = NULL;//初始目录为默认  
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;//目录必须存在，覆盖文件前发出警告  
	ofn.lpstrTitle = TEXT("保存到");//使用系统默认标题留空即可  
	ofn.lpstrDefExt = TEXT("bmp");//默认追加的扩展名  
	if (GetSaveFileName(&ofn))
	{
		MessageBox(NULL, "保存成功", TEXT("提示"), 0);
	}


}