#include<stdio.h>
#include<windows.h>
bool readMap(char *pBmpName);
bool  saveBmp(char  *bmpName, unsigned  char  *imgBuf, int  Swidth, int  Sheight, int  SbiBitCount);
unsigned char *pBmpbuf;   //存放图片的路径
int bmpWidth;      // 图像宽度
int bmpHight;      //图像高度
RGBQUAD *pColorTable;  //颜色像素指针，//没用到
int biBitCount;   //图像类型，每像素位

int main()
{
	char readname[] = "C:\\Users\\Administrator\\Desktop\\picture\\lena.bmp";
	char savename[] = "C:\\Users\\Administrator\\Desktop\\新建文件夹\\transtlat.bmp";
	readMap(readname);
	printf("width=%d,height=%d,bi Bit Count=%d\n", bmpWidth, bmpHight, biBitCount);
	int lineBite = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;             //图片行数，必须是四的倍数（存储规则）
	
	for (int i = bmpWidth/2; i >0; i--)
	{
		for (int j = bmpHight; j >0; j--)
		{
			for (int k = 0; k < 3; k++)
			{
				int res = *(pBmpbuf + i*lineBite + j * 3 + k)*5;
				int t;
			/*	if (res>255)
				{
					*(pBmpbuf + i*lineBite + j * 3 + k) = 255;
					continue;
				}        
				*(pBmpbuf + i*lineBite + j * 3 + k) = res;*/
				//变亮超过255处
				int c = bmpWidth - i-1;
				 t = *(pBmpbuf + i*lineBite + j * 3 + k);
				 *(pBmpbuf + i*lineBite + j * 3 + k) = *(pBmpbuf + c*lineBite + j * 3 + k);
				 *(pBmpbuf + c*lineBite + j * 3 + k) = t;
			/*	*(pBmpbuf + i*lineBite + j * 3 + k) = 0;*/
			}
		}
	}
	
	if(saveBmp(savename, pBmpbuf,500,500,24)==0)printf("未完成");
	delete pBmpbuf;
	printf("完成");
	getchar();
	return 0;
}

bool readMap(char *pBmpName)
{
	char *lf;
	FILE *fp = fopen(pBmpName, "rb+");
	if (fp == 0)return 0;
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);
	BITMAPINFOHEADER   head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	bmpWidth = head.biWidth;
	bmpHight = head.biHeight;
	biBitCount = head.biBitCount;
	int lineBite = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	if (biBitCount == 8)
	{            
		pColorTable = new RGBQUAD[256];
		fread(pColorTable,sizeof(RGBQUAD),256,fp);
	}
	pBmpbuf = new unsigned char[lineBite*bmpHight];
	fread(pBmpbuf, 1, lineBite*bmpHight, fp);
	fclose(fp);
	return 1;
}

bool  saveBmp(char  *bmpName, unsigned  char  *imgBuf, int  Swidth, int Sheight,int  SbiBitCount)
{
	//如果位图数据指针为0，则没有数据传入，函数返回

	if (!imgBuf)
		return  0;
	//颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0
		int  colorTablesize = 0;
	//if (biBit Count == 8)
	//	color Tablesize = 1024;
	//待存储图像数据每行字节数为4的倍数

		int  lineByte = (Swidth  *  SbiBitCount / 8 + 3) / 4 * 4;
	//以二进制写的方式打开文件
		FILE  *fp = fopen(bmpName, "wb+");
	if (fp == 0)  return  0;
	//申请位图文件头结构变量，填写文件头信息

BITMAPFILEHEADER  fileHead;
fileHead.bfType = 0x4D42;//bmp 类型
//bf Size 是图像文件4个组成部分之和
fileHead.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+colorTablesize + lineByte*Sheight;
fileHead.bfReserved1 = 0;
fileHead.bfReserved2 = 0;


//bf Off Bits 是图像文件前3个部分所需空间之和
fileHead.bfOffBits = 54 ;
//写文件头进文件

fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
//申请位图信息头结构变量，填写信息头信息

BITMAPINFOHEADER  head;
head.biBitCount = SbiBitCount;
head.biClrImportant = 0;
head.biClrUsed = 0;
head.biCompression = 0;
head.biHeight = Sheight;
head.biPlanes = 1;
head.biSize = 40;
head.biSizeImage = lineByte*Sheight;
head.biWidth = Swidth;
head.biXPelsPerMeter = 0;
head.biYPelsPerMeter = 0;
//写位图信息头进内存
fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);
//如果灰度图像，有颜色表，写入文件
//if (biBitCount == 8) 
//fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
//写位图数据进文件

fwrite(imgBuf, Sheight*lineByte, 1, fp);
//关闭文件

fclose(fp);
return  1;
}


