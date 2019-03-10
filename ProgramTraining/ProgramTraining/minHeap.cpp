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

/*ɾ��Ԫ��
**1.�Ѷѵĵ�index��Ԫ��ɾ�������Ѷѵ����һ��Ԫ�طŵ�index����
**2.�Ѷѵĵ�index��Ԫ���³���
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
**1.�Ӹ���ʼ���ø��ڵ������ӽڵ�Ƚϣ������ڵ�������ӽڵ㣬�򽻻����ǵ�ֵ����
**2.�ø��ڵ����ҽڵ�Ƚϣ������ڵ�������ӽڵ㣬�򽻻����ǵ�ֵ��
**3.���������������������³���ֱ���޷��³�Ϊֹ
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

/*���Ԫ��
**1.��Ԫ����ӵ��ѵ����
**2.��ʹ���ϸ��ķ����Ѷѵ����һ��Ԫ���ϸ���
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
**1.�����е�index��Ԫ�������ĸ��ױȽϣ���С�ڸ��ڵ㣬���������׽�����ֵ��
**2.���������������������������ϸ���
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