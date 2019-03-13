#include <iostream>

using namespace std;
struct ArcNode //边表顶点
{
	int adjvex;
	struct ArcNode *next;
};
template<typename T>
struct VertexNode{//顶点表
	T vertex;
	ArcNode *firstedge;
};
//基于邻接矩阵存储的图的类实现
const int MaxSize = 10;
//int visited[MaxSize] = { 0 };//定点是否被访问标记
template<typename T>
class ALGraph{
public:
	ALGraph(T a[], int n, int e);//构造函数建立具有n个顶点e条边的图
	int degree(T val);//求顶点为val的度
	void printMatrix();
private:
	VertexNode<T> adjlist[MaxSize];//存放图中顶点的数组
	int vertexNum, arcNum;//图中顶点数和边数
};

template<typename T>
int ALGraph<T>::degree(T val)
{
	int res = 0;
	int i = -1;
	while (adjlist[++i].vertex != val);//找到顶点值为val的位置
	if (i >= vertexNum) return res;
	ArcNode *p = adjlist[i].firstedge;//遍历顶点表的链长
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
	cout << "无向图的邻接表:\n";
	for (int i = 0; i < vertexNum;i++)
	{
		cout << adjlist[i].vertex << ": ";
		ArcNode *p = adjlist[i].firstedge;
		while (p)
		{
			cout << adjlist[p->adjvex].vertex;//将邻接表的顶点值打印出来
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
	cout << "请输入" << e << "条边依附的顶点的编号：\n";//第i个顶点和第j个顶点
	for (int k = 0; k < arcNum;k++)
	{
		int i, j;
		cin >> i >> j;//i与j相连
		i--; j--;//顶点的编号比实际下标大1
		ArcNode *s = new ArcNode;//头插法
		s->adjvex = j;
		s->next = adjlist[i].firstedge;
		adjlist[i].firstedge = s;
		//ArcNode *s2 = new ArcNode;//头插法
		//s2->adjvex = i;
		//s2->next = adjlist[j].firstedge;
		//adjlist[j].firstedge = s2;
	}
}


int mainAdjacnecy(){
	int arry[] = { 22, 33, 44, 55, 66, 77 };
	ALGraph<int> graph(arry, 6, 9);
	cout << "顶点22的度为：" << graph.degree(22) << endl;
	graph.printMatrix();

	return 0;
}