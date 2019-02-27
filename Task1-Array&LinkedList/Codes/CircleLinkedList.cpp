#include <iostream>
#include "stdio.h"
using namespace std;
typedef struct node{
	int data;
	struct node *next;
}Node, *pNode;
void initCLinkedList(pNode *list){//list代表头节点，不存放数据
	if (list == nullptr) return;
	int data = 0;
	pNode target=nullptr, head = nullptr;
	//插入新结点时，判断：如果链表为空，则创建一个链表，指针域指向自己，否则寻找尾节点target，
	//尾结点指针域指向新节点，新节点指针域指向头节点 
	cout << "请输入结点数据，0代表结束初始化：\n";
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
			for (target = (*list)->next; target->next!=(*list); target = target->next);//找到尾结点
			pNode node = (pNode)malloc(sizeof(Node));
			node->data = data;
			node->next = (*list);//新节点指向头节点
			target->next = node;//尾结点指向新节点
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
//在第n个结点后插入，和单链表实现方法一样,只是跳出循环的条件不一样
void insert(pNode head,int n,int data){
	if (head == nullptr || n <= 0) return;
	pNode p = head;
	int i = 1;
	while (i <= n&&p->next!=head)
	{
		p = p->next;
		i++;
	}
	if (i <= n) cout << "链表中元素个数小于" << n << "个，将直接插入末尾\n";
	//直接插入p后面
	pNode pNew = (pNode)malloc(sizeof(Node));
	pNew->data = data;
	pNew->next = p->next;
	p->next = pNew;
}
//删除第n个结点
void delNthNode(pNode head, int n, int &data){
	if (head == nullptr || head->next == nullptr || n <= 0) return;//中间的判断属于链表为空
	pNode p = head;
	int i = 1;
	while (i < n&&p->next->next!=head)
	{
		p = p->next;
		i++;
	}
	//删除p后面的结点,即p为删除结点的前一个结点
	if (i < n - 1){
		cout << "链表中元素个数小于" << n << "个，删除失败\n"; return;
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
	insert(list, 2, 333);//在第2个结点后插入
	insert(list, 10, 3333);//超过结点个数，将在尾部添加
	print(list);
	int ret = 0;
	delNthNode(list, 2, ret);
	cout << "删除的数据为：" << ret << endl;
	destory(list);
	return 0;
}