#include <iostream>
using namespace std;
/*
**��Ȼʹ��ģ�幹����
**����ʵ�ֵĶ���֧�ֶ�̬���ݣ�
**����������ӷ�����ĩβ�����Ӵ�����ͷ�������ݣ���˻��������ռ��˷ѣ���ʹ��ѭ���������ܽ���������
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
	cout << "��ʱ����Ԫ��Ϊ��" << queue.Front()<<endl;
	queue.traverse();

	return 0;
}