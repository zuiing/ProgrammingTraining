#include <iostream>
using namespace std;
template <class T>
class LinkStack{
private:
	struct node{
		T data;
		struct node *next;
		node(const T &x, node *N = nullptr){
			data = x; next = N;
		}
		node() :next(nullptr){}
		~node(){}
	};
	struct node *top;
public:
	LinkStack(){ top = nullptr; }
	~LinkStack(){
		node *tmp;
		while (top!=nullptr)
		{
			tmp = top;
			top = top->next;
			delete tmp;
		}
	}
	bool isEmpty() {
		return top == nullptr;
	}
	T Top(){
		if (top == nullptr) return -1;
		return top->data;
	}
	T Pop(){
		node *del = top;
		T x = top->data;
		top = top->next;
		delete del;
		return x;
	}
	void Push(const T &x){
		node *newNode = new node(x, top);//ͷ��
		top = newNode;//�½ڵ��Ϊͷ�ڵ�
	}
	void Treverse(){
		node *tmp = top;
		while (tmp!=nullptr)
		{
			cout << tmp->data << " ";
			tmp = tmp->next;
		}cout << endl;
	}
};

int main2(int argv, char* argc[]){
	LinkStack<int> stack;
	stack.Push(2);
	stack.Push(22);
	stack.Push(222);
	cout << "ջ��Ԫ��Ϊ��" << stack.Top()<<endl;
	stack.Push(2222);
	int  del = stack.Pop();
	cout << "ɾ������ջ��Ԫ��Ϊ��" << del << endl;
	cout << "������ʽջ��";
	stack.Treverse();
	return 0;
}