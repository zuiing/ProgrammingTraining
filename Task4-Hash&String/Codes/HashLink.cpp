#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define N 10 //hash���������
typedef struct hash_node{
	char ch_value[100];
	struct hash_node *pre;//ָ����һ�����ָ��
	struct hash_node *cur;//ÿ��hash_table[k]��βָ��
	//û�и�ָ�룬ÿ�β��뵽��Ӧ������Ҫ��ͷ��β�����������ָ�룬�ɽ��ѭ����ͻ���������
	struct hash_node *next;//ָ����һ���ڵ�

}hashNode;
//��ʼ����ϣ��
hashNode** initHashTable(){
	hashNode **hashTab = (hashNode**)malloc(N*sizeof(hashNode));	
	for (int i = 0; i < N;i++)
	{
		hashTab[i] = nullptr;
	}
	return hashTab;
}
//����hash�������������ַ���ASCII����ϣ
int hashFun(const char* ch){
	int sum = 0;
	for (int i = 0; i < strlen(ch); i++)
	{
		sum += ch[i];
	}
	return sum%N;
}
//��������
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
//���Һ���
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
//�ͷŹ�ϣ��ÿ����
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
//ɾ������
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
		if (ptr_new==ptr_tmp)//����ֻ��һ��Ԫ��
		{
			hashTab[key] = ptr_tmp->next;
			free(ptr_tmp);
			ptr_tmp = nullptr;
		}
		else{
			//�����в���Ҫɾ���Ľڵ�
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
//��ӡÿ�����ϵ�����
void printHashTable(hashNode** hashTab){
	for (int i = 0; i < N;i++)
	{
		hashNode* ptr_tmp = hashTab[i];
		cout << "��" << i << "������";
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

	cout << "\n�����ַ���2222" << endl;
	if (findHashTable("2222",hashTab)!=nullptr)
		cout << "find\n";
	else cout << "not find\n";
	deleteHashTable("2222", hashTab);
	cout << "ɾ���ַ���2222֮��,�ٲ��Ҹ��ַ�����" << endl;
	if (findHashTable("2222", hashTab) != nullptr)
		cout << "find\n";
	else cout << "not find\n";
	return 0;
}