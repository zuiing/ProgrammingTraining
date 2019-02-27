#include <iostream>
using namespace std;
const int initLen = 10;
template < class T>
class SortedArray{
public:
	SortedArray(int len=initLen){
		data = new T(len);
		capacity = len;
		size = 0;
	}
	~SortedArray(){

	}
private:
	T *data;
	int capacity;
	int size;
public:
	void insert(T num){
		if (size >= capacity){
			cout << "数组已满\n"; return;
		}
		int i = 0;
		while (data[i] < num&&i<size) i++;
		for (int j=size-1;j>=i;j--)
		{
			data[j+1] = data[j];
		}
		data[i] = num;
		size++;
	}
	void remove(T num){
		if (size<=0)
		{
			cout << "数组为空\n"; return;
		}
		int i = 0;
		while (i < size&&data[i] != num) i++;
		if (i>=size)
		{
			cout << "未找到要删除的数据\n"; return;
		}
		else{
			for (; i < size-1;i++)
			{
				data[i] = data[i + 1];
			}
			size--;
		}
	}
	void print(){
		cout << "capacity:" << capacity << " size:" << size << endl << "[";
		for (int i = 0; i < size; i++)
		{
			cout << data[i];
			if (i != size - 1) cout << ',';
		}
		cout << "]\n\n";
	}
};
int main2(int argv, char *argc[]){
	SortedArray<int> sa(5);
	sa.insert(2);
	sa.insert(22);
	sa.insert(1);
	sa.insert(11);
	sa.insert(10);
	sa.print();
	sa.insert(20);
	sa.remove(22);
	sa.remove(20);
	sa.print();
	cout << "test over";
	return 0;
}