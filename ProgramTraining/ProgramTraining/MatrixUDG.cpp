//Dijkstra�㷨��ȡ���·�����ڽӾ���
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
struct EData
{
	char start;
	char end;
	int weight;
	EData(char s, char e, char w) :start(s), end(e), weight(w){}
};
#define MAX 100
#define INF 0X7FFFFFFF
class MatrixUDG{
private:
	char Vexs[MAX];//���㼯��
	int VexNum;//������
	int EdgeNum;//����
	int Matrix[MAX][MAX];//�ڽӾ���
public:
	MatrixUDG();//����ͼ���Լ���������
	MatrixUDG(char vexs[], int vlen, int matrix[][9]);//����ͼ�������ṩ�ľ���
	void DFS();//���������������ͼ
	void BFS();//���������������ͼ
	void dijkstra(int vs, int prev[], int dist[]);//dijkstra���·��
	void print();//��ӡ�������ͼ
private:
	int getPosition(char ch); //����ch��Matrix�����е�λ��
	void DFS(int i, int *visited);
	int firstVertex(int v);//���ض���v�ĵ�һ���ڽӶ����������ʧ�ܷ���-1
	int nextVertex(int v,int w);//���ض���v�����w����һ���ڽӶ��������
};

MatrixUDG::MatrixUDG()
{
	char c1, c2;
	int p1, p2, weight;
	cout << "���붥�����ͱ���:\n";
	cin >> VexNum >> EdgeNum;
	if (VexNum<1||EdgeNum<1||(EdgeNum>VexNum*(VexNum-1)))
	{
		cout << "input error:invalid parameters!\n"; return;
	}
	//��ʼ������
	for (int i = 0; i < VexNum;i++)
	{
		cout << "vertex(" << i << "): ";
		cin >> Vexs[i];
	}
	//1.��ʼ���ߵ�Ȩֵ
	for (int i = 0; i < VexNum;i++)
	{
		for (int j = 0; i < VexNum;j++)
		{
			if (i == j)
				Matrix[i][j] = 0;
			else
				Matrix[i][j] = INF;
		}
	}
	//2.��ʼ���ߵ�Ȩֵ�������û�������г�ʼ��
	for (int i = 0; i < EdgeNum;i++)
	{
		//��ȡ�ߵ���ʼ����ͽ������㡢Ȩֵ
		cout << "edge(" << i << "): ";
		cin >> c1 >> c2 >> weight;
		p1 = getPosition(c1);
		p2 = getPosition(c2);
		if (p1 == -1 || p2 == -1){
			cout << "input error:invalid edge!\n"; return;
		}
		Matrix[p1][p2] = weight;
		Matrix[p2][p1] = weight;
	}
}

MatrixUDG::MatrixUDG(char vexs[], int vlen, int matrix[][9])
{
	VexNum = vlen;
	//��ʼ������
	for (int i = 0; i < VexNum; i++)
		Vexs[i] = vexs[i];
	//��ʼ����
	for (int i = 0; i < VexNum; i++){
		for (int j = 0; j < VexNum; j++)
			Matrix[i][j] = matrix[i][j];
	}
	//ͳ�Ʊߵ���Ŀ
	for (int i = 0; i < VexNum;i++)
	{
		for (int j = 0; j < VexNum; j++){
			if (i != j&&Matrix[i][j] != INF)
				EdgeNum++;
		}	
	}
	EdgeNum /= 2;
}

int MatrixUDG::getPosition(char ch)
{
	for (int i = 0; i < VexNum;i++)
	{
		if (Vexs[i] == ch)
			return i;
	}
	return -1;
}

void MatrixUDG::print()
{
	cout << "Matrix Graph:" << endl;
	for (int i = 0; i < VexNum;i++)
	{
		for (int j = 0; j < VexNum; j++)
			cout << setw(10) << Matrix[i][j] << " ";
		cout << endl;
	}
}

void MatrixUDG::DFS()
{
	int visited[MAX] = { 0 };
	cout << "DFS:";
	for (int i = 0; i < VexNum;i++)
	{
		if (!visited[i])
			DFS(i, visited);
	}
	cout << endl;
}

void MatrixUDG::DFS(int i, int *visited)
{
	visited[i] = 1;
	cout << Vexs[i] << " ";
	//�����ö���������ڽӶ��㣬��û�з��ʹ����ͼ���������
	for (int w = firstVertex(i); w >=0; w = nextVertex(i, w)){
		if (!visited[w])
			DFS(w, visited);
	}
}

