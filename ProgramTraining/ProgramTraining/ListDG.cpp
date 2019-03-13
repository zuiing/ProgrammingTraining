#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
#define  MAX 100
//�ڽӱ� ����ͼ
class ListDG
{
private:
	struct ENode //�ڽӱ��ж�Ӧ������Ķ���
	{
		int ivex;//�ñ���ָ��Ķ����λ��
		ENode *nextEdge;//ָ����һ������ָ��
	};
	struct VNode //�ڽӱ��б�Ķ���
	{
		char data;//������Ϣ
		ENode *firstEdge;//ָ���һ�������õ�Ļ�
	};

	int VexNum;//ͼ�Ķ������Ŀ
	int EdgeNum;//ͼ�ıߵ���Ŀ
	VNode Vexs[MAX];

public:
	//�����ڽӱ��Ӧ��ͼ���Լ����룩
	ListDG();
	//�����ڽӱ��Ӧ��ͼ�������ṩ�����ݣ�
	ListDG(char vexs[], int vlen, char edges[][2], int elen);
	~ListDG();
	void DFS();
	void BFS();//����������������������Ĳ������
	void print();//��ӡ�ڽӱ�ͼ
	//��������
	int topologicalSort();

private:
	//����ch��λ��
	int getPosition(char ch);
	//�������������������
	void DFS(int i, int visited[]);
};

ListDG::ListDG()
{
	char c1,c2;
	int p1, p2;
	cout << "���붥�����ͱ�����\n";
	cin >> VexNum >> EdgeNum;
	if (VexNum<1||EdgeNum<1||(EdgeNum>VexNum*(VexNum-1)))
	{
		cout << "input error:invalid parameters!\n";
		return;
	}
	//��ʼ���ڽӱ�Ķ���
	for (int i = 0; i < VexNum;i++)
	{
		cout << "vertex(" << i << "):";
		cin >> Vexs[i].data;
		Vexs[i].firstEdge = nullptr;
	}
	//��ʼ���ڽӱ�ı�
	for (int i = 0; i < EdgeNum;i++)
	{
		//��ȡ�ߵ���ʼ����ͽ�������
		cout << "edge(" << i << "):";
		cin >> c1 >> c2;
		p1 = getPosition(c1);
		p2 = getPosition(c2);
		ENode *node = new ENode;
		node->ivex = p2;
		node->nextEdge = nullptr;
		//��node���ӵ�p1���������ĩβ��β��
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
		//��ȡ�ߵ���ʼ�ڵ�ͽ����ڵ�
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
	int visited[MAX] = { 0 };//������ʱ��
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
	int queue[MAX];//��������
	int visited[MAX] = { 0 };//������ʱ��
	int j, k;
	ENode *node;
	cout << "BFS:";
	for (int i = 0; i < VexNum;i++)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			cout << Vexs[i].data << " ";
			queue[rear++] = i;//�����
		}
		while (head!=rear)
		{
			j = queue[head++];//������
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
**����ֵ��
** -1 ʧ�ܣ������ڴ治���ԭ����ɵģ�
** 0 �ɹ�����������
** 1 ʧ�ܣ�������ͼ���ǻ��ģ�
*/
int ListDG::topologicalSort()
{
	int head = 0, rear = 0;//�������е�ͷ��β
	int *queue = new int[VexNum];//��������
	int *ins = new int[VexNum];//�������
	char *tops = new char[VexNum];//�������������飬��¼ÿ���ڵ�����������
	ENode *node;
	memset(queue, 0, VexNum*sizeof(int));
	memset(ins, 0, VexNum*sizeof(int));
	memset(tops, 0, VexNum*sizeof(char));
	int j, index = 0;
	//ͳ��ÿ������������
	for (int i = 0; i < VexNum;i++)
	{
		node = Vexs[i].firstEdge;
		while (node)
		{
			ins[node->ivex]++;
			node = node->nextEdge;
		}
	}
	//���������Ϊ0�Ķ��������
	for (int i = 0; i < VexNum;i++)
	{
		if (ins[i] == 0)
			queue[rear++] = i;
	}
	while (head!=rear)//���зǿ�
	{
		//cout << "head=" << head << " rear=" << rear << endl;
		j = queue[head++];//����
		tops[index++] = Vexs[j].data;//���ö�����ӵ�tops�У�tops��������
		node = Vexs[j].firstEdge;//��ȡ�Ըýڵ�Ϊ���ĳ��߶���
		//����node�����Ľڵ����ȼ�1
		//����1֮�󣬸ýڵ�����Ϊ0���򽫸ýڵ���ӵ�������
	//	cout << "j="<<j<<": ";
		while (node!=nullptr)
		{
			//cout << ins[node->ivex] << "ǰ,";
			ins[node->ivex]--;
			//cout << ins[node->ivex] << "��,";
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
	//��ӡ����������
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
	//pG->print();//��ӡͼ
	//pG->DFS();
	//pG->BFS();

	ListDG *pG2;
	pG2 = new ListDG();
	pG2->topologicalSort();
	return 0;
}