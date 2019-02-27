#include <iostream>
using namespace std;
typedef int ElementType;
typedef struct node{
	ElementType data;
	struct node *next;
}Node,*pNode;
pNode  creatList(){
	//创建链表时最好创建一个头节点，该节点不存放数据，它指向第一个元素
	pNode head = (pNode)malloc(sizeof(Node));
	if (head == nullptr) return nullptr;
	head->next = nullptr;
	return head;
}
//直接插入尾部
void insertLast(pNode head,ElementType data){
	if (head == nullptr) return ;
	pNode p = head;
	while (p->next)   p = p->next;
	//插入p后面
	pNode pNew=(pNode)malloc(sizeof(Node));
	pNew->data = data;
	pNew->next = nullptr;
	p->next = pNew;
}
//在第n个结点后插入
void insert(pNode head, int n, ElementType data ){
	if (head == nullptr||n<=0) return;
	pNode p = head;
	int i = 1;
	while (i<=n&&p->next)
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
void deleteNth(pNode head,int n){
	if (head == nullptr ||head->next==nullptr|| n <= 0) return;
	pNode p = head;
	int i = 1;
	while (i < n&&p->next->next)
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
	insertLast(linkList, 222);//尾插
	print(linkList);
	insert(linkList, 6, 333);//在第2个结点后插入
	print(linkList);
	deleteNth(linkList, 2);//删除第2个结点
	deleteNth(linkList,10);
	print(linkList);
	return 0;
}