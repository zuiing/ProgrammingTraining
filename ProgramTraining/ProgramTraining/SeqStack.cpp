#include <iostream>
using namespace std;


const int DEFAULT_SIZE =20;
template <class T>
class SeqStack
{
public:
	SeqStack(int cap=DEFAULT_SIZE){//创建栈
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
	void Push(const T& data){//入站
		CheckCapicity();//检查容量
		_array[size] = data;
		size++;
	}
	void Pop(){//出栈
		if (size == 0) return;
		size--;
	}
	T Top(){//取栈顶元素
		if (isEmpty()) return -1;
		return _array[size - 1];
	}
	int Size(){//栈当前元素个数
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

	void CheckCapicity(){//检查容量（扩容）
		if (size == capacity){//栈满扩容	
			//开辟新空间
			capacity +=capacity;
			T* new_array = new T[capacity];
			if (new_array == nullptr) { cout << "error";  return; }
			//拷贝数据
			for (int i = 0; i < size; i++)
			{
				new_array[i] = _array[i];
			}
			//释放原来的空间
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
	cout << "当前元素个数为：" << stack.Size() << endl;
	cout << "当前栈顶元素为：" << stack.Top()<<endl;
	stack.Pop();
	cout << "删除栈顶元素后，遍历栈：";
	stack.Traverse();

	cout << "\nEnd....";
	return 0;
}