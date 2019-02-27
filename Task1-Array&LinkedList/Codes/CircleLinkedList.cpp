#include <iostream>
#include "stdio.h"
using namespace std;
typedef struct node{
	int data;
	struct node *next;
}Node, *pNode;
void initCLinkedList(pNode *list){//list����ͷ�ڵ㣬���������
	if (list == nullptr) return;
	int data = 0;
	pNode target=nullptr, head = nullptr;
	//�����½��ʱ���жϣ��������Ϊ�գ��򴴽�һ������ָ����ָ���Լ�������Ѱ��β�ڵ�target��
	//β���ָ����ָ���½ڵ㣬�½ڵ�ָ����ָ��ͷ�ڵ� 
	cout << "�����������ݣ�0���������ʼ����\n";
	while (cin >> data&&data!=0){
		if (*list==nullptr)
		{
			pNode head = (pNode)malloc(sizeof(Node));
			if (head == nullptr) exit(0);
			*list = head;
			pNode node = (pNode)malloc(sizeof(Node));
			node->data = data;
			node->next = head;
			head->next = node;
		}
		else{
			for (target = (*list)->next; target->next!=(*list); target = target->next);//�ҵ�β���
			pNode node = (pNode)malloc(sizeof(Node));
			node->data = data;
			node->next = (*list);//�½ڵ�ָ��ͷ�ڵ�
			target->next = node;//β���ָ���½ڵ�
		}
	}
	return;
}
void print(pNode head){
	if (head == nullptr) return;
	pNode p = head;
	cout << "Print LinkedList:\n";
	do{
		if (p->next!=head)
			cout << p->next->data<<' ';
		p = p->next;
	} while (p != head);
	cout << "\n\n";
}
//�ڵ�n��������룬�͵�����ʵ�ַ���һ��,ֻ������ѭ����������һ��
void insert(pNode head,int n,int data){
	if (head == nullptr || n <= 0) return;
	pNode p = head;
	int i = 1;
	while (i <= n&&p->next!=head)
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
void delNthNode(pNode head, int n, int &data){
	if (head == nullptr || head->next == nullptr || n <= 0) return;//�м���ж���������Ϊ��
	pNode p = head;
	int i = 1;
	while (i < n&&p->next->next!=head)
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
	data = pdel->data;
	delete(pdel);
}
void destory(pNode head){
	if (head == nullptr) return;
	pNode p = head;
	
	do{
		pNode pdel = p->next;
		p->next = p->next->next;
		delete pdel;
	}while (p!=head);
	delete p;
	cout << "Delete LinkedList successfully\n";
}

int main(int argv, char *argc[]){
	pNode list = nullptr;
	initCLinkedList(&list);
	print(list);
	insert(list, 2, 333);//�ڵ�2���������
	insert(list, 10, 3333);//����������������β�����
	print(list);
	int ret = 0;
	delNthNode(list, 2, ret);
	cout << "ɾ��������Ϊ��" << ret << endl;
	destory(list);
	return 0;
}