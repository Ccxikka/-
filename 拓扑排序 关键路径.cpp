#include <iostream>
#include <stack>
#include <vector>
using namespace std;

//边表结点
typedef struct EdgeNode {
	int adjvex;//顶点对应的下标
	int weight;//边对应的权重
	struct EdgeNode *next;//指向下一个邻接点
} edgeNode;

//顶点表结点
typedef struct VertexNode {	
	int data;//顶点数据
	int in;//存储顶点的入度信息
	edgeNode *firstedge;//边表头指针
} VertexNode, AdjList[100];

//集合
typedef struct {
	AdjList adjList;
	int numVertexes, numEdges;//顶点数和边数
} GraphAdjList;

class AdjacencyList {
public:

	void CreateALGraph(GraphAdjList *G);

	void ShowALGraph(GraphAdjList *G);
	
	bool toposort(GraphAdjList *G, stack<int> &topo, vector<int>& etv);

	void criticalpath(GraphAdjList *G, stack<int> &topo, vector<int>& etv);

	void Test();

};

void AdjacencyList::CreateALGraph(GraphAdjList *G) {
	int i, j, k,weight;
	edgeNode *e;
	G->numVertexes = 10;
	G->numEdges = 13;
	for (i = 0; i < G->numVertexes; i++)
	{
		G->adjList[i].data = i;//输入顶点信息
		G->adjList[i].in = 0;
		G->adjList[i].firstedge = NULL;//将边表置为空表
	}
	for (k = 0; k < G->numEdges; k++)
	{//建立边表（头插法）
		cout << "输入边（vi,vj）上的顶点序号 及边的权重" << endl;//注意输入时顶点从0开始
		cin >> i >> j >>weight;
		e = new EdgeNode;
		e->adjvex = j;
		e->weight = weight;
		e->next = G->adjList[i].firstedge;
		G->adjList[i].firstedge = e;
		G->adjList[j].in++;
	}
}

void AdjacencyList::Test() {
	cout << "ALL IS OK." << endl;
}

void AdjacencyList::ShowALGraph(GraphAdjList *G) {
	for (int i = 0; i < G->numVertexes; i++)
	{
		cout << "顶点" << i << ": " << G->adjList[i].data <<" in:"<< G->adjList[i].in << "--firstedge--";
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

bool  AdjacencyList::toposort(GraphAdjList *G, stack<int> &topo, vector<int>& etv)
{//参数分别为图结构，保存拓扑序列的栈，保存事件最早发生时间的数组
	stack<int> s;//保存入度为0的顶点，避免每次都遍历查找入度为0的顶点
	int count = 0, k = 0;
	for (int i = 0; i < G->numVertexes; i++)
	{//将入度为0的点入栈，一个AOV网至少存在一个入度为0的点，初始化etv
		if (G->adjList[i].in == 0)
			s.push(i);
		etv.push_back(0);
	}
	while (!s.empty())
	{
		int cur = s.top();
		s.pop();
		topo.push(cur);//将输出的拓扑序列保存到栈中，由于之后求ltv需从后往前，所以用栈
		count++;//统计输出顶点数
		edgeNode *p = G->adjList[cur].firstedge;//得到与该顶点邻接的点
		while (p)
		{//依次删除以该点为起始顶点的边，即将其所有邻接点的入度减1
			k = p->adjvex;
			if ((--G->adjList[k].in) == 0)
				s.push(k);//若减1后入度为0，则进栈便于下次输出
			if (etv[cur] + p->weight > etv[k])
				etv[k] = etv[cur] + p->weight;//得到时间的最早发生时间
			p = p->next;//遍历该点的所有邻接点
		}
	}
	if (count < G->numVertexes)
		return false;//如果输出的点不是全部顶点，则说明不是AOV网
	else//输出的点与顶点数目相等，是一个AOV网
		return true;
}

void AdjacencyList::criticalpath(GraphAdjList *G, stack<int> &topo, vector<int>& etv)
{//参数分别为图结构，保存拓扑序列的栈，保存事件最早发生时间的数组，后两者在拓扑排序时得到
	int ete, lte,k;//活动的最早最晚发生时间
	vector<int> ltv;//事件的最晚发生时间
	for (int i = 0; i < G->numVertexes; i++)
		ltv.push_back(etv[G->numVertexes-1]);
	while (!topo.empty())
	{//栈topo保存了该图的拓扑序列
		int cur = topo.top();
		topo.pop();
		edgeNode *p = G->adjList[cur].firstedge;
		while (p)
		{
			k = p->adjvex;
			if (ltv[k] - p->weight < ltv[cur])
				ltv[cur] = ltv[k] - p->weight;//需要从后往前得到ltv，所以拓扑序列用栈保存
			p = p->next;
		}
	}
	for (int i = 0; i < G->numVertexes; i++)
	{
		edgeNode *p = G->adjList[i].firstedge;
		while (p)
		{
			k = p->adjvex;
			ete = etv[i];//顶点i的事件发生了，弧代表的活动才可以开始，故ete=etv
			lte = ltv[k] - p->weight;//活动最晚要在k事件前发生
			if (ete == lte)
				cout << "v"<<i << "->" << "v" <<k << " len:" << p->weight<<endl;//输出关键路径
			p = p->next;
		}
	}
}

int main() {

	AdjacencyList adjacencyList;
	GraphAdjList *GA = new GraphAdjList;
	adjacencyList.Test();
	adjacencyList.CreateALGraph(GA);
	adjacencyList.ShowALGraph(GA);

	stack<int> topo;//保存拓扑序列
	vector<int> etv;//保存事件最早发生时间
	bool result = adjacencyList.toposort(GA,topo,etv);
	//if (result)
	//	cout << "istopo" << endl;
	//else
	//	cout << "nottopo" << endl;
	adjacencyList.criticalpath(GA, topo, etv);
	
	return 0;
}