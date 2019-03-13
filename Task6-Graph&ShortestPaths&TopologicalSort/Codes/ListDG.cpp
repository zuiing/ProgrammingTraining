#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
#define  MAX 100
//邻接表 有向图
class ListDG
{
private:
	struct ENode //邻接表中对应的链表的顶点
	{
		int ivex;//该边所指向的顶点的位置
		ENode *nextEdge;//指向下一条弧的指针
	};
	struct VNode //邻接表中表的顶点
	{
		char data;//顶点信息
		ENode *firstEdge;//指向第一条依附该点的弧
	};

	int VexNum;//图的顶点的数目
	int EdgeNum;//图的边的数目
	VNode Vexs[MAX];

public:
	//创建邻接表对应的图（自己输入）
	ListDG();
	//创建邻接表对应的图（用已提供的数据）
	ListDG(char vexs[], int vlen, char edges[][2], int elen);
	~ListDG();
	void DFS();
	void BFS();//广度优先搜索，类似与树的层序遍历
	void print();//打印邻接表图
	//拓扑排序
	int topologicalSort();

private:
	//返回ch的位置
	int getPosition(char ch);
	//深度优先搜索辅助函数
	void DFS(int i, int visited[]);
};

ListDG::ListDG()
{
	char c1,c2;
	int p1, p2;
	cout << "输入顶点数和边数：\n";
	cin >> VexNum >> EdgeNum;
	if (VexNum<1||EdgeNum<1||(EdgeNum>VexNum*(VexNum-1)))
	{
		cout << "input error:invalid parameters!\n";
		return;
	}
	//初始化邻接表的顶点
	for (int i = 0; i < VexNum;i++)
	{
		cout << "vertex(" << i << "):";
		cin >> Vexs[i].data;
		Vexs[i].firstEdge = nullptr;
	}
	//初始化邻接表的边
	for (int i = 0; i < EdgeNum;i++)
	{
		//读取边的起始顶点和结束顶点
		cout << "edge(" << i << "):";
		cin >> c1 >> c2;
		p1 = getPosition(c1);
		p2 = getPosition(c2);
		ENode *node = new ENode;
		node->ivex = p2;
		node->nextEdge = nullptr;
		//将node链接到p1所在链表的末尾，尾插
		if (Vexs[p1].firstEdge == nullptr)
			Vexs[p1].firstEdge = node;
		else{
			ENode *t = Vexs[p1].firstEdge;
			while (t->nextEdge)			
				t = t->nextEdge;			
			t->nextEdge = node;
		}
	}
}

ListDG::ListDG(char vexs[], int vlen, char edges[][2], int elen)
{
	char c1, c2;
	int p1, p2;
	VexNum = vlen;
	EdgeNum = elen;
	for (int i = 0; i < VexNum;i++)
	{
		Vexs[i].data = vexs[i];
		Vexs[i].firstEdge = nullptr;
	}
	for (int i = 0; i < EdgeNum;i++)
	{
		//读取边的起始节点和结束节点
		c1 = edges[i][0];
		c2 = edges[i][1];
		p1 = getPosition(c1);
		p2 = getPosition(c2);
		ENode *node = new ENode;
		node->ivex = p2;
		node->nextEdge = nullptr;
		if (Vexs[p1].firstEdge == nullptr)
			Vexs[p1].firstEdge = node;
		else{
			ENode *t = Vexs[p1].firstEdge;
			while (t->nextEdge)
				t = t->nextEdge;
			t->nextEdge = node;
		}
	}
}

ListDG::~ListDG()
{
}

int ListDG::getPosition(char ch)
{
	for (int i = 0; i < VexNum;i++)
	{
		if (Vexs[i].data == ch)
			return i;
	}
	return -1;
}

void ListDG::DFS()
{
	int visited[MAX] = { 0 };//顶点访问标记
	cout << "DFS:";
	for (int i = 0; i < VexNum;i++)
	{
		if (!visited[i])
			DFS(i, visited);
	}
	cout << endl;
}

void ListDG::DFS(int i, int visited[])
{
	visited[i] = 1;
	cout << Vexs[i].data << " ";
	ENode *node = Vexs[i].firstEdge;
	while (node)
	{
		if (!visited[node->ivex])
			DFS(node->ivex, visited);
		node = node->nextEdge;
	}
}

