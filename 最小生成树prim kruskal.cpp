#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

#define INFINITY 65535
#define vexnum 6//顶点数量
vector<char> vex{ 'A', 'B', 'C', 'D', 'E', 'F' };//顶点数据
int edgenum = 0;
struct edgenode
{
	int begin;
	int end;
	int weight;
};

void AdjMatrix(vector<vector<int>> &adjMat) //邻接矩阵表示法
{
	vector<int> line;
	for (int i = 0; i < vexnum; i++) //初始化邻接矩阵
	{
		for (int j = 0; j < vexnum; j++)
		{
			line.push_back(INFINITY);
		}
		adjMat.push_back(line);
		line.clear();
	}		
	adjMat[0][1] = 6; adjMat[0][2] = 1; adjMat[0][3] = 5;
	adjMat[1][0] = 6; adjMat[1][2] = 5; adjMat[1][4] = 3;
	adjMat[2][0] = 1; adjMat[2][1] = 5; adjMat[2][3] = 5; adjMat[2][4] = 6; adjMat[2][5] = 4;
	adjMat[3][0] = 5; adjMat[3][2] = 5; adjMat[3][5] = 2;
	adjMat[4][1] = 3; adjMat[4][2] = 6; adjMat[4][5] = 6;
	adjMat[5][2] = 4; adjMat[5][3] = 2; adjMat[5][4] = 6;
}

void prim(const vector<vector<int>> &adjMat)
{
	cout << "prim" << endl;
	int adjvex[vexnum];//保存顶点下标,vexnum为顶点数目
	int lowcost[vexnum];//保存顶点间边的权值，权值为0表示该顶点加入生成树中
	lowcost[0] = 0; //从0开始，将顶点0加入生成树中
	adjvex[0] = 0;//初始化第一个顶点下标为0
	for (int i = 1; i < vexnum; i++)
	{
		lowcost[i] = adjMat[0][i];//将与顶点0有边的权值存入lowcost
		adjvex[i] = 0;
	}
	for (int i = 1; i < vexnum; i++)
	{
		int min = INFINITY;
		int k = 0,j =1;
		for (j = 1; j < vexnum; j++)
		{
			if (lowcost[j] != 0 && lowcost[j] < min)
			{//权值为0的顶点为已经加入生成树的顶点，不再进行比较，得到当前最小权值的边
				min = lowcost[j];
				k = j;//记录权值最小的边对应的顶点
			}
		}
		cout << vex[adjvex[k]] << "--" << vex[k] << endl;//打印最小权值的边,vex为顶点数据数组
		lowcost[k] = 0;//将最小权值的边对应的顶点加入数组

		for (j = 1; j < vexnum; j++)
		{
			if (lowcost[j] != 0 && adjMat[k][j] < lowcost[j])
			{//加入新的顶点后，更新对应的边表权值
				lowcost[j] = adjMat[k][j];//将较小权值存入lowcost
				adjvex[j] = k;//对于更新的边表权值，更新该边的下标为k，表示为该顶点对应的边
			}
		}
	}

}

bool compare(const edgenode& node1, const edgenode& node2)
{
	return node1.weight < node2.weight;
}
void sortedge(vector<edgenode> &edges,vector<vector<int>> &adjMat)
{
	edgenode node;
	for (int i = 0; i < vexnum; i++)
	{
		for (int j = i; j < vexnum; j++)
		{//j从i开始，同一条边不进行两次记录
			if (adjMat[i][j] != INFINITY )
			{
				node.begin = i;
				node.end = j;
				node.weight = adjMat[i][j];
				edges.push_back(node);
				edgenum++;//记录边的数目
			}
		}
	}
	sort(edges.begin(), edges.end(), compare);//按照weight排序
//	for (vector<edgenode>::iterator it = edges.begin(); it != edges.end(); it++)
//	{
//		cout << "begin:" << (*it).begin << " end:" << (*it).end << " weight:" << (*it).weight << endl;
//	}
}

int findend(int* ring, int begin)
{//通过ring数组查找从begin顶点出发，通过已加入生成树的边可到达的最终顶点的下标
	while (ring[begin] > 0)
		begin = ring[begin];
	return begin;
}

void kruskal(vector<edgenode>& edges)
{//参数edges为图的边的集合，按照边的权值排序
	cout << "kruskal:" << endl;
	int ring[vexnum];//用于判断新加入的边是否会形成环路，数组下标为已加入的边的起始顶点，对应的成员值为由该顶点出发，通过已有边能到达的最终顶点的下标
	int i = 0, be = 0, en = 0;
	for (i = 0; i < vexnum; i++)
		ring[i] = 0;//初始时各个顶点到其他顶点均不可达
	for (i = 0; i < edgenum; i++)
	{
		be = findend(ring, edges[i].begin);
		en = findend(ring, edges[i].end);
		if (be != en)
		{ //没有形成环路，若相等则说明通过begin本就可以到达顶点en，若再加入这条边则会形成环路
			ring[be] = en;//加入新的边，修改ring数组
			cout << vex[edges[i].begin] << "--" << vex[edges[i].end] << endl;
		}
	}
}

int main() {
	vector<vector<int>> adjMat;
	AdjMatrix(adjMat);
	prim(adjMat);
	cout << endl;

	vector<edgenode> edges;
	sortedge(edges,adjMat);
	kruskal(edges);

	return 0;
}