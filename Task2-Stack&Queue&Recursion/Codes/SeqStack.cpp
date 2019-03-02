#include <iostream>
using namespace std;


const int DEFAULT_SIZE =20;
template <class T>
class SeqStack
{
public:
	SeqStack(int cap=DEFAULT_SIZE){//����ջ
		capacity = cap;
		_array = new T[capacity];
		size = 0;
	}
	~SeqStack(){
		delete []_array;
	}
	bool isEmpty(){
		return size == 0;
	}
	void Push(const T& data){//��վ
		CheckCapicity();//�������
		_array[size] = data;
		size++;
	}
	void Pop(){//��ջ
		if (size == 0) return;
		size--;
	}
	T Top(){//ȡջ��Ԫ��
		if (isEmpty()) return -1;
		return _array[size - 1];
	}
	int Size(){//ջ��ǰԪ�ظ���
		return size;
	}
	void Traverse(){
		for (int i = 0; i < size;i++)
		{
			cout << _array[i] << ' ';
		}
		cout << endl;
	}

private:
	T* _array;
	int capacity;
	int size;

	void CheckCapicity(){//������������ݣ�
		if (size == capacity){//ջ������	
			//�����¿ռ�
			capacity +=capacity;
			T* new_array = new T[capacity];
			if (new_array == nullptr) { cout << "error";  return; }
			//��������
			for (int i = 0; i < size; i++)
			{
				new_array[i] = _array[i];
			}
			//�ͷ�ԭ���Ŀռ�
			delete[] _array;
			_array = new_array;
		}
		else
			return;
	}	
};

int main1(int argv, char *argc[]){
	SeqStack<int> stack(5);
	int val = 2;
	for (int i = 0; i < 8;i++)
	{
		stack.Push(val);
		val = val * 10 + 2;
	}
	cout << "��ǰԪ�ظ���Ϊ��" << stack.Size() << endl;
	cout << "��ǰջ��Ԫ��Ϊ��" << stack.Top()<<endl;
	stack.Pop();
	cout << "ɾ��ջ��Ԫ�غ󣬱���ջ��";
	stack.Traverse();

	cout << "\nEnd....";
	return 0;
}