void ListDG::BFS()
{
	int head=0, rear = 0;
	int queue[MAX];//辅助队列
	int visited[MAX] = { 0 };//顶点访问标记
	int j, k;
	ENode *node;
	cout << "BFS:";
	for (int i = 0; i < VexNum;i++)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			cout << Vexs[i].data << " ";
			queue[rear++] = i;//入队列
		}
		while (head!=rear)
		{
			j = queue[head++];//出队列
			node = Vexs[j].firstEdge;
			while (node)
			{
				k = node->ivex;
				if (!visited[k])
				{
					visited[k] = 1;
					cout << Vexs[k].data << " ";
					queue[rear++] = k;
				}
				node = node->nextEdge;
			}
		}
	}cout << endl;
}

void ListDG::print()
{
	ENode *node;
	cout << "List Graph:\n";
	for (int i = 0; i < VexNum; i++)
	{
		cout << i << "(" << Vexs[i].data << "): ";
		node = Vexs[i].firstEdge;
		while (node)
		{
			cout << node->ivex << "(" << Vexs[node->ivex].data << ") ";
			node = node->nextEdge;
		}
		cout << endl;
	}
}
/*
**返回值：
** -1 失败（由于内存不足等原因造成的）
** 0 成功排序并输出结果
** 1 失败（该有向图是忧环的）
*/
int ListDG::topologicalSort()
{
	int head = 0, rear = 0;//辅助队列的头和尾
	int *queue = new int[VexNum];//辅助队列
	int *ins = new int[VexNum];//入度数组
	char *tops = new char[VexNum];//拓扑排序结果数组，记录每个节点的排序后的序号
	ENode *node;
	memset(queue, 0, VexNum*sizeof(int));
	memset(ins, 0, VexNum*sizeof(int));
	memset(tops, 0, VexNum*sizeof(char));
	int j, index = 0;
	//统计每个顶点的入度数
	for (int i = 0; i < VexNum;i++)
	{
		node = Vexs[i].firstEdge;
		while (node)
		{
			ins[node->ivex]++;
			node = node->nextEdge;
		}
	}
	//将所有入度为0的顶点入队列
	for (int i = 0; i < VexNum;i++)
	{
		if (ins[i] == 0)
			queue[rear++] = i;
	}
	while (head!=rear)//队列非空
	{
		//cout << "head=" << head << " rear=" << rear << endl;
		j = queue[head++];//出队
		tops[index++] = Vexs[j].data;//将该顶点添加到tops中，tops是排序结果
		node = Vexs[j].firstEdge;//获取以该节点为起点的出边队列
		//将与node关联的节点的入度减1
		//若减1之后，该节点的入度为0；则将该节点添加到队列中
	//	cout << "j="<<j<<": ";
		while (node!=nullptr)
		{
			//cout << ins[node->ivex] << "前,";
			ins[node->ivex]--;
			//cout << ins[node->ivex] << "后,";
			if (ins[node->ivex] == 0)
				queue[rear++] = node->ivex;
			node = node->nextEdge;
		}
		//cout << endl;
	}
	//cout << "index=" << index <<"VexNum="<<VexNum<< endl;
	if (index!=VexNum)
	{
		cout << "Graph has a cycle\n";
		delete queue;
		delete ins;
		delete tops;
		return 1;
	}
	//打印拓扑排序结果
	cout << "TopoSort:";
	for (int i = 0; i < VexNum; i++)
	{
		cout << tops[i] << " ";
	}cout << endl;
	delete queue;
	delete ins;
	delete tops;
	return 0;
}


int mainListDG(){
	//char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	//char edges[][2] = { { 'A', 'B' }, { 'B', 'C' }, { 'B', 'E' }, { 'B', 'F' }, { 'C', 'E' },
	//{ 'D', 'C' }, { 'E', 'B' }, { 'E', 'D' }, { 'F', 'G' }, };
	//int vlen = sizeof(vexs) / sizeof(vexs[0]);
	//int elen = sizeof(edges) / sizeof(edges[0]);
	//ListDG *pG;
	//pG = new ListDG(vexs, vlen, edges, elen);
	//pG->print();//打印图
	//pG->DFS();
	//pG->BFS();

	ListDG *pG2;
	pG2 = new ListDG();
	pG2->topologicalSort();
	return 0;
}