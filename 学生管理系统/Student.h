#pragma once
/*
���ļ������ڴ�������ʱ�õ��ĺ���
���ߣ������������񶫣�����
*/
struct Student
{
	char name[20];//����
	char ID[20];//ѧ��
	char age[3];//����
	char sex[3];//�Ա�,true��ʾ�У�false��ʾŮ
	char birth[11];//��������
	char dateOfAdmission[11];//��ѧ����
	char address[40];//��ַ
	char phone[20];//�绰
	char mail[40];//����
	struct Student *next;//ָ����һ�ڵ�
};
TCHAR* name = (TCHAR*)malloc(sizeof(TCHAR) * 20);//TCHAR���ͱ���
TCHAR* id = (TCHAR*)malloc(sizeof(TCHAR) * 20);
TCHAR* sex = (TCHAR*)malloc(sizeof(TCHAR) * 3);
TCHAR* phone = (TCHAR*)malloc(sizeof(TCHAR) * 20);
TCHAR* birth = (TCHAR*)malloc(sizeof(TCHAR) * 111);
TCHAR* age = (TCHAR*)malloc(sizeof(TCHAR) * 3);
TCHAR* dateOfAdmission = (TCHAR*)malloc(sizeof(TCHAR) * 11);
TCHAR* address = (TCHAR*)malloc(sizeof(TCHAR) * 40);
TCHAR* mail = (TCHAR*)malloc(sizeof(TCHAR) * 40);
void TcharToChar(const TCHAR * tchar, char * _char);//��TCHAR�����ַ�ת��Ϊchar����
void CharToTchar(const char * _char, TCHAR * tchar);//��char�����ַ�ת��ΪTCHAR����
Student* CreateList();//����һ������Ľڵ�
Student* GetList();//ȡ���ļ��е�����
void deleteAppointStu(Student *Node);//ɾ��ָ��ID��ѧ����Ϣ
Student* searchAppointID(Student *headNode);//����ָ��ID��ѧ����Ϣ����û���ҵ������ؿ�ָ��
Student* searchAppointName(Student *headNode);//����ָ��������ѧ����Ϣ����û���ҵ������ؿ�ָ��
Student* listMergeSortSmalltoBig(Student* headNode);//����ID��ѧ����Ϣ��������
Student* getMiddle(Student* headNode);//�ҵ�������м�λ��,�ڹ鲢��������ʹ��
int stringCompare(char str1[], char str2[]);//����ѧ��ID��С�ȽϺ���

int Interface;//ȫ�ֱ�������ȷ����ǰ��������,0��ʾ�����棬1��ʾѧ���б�2��ʾ��Ϣ¼����棬3��ʾ��������ѯ��4��ʾ��ѧ�Ų�ѯ��5��ʾѧ���б��������
int page = 0;//ȫ�ֱ�������ʾ��ѧ���б���ʾʱ��ҳ��
Student* list = CreateList();//ȫ�ֱ�������Ҫ������Ӻ�ɾ��ѧ����Ϣ

int counter = 0;//ȫ�ֱ��������ڴ洢��������������

void TcharToChar(const TCHAR * tchar, char * _char)
{
	int iLength;
	//��ȡ�ֽڳ���   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//��tcharֵ����_char    
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}

void deleteAppointStu(Student *Node) {
	FILE *fin, *ftp;
	char a[200] = { 0 };
	char target[200] = { 0 };
	fin = fopen("Data.txt", "r");//����ԭ�ļ�123.txt
	ftp = fopen("tmp.txt", "w");//�½���д����ʱ�ļ�tmp.txt
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
	while (fgets(a, 200, fin))//��ԭ�ļ���ȡһ��
		if (strcmp(a,target))//������Ҫɾ��������?
			fputs(a, ftp);//��������һ��д����ʱ�ļ�tmp.txt
	fclose(fin);
	fclose(ftp);
	remove("Data.txt");//ɾ��ԭ�ļ�
	rename("tmp.txt", "Data.txt");//����ʱ�ļ�����Ϊԭ�ļ���
}


