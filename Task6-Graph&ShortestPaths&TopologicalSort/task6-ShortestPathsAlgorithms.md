# <center>  最短路径算法  </center>

---  
<font size=4>  

## 1.实现Dijkstra算法   
**问题分析：** 迪杰斯特拉是典型最短路径算法，用于计算一个节点到其他节点的最短路径。它的主要特点是以起始点为中心向外层拓展，直到扩展到终点为止。  
**基本思想：** 通过Dijkstra计算图G中的最短路径，需要指定起点s(即以顶点s开始计算).此外，引进两个几何S和U。S的作用是记录已求出最短路径的顶点(以及相应的最短路径长度)，而U则记录还未求出最短路径的顶点(以及该顶点到起点s的距离)。  
初始时，S中只有起点s；U中就是除s之外的顶点，并且U中顶点的路径是“起点s到该顶点的路径”。然后，从U中找出路径最短的顶点，并将其加入到S中；接着，更新U中的顶点和顶点对应的路径。然后再从U中找出路径最短的顶点，并将其加入到S中；接着，更新U中的顶点和顶点对应的路径，...重复该操作，直到遍历完所有顶点。  

**代码实现：**   
```

	//Dijkstra算法获取最短路径（邻接矩阵）
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
		char Vexs[MAX];//顶点集合
		int VexNum;//顶点数
		int EdgeNum;//边数
		int Matrix[MAX][MAX];//邻接矩阵
	public:
		MatrixUDG();//创建图，自己输入数据
		MatrixUDG(char vexs[], int vlen, int matrix[][9]);//创建图，用已提供的矩阵
		void DFS();//深度优先搜索遍历图
		void BFS();//广度优先搜索遍历图
		void dijkstra(int vs, int prev[], int dist[]);//dijkstra最短路径
		void print();//打印矩阵队列图
	private:
		int getPosition(char ch); //返回ch在Matrix矩阵中的位置
		void DFS(int i, int *visited);
		int firstVertex(int v);//返回顶点v的第一个邻接顶点的索引，失败返回-1
		int nextVertex(int v,int w);//返回顶点v相对于w的下一下邻接顶点的索引
	};
	
	MatrixUDG::MatrixUDG()
	{
		char c1, c2;
		int p1, p2, weight;
		cout << "输入顶点数和边数:\n";
		cin >> VexNum >> EdgeNum;
		if (VexNum<1||EdgeNum<1||(EdgeNum>VexNum*(VexNum-1)))
		{
			cout << "input error:invalid parameters!\n"; return;
		}
		//初始化顶点
		for (int i = 0; i < VexNum;i++)
		{
			cout << "vertex(" << i << "): ";
			cin >> Vexs[i];
		}
		//1.初始化边的权值
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
		//2.初始化边的权值：根据用户输入进行初始化
		for (int i = 0; i < EdgeNum;i++)
		{
			//读取边的起始顶点和结束顶点、权值
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
		//初始化顶点
		for (int i = 0; i < VexNum; i++)
			Vexs[i] = vexs[i];
		//初始化边
		for (int i = 0; i < VexNum; i++){
			for (int j = 0; j < VexNum; j++)
				Matrix[i][j] = matrix[i][j];
		}
		//统计边的数目
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
		//遍历该顶点的所有邻接顶点，若没有访问过，就继续往下走
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
	**Dijkstra最短路径，即，统计图中顶点vs到其它各个顶点的最短路径
	**参数说明：
	**    vs   起始顶点
	**    prev 前驱顶点数组，即，prev[i]的值是顶点vs到顶点i的最短路径所经历的全部顶点中，位于顶点i之前的那个顶点。
	**    dist 长度数组，即，dist[i]是顶点vs到顶点i的最短路径的长度。
	*/
	void MatrixUDG::dijkstra(int vs, int prev[], int dist[])
	{
		int min, tmp;
		int flag[MAX];//flag[i]=1表示顶点vs到顶点i的最短路径已经成功获取
		//初始化
		for (int i = 0; i < VexNum; i++)
		{
			flag[i] = 0;
			prev[i] = 0;
			dist[i] = Matrix[vs][i];//顶点i的最短路径为顶点vs到顶点i的权
		}
		//对顶点vs自身进行初始化
		flag[vs] = 1;
		dist[vs] = 0;
		//遍历Vertex-1次；每一次找出一个顶点的最短路径
		for (int i = 1; i < VexNum;i++)
		{
			//寻找当前最小的路径，即，在未获取最短路径的顶点中，找到离vs最近的顶点k
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
			//标记顶点k为已获取到最短路径
			flag[k] = 1;
			//修正当前最短路径和前驱顶点，即，当已经"顶点k的最短路径"之后，更新"为获取最短路径的顶点的最短路径和前驱顶点"
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
	
	
	int main(){
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
```


## 2.A*算法  
**太难了，以前根本没学过图，以后有时间再完成吧！** 

</front>