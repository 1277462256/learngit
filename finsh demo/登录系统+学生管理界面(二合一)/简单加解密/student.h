
#include<stdio.h>
#include<graphics.h>
#include<windows.h>
#include<string.h>


typedef struct student
{
	char name[20];          //姓名
	char  number[20];    //学号
	char  grade[20];   //成绩
	int i;            //确定修改位置
	struct student* next;
}STU, *PSTU;

void init();             //初始化
void adddata(PSTU head, char name[20], char number[20], char grade[20]);            //增加数据
void changedata(PSTU head, char number[20], char change_number[20]);     //改变数据
PSTU fidedata(PSTU head, char number[20]);           //查找数据
void deletedata(PSTU head, char number[20]);          //删除数据
int emptydata(PSTU head);      //清空数据
int button(PSTU head);
void encryption();   //加密文件方法
void Init();         //初始化
void getmous();      //获取鼠标当前位置 ，测试用
int signaccount();    //注册按钮操作
int signinterface();  //注册界面
int confirmation();  //用户登录
int loop();
