#include <iostream>
using namespace std;
/*
**依然使用模板构造类
**数组实现的队列支持动态扩容，
**但是由于入队放数组末尾，出队从数组头部拿数据，因此会造成数组空间浪费，若使用循环队列则能解决这个问题
*/
const int initialLen = 10;
template <typename T>
class ArrayQueue{
public:
	ArrayQueue(int cap = initialLen){
		T *p = new T[cap];
		data = p;
		capacity = cap;
		size = 0;
		head = 0; 
	}
	~ArrayQueue(){
		delete []data;
	}
	bool isEmpty(){
		return size == 0;
	}
	bool isFull(){
		return size == capacity;
	}
	int Size(){
		return size;
	}
	void reSize(int len){
		T *p = new T[len];
		for (int i = 0; i < size;i++)
		{
			p[i] = data[i];
		}
		delete []data;
		data = p;
		capacity = len;
	}
	void traverse(){
		cout << "Array: ";
		cout << "Capacity = " << capacity << ", " << "Size = " << size-head << endl;
		cout << '[';
		for (int i = head; i < size; ++i){
			cout << data[i];
			if (i != size - 1){
				cout << ',';
			}
		}
		cout << ']' << endl;		
	}
	void Push(T x){
		if (size == capacity) reSize(capacity * 2);
		data[size] = x;
		size++;
	}
	T Pop(){
		T ret = data[head];
		head++;
		return ret;
	}
	T Front(){
		return data[head];
	}
private:
	T *data;
	int capacity;
	int size;
	int head;
};

int main2(){
	ArrayQueue<int> queue(5);
	queue.Push(2);
	queue.Push(22);
	queue.Push(222);
	queue.Push(3333);
	queue.Push(33333);
	queue.Push(333333);
	queue.Pop();
	cout << "此时队首元素为：" << queue.Front()<<endl;
	queue.traverse();

	return 0;
}