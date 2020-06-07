#pragma once
/*
此文件包含在处理数据时用到的函数
作者：李子轩，赵旭东，陈锐
*/
struct Student
{
	char name[20];//姓名
	char ID[20];//学号
	char age[3];//年龄
	char sex[3];//性别,true表示男，false表示女
	char birth[11];//出生日期
	char dateOfAdmission[11];//入学日期
	char address[40];//地址
	char phone[20];//电话
	char mail[40];//邮箱
	struct Student *next;//指向下一节点
};
TCHAR* name = (TCHAR*)malloc(sizeof(TCHAR) * 20);//TCHAR类型变量
TCHAR* id = (TCHAR*)malloc(sizeof(TCHAR) * 20);
TCHAR* sex = (TCHAR*)malloc(sizeof(TCHAR) * 3);
TCHAR* phone = (TCHAR*)malloc(sizeof(TCHAR) * 20);
TCHAR* birth = (TCHAR*)malloc(sizeof(TCHAR) * 111);
TCHAR* age = (TCHAR*)malloc(sizeof(TCHAR) * 3);
TCHAR* dateOfAdmission = (TCHAR*)malloc(sizeof(TCHAR) * 11);
TCHAR* address = (TCHAR*)malloc(sizeof(TCHAR) * 40);
TCHAR* mail = (TCHAR*)malloc(sizeof(TCHAR) * 40);
void TcharToChar(const TCHAR * tchar, char * _char);//将TCHAR类型字符转换为char类型
void CharToTchar(const char * _char, TCHAR * tchar);//将char类型字符转换为TCHAR类型
Student* CreateList();//创建一个链表的节点
Student* GetList();//取出文件中的链表
void deleteAppointStu(Student *Node);//删除指定ID的学生信息
Student* searchAppointID(Student *headNode);//查找指定ID的学生信息，若没有找到，返回空指针
Student* searchAppointName(Student *headNode);//查找指定姓名的学生信息，若没有找到，返回空指针
Student* listMergeSortSmalltoBig(Student* headNode);//按照ID对学生信息进行排序
Student* getMiddle(Student* headNode);//找到链表的中间位置,在归并排序函数中使用
int stringCompare(char str1[], char str2[]);//两个学生ID大小比较函数

int Interface;//全局变量，以确定当前所处界面,0表示主界面，1表示学生列表，2表示信息录入界面，3表示按姓名查询，4表示按学号查询，5表示学生列表的主界面
int page = 0;//全局变量，表示在学生列表显示时的页数
Student* list = CreateList();//全局变量，主要用于添加和删除学生信息

int counter = 0;//全局变量，用于存储链表中数据数量

void TcharToChar(const TCHAR * tchar, char * _char)
{
	int iLength;
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char    
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}

void deleteAppointStu(Student *Node) {
	FILE *fin, *ftp;
	char a[200] = { 0 };
	char target[200] = { 0 };
	fin = fopen("Data.txt", "r");//读打开原文件123.txt
	ftp = fopen("tmp.txt", "w");//新建并写打开临时文件tmp.txt
	strcat(target, Node->name);
	strcat(target, " ");
	strcat(target, Node->ID);
	strcat(target, " ");
	strcat(target, Node->sex);
	strcat(target, " ");
	strcat(target, Node->phone);
	strcat(target, " ");
	strcat(target, Node->birth);
	strcat(target, " ");
	strcat(target, Node->age);
	strcat(target, " ");
	strcat(target, Node->dateOfAdmission);
	strcat(target, " ");
	strcat(target, Node->address);
	strcat(target, " ");
	strcat(target, Node->mail);
	strcat(target, "\n");
	while (fgets(a, 200, fin))//从原文件读取一行
		if (strcmp(a,target))//检验是要删除的行吗?
			fputs(a, ftp);//不是则将这一行写入临时文件tmp.txt
	fclose(fin);
	fclose(ftp);
	remove("Data.txt");//删除原文件
	rename("tmp.txt", "Data.txt");//将临时文件名改为原文件名
}


Student* searchAppointID(Student *headNode) {
	Student* posNode = headNode->next;
	char posID[20];	
	InputBox(id, 20, _T("请输入要查找的学生学号"));
	FlushMouseMsgBuffer();
	TcharToChar(id, posID);
	while (strcmp(posID, posNode->ID)) {//进行遍历，若该结点学生ID不是指定ID且不为空，移向下一节点
		posNode = posNode->next;
		if (posNode == NULL) {//若以遍历完成,仍未找到			
			return NULL; //返回空指针
		}
	}	
	return posNode;//返回最终找到的结点
}


Student* searchAppointName(Student *headNode) {
	Student* posNode = headNode->next;
	
	char posName[20];
	InputBox(name, 20, _T("请输入要查找的学生姓名"));
	FlushMouseMsgBuffer();
	TcharToChar(name, posName);
	while (strcmp(posName, posNode->name)) {//进行遍历，若该结点学生姓名不是指定姓名且不为空，移向下一节点
		posNode = posNode->next;
		if (posNode == NULL) {//若以遍历完成,仍未找到			
			return NULL; //返回空指针
		}
	}
	
	return posNode;//返回最终找到的结点
}

