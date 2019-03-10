#include <iostream>
#include <map>
using namespace std;
/*
**definition oa cachelist node,it's a double linked list node.
*/
struct CacheNode
{
	int key, value;
	struct CacheNode *pre, *next;
	CacheNode(int k, int v) :key(k), value(v), pre(nullptr), next(nullptr){ }
};
class LRUCache
{
private:
	int size;//Maximum of Cachelist size
	CacheNode *head, *tail;
	map<int, CacheNode*> mp;
public:
	LRUCache(int capacity){
		size = capacity;
		head = nullptr;
		tail = nullptr;
	}
	~LRUCache(){}

	int get(int key){
		map<int, CacheNode*>::iterator it = mp.find(key);
		if (it!=mp.end())
		{
			CacheNode *node = it->second;
			remove(node);
			setHead(node);
			return node->value;
		}
		else
		return -1;
	}
	void put(int key,int value){
		map<int, CacheNode*>::iterator it= mp.find(key);
		if (it!=mp.end())
		{
			CacheNode *node = it->second;
			node->value = value;
			remove(node);
			setHead(node);
		}
		else{
			CacheNode *newNode = new CacheNode(key, value);
			if (mp.size()>=size)
			{
				map<int, CacheNode*>::iterator it = mp.find(tail->key);
				remove(tail);
				mp.erase(it);
			}
			setHead(newNode);
			mp[key] = newNode;
		}
	}
	void remove(CacheNode* node){
		if (node->pre != nullptr)
			node->pre->next = node->next;
		else
			head = node->next;
		if (node->next != nullptr)
			node->next->pre = node->pre;
		else
			tail = node->next;
	}
	void setHead(CacheNode *node){
		node->next = head;
		node->pre = nullptr;
		if (head != nullptr)
			head->pre = node;
		head = node;
		if (tail == nullptr)
			tail = head;
	}
};


int mainLRU(){
	LRUCache *lruCache = new LRUCache(3);
	lruCache->put(1, 2);
	lruCache->put(11, 22);
	lruCache->put(111, 222);
	cout << lruCache->get(1) << endl;//Êä³ö2
	lruCache->put(1111, 2222);
	cout << lruCache->get(111) << endl;//Êä³ö222
	cout << lruCache->get(1) << endl;//Êä³ö-1
	return 0;
}