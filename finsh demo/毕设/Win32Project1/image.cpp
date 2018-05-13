#pragma  once
#include "image.h"
#define MAX_LOADSTRING 100

HINSTANCE imagehInst;								// ��ǰʵ��
TCHAR imageszTitle[MAX_LOADSTRING]="ͼ��任��ʾ";					// �������ı�
TCHAR imageszWindowClass[MAX_LOADSTRING];			// ����������
HWND imagetemphwnd;
Mat changeimage, originalimage;
TCHAR strFilename[100];
RECT rect;
//�����븯ʴ
int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;
//�������Լ�������̬�仯
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
		MessageBox(imagetemphwnd, "δѡ���ļ�", "��ʾ",NULL);
		return  0;
	}
	originalimage = img;
	// ��ʼ��ȫ���ַ���
	LoadString(ihInstance, IDS_APP_TITLE, imageszTitle, MAX_LOADSTRING);
	/*LoadString(ihInstance, IDC_WIN32PROJECT1, imageszWindowClass, MAX_LOADSTRING);*/
	imageRegisterClass(ihInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!imageInitInstance(ihInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(ihInstance, MAKEINTRESOURCE(IDR_image));

	// ����Ϣѭ��: 
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

	imagehInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����00

	ihWnd = CreateWindow("test","ͼ����" , WS_OVERLAPPEDWINDOW,
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
		// �����˵�ѡ��: 
		
		switch (wmId)
		{
		case ID_32791:      //��ʴ����
			namedWindow("��ʴ����ѡ��");
			createTrackbar("��ʴ��ʽ","��ʴ����ѡ��",
				&erosion_elem, max_elem,
				Erosion);

			createTrackbar("��ʴ��", "��ʴ����ѡ��",
				&erosion_size, max_kernel_size,
				Erosion);

			break;
		case ID_32807:       //���Ͳ���
			namedWindow("���ͻ���ѡ��");
			createTrackbar("���ͷ�ʽ", "���ͻ���ѡ��",
				&dilation_elem, max_elem,
				Dilation);

			createTrackbar("���Ͷ�", "���ͻ���ѡ��",
				&dilation_size, max_kernel_size,
				Dilation);

			break;
		case ID_32792:
			namedWindow("�����㻬��ѡ��");
			morph_operator = 2;
			createTrackbar("�����㷽ʽ", "�����㻬��ѡ��",
				&morph_elem, max_elem,
				more_dst);

			createTrackbar("�������", "�����㻬��ѡ��",
				&morph_size, max_kernel_size,
				more_dst);
			break;
		case ID_32793:
			namedWindow("�����㻬��ѡ��");
			morph_operator = 3;
			createTrackbar("�����㷽ʽ", "�����㻬��ѡ��",
				&morph_elem, max_elem,
				more_dst);

			createTrackbar("�������", "�����㻬��ѡ��",
				&morph_size, max_kernel_size,
				more_dst);
			break;
		case ID_32794:
			namedWindow("��̬�ݶȻ���ѡ��");
			morph_operator = 4;
			createTrackbar("��̬�ݶ����㷽ʽ", "��̬�ݶȻ���ѡ��",
				&morph_elem, max_elem,
				more_dst);

			createTrackbar("��̬�ݶ������", "��̬�ݶȻ���ѡ��",
				&morph_size, max_kernel_size,
				more_dst);
			break;
		case ID_32795:
			namedWindow("��ñ����ѡ��");
			morph_operator = 5;
			createTrackbar("��ñ���㷽ʽ", "��ñ����ѡ��",
				&morph_elem, max_elem,
				more_dst);

			createTrackbar("��ñ�����", "��ñ����ѡ��",
				&morph_size, max_kernel_size,
				more_dst);
			break;
		case ID_32796:
			namedWindow("��ñ����ѡ��");
			morph_operator = 6;
			createTrackbar("��ñ���㷽ʽ", "��ñ����ѡ��",
				&morph_elem, max_elem,
				more_dst);

			createTrackbar("��ñ�����", "��ñ����ѡ��",
				&morph_size, max_kernel_size,
				more_dst);
			break;
		case ID_32797:                     //ͼ��Ŵ�
			changeimage = imageup(tempimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			tempimage = changeimage;
			break;
		case ID_32798:                     //ͼ����С
			changeimage = imagedown(tempimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			tempimage = changeimage;
			break;
		case ID_32803:                     //��ֵ�˲�
			changeimage =blurimage(originalimage);
			
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case ID_32804:             //��˹�˲�
			changeimage =gosiimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case ID_32805:           //��ָ�˲�
			changeimage = medianimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case ID_32806:             //˫���˲�
			changeimage = bilateralimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case  ID_32799:            //canny��Ե���
			changeimage = cannyimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case  ID_32800:            //sobel��Ե���
			changeimage = sobelimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case  ID_32801:            //sobel��Ե���
			changeimage = laplaceimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case  ID_32786:            //ͼ����ת
			changeimage = changgeimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case  ID_32802:            //ͼ����ת
			changeimage = faceselectimage(originalimage);
			GetWindowRect(imagetemphwnd, &rect);
			WinShowMatImage(changeimage, GetWindowDC(imagetemphwnd), rect);
			break;
		case  ID_Menu:            //����ֱ��ͼ
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
				MessageBox(NULL,s , TEXT("��ʾ"), 0);*/

			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  �ڴ���������ͼ����...
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

	/// ��ʴ����
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
	/// ���Ͳ���
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
	/// ��÷���任
	warp_mat = getAffineTransform(srcTri, dstTri);

	/// ��Դͼ��Ӧ��������õķ���任
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	/** ��ͼ��Ť��������ת */

	/// ������ͼ���е�˳ʱ����ת50����������Ϊ0.6����ת����
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;

	/// ͨ���������תϸ����Ϣ�����ת����
	rot_mat = getRotationMatrix2D(center, angle, scale);

	/// ��ת��Ť��ͼ��
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());

	return warp_dst;
}
Mat splitimage(Mat src)
{
	Mat dst;
	Mat  rgb_planes[3];

	split(src, rgb_planes);
	/// �趨bin��Ŀ
	int histSize = 255;

	/// �趨ȡֵ��Χ ( R,G,B) )
	float range[] = { 0, 255 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat r_hist, g_hist, b_hist;

	/// ����ֱ��ͼ:
	calcHist(&rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

	// ����ֱ��ͼ����
	int hist_w = 400; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));

	/// ��ֱ��ͼ��һ������Χ [ 0, histImage.rows ]
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// ��ֱ��ͼ�����ϻ���ֱ��ͼ
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

Mat faceselectimage(Mat img)    //����ʶ��
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
		  //���ط�������ע���ļ�·��  
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
void AddItemsToCommonPlaces()   //�ļ�����
{
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(OPENFILENAME);//�ṹ���С  
	ofn.hwndOwner = NULL;//ӵ���Ŵ��ھ����ΪNULL��ʾ�Ի����Ƿ�ģ̬�ģ�ʵ��Ӧ����һ�㶼Ҫ��������  
	ofn.lpstrFilter = TEXT("*_*.bmp");//���ù���  
	ofn.nFilterIndex = 1;//����������  
	ofn.lpstrFile = strFilename;//���շ��ص��ļ�����ע���һ���ַ���ҪΪNULL  
	ofn.nMaxFile = sizeof(strFilename);//����������  
	ofn.lpstrInitialDir = NULL;//��ʼĿ¼ΪĬ��  
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;//Ŀ¼������ڣ������ļ�ǰ��������  
	ofn.lpstrTitle = TEXT("���浽");//ʹ��ϵͳĬ�ϱ������ռ���  
	ofn.lpstrDefExt = TEXT("bmp");//Ĭ��׷�ӵ���չ��  
	if (GetSaveFileName(&ofn))
	{
		MessageBox(NULL, "����ɹ�", TEXT("��ʾ"), 0);
	}


}