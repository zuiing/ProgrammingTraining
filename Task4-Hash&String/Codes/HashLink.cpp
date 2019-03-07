#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define N 10 //hash链表的数量
typedef struct hash_node{
	char ch_value[100];
	struct hash_node *pre;//指向上一个结点指针
	struct hash_node *cur;//每个hash_table[k]的尾指针
	//没有该指针，每次插入到对应的链都要从头到尾遍历，加入该指针，可解决循环冲突链表的问题
	struct hash_node *next;//指向下一个节点

}hashNode;
//初始化哈希表
hashNode** initHashTable(){
	hashNode **hashTab = (hashNode**)malloc(N*sizeof(hashNode));	
	for (int i = 0; i < N;i++)
	{
		hashTab[i] = nullptr;
	}
	return hashTab;
}
//定义hash函数，这里用字符串ASCII来哈希
int hashFun(const char* ch){
	int sum = 0;
	for (int i = 0; i < strlen(ch); i++)
	{
		sum += ch[i];
	}
	return sum%N;
}
//插入数据
void insertHashTable(const char* ch,hashNode** hashTab){
	int key = hashFun(ch);
	hashNode* ptr_new = (hashNode*)malloc(sizeof(hashNode));
	strcpy_s(ptr_new->ch_value, ch);
	ptr_new->pre = nullptr;
	ptr_new->next = nullptr;
	ptr_new->cur = nullptr;

	hashNode *ptr_head = hashTab[key];
	if (ptr_head==nullptr){
		hashTab[key] = ptr_new;
		hashTab[key]->cur = ptr_new;
	}
	else{
		hashTab[key]->cur->next = ptr_new;
		ptr_new->pre = hashTab[key]->cur;
		hashTab[key]->cur = ptr_new;
	}
}
//查找函数
hashNode* findHashTable(const char* ch,hashNode** hashTab){
	int key = hashFun(ch);
	hashNode* ptr_new = hashTab[key];
	if (ptr_new == nullptr) return nullptr;
	while (ptr_new!=nullptr)
	{
		int res = strcmp(ptr_new->ch_value, ch);
		if (res == 0) return ptr_new;
		ptr_new = ptr_new->next;
	}
	return nullptr;
}
//释放哈希表每条链
void freeHashTable(hashNode** hashTab){
	hashNode* ptr_move;
	for (int i = 0; i < N;i++)
	{
		ptr_move = hashTab[i];
		while (ptr_move != nullptr)
		{
			hashNode *del = ptr_move;
			ptr_move = ptr_move->next;
			free(del);
			del = nullptr;
		}
	}
}
//删除函数
int deleteHashTable(const char* ch,hashNode** hashTab){
	int key = hashFun(ch);
	hashNode* ptr_new = hashTab[key];
	hashNode* ptr_tmp = findHashTable(ch, hashTab);
	if (hashTab[key]==nullptr||ptr_tmp==nullptr)
	{
		cout << "error!"; return 0;
	}
	if (ptr_tmp!=nullptr)
	{
		if (ptr_new==ptr_tmp)//该链只有一个元素
		{
			hashTab[key] = ptr_tmp->next;
			free(ptr_tmp);
			ptr_tmp = nullptr;
		}
		else{
			//从链中查找要删除的节点
			while (ptr_new->next!=ptr_tmp)
			{
				ptr_new = ptr_new->next;
			}
			ptr_new->next = ptr_tmp->next;
			free(ptr_tmp);
			ptr_tmp = nullptr;
			hashTab[key]->cur = ptr_new;
			ptr_new->next = nullptr;
			ptr_new->cur = nullptr;
		}
	}
}
//打印每条链上的数据
void printHashTable(hashNode** hashTab){
	for (int i = 0; i < N;i++)
	{
		hashNode* ptr_tmp = hashTab[i];
		cout << "第" << i << "条链：";
		if (ptr_tmp!=nullptr)
		{
			while (ptr_tmp!=nullptr)
			{
				cout << ptr_tmp->ch_value<<" ";
				ptr_tmp = ptr_tmp->next;
			}
		}
		cout << endl;
	}
}
int main1(){
	hashNode** hashTab = initHashTable();
	insertHashTable("0000000000000", hashTab);
	insertHashTable("angry", hashTab);
	insertHashTable("2222", hashTab);
	insertHashTable("hashTable", hashTab);
	insertHashTable("32", hashTab);
	insertHashTable("23", hashTab);
	insertHashTable("24", hashTab);
	insertHashTable("25", hashTab);
	insertHashTable("26", hashTab);
	insertHashTable("27", hashTab);
	insertHashTable("28", hashTab);
	printHashTable(hashTab);

	cout << "\n查找字符串2222" << endl;
	if (findHashTable("2222",hashTab)!=nullptr)
		cout << "find\n";
	else cout << "not find\n";
	deleteHashTable("2222", hashTab);
	cout << "删除字符串2222之后,再查找该字符串：" << endl;
	if (findHashTable("2222", hashTab) != nullptr)
		cout << "find\n";
	else cout << "not find\n";
	return 0;
}