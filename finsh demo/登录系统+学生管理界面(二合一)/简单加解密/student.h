
#include<stdio.h>
#include<graphics.h>
#include<windows.h>
#include<string.h>


typedef struct student
{
	char name[20];          //����
	char  number[20];    //ѧ��
	char  grade[20];   //�ɼ�
	int i;            //ȷ���޸�λ��
	struct student* next;
}STU, *PSTU;

void init();             //��ʼ��
void adddata(PSTU head, char name[20], char number[20], char grade[20]);            //��������
void changedata(PSTU head, char number[20], char change_number[20]);     //�ı�����
PSTU fidedata(PSTU head, char number[20]);           //��������
void deletedata(PSTU head, char number[20]);          //ɾ������
int emptydata(PSTU head);      //�������
int button(PSTU head);
void encryption();   //�����ļ�����
void Init();         //��ʼ��
void getmous();      //��ȡ��굱ǰλ�� ��������
int signaccount();    //ע�ᰴť����
int signinterface();  //ע�����
int confirmation();  //�û���¼
int loop();
