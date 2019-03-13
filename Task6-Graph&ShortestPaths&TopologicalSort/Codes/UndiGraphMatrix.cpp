#include <iostream>

using namespace std;

//基于邻接矩阵存储的图的类实现
const int MaxSize = 10;
int visited[MaxSize] = { 0 };//定点是否被访问标记
template<typename T>
class MGraph{
public:
	MGraph(T a[], int n, int e);//构造函数建立具有n个顶点e条边的图
	~MGraph();
	int degree(T val);//求顶点为val的度
	void printMatrix();
	void DFSTraverse(int v);//深度优先遍历图
private:
	T vertex[MaxSize];//存放图中顶点的数组
	int arc[MaxSize][MaxSize];//存放图中边的数组 0表示不连通，1表示连通
	int vertexNum, arcNum;//图中顶点数和边数
};

template<typename T>
MGraph<T>::~MGraph()
{

}

template<typename T>
void MGraph<T>::printMatrix()
{
	cout << "无向图的邻接矩阵:\n   ";
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
	while (vertex[i++] != val);//找到顶点为val的位置
	if (i > vertexNum) return -1;
	i--;
	int res=0;//求第i行值为1的个数
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
	for (int i = 0; i < vertexNum; i++)//顶点初始化
		vertex[i] = a[i];
	for (int i = 0; i < vertexNum; i++){
		for (int j = 0; j < vertexNum; j++)
			arc[i][j] = 0;
	}
	cout << "请输入" << e << "条边依附的顶点的编号：\n";//第i个顶点和第j个顶点
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
	cout << "顶点1的度为：" << graph.degree(22) << endl;
	graph.printMatrix();
	return 0;
}