int MatrixUDG::firstVertex(int v)
{
	if (v<0 || v>(VexNum - 1)) return -1;
	for (int i = 0; i < VexNum;i++)
	{
		if (Matrix[v][i] != 0 && Matrix[v][i] != INF)
			return i;
	}
	return -1;
}

int MatrixUDG::nextVertex(int v, int w)
{
	if (v<0 || v>(VexNum - 1)||w<0||w>(VexNum-1)) return -1;
	for (int i = w + 1; i < VexNum;i++)
	{
		if (Matrix[v][i] != 0 && Matrix[v][i] != INF)
			return i;
	}
	return -1;
}

void MatrixUDG::BFS()
{
	int head = 0, rear = 0;
	int queue[MAX] ;
	int visited[MAX] = { 0 };
	cout << "BFS:";
	for (int i = 0; i < VexNum;i++)
	{
		if (!visited[i]){
			visited[i] = 1;
			cout << Vexs[i] << " ";
			queue[rear++] = i;
		}
		while (head!=rear)
		{
			int j = queue[head++];
			for (int k = firstVertex(j); k >= 0;k=nextVertex(j,k))
			{
				if (!visited[k])
				{
					visited[k] = 1;
					cout << Vexs[k] << " ";
					queue[rear++] = k;
				}
			}
		}
	}
	cout << endl;
}

/*
**Dijkstra���·��������ͳ��ͼ�ж���vs������������������·��
**����˵����
**    vs   ��ʼ����
**    prev ǰ���������飬����prev[i]��ֵ�Ƕ���vs������i�����·����������ȫ�������У�λ�ڶ���i֮ǰ���Ǹ����㡣
**    dist �������飬����dist[i]�Ƕ���vs������i�����·���ĳ��ȡ�
*/
void MatrixUDG::dijkstra(int vs, int prev[], int dist[])
{
	int min, tmp;
	int flag[MAX];//flag[i]=1��ʾ����vs������i�����·���Ѿ��ɹ���ȡ
	//��ʼ��
	for (int i = 0; i < VexNum; i++)
	{
		flag[i] = 0;
		prev[i] = 0;
		dist[i] = Matrix[vs][i];//����i�����·��Ϊ����vs������i��Ȩ
	}
	//�Զ���vs������г�ʼ��
	flag[vs] = 1;
	dist[vs] = 0;
	//����Vertex-1�Σ�ÿһ���ҳ�һ����������·��
	for (int i = 1; i < VexNum;i++)
	{
		//Ѱ�ҵ�ǰ��С��·����������δ��ȡ���·���Ķ����У��ҵ���vs����Ķ���k
		min = INF;
		int k;
		for (int j = 0; j < VexNum;j++)
		{
			if (flag[j]==0&&dist[j]<min)
			{
				min = dist[j];
				k = j;
			}
		}
		//��Ƕ���kΪ�ѻ�ȡ�����·��
		flag[k] = 1;
		//������ǰ���·����ǰ�����㣬�������Ѿ�"����k�����·��"֮�󣬸���"Ϊ��ȡ���·���Ķ�������·����ǰ������"
		for (int j = 0; j < VexNum;j++)
		{
			tmp = Matrix[k][j] == INF ? INF : (min + Matrix[k][j]);
			if (flag[j]==0&&tmp<dist[j])
			{
				dist[j] = tmp;
				prev[j] = k;
			}
		}
	}
	cout << "dijkstra(" << Vexs[vs] << "):" << endl;
	for (int i = 0; i < VexNum;i++)
	{
		cout << "shortest(" << Vexs[vs] << ", " << Vexs[i] << "):" << dist[i] << endl;
	}
}


int mainUDG(){
	int prev[MAX] = { 0 };
	int dist[MAX] = { 0 };
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	int matrix[][9] = {
		/*A*//*B*//*C*//*D*//*E*//*F*//*G*/
		/*A*/{ 0, 12, INF, INF, INF, 16, 14 },
		/*B*/{ 12, 0, 10, INF, INF, 7, INF },
		/*C*/{ INF, 10, 0, 3, 5, 6, INF },
		/*D*/{ INF, INF, 3, 0, 4, INF, INF },
		/*E*/{ INF, INF, 5, 4, 0, 2, 8 },
		/*F*/{ 16, 7, 6, INF, 2, 0, 9 },
		/*G*/{ 14, INF, INF, INF, 8, 9, 0 } };
	int vlen = sizeof(vexs) / sizeof(vexs[0]);
	MatrixUDG *pG;
	pG = new MatrixUDG(vexs, vlen, matrix);
	/*pG->print();
	pG->DFS();
	pG->BFS();*/
	
	pG->dijkstra(3, prev, dist);
	return 0;
}