Student* searchAppointID(Student *headNode) {
	Student* posNode = headNode->next;
	char posID[20];	
	InputBox(id, 20, _T("������Ҫ���ҵ�ѧ��ѧ��"));
	FlushMouseMsgBuffer();
	TcharToChar(id, posID);
	while (strcmp(posID, posNode->ID)) {//���б��������ý��ѧ��ID����ָ��ID�Ҳ�Ϊ�գ�������һ�ڵ�
		posNode = posNode->next;
		if (posNode == NULL) {//���Ա������,��δ�ҵ�			
			return NULL; //���ؿ�ָ��
		}
	}	
	return posNode;//���������ҵ��Ľ��
}


Student* searchAppointName(Student *headNode) {
	Student* posNode = headNode->next;
	
	char posName[20];
	InputBox(name, 20, _T("������Ҫ���ҵ�ѧ������"));
	FlushMouseMsgBuffer();
	TcharToChar(name, posName);
	while (strcmp(posName, posNode->name)) {//���б��������ý��ѧ����������ָ�������Ҳ�Ϊ�գ�������һ�ڵ�
		posNode = posNode->next;
		if (posNode == NULL) {//���Ա������,��δ�ҵ�			
			return NULL; //���ؿ�ָ��
		}
	}
	
	return posNode;//���������ҵ��Ľ��
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
	if (posNode == NULL) {//������Ϊ�գ��޷�����
		puts("ѧ������Ϊ�գ��޷��������������");
		return NULL;//���ؿ�ָ��
	}
	return listMergeSortSmalltoBig(headNode);
}

Student* getMiddle(Student* headNode) {
	Student* fast = headNode->next;  //fastָ���2���ڵ�
	Student* slow = headNode;	  //slowָ���1���ڵ�	
	while (fast != NULL&&fast->next != NULL) {
		fast = fast->next->next; //fastÿ��������
		slow = slow->next;	//slowÿ����һ��������slow�ͻ��ߵ������е�
	}
	return slow;//slow���ָ����n��Ԫ�ص�����ĵ�n/2��Ԫ�ء�
}
int stringCompare(char str1[],  char str2[]) {
	char *p1 = str1;
	char *p2 = str2;
	if (strcmp(p1, p2) <= 0)
		return 0;//�����ߴ��ڵ���ǰ�ߣ�����1
	else
		return 1;//ǰ�ߴ��ں��ߣ�����0
}
//���ù鲢�����㷨����ID��С��������
Student* listMergeSortSmalltoBig(Student* headNode) {
	if (headNode->next == NULL)
		return headNode;
	Student* left = headNode;//������ضϣ���ߴӵ�һ����ʼ
	Student* right = getMiddle(headNode)->next;//�ұߴ�n/2+1��(����ȡ��)��ʼ
	getMiddle(headNode)->next = NULL;
	//��������ضϵ�����������������ù鲢����������ź���ġ��¡�������������Ȼ��ʼ�鲢
	Student* newLeft = listMergeSortSmalltoBig(left);
	Student* newRight = listMergeSortSmalltoBig(right);
	Student * newList;  //ʹ��newList�������
	Student * tail;//tailΪ������в�����ָ��
	if (stringCompare(newRight->ID, newLeft->ID)) {//���д�С�Ƚ�,������ߴ���ǰ��
		newList = newLeft;
		newLeft = newLeft->next;
	}
	else {
		newList = newRight;
		newRight = newRight->next;
	}
	tail = newList;
	tail->next = NULL;//��newList�ĵ�һ���ڵ�����������������ͷ�ڵ�Ľ�С��Ԫ��
	while (newLeft != NULL || newRight != NULL) {
		if (newLeft == NULL) {		//�����ȫ�����꣬���ұ������������ȥ
			tail->next = newRight;
			newRight = NULL;
		}
		else if (newRight == NULL) {	//���ұ�ȫ�����꣬ͬ��
			tail->next = newLeft;
			newLeft = NULL;
		}
		else if (stringCompare(newRight->ID, newLeft->ID)) {
			tail->next = newLeft;		//�����һ�������������ǽ������е���Ԫ�صĲ���
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
	return newList;   //�����½Ӻõ�����
}

