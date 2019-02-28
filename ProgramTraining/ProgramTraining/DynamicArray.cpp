#include <iostream>
using namespace std;
const int initLen = 10;
template < class T>
class DynamicArray
{
public:
	DynamicArray(int len=initLen){
		data = new T[len];
		capacity = len;
		size = 0;
	}
	~DynamicArray(){

	}

private:
	T *data;
	int capacity;//��������
	int size;//���鵱ǰ��С

public:
	void resize(int len){
		T *p = new T[len];
		for (int i = 0; i < size;i++)
		{
			p[i] = data[i];
		}
		delete data;
		data = p;
		capacity = len;
	}
	//β������
	void insert(T num){
		if (size >= capacity) resize(2 * capacity);
		data[size++] = num;
	}
	void removeLast(T &val){
		if (size <= 0) return;
		val = data[size - 1];
		size--;
		if (size < capacity / 4) resize(capacity / 2);
	}
	//ɾ����n����
	void remove(int n, T &val){
		if (n <= 0 || n>size || size <= 0) return;
		val = data[n - 1];
		for (int i = n - 1; i < size-1;i++)
		{
			data[i] = data[i + 1];
		}
		size--;
		if (size < capacity / 4) resize(capacity / 2);
	}
	void print(){
		cout << "capacity:" << capacity << " size:" << size << endl<<"[";
		for (int i= 0; i < size;i++)
		{
			cout << data[i];
			if (i != size - 1) cout << ',';
		}
		cout << "]\n\n";
	}
	bool isEmpty(){
		return size == 0;
	}
	int capacity_(){
		return capacity;
	}
	int size_(){
		return size;
	}
};

int main1(int argv, char *argc[]){
	DynamicArray<int> da(5);
	//����11����
	for (int i = 1; i <= 11;i++)
	{
		da.insert(i*i);
	}
	da.print();
	int delData;
	da.removeLast(delData);
	cout << "ɾ��������Ϊ��" << delData << endl;
	da.remove(3, delData);
	cout << "ɾ��������Ϊ��" << delData << endl;
	da.print();

	return 0;
}