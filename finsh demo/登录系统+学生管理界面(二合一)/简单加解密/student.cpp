
#include"student.h"

int loop()
{

	while (1)
	{
		PSTU head = (PSTU)malloc(sizeof(STU));
		strcpy_s(head->name, "0");
		strcpy_s(head->number, "0");
		strcpy_s(head->grade, "0");
		head->i = 0;
		head->next = NULL;
		init();
		if (button(head) == -1)
		{
			return 0;
		}
	}

	return 0;
}
void init()
{
	IMAGE mape[10];
	initgraph(640, 480);
	loadimage(&mape[0], "picture\\0-7.jpg", 640, 480);
	loadimage(&mape[1], "picture\\1-0.bmp", 190, 60);
	loadimage(&mape[2], "picture\\1-1.bmp", 190, 60);
	loadimage(&mape[3], "picture\\1-2.bmp", 190, 60);
	loadimage(&mape[4], "picture\\1-3.bmp", 190, 60);
	loadimage(&mape[5], "picture\\1-4.bmp", 190, 60);
	loadimage(&mape[6], "picture\\1-5.bmp", 190, 60);
	putimage(0, 0, &mape[0]);
	putimage(400, 20, &mape[1]);
	putimage(400, 90, &mape[2]);
	putimage(400, 160, &mape[3]);
	putimage(400, 230, &mape[4]);
	putimage(400, 300, &mape[5]);
	putimage(400, 370, &mape[6]);
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 0, _T("宋体"));
	outtextxy(0, 0, "姓名");
	outtextxy(80, 0, "学号");
	outtextxy(220, 0, "成绩");
}
void adddata(PSTU head, char name[20], char number[20], char grade[20])
{

	PSTU p = head;


	while (p->next != NULL)
	{
		p = p->next;
	}

	p->next = (PSTU)malloc(sizeof(STU));
	p->next->next = NULL;
	strcpy_s(p->next->name, name);
	strcpy_s(p->next->number, number);
	strcpy_s(p->next->grade, grade);
	p->next->i = p->i + 1;


	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 0, _T("宋体"));
	outtextxy(0, 40 * (p->next->i), p->next->name);
	outtextxy(80, 40 * (p->next->i), p->next->number);
	outtextxy(220, 40 * (p->next->i), p->next->grade);

}     //  增加数据
PSTU fidedata(PSTU head, char number[20])
{
	PSTU p = head->next;
	while (p != NULL)
	{
		if (strcmp(p->number, number) == 0)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}  //查找数据
void changedata(PSTU head, char number[20], char change_number[20])
{
	PSTU p = fidedata(head, number);
	if (p == NULL)
	{
		MessageBox(GetHWnd(), "请确定有此学号", "错误", 1);
		return;
	}
	strcpy_s(p->number, change_number);
	outtextxy(80, 40 * (p->i), p->number);
}  //修改数据
void deletedata(PSTU head, char number[20])
{
	/*PSTU p, q;
	p = fidedata(head, number);
	if (p == NULL)
	return;
	q = p;
	p = q->next;*/
	PSTU p = head, q;
	while (p->next != NULL)
	{
		if (strcmp(p->next->number, number) == 0)
		{
			outtextxy(0, 40 * (p->next->i), "               ");
			outtextxy(80, 40 * (p->next->i), "              ");
			outtextxy(220, 40 * (p->next->i), "          ");
			q = p->next;
			p->next = q->next;
			free(q);
			q = NULL;
			return;
		}
		p = p->next;
	}
	MessageBox(GetHWnd(), "请确定有此学号", "错误", 1);
	return;
}
int emptydata(PSTU head)
{
	PSTU p = head, q;
	while (p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	return 1;
}
int button(PSTU head)
{
	MOUSEMSG  msg;
	char name[20];
	char number[20];
	char grade[20];
	char change_number[20];
	while (1)
	{
		msg = GetMouseMsg();
		while (msg.uMsg == WM_LBUTTONDOWN)
		{
			while (msg.x >= 400 && msg.x <= 596)
			{
				while (msg.y >= 20 && msg.y <= 80)
				{
					InputBox(name, 20, "输入姓名");
					InputBox(number, 20, "输入学号");
					InputBox(grade, 20, "输入成绩");
					adddata(head, name, number, grade);
					break;
				}
				while (msg.y >= 90 && msg.y <= 150)        //修改
				{

					InputBox(number, 20, "输入学号");
					InputBox(change_number, 20, "输入要修改的学号");
					changedata(head, number, change_number);

					break;
				}
				while (msg.y >= 160 && msg.y <= 220)        //查找
				{

					InputBox(number, 20, "输入学号");
					PSTU p = fidedata(head, number);
					if (p == NULL)
					{
						MessageBox(GetHWnd(), "请确定有此学号", "错误", 1);
						break;
					}
					//outtextxy(100, 200, p->name);
					MessageBox(GetHWnd(), p->name, "姓名为", 1);
					MessageBox(GetHWnd(), p->grade, "成绩为", 1);
					break;
				}
				while (msg.y >= 230 && msg.y <= 290)        //删除
				{
					InputBox(number, 20, "输入要删除的学号");
					deletedata(head, number);
					break;
				}
				while (msg.y >= 300 && msg.y <= 360)        //清空
				{
					
					if (emptydata(head) == 1)
					{
						return 0;
					}
					break;
				}
				while (msg.y >= 370 && msg.y <= 430)        //退出
				{
					
					return -1;
				}
				break;
			}
			break;
		}

	}
	return 0;
}
