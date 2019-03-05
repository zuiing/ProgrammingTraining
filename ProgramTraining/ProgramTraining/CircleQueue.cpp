#include <iostream>
using namespace std;
template<typename T>
class CircleQueue{
private:
	T *data;
	int front, rear;
	int capacity;
public:
	CircleQueue(int sz=10){
		front = rear = 0;
		capacity = sz;
		data = new T[capacity];
	}
	~CircleQueue(){
		delete[] data;
	}
	bool Push(T x){//EnQueue
		if (isFull()) {
			cout << "队列已满\n";
			return false;
		}
		data[rear] = x;
		rear = (rear + 1) % capacity;
		return true;
	}
	bool Pop(T& x){//DeQueue
		if (isEmpty()) return false;
		x = data[front];
		front = (front + 1) % capacity;
		return true;
	}
	T Front(){//take the front element
		if (isEmpty()) return -1;
		return data[front];
	}
	bool isEmpty(){
		return (front == rear) ? true : false;
	}
	bool isFull(){
		return ((rear + 1) % capacity == front) ? true : false;
	}
	void makeEmpty(){
		front = rear;
	}
	void Traverse(){
		for (int i = front;i!=rear;i=(i+1)%capacity)
		{
			cout << data[i] << ' ';
		}cout << endl;
	}
};
int main0(){
	CircleQueue<int> queue(5);
	queue.Push(2);
	queue.Push(22);
	queue.Push(222);
	queue.Push(333);
	int x;
	queue.Pop(x);
	cout << "出队的元素为：" << x << endl;
	queue.Push(333);
	queue.Push(444);//此时队列已满
	queue.Traverse();//遍历队列
	return 0;
}




