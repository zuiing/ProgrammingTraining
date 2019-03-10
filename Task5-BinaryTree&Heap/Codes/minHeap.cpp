#include <iostream>
#include <vector>
using namespace std;
template<typename T>
class minHeap{
private:
	int capacity;
	int size;
	vector<T> data;
public:
	minHeap(T buff[], int len);
	minHeap(int capacity);
	virtual ~minHeap();
	int getSize();
	bool isFull();
	bool isEmpty();
	void swap(vector<T> &vec, int i, int j);
	void floating(int index);
	void sink(int index);
	bool push(T dt);
	bool pop(int index);
	void print();
};

template<typename T>
void minHeap<T>::print()
{
	cout << "heap:";
	for (int i = 0; i < size;i++)
	{
		cout << data[i] << ' ';
	}
	cout << "\n\n";
}

/*删除元素
**1.把堆的第index个元素删除，并把堆的最后一个元素放到index处；
**2.把堆的第index个元素下沉。
*/
template<typename T>
bool minHeap<T>::pop(int index)
{
	if (isEmpty()) return false;
	data[index] = data[size - 1];
	size--;
	sink(index + 1);
}
/*
**1.从根开始，用父节点与左子节点比较，若父节点大于左子节点，则交换它们的值；；
**2.用父节点与右节点比较，若父节点大于右子节点，则交换它们的值。
**3.若上述情况发生，则继续下沉，直到无法下沉为止
*/
template<typename T>
void minHeap<T>::sink(int index)
{
	int i = index;
	while (i*2<=size)
	{
		if (data[i - 1] > data[i * 2 - 1]){
			swap(data, i - 1, i * 2 - 1);
			if (i * 2 + 1 <= size&&data[i - 1] > data[i * 2])
				swap(data, i - 1, i * 2);
			i = i * 2;
		}
		else if (i * 2 + 1 <= size&&data[i - 1] > data[i * 2]){
			swap(data, i - 1, i * 2);
			i = i * 2 + 1;
		}
		else
			break;
	}
}

/*添加元素
**1.把元素添加到堆的最后；
**2.并使用上浮的方法把堆的最后一个元素上浮。
*/
template<typename T>
bool minHeap<T>::push(T dt)
{
	if (isFull()) return false;
	data[size] = dt;
	size++;
	floating(size);
}

/*
**1.将堆中第index个元素与它的父亲比较，若小于父节点，则与它父亲交换数值；
**2.上述过程如果发生，则把它继续上浮。
*/
template<typename T>
void minHeap<T>::floating(int index)
{
	for (int i = index; i > 0;i*=0.5)
	{
		if (data[i-1] < data[i*0.5-1])
			swap(data, i-1 , i* 0.5-1 );
		else
			break;
	}
}

template<typename T>
void minHeap<T>::swap(vector<T> &vec, int i, int j)
{
	T tmp = vec[i];
	vec[i] = vec[j];
	vec[j] = tmp;
}

template<typename T>
bool minHeap<T>::isEmpty()
{
	return size == 0;
}

template<typename T>
bool minHeap<T>::isFull()
{
	return size == capacity;
}

template<typename T>
int minHeap<T>::getSize()
{
	return size;
}

template<typename T>
minHeap<T>::~minHeap()
{

}

template<typename T>
minHeap<T>::minHeap(int capacity)
{
	this->capacity = capacity;
	size = 0;
	data.resize(capacity);
}

template<typename T>
minHeap<T>::minHeap(T buff[], int len)
{
	capacity = len;
	size = 0;
	data.resize(len);
	for (int i = 0; i < len; i++)
	{
		push(buff[i]);
	}

}

int mainHeap(){
	int buffer[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	minHeap<int> heap(buffer, 10);
	heap.print();
	heap.pop(1);
	heap.print();
	heap.push(1);
	heap.print();
	return 0;
}