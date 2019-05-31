#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define INFINITY 65535
#define vexnum 6//顶点数量
vector<char> vex{ 'A', 'B', 'C', 'D', 'E', 'F' };//顶点数据

void AdjMatrix(vector<vector<int>> &adjMat) //邻接矩阵表示法
{
	vector<int> line;
	for (int j = 0; j < vexnum; j++)
	{
		line.push_back(INFINITY);
	}
	for (int i = 0; i < vexnum; i++) //初始化邻接矩阵
	{		
		adjMat.push_back(line);
	}		
	adjMat[0][1] = 50; adjMat[0][2] = 10; adjMat[0][4] = 45;
	adjMat[1][2] = 15; adjMat[1][4] = 10;
	adjMat[2][0] = 20; adjMat[2][3] = 15;
	adjMat[3][1] = 20; adjMat[3][4] = 35; adjMat[3][5] = 3;
	adjMat[4][3] = 30;
}

void dijkstra(vector<vector<int>>& adjMat, int begin)
{
	int find[vexnum]; //标识已找到最短路径的顶点
	int dist[vexnum]; //标识源点到其他点的最短路径长度
	int source[vexnum];//标识到某顶点最短路径的直接源点
	string path;//存储完整路径信息
	int i = 0, j=0, k=0, s=0, min = INFINITY;//infinity为一个较大整数
	cout << "dijkstra单源最短路径：" << endl;
	for (i = 0; i < vexnum; i++)
	{
		source[i] = begin;//初始将所有路径的源点设为参数begin
		dist[i] = adjMat[begin][i];//初始化为源点到其他顶点的路径长度
		find[i] = 0;
	}
	dist[begin] = 0;
	find[begin] = 1;//源点到自己的路径找到，即为0；
	for (i = 0; i < vexnum-1; i++)//除去到自身的，只需要循环顶点数-1次
	{//获取到各个顶点的最短路径
		min = INFINITY;
		for (j = 0; j < vexnum; j++)
		{
			if (find[j] == 0 && dist[j] < min)
			{//获取最短路径及对应的顶点，在所有未确定最短路径的顶点中寻找
				k = j;
				min = dist[j];
			}
		}	
		find[k] = 1;//将最短路径对应的顶点加入，表示已找到到该顶点的最短路径
		path = "--";//初始化
		s = source[k];//记录结点k的最直接源点
		while (s != begin)
		{//如果最短路径的起始点不是源点，则通过source数组逆向拼接路径
			path = vex[s] +  path;//vex为结点数组，s为结点下标
			path = "--" + path;
			s = source[s];//逆向拼接直到source为源点
		}
		path = vex[begin]  + path;//加上源点
		path = path + vex[k];//加上目的结点，此时path为源点到目的结点的完整路径
		cout << vex[begin]<<"--"<<vex[k]<<" dist:"<<dist[k]<< " path:"<<path << endl;
		for (j = 0; j < vexnum; j++)
		{//更新路径数组，判断通过新加入的顶点到其他顶点的路径是否可缩短
			if (find[j] == 0 && (min + adjMat[k][j]) < dist[j])
			{
				dist[j] = adjMat[k][j] + min;//满足条件说明通过新加入的结点可使路径变短
				source[j] = k;//修改到该顶点的最短路径的直接源点为顶点k
			}
		}
	}
}

void floyd(vector<vector<int>>& adjMat)
{//参数adjMat为图的邻接矩阵
	int dist[vexnum][vexnum];//存放各个顶点到其他顶点的最短路径
	int source[vexnum][vexnum];//存放最短路径的中转点
	int i = 0, j = 0, k = 0;
	cout << "floyd多源最短路径：" << endl;
	for (i = 0; i < vexnum; i++)
	{
		for (j = 0; j < vexnum; j++)
		{
			dist[i][j] = adjMat[i][j];//初始化路径长度
			dist[i][i] = 0;//设置到自己的路径为0，若邻接矩阵中已设置则不需要此行
			source[i][j] = j;//初始化中转点数组
		}
	}
	for (i = 0; i < vexnum; i++)
	{//i为中转顶点
		for (j = 0; j < vexnum; j++)
		{//j为起始顶点
			for (k = 0; k < vexnum; k++)
			{//k为结束顶点
				if (dist[j][i] != INFINITY && dist[i][k] != INFINITY && dist[j][i] + dist[i][k] < dist[j][k])
				{//先直接判断到起始顶点到中转顶点，及中转顶点到结束顶点是否可达，避免直接相加可能导致的溢出
					dist[j][k] = dist[j][i] + dist[i][k];//更新最短路径
					source[j][k] = source[j][i];//更新路径中转点
				}
			}
		}
	}
	for (i = 0; i < vexnum; i++)
	{//打印最短路径的结点
		for (j = 0; j < vexnum; j++)
		{
			cout << vex[i] << "--" << vex[j] << " dist:" << dist[i][j] << " path:";
			k = source[i][j];
			cout << vex[i];//打印起始顶点,vex为顶点数组，i为顶点下标
			while (k != j)
			{//如果路径下标不是结束顶点，则依次向下打印
				cout << "--" << vex[k];
				k = source[k][j];//k为中转结点，因此依次遍历中转结点k到结束顶点j即为完整路径
			}
			cout << "--" << vex[j] << endl;
		}
		cout << endl;
	}
}


int main() {
	vector<vector<int>> adjMat;
	AdjMatrix(adjMat);
	dijkstra(adjMat, 0);
	cout << endl;
	floyd(adjMat);
	return 0;
}