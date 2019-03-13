#include <iostream>

using namespace std;

//�����ڽӾ���洢��ͼ����ʵ��
const int MaxSize = 10;
int visited[MaxSize] = { 0 };//�����Ƿ񱻷��ʱ��
template<typename T>
class MGraph{
public:
	MGraph(T a[], int n, int e);//���캯����������n������e���ߵ�ͼ
	~MGraph();
	int degree(T val);//�󶥵�Ϊval�Ķ�
	void printMatrix();
	void DFSTraverse(int v);//������ȱ���ͼ
private:
	T vertex[MaxSize];//���ͼ�ж��������
	int arc[MaxSize][MaxSize];//���ͼ�бߵ����� 0��ʾ����ͨ��1��ʾ��ͨ
	int vertexNum, arcNum;//ͼ�ж������ͱ���
};

template<typename T>
MGraph<T>::~MGraph()
{

}

template<typename T>
void MGraph<T>::printMatrix()
{
	cout << "����ͼ���ڽӾ���:\n   ";
	for (int i = 0; i < vertexNum; i++)
		cout << vertex[i] << ' ';
	cout << endl;
	for (int i = 0; i < vertexNum;i++)
	{
		cout << vertex[i] << "  ";
		for (int j=0;j<vertexNum;j++)
		{
			cout << arc[i][j] << "  ";
		}cout << endl;
	}
}


template<typename T>
void MGraph<T>::DFSTraverse(int v)
{
	cout << vertex[v] << " ";
	visited[v] = 1;
	for (int j = 0; j < vertexNum;j++)
	{
		if (arc[v][j] && visited[j] == 0)
			DFSTraverse(j);
	}
}

template<typename T>
int MGraph<T>::degree(T val)
{
	int i = 0;
	while (vertex[i++] != val);//�ҵ�����Ϊval��λ��
	if (i > vertexNum) return -1;
	i--;
	int res=0;//���i��ֵΪ1�ĸ���
	for (int j = 0; j < vertexNum; j++)
	{
		if (arc[i][j] == 1) res ++;
	}
	return res;
}

template<typename T>
MGraph<T>::MGraph(T a[], int n, int e)
{
	vertexNum = n;
	arcNum = e;
	for (int i = 0; i < vertexNum; i++)//�����ʼ��
		vertex[i] = a[i];
	for (int i = 0; i < vertexNum; i++){
		for (int j = 0; j < vertexNum; j++)
			arc[i][j] = 0;
	}
	cout << "������" << e << "���������Ķ���ı�ţ�\n";//��i������͵�j������
	for (int k = 0; k < e;k++)
	{
		int i, j;
		cin >> i >> j;
		arc[i-1][j-1] = 1;
		arc[j-1][i-1] = 1;
	}
}


int mainMatrix(){
	int array[] = { 22, 23, 33, 44, 55, 66 };
	MGraph<int> graph(array, 6, 9);
	cout << "����1�Ķ�Ϊ��" << graph.degree(22) << endl;
	graph.printMatrix();
	return 0;
}