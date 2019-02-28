#include <iostream>
using namespace std;
/*
**为方便对双向链表操作，还创建了链表结点，链表结点用于记录链表本身的头、尾、当前指针以及结点个数
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
**创建链表，成功返回链表指针，否则返回nullptr,需注意，此时链表为空
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
//尾部插入 成功返回链表size，否则返回-1
int insertBack(LinkedList* list, int data){
	if (list == nullptr) return -1;
	pNode pNew = (pNode)malloc(sizeof(Node));
	if (pNew == nullptr) return -1;
	pNew->data = data;//.
	pNew->next = nullptr;//..
	//...
	if (list->tail)//链表不为空
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
//头部插入 成功返回链表size，否则返回-1
int insertFront(LinkedList* list, int data){
	if (list == nullptr) return -1;
	pNode pNew = (pNode)malloc(sizeof(Node));
	if (pNew == nullptr) return -1;
	pNew->data = data;//.
	pNew->prev = nullptr;//..不管怎样，头插时该结点前驱总为null
	//...
	if (list->head)//链表不为空
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
//从末端删除，成功删除返回删除的结点
int removeBack(LinkedList* list){
	if (list == nullptr) return 0;
	if (!list->size){ cout << "链表为空..."; return 0; }
	pNode del = list->tail;
	int ret = del->data;
	if (list->head == list->tail){//删除后链表为空
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
//从前端删除，成功删除返回删除的结点
int removeFront(LinkedList* list){
	if (list == nullptr) return 0;
	if (!list->size){ cout << "链表为空..."; return 0; }
	pNode del = list->head;
	int ret = del->data;
	if (list->head == list->tail){//删除后链表为空
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
//将当前位置移到链表开头
void Begin(LinkedList* list){
	list->cur = list->head;
}
void End(LinkedList* list){
	list->cur = list->tail;
}
//当前位置之后是否还有结点
bool hasNext(LinkedList* list){
	if (list->cur == nullptr) return false;
	if (list->cur == list->tail) return true;//到达结尾时也返回真
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
//反向打印
void rTraverse(LinkedList* list){
	for(End(list);hasPrev(list);movePrev(list))
	{
		cout << currentData(list) << " ";
	}
	cout << "\n\n";
}
//回收内存
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
	cout << "正向打印链表：\n";
	traverse(list);
	cout << "反向打印链表：\n";
	rTraverse(list);
	removeBack(list);
	removeFront(list);
	cout << "删除头尾结点后正向打印链表：\n";
	traverse(list);
	destory(list);
	return 0;
}