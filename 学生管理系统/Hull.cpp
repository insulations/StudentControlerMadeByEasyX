/*
此文件是程序的图形化界面
作者：李子轩
*/
#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include"Student.h"
void Init();//初始化图形界面
void SoftwareControler();//事件控制
void GoToMain();//界面切换为主界面
void GoToList();//界面切换为学生列表
void GoToLogging();//界面切换为信息录入
void GoToSearchForName();//界面切换为按姓名查询
void GoToSearchForID();//界面切换为按学号查询
void GoToList2(Student* L);//界面切换为学生列表的子界面
void ListShowing();//在学生列表中显示学生
void LoggingInit();//在进行学生信息录入前的初始化
void SetTCHARVar();//初始化TCHAR类型的全局变量或清空缓存
int main()
{	
	Init();
	SoftwareControler();
	closegraph();//关闭绘图窗口
	return 0;
}
void Init()
{
	Interface = 0;
	initgraph(1600, 800);//初始化绘图窗口
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	IMAGE imageMain;
	loadimage(&imageMain, _T("Main.jpg"));
	putimage(170, 70, &imageMain);
	SetTCHARVar();
}
void SoftwareControler()
{
	FILE *fp ;
	MOUSEMSG mousemsg;//创建鼠标事件
	while (1)
	{	
	mousemsg = GetMouseMsg();//获取鼠标事件
	if (mousemsg.mkLButton)//如果左键单击
		{
			switch (Interface)
				{
					case 0://主页
					{

					if (mousemsg.x >= 800 && mousemsg.x <= 1170)
						if (mousemsg.y >= 110 && mousemsg.y <= 160)
							GoToList();
						else if (mousemsg.y >= 220 && mousemsg.y <= 270)
							GoToLogging();
						else if (mousemsg.y >= 340 && mousemsg.y <= 390)
							GoToSearchForName();
						else if (mousemsg.y >= 460 && mousemsg.y <= 510)
							GoToSearchForID();
						if (mousemsg.x >= 1145 && mousemsg.x <= 1330)
							if (mousemsg.y >= 600 && mousemsg.y <= 670)
								return;

				}break;
				case 1://学生列表
				{
					if (mousemsg.x >= 1370 && mousemsg.x <= 1500)
						if (mousemsg.y >= 230 && mousemsg.y <= 275)
							GoToMain();
					if (mousemsg.x >= 35 && mousemsg.x <= 140)
					{
						int num = (mousemsg.y - 220 ) / 35;
					
						Student* head = GetList();
						Student* L = listMergeSortSmalltoBig(head);
						for (int i = 0; i < num; i++)
						{
							if (L->next == NULL)
								continue;
							else
							L = L->next;
						}
						GoToList2(L);
						
					}
					if (mousemsg.y >= 550 && mousemsg.y <= 610)
					{						
						if (mousemsg.x >= 1370 && mousemsg.x <= 1430)
						{
							if (page)
							{
								page--;
								GoToList();
							}
						
						}
						if (mousemsg.x >= 1450 && mousemsg.x <= 1510)
						{
							if (page<counter/12&&counter!=12)
							{
								page++;
								GoToList();
							}
						}
					}
						
				}
				break;
				case 2://信息录入
				{																										
					if (mousemsg.x >= 1090 && mousemsg.x <= 1220)
					{
						if (mousemsg.y >= 240 && mousemsg.y <= 275)//退出键
						{
							SetTCHARVar();
							GoToMain();
						}
						if (mousemsg.y >= 330 && mousemsg.y <= 365)//增加该项键
						{
							fp = fopen("Data.txt", "a+");
							fprintf(fp, "%s %s %s %s %s %s %s %s %s\n", list->name, list->ID, list->sex, list->phone, list->birth, list->age, list->dateOfAdmission, list->address,  list->mail);																				
							TCHAR zero = NULL;							
							fclose(fp);																											
							GoToMain();
							//清空缓存	
							SetTCHARVar();
						}
					}
					if (mousemsg.x >= 330 && mousemsg.x <= 410)//点击各项名称输入
					{
						if (mousemsg.y >= 220 && mousemsg.y <= 266)
						{
							
							InputBox(name, 20, _T("请输入姓名"));//调用弹窗输入
							TcharToChar(name, list->name);//TCHAR到char的类型转换							
							FlushMouseMsgBuffer();//清空鼠标信息防止反复
							
						}
						if (mousemsg.y >= 266 && mousemsg.y <= 312)
						{
														
							InputBox(id, 20, _T("请输入学号"));
							TcharToChar(id,list->ID );														
							FlushMouseMsgBuffer();
						}
						if (mousemsg.y >= 312 && mousemsg.y <= 358)
						{
							InputBox(sex, 3, _T("请输入性别"));
							TcharToChar(sex, list ->sex);							
							FlushMouseMsgBuffer();
						}
						if (mousemsg.y >= 358 && mousemsg.y <= 404)
						{
							
							InputBox(phone, 20, _T("请输入电话"));
							TcharToChar(phone, list->phone);							
							FlushMouseMsgBuffer();
						}
						if (mousemsg.y >= 404 && mousemsg.y <= 450)
						{
							
							InputBox(birth, 11, _T("请输入出生日期"));
							TcharToChar(birth, list->birth);
							FlushMouseMsgBuffer();
						}
						if (mousemsg.y >= 450 && mousemsg.y <= 496)
						{
							
							InputBox(age, 3, _T("请输入年龄"));
							TcharToChar(age, list->age);
							FlushMouseMsgBuffer();
						}
						if (mousemsg.y >= 496 && mousemsg.y <= 542)
						{
							
							InputBox(dateOfAdmission, 11, _T("请输入入学日期"));
							TcharToChar(dateOfAdmission, list->dateOfAdmission);
							FlushMouseMsgBuffer();
						}
						if (mousemsg.y >= 542 && mousemsg.y <= 588)
						{
							
							InputBox(address, 40, _T("请输入地址"));
							TcharToChar(address, list->address);
							FlushMouseMsgBuffer();
						}
						if (mousemsg.y >= 588 && mousemsg.y <= 634)
						{
							
							InputBox(mail, 40, _T("请输入邮箱"));
							TcharToChar(mail, list->mail);
							FlushMouseMsgBuffer();
						}
					}
					//输出显示	
					outtextxy(440, 243, name);					
					outtextxy(440, 289, id);
					outtextxy(440, 335, sex);
					outtextxy(440, 381, phone);
					outtextxy(440, 427, birth);
					outtextxy(440, 473, age);
					outtextxy(440, 519, dateOfAdmission);
					outtextxy(440, 565, address);
					outtextxy(440, 611, mail);
				}
				break;
				case 3://姓名查询
				{
									
					if (mousemsg.x >= 1370 && mousemsg.x <= 1500)
						if (mousemsg.y >= 230 && mousemsg.y <= 275)
							GoToMain();
					if (mousemsg.x >= 690 && mousemsg.x <= 1170)
						if (mousemsg.y >= 100 && mousemsg.y <= 150)
						{
							Student *head = GetList();	
							list = searchAppointName(head);
							GoToSearchForName();
							if (list)
							{
								CharToTchar(list->name, name);
								CharToTchar(list->ID, id);
								CharToTchar(list->age, age);
								CharToTchar(list->sex, sex);
								CharToTchar(list->birth, birth);
								CharToTchar(list->dateOfAdmission, dateOfAdmission);
								CharToTchar(list->address, address);
								CharToTchar(list->phone, phone);
								CharToTchar(list->mail, mail);
								outtextxy(65, 236, name);
								outtextxy(190, 236, id);
								outtextxy(425, 236, sex);
								outtextxy(530, 236, phone);
								outtextxy(680, 236, birth);
								outtextxy(820, 236, age);
								outtextxy(945, 236, dateOfAdmission);
								if (strlen(list->address) <= 16)
									outtextxy(1040, 236, address);
								else
									outtextxy(1040, 236, _T("请进入详情页查看"));
								if (strlen(list->mail) <= 16)
									outtextxy(1180, 236, mail);
								else
									outtextxy(1180, 236, _T("请进入详情页查看"));
							}
							else
							{
								outtextxy(65, 236, _T("不含有拥有此姓名的学生信息"));
							}
						}
					if (mousemsg.x >= 35 && mousemsg.x <= 140)
						if (mousemsg.y >= 220 && mousemsg.y <= 255)
						{
							GoToList2(list);							
						}
				}
				break;
				case 4://学号查询
				{
					if (mousemsg.x >= 1370 && mousemsg.x <= 1500)
						if (mousemsg.y >= 230 && mousemsg.y <= 275)
							GoToMain();
					if (mousemsg.x >= 690 && mousemsg.x <= 1170)
						if (mousemsg.y >= 100 && mousemsg.y <= 150)
						{
							Student *head = GetList();
							list = searchAppointID(head);
							GoToSearchForID();
							if (list)
							{
								CharToTchar(list->name, name);
								CharToTchar(list->ID, id);
								CharToTchar(list->age, age);
								CharToTchar(list->sex, sex);
								CharToTchar(list->birth, birth);
								CharToTchar(list->dateOfAdmission, dateOfAdmission);
								CharToTchar(list->address, address);
								CharToTchar(list->phone, phone);
								CharToTchar(list->mail, mail);
								outtextxy(65, 236, name);
								outtextxy(190, 236, id);
								outtextxy(425, 236, sex);
								outtextxy(530, 236, phone);
								outtextxy(680, 236, birth);
								outtextxy(820, 236, age);
								outtextxy(945, 236, dateOfAdmission);
								if (strlen(list->address) <= 16)
									outtextxy(1040, 236, address);
								else
									outtextxy(1040, 236, _T("请进入详情页查看"));
								if (strlen(list->mail) <= 16)
									outtextxy(1180, 236, mail);
								else
									outtextxy(1180, 236, _T("请进入详情页查看"));
							}
							else
							{
								outtextxy(65, 236, _T("不含有拥有此学号的学生信息"));
							}
						}
					if (mousemsg.x >= 35 && mousemsg.x <= 140)
						if (mousemsg.y >= 220 && mousemsg.y <= 255)
						{
							GoToList2(list);
						}
						
				}
				case 5://详情页面
				{
					if (mousemsg.x >= 1095 && mousemsg.x <= 1220)
					{
						if (mousemsg.y >= 240 && mousemsg.y <= 275)//退出键
						{
							SetTCHARVar();
							GoToMain();
						}						
						if (mousemsg.y >= 330 && mousemsg.y <= 365)
						{
							deleteAppointStu(list);
							GoToMain();
						}
					}				
				}
			}		
		}
	}
}
void GoToMain()
{
	Interface = 0;
	cleardevice();
	IMAGE imageMain;
	loadimage(&imageMain, _T("Main.jpg"));
	putimage(230, 70, &imageMain);
	
}
void GoToList()
{
	Interface = 1;
	cleardevice();
	IMAGE imageList;
	loadimage(&imageList, _T("List.jpg"));
	putimage(10, 70, &imageList);
	ListShowing();
}
void GoToLogging()
{	
	Interface = 2;
	cleardevice();
	IMAGE imageLogging;
	loadimage(&imageLogging, _T("Logging.jpg"));
	putimage(300, 70, &imageLogging);
	//清空缓存	
	SetTCHARVar();
}
void GoToSearchForName()
{
	Interface = 3;
	cleardevice();
	IMAGE imageName;
	loadimage(&imageName, _T("Name.jpg"));
	putimage(10, 70, &imageName);
	
}
void GoToSearchForID()
{
	Interface = 4;
	cleardevice();
	IMAGE imageID;
	loadimage(&imageID, _T("ID.jpg"));
	putimage(10, 70, &imageID);
	
}
void GoToList2(Student* L)
{
	Interface = 5;
	cleardevice();
	IMAGE imageList2;
	loadimage(&imageList2, _T("List2.jpg"));
	putimage(300, 70, &imageList2);
	CharToTchar(L->name, name);
	CharToTchar(L->ID, id);
	CharToTchar(L->age, age);
	CharToTchar(L->sex, sex);
	CharToTchar(L->birth, birth);
	CharToTchar(L->dateOfAdmission, dateOfAdmission);
	CharToTchar(L->address, address);
	CharToTchar(L->phone, phone);
	CharToTchar(L->mail, mail);
	outtextxy(440, 243, name);
	outtextxy(440, 289, id);
	outtextxy(440, 335, sex);
	outtextxy(440, 381, phone);
	outtextxy(440, 427, birth);
	outtextxy(440, 473, age);
	outtextxy(440, 519, dateOfAdmission);
	outtextxy(440, 565, address);
	outtextxy(440, 611, mail);
	list = L;
}
void ListShowing()
{
	if (Interface = 1)
	{
		Student* head = GetList();
		Student* L = listMergeSortSmalltoBig(head);
		 
		for (int j = 0; j < page*12; j++)
		{
			L = L->next;
		}
		if(counter - page * 12 <=12)
		for (int i = 0; i < counter-page*12; i++)
		{
			CharToTchar(L->name, name);
			CharToTchar(L->ID, id);
			CharToTchar(L->age, age);
			CharToTchar(L->sex, sex);
			CharToTchar(L->birth, birth);
			CharToTchar(L->dateOfAdmission, dateOfAdmission);
			CharToTchar(L->address, address);
			CharToTchar(L->phone, phone);
			CharToTchar(L->mail, mail);
			outtextxy(65, 236 + 35 * i, name);
			outtextxy(190, 236 + 35 * i, id);			
			outtextxy(425, 236 + 35 * i, sex);
			outtextxy(530, 236 + 35 * i, phone);
			outtextxy(680, 236 + 35 * i, birth);
			outtextxy(820, 236 + 35 * i, age);
			outtextxy(945, 236 + 35 * i, dateOfAdmission);
			if(strlen(L->address)<=16)
				outtextxy(1040, 236 + 35 * i, address);
			else
				outtextxy(1040, 236 + 35 * i, _T("请进入详情页查看"));
			if (strlen(L->mail) <= 16)
				outtextxy(1180, 236 + 35 * i, mail);
			else
				outtextxy(1180, 236 + 35 * i, _T("请进入详情页查看"));
			if (L->next)
				L = L->next;
		}
		else
			for (int i = 0; i < 12; i++)
			{
				CharToTchar(L->name, name);
				CharToTchar(L->ID, id);
				CharToTchar(L->age, age);
				CharToTchar(L->sex, sex);
				CharToTchar(L->birth, birth);
				CharToTchar(L->dateOfAdmission, dateOfAdmission);
				CharToTchar(L->address, address);
				CharToTchar(L->phone, phone);
				CharToTchar(L->mail, mail);
				outtextxy(65, 236 + 35 * i, name);
				outtextxy(190, 236 + 35 * i, id);
				outtextxy(425, 236 + 35 * i, sex);
				outtextxy(530, 236 + 35 * i, phone);
				outtextxy(680, 236 + 35 * i, birth);
				outtextxy(820, 236 + 35 * i, age);
				outtextxy(945, 236 + 35 * i, dateOfAdmission);
				if (strlen(L->address) <= 16)
					outtextxy(1040, 236 + 35 * i, address);
				else
					outtextxy(1040, 236 + 35 * i, _T("请进入详情页查看"));
				if (strlen(L->mail) <= 16)
					outtextxy(1180, 236 + 35 * i, mail);
				else
					outtextxy(1180, 236 + 35 * i, _T("请进入详情页查看"));
				if (L->next)
					L = L->next;
					}		
	}
}

void SetTCHARVar()
{
	memset(name, 0, sizeof(name));
	memset(id, 0, sizeof(id));
	memset(sex, 0, sizeof(sex));
	memset(phone, 0, sizeof(phone));
	memset(birth, 0, sizeof(birth));
	memset(age, 0, sizeof(age));
	memset(dateOfAdmission, 0, sizeof(dateOfAdmission));
	memset(address, 0, sizeof(address));
	memset(mail, 0, sizeof(mail));
}
