/*
输入： 小明搜集到的系统耗时和依赖列表
5  4   // 表示有5个系统和 4个依赖关系
3      // 调用1号系统耗时 3 ms
2      // 调用2号系统耗时 2 ms
10     // 调用3号系统耗时 10 ms
5      // 调用4号系统耗时 5 ms
7      //  调用5号系统耗时 7 ms
1 2    //  2号系统依赖1号系统
1 3    //  3号系统依赖1号系统
2 5    //  2号系统依赖5号系统
4 5    //  4号系统依赖5号系统
输出:  调用链路的数目 和最大的耗时， 这里有三条链路1->2->5，1->3， 4->5，
最大的耗时是1到3的链路 3+10 = 13，无需考虑环形依赖的存在。

输入：
5 4
3
2
10
5
7
1 2
1 3
2 5
4 5
输出：
3  13

思路为dfs深度优先搜索：
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

struct edge
{//存储每一条边
	int end;
	edge * next;
	bool visit;//每条边是否被访问过
};
struct node
{
	int time;//每个结点耗时
	edge *first;//以每个顶点为起始顶点的边，即依赖关系	
};

int nodelink(vector<node>&vexdata, node &curnode, int* time, int*count)
{
	edge *p = curnode.first;
	if (p == nullptr)
	{//到链路末尾，链路总数加1，返回该链路的时间
		*count += 1;
		return *time;
	}
	int oritime = *time;
	int max = *time;
	while (p != nullptr && !p->visit)
	{
		*time += vexdata[p->end - 1].time;
		p->visit = true;
		int curtime = nodelink(vexdata, vexdata[p->end - 1], time,count);
		if (curtime > max)
			max = curtime;
		p = p->next;//计算该结点的下一条链路
		*time = oritime;//时间要恢复为初始时间，开始新的路径计算
	}
	return max;//返回curnode为起始结点的链路中最长时间
}
void getlink(vector<node> &vexdata)
{//实质为一个dfs
	int maxlen = 0, links = 0;
	for (int i = 0; i < vexdata.size(); i++)
	{//对每个结点遍历
		edge *p = vexdata[i].first;
		int time = 0, count = 0;
		if (p != nullptr && !p->visit)
		{//对于有链路的结点才进行计算
			time = vexdata[i].time;//第一个结点的时间
			int curtime = nodelink(vexdata, vexdata[i], &time, &count);//curtime为以当前结点为起始结点的所有链路中，耗时最长的时间，count为以当前结点为起始结点的链路的条数
			if (curtime > maxlen)
				maxlen = curtime;
			links += count;
		}
	}
	cout << links << " " << maxlen;
}

int main()
{
	int vex, edges;
	cin >> vex >> edges;
	vector<node> vexdata(vex);
	for (int i = 0; i < vex; i++)
	{
		cin >> vexdata[i].time;
		vexdata[i].first = nullptr;
	}
	for (int i = 0; i < edges; i++)
	{
		int begin, end;
		cin >> begin >> end;
		edge *p = new edge();
		//每一条边插到头部
		p->end = end;
		p->visit = false;
		p->next = vexdata[begin - 1].first;
		vexdata[begin - 1].first = p;
	}
	getlink(vexdata);
	return 0;
}
