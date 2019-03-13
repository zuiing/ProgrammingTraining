#include <iostream>

using namespace std;
struct ArcNode //�߱���
{
	int adjvex;
	struct ArcNode *next;
};
template<typename T>
struct VertexNode{//�����
	T vertex;
	ArcNode *firstedge;
};
//�����ڽӾ���洢��ͼ����ʵ��
const int MaxSize = 10;
//int visited[MaxSize] = { 0 };//�����Ƿ񱻷��ʱ��
template<typename T>
class ALGraph{
public:
	ALGraph(T a[], int n, int e);//���캯����������n������e���ߵ�ͼ
	int degree(T val);//�󶥵�Ϊval�Ķ�
	void printMatrix();
private:
	VertexNode<T> adjlist[MaxSize];//���ͼ�ж��������
	int vertexNum, arcNum;//ͼ�ж������ͱ���
};

template<typename T>
int ALGraph<T>::degree(T val)
{
	int res = 0;
	int i = -1;
	while (adjlist[++i].vertex != val);//�ҵ�����ֵΪval��λ��
	if (i >= vertexNum) return res;
	ArcNode *p = adjlist[i].firstedge;//��������������
	while(p)
	{
		res++;
		p = p->next;
	}
	return res;
}

template<typename T>
void ALGraph<T>::printMatrix()
{
	cout << "����ͼ���ڽӱ�:\n";
	for (int i = 0; i < vertexNum;i++)
	{
		cout << adjlist[i].vertex << ": ";
		ArcNode *p = adjlist[i].firstedge;
		while (p)
		{
			cout << adjlist[p->adjvex].vertex;//���ڽӱ�Ķ���ֵ��ӡ����
			p = p->next;
			if (p) cout << "->";
		}
		cout << endl;
	}
}

template<typename T>
ALGraph<T>::ALGraph(T a[], int n, int e)
{
	vertexNum = n;
	arcNum = e;
	for (int i = 0; i < vertexNum;i++)
	{
		adjlist[i].vertex = a[i];
		adjlist[i].firstedge = nullptr;
	}
	cout << "������" << e << "���������Ķ���ı�ţ�\n";//��i������͵�j������
	for (int k = 0; k < arcNum;k++)
	{
		int i, j;
		cin >> i >> j;//i��j����
		i--; j--;//����ı�ű�ʵ���±��1
		ArcNode *s = new ArcNode;//ͷ�巨
		s->adjvex = j;
		s->next = adjlist[i].firstedge;
		adjlist[i].firstedge = s;
		//ArcNode *s2 = new ArcNode;//ͷ�巨
		//s2->adjvex = i;
		//s2->next = adjlist[j].firstedge;
		//adjlist[j].firstedge = s2;
	}
}


int mainAdjacnecy(){
	int arry[] = { 22, 33, 44, 55, 66, 77 };
	ALGraph<int> graph(arry, 6, 9);
	cout << "����22�Ķ�Ϊ��" << graph.degree(22) << endl;
	graph.printMatrix();

	return 0;
}