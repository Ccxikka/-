#include <iostream>
#include <deque>
using namespace std;

//访问标志的数组,为1表示访问过，为0表示未被访问
int visted[100];
//边表结点
typedef struct EdgeNode {
	//顶点对应的下标
	int adjvex;
	//指向下一个邻接点
	struct EdgeNode *next;
} edgeNode;

//顶点表结点
typedef struct VertexNode {
	//顶点数据
	char data;
	//边表头指针
	edgeNode *firstedge;
} VertexNode, AdjList[100];

//集合
typedef struct {
	AdjList adjList;
	//顶点数和边数
	int numVertexes, numEdges;
} GraphAdjList;

class AdjacencyList {
public:

	void CreateALGraph(GraphAdjList *G);

	void ShowALGraph(GraphAdjList *G);

	void BFSTraverse(GraphAdjList *G);

	void DFS(GraphAdjList *G, int i);

	void DFSTraverse(GraphAdjList *G);

	void Test();

};

void AdjacencyList::CreateALGraph(GraphAdjList *G) {
	int i, j, k;
	edgeNode *e;
	cout << "输入顶点数和边数" << endl;
	//输入顶点数和边数
	cin >> G->numVertexes >> G->numEdges;
	//读入顶点信息，建立顶点表
	for (i = 0; i < G->numVertexes; i++)
	{
		//输入顶点信息
		cin >> G->adjList[i].data;
		//将边表置为空表
		G->adjList[i].firstedge = NULL;
	}
	//建立边表（头插法）
	for (k = 0; k < G->numEdges; k++)
	{
		cout << "输入边（vi,vj）上的顶点序号" << endl;
		cin >> i >> j;
		e = new EdgeNode;
		e->adjvex = j;
		e->next = G->adjList[i].firstedge;
		G->adjList[i].firstedge = e;

		e = new EdgeNode;

		e->adjvex = i;
		e->next = G->adjList[j].firstedge;
		G->adjList[j].firstedge = e;
	}
}

void AdjacencyList::Test() {
	cout << "ALL IS OK." << endl;
}

void AdjacencyList::ShowALGraph(GraphAdjList *G) {
	for (int i = 0; i < G->numVertexes; i++)
	{
		cout << "顶点" << i << ": " << G->adjList[i].data << "--firstedge--";
		edgeNode *p = new edgeNode;
		p = G->adjList[i].firstedge;
		while (p)
		{
			cout << p->adjvex << "--Next--";
			p = p->next;
		}
		cout << "--NULL" << endl;
	}

}

void AdjacencyList::DFS(GraphAdjList *G, int i) {
	EdgeNode *p;
	visted[i] = 1; //设置顶点i为已访问
	cout << G->adjList[i].data << "--";
	p = G->adjList[i].firstedge;//邻接表存储，p为顶点i的边表中的第一个结点
	while (p)
	{
		if (!visted[p->adjvex])
		{// p->adjvex为顶点下标
			//递归访问
			DFS(G, p->adjvex);
		}
		p = p->next;//next为该边表中的下一个结点
	}
}

void AdjacencyList::DFSTraverse(GraphAdjList *G) {
	//初始化所有顶点都没有访问过
	cout << "深度优先遍历结果为：" << endl;
	for (int i = 0; i < G->numVertexes; i++)
	{// G->numVertexes为顶点数
		visted[i] = 0;
	}
	for (int i = 0; i < G->numVertexes; i++)
	{
		if (visted[i] == 0)
		{
			DFS(G, i);//对于没有访问的顶点进行访问
		}
	}
	cout << endl;
}


void AdjacencyList::BFSTraverse(GraphAdjList *G) {
	//初始化所有顶点都没有访问过
	cout << "广度优先遍历结果为：" << endl;
	deque<int> q;
	for (int i = 0; i < G->numVertexes; i++)
	{
		visted[i] = 0;
	}
	for (int i = 0; i < G->numVertexes; i++)
	{//有的顶点可能和前面的顶点都没有边，因此需要for循环所有顶点
		if (visted[i] == 0)
		{
			visted[i] = 1;
			cout << G->adjList[i].data << "--";
			q.push_back(i);
			while (!q.empty())
			{
				int cur = q.front();
				q.pop_front();
				EdgeNode *p = G->adjList[cur].firstedge;
				while (p)
				{
					if (visted[p->adjvex] == 0)
					{
						visted[p->adjvex] = 1;
						cout << G->adjList[p->adjvex].data << "--";
						q.push_back(p->adjvex);
					}
					p = p->next;
				}
			}
		}		
	}
	cout << endl;
}


int main() {

	AdjacencyList adjacencyList;
	GraphAdjList *GA = new GraphAdjList;
	adjacencyList.Test();
	adjacencyList.CreateALGraph(GA);
	adjacencyList.ShowALGraph(GA);
	adjacencyList.BFSTraverse(GA);
	adjacencyList.DFSTraverse(GA);
	return 0;
}