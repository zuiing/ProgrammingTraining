#include <iostream>
using namespace std;
/*
**Ϊ�����˫������������������������㣬���������ڼ�¼�������ͷ��β����ǰָ���Լ�������
*/
typedef struct node{
	int data;
	struct node *prev, *next;
}Node,*pNode;
typedef struct LinkedList
{
	pNode head,tail,cur;
	int size;
}LinkedList;
/*
**���������ɹ���������ָ�룬���򷵻�nullptr,��ע�⣬��ʱ����Ϊ��
*/
LinkedList* CreateList(){
	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	if (list == nullptr) return nullptr;
	list->head = nullptr;
	list->tail = nullptr;
	list->cur = nullptr;
	list->size = 0;
	return list;
}
//β������ �ɹ���������size�����򷵻�-1
int insertBack(LinkedList* list, int data){
	if (list == nullptr) return -1;
	pNode pNew = (pNode)malloc(sizeof(Node));
	if (pNew == nullptr) return -1;
	pNew->data = data;//.
	pNew->next = nullptr;//..
	//...
	if (list->tail)//����Ϊ��
	{
		list->tail->next = pNew;
		pNew->prev = list->tail;		
	}
	else{
		pNew->prev = nullptr;
		list->head = pNew;
	}
	list->tail = pNew;//....
	return ++list->size;
}
//ͷ������ �ɹ���������size�����򷵻�-1
int insertFront(LinkedList* list, int data){
	if (list == nullptr) return -1;
	pNode pNew = (pNode)malloc(sizeof(Node));
	if (pNew == nullptr) return -1;
	pNew->data = data;//.
	pNew->prev = nullptr;//..����������ͷ��ʱ�ý��ǰ����Ϊnull
	//...
	if (list->head)//����Ϊ��
	{
		list->head->prev = pNew;
		pNew->next = list->head;
	}
	else{
		pNew->next = nullptr;
		list->tail = pNew;
	}
	list->head = pNew;//....
	return ++list->size;

}
//��ĩ��ɾ�����ɹ�ɾ������ɾ���Ľ��
int removeBack(LinkedList* list){
	if (list == nullptr) return 0;
	if (!list->size){ cout << "����Ϊ��..."; return 0; }
	pNode del = list->tail;
	int ret = del->data;
	if (list->head == list->tail){//ɾ��������Ϊ��
		list->head = nullptr;
		list->tail = nullptr;
		list->cur = nullptr;
	}
	else{
		list->tail = list->tail->prev;
		list->tail->next = nullptr;
	}
	delete del;
	list->size--;
	return ret;
}
//��ǰ��ɾ�����ɹ�ɾ������ɾ���Ľ��
int removeFront(LinkedList* list){
	if (list == nullptr) return 0;
	if (!list->size){ cout << "����Ϊ��..."; return 0; }
	pNode del = list->head;
	int ret = del->data;
	if (list->head == list->tail){//ɾ��������Ϊ��
		list->head = nullptr;
		list->tail = nullptr;
		list->cur = nullptr;
	}
	else{
		list->head->prev = nullptr;
		list->head = list->head->next;
	}
	delete del;
	list->size--;
	return ret;
}
bool isEmpty(LinkedList* list){
	return !list->size;
}
//����ǰλ���Ƶ�����ͷ
void Begin(LinkedList* list){
	list->cur = list->head;
}
void End(LinkedList* list){
	list->cur = list->tail;
}
//��ǰλ��֮���Ƿ��н��
bool hasNext(LinkedList* list){
	if (list->cur == nullptr) return false;
	if (list->cur == list->tail) return true;//�����βʱҲ������
	return list->cur->next != nullptr;
}
bool hasPrev(LinkedList* list){
	if (list->cur == nullptr) return false;
	if (list->cur == list->head) return true;
	return list->cur->prev != nullptr;
}
void moveNext(LinkedList* list){
	list->cur = list->cur->next;
}
void movePrev(LinkedList* list){
	list->cur = list->cur->prev;
}
int currentData(LinkedList* list){
	return list->cur->data;
}
void traverse(LinkedList* list){
	for (Begin(list);hasNext(list);moveNext(list))
	{
		cout << currentData(list) << " ";
	}
	cout << "\n\n";
}
//�����ӡ
void rTraverse(LinkedList* list){
	for(End(list);hasPrev(list);movePrev(list))
	{
		cout << currentData(list) << " ";
	}
	cout << "\n\n";
}
//�����ڴ�
void destory(LinkedList* list){
	while (!isEmpty(list))
	{
		removeBack(list);
	}
}
int main(int argv, char *argc[]){
	LinkedList *list = CreateList();
	insertFront(list, 2);
	insertFront(list, 22);
	insertFront(list, 222);
	insertBack(list, 1);
	insertBack(list, 11);
	insertBack(list, 111);
	cout << "�����ӡ����\n";
	traverse(list);
	cout << "�����ӡ����\n";
	rTraverse(list);
	removeBack(list);
	removeFront(list);
	cout << "ɾ��ͷβ���������ӡ����\n";
	traverse(list);
	destory(list);
	return 0;
}