Student* CreateList() {
	Student* node = (Student*)malloc(sizeof(Student));
	node->next = NULL;
	return node;
}



Student* GetList()
{
	FILE* fp = fopen("Data.txt","r+");
	Student *head = CreateList();
	Student *p;
	Student *q;
	p = q = head;
	char *name = (char*)malloc(sizeof(char)*20);
	char *ID = (char*)malloc(sizeof(char) * 20);
	char *age = (char*)malloc(sizeof(char) * 3);
	char *sex = (char*)malloc(sizeof(char) * 3);
	char *birth = (char*)malloc(sizeof(char) * 11);
	char *dateOfAdmission = (char*)malloc(sizeof(char) * 11);
	char *address = (char*)malloc(sizeof(char) * 40);
	char *phone = (char*)malloc(sizeof(char) * 20);
	char *mail = (char*)malloc(sizeof(char) * 40);
	memset(name, 0, 20);
	memset(ID, 0, 20);
	memset(age, 0, 3);
	memset(sex, 0, 3);
	memset(birth, 0, 11);
	memset(dateOfAdmission, 0, 11);
	memset(address, 0, 40);
	memset(phone, 0, 20);
	memset(mail, 0, 40);
	counter = 0;
	
	while (fscanf(fp, "%s %s %s %s %s %s %s %s %s", name,ID,sex,phone,birth,age,dateOfAdmission,address,mail) != EOF)
	{	
		
		q = CreateList();
		strcpy(q->name, name);		
		strcpy(q->ID, ID);
		strcpy(q->age, age);
		strcpy(q->sex, sex);
		strcpy(q->birth, birth);
		strcpy(q->dateOfAdmission, dateOfAdmission);
		strcpy(q->address, address);
		strcpy(q->phone, phone);
		strcpy(q->mail, mail);		
		p->next = q;
		p = q;
		counter++;		
	}
	p->next = NULL;
	fclose(fp);
	return head;
}
void CharToTchar(const char * _char, TCHAR * tchar)
{
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

Student* sortStuID(Student* headNode) {
	Student* posNode = headNode->next;
	if (posNode == NULL) {//若链表为空，无法排序
		puts("学生数据为空，无法进行排序操作。");
		return NULL;//返回空指针
	}
	return listMergeSortSmalltoBig(headNode);
}

Student* getMiddle(Student* headNode) {
	Student* fast = headNode->next;  //fast指向第2个节点
	Student* slow = headNode;	  //slow指向第1个节点	
	while (fast != NULL&&fast->next != NULL) {
		fast = fast->next->next; //fast每次走两步
		slow = slow->next;	//slow每次走一步，最终slow就会走到链表中点
	}
	return slow;//slow最后指向有n个元素的链表的第n/2个元素。
}
int stringCompare(char str1[],  char str2[]) {
	char *p1 = str1;
	char *p2 = str2;
	if (strcmp(p1, p2) <= 0)
		return 0;//若后者大于等于前者，返回1
	else
		return 1;//前者大于后者，返回0
}
//采用归并排序算法进行ID从小到大排序
Student* listMergeSortSmalltoBig(Student* headNode) {
	if (headNode->next == NULL)
		return headNode;
	Student* left = headNode;//将链表截断，左边从第一个开始
	Student* right = getMiddle(headNode)->next;//右边从n/2+1个(向下取整)开始
	getMiddle(headNode)->next = NULL;
	//假设上面截断的左右两个子链表调用归并排序后变成了排好序的“新”左右两个链表，然后开始归并
	Student* newLeft = listMergeSortSmalltoBig(left);
	Student* newRight = listMergeSortSmalltoBig(right);
	Student * newList;  //使用newList保存起点
	Student * tail;//tail为后面进行操作的指针
	if (stringCompare(newRight->ID, newLeft->ID)) {//进行大小比较,如果后者大于前者
		newList = newLeft;
		newLeft = newLeft->next;
	}
	else {
		newList = newRight;
		newRight = newRight->next;
	}
	tail = newList;
	tail->next = NULL;//向newList的第一个节点存入左右两个链表的头节点的较小的元素
	while (newLeft != NULL || newRight != NULL) {
		if (newLeft == NULL) {		//若左边全部接完，则右边整条链表接上去
			tail->next = newRight;
			newRight = NULL;
		}
		else if (newRight == NULL) {	//若右边全部接完，同上
			tail->next = newLeft;
			newLeft = NULL;
		}
		else if (stringCompare(newRight->ID, newLeft->ID)) {
			tail->next = newLeft;		//上面接一整个链表，这里是接链表中单个元素的操作
			newLeft = newLeft->next;
			tail = tail->next;
			tail->next = NULL;
		}
		else {
			tail->next = newRight;
			newRight = newRight->next;
			tail = tail->next;
			tail->next = NULL;
		}
	}
	return newList;   //返回新接好的链表。
}

