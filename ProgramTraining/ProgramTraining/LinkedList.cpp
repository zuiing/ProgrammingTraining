#include <iostream>
using namespace std;
typedef int ElementType;
typedef struct node{
	ElementType data;
	struct node *next;
}Node,*pNode;
pNode  creatList(){
	//��������ʱ��ô���һ��ͷ�ڵ㣬�ýڵ㲻������ݣ���ָ���һ��Ԫ��
	pNode head = (pNode)malloc(sizeof(Node));
	if (head == nullptr) return nullptr;
	head->next = nullptr;
	return head;
}
//ֱ�Ӳ���β��
void insertLast(pNode head,ElementType data){
	if (head == nullptr) return ;
	pNode p = head;
	while (p->next)   p = p->next;
	//����p����
	pNode pNew=(pNode)malloc(sizeof(Node));
	pNew->data = data;
	pNew->next = nullptr;
	p->next = pNew;
}
//�ڵ�n���������
void insert(pNode head, int n, ElementType data ){
	if (head == nullptr||n<=0) return;
	pNode p = head;
	int i = 1;
	while (i<=n&&p->next)
	{
		p = p->next; 
		i++;
	}
	if (i <= n) cout << "������Ԫ�ظ���С��" << n << "������ֱ�Ӳ���ĩβ\n";
	//ֱ�Ӳ���p����
	pNode pNew = (pNode)malloc(sizeof(Node));
	pNew->data = data;
	pNew->next = p->next;
	p->next = pNew;
}
//ɾ����n�����
void deleteNth(pNode head,int n){
	if (head == nullptr ||head->next==nullptr|| n <= 0) return;
	pNode p = head;
	int i = 1;
	while (i < n&&p->next->next)
	{
		p = p->next;
		i++;
	}
	//ɾ��p����Ľ��,��pΪɾ������ǰһ�����
	if (i < n - 1){
		cout << "������Ԫ�ظ���С��" << n << "����ɾ��ʧ��\n"; return;
	}
	pNode pdel = p->next;
	p->next = p->next->next;
	delete(pdel);
}
void print(pNode head){
	if (head == nullptr) return;
	pNode p = head;
	cout << "Print LinkedList:\n[";
	while (p->next)
	{
		cout << p->next->data;
		if (p->next->next!= nullptr) cout << ',';
		p = p->next;
	}
	cout << "]\n\n";
}
void destory(pNode head){
	if (head == nullptr) return;
	pNode p = head;
	while (p->next)
	{
		pNode pdel = p->next;
		p->next = p->next->next;
		delete pdel;
	}
	delete p;
	cout << "Delete LinkedList successfully\n";
}

int main0(int argv, char *argc[]){
	pNode linkList = creatList();
	insertLast(linkList, 2);
	insertLast(linkList, 22);
	insertLast(linkList, 222);//β��
	print(linkList);
	insert(linkList, 6, 333);//�ڵ�2���������
	print(linkList);
	deleteNth(linkList, 2);//ɾ����2�����
	deleteNth(linkList,10);
	print(linkList);
	return 0;
}