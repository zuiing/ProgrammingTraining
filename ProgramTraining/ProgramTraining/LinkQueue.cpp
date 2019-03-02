#include <iostream>
using namespace std;
template <typename T>
struct LinkNode{
	T data;
	struct LinkNode<T> *next;
	LinkNode(T& x, struct LinkNode<T> *p = nullptr){
		data = x;
		next = p;
	}
};
template <typename T>
class LinkedQueue
{
public:
	LinkedQueue(){
		front = rear = nullptr;
	}
	~LinkedQueue(){
		DestoryList();
	}

private:
	LinkNode<T> *front, *rear;

public:
	bool Push(T data){
		LinkNode<T> *node = new LinkNode<T>(data);
		if (front == nullptr)
			front = rear = node;
		else{
			rear->next = node;
			rear = rear->next;
		}
		return true;
	}
	bool Pop(T& x){
		if (isEmpty()) return false;
		LinkNode<T> *del=front;
		front = front->next;
		x = del->data;
		delete del;
		return true;
	}
	//该成员函数加了const，意思是该函数不能更改类数据成员的值
	//一旦企图更改，编译器按错误处理，提高程序的可读性
	bool Front(T& x) const{//取队首元素
		if (isEmpty()) return false;
		x = front->data;
		return true;
	}
	bool isEmpty(){
		return (front == rear) ? true : false;
	}
	int Size(){
		int ret=0;
		LinkNode<T> *p=front;
		while (p)
		{
			ret++;
			p = p->next;
		}
		return ret;
	}
	void Traverse(){
		LinkNode<T> *p=front;
		cout << "遍历链式队列：";
		while (p)
		{
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
	void DestoryList(){
		LinkNode<T> *p;
		while (front)
		{
			p = front;
			front = front->next;
			delete p;
		}
	}
};

int main3(){
	LinkedQueue<int> queue;
	queue.Push(2);
	queue.Push(3);
	queue.Push(4);
	queue.Push(5);
	int a; 
	queue.Front(a);
	cout << "队首元素为：" << a<<endl;
	queue.Pop(a);//将队首元素删除，并放在a中
	queue.Traverse();
	queue.DestoryList();
	return 0;
}