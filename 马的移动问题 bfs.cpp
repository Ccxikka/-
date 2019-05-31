/*
题目描述
小明很喜欢下国际象棋，一天，他拿着国际象棋中的“马”时突然想到一个问题：
给定两个棋盘上的方格a和b，马从a跳到b最少需要多少步？
国际象棋棋盘为8格*8格，马的走子规则为，每步棋先横走或直走一格，然后再往外斜走一格。

输入格式
输入包含多组测试数据。每组输入由两个方格组成，每个方格包含一个小写字母（a~h），表示棋盘的列号，和一个整数（1~8），表示棋盘的行号。

输出
对于每组输入，输出一行“To get from xx to yy takes n knight moves.”。

样例输入
e2 e4
a1 b2
b2 c3
a1 h8

样例输出
To get from e2 to e4 takes 2 knight moves.
To get from a1 to b2 takes 4 knight moves.
To get from b2 to c3 takes 2 knight moves.
To get from a1 to h8 takes 6 knight moves.

解题思路：这是一道简单的广搜问题，根据起始的位置，可以知道下一步可以走的八个位置，进行搜索，中间判断，不能走到原来的位置，还有就是不能跳到棋盘的外面去了，然后一步步搜索，直到找到最终位置就可以了。
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

struct node
{//存储每一步的位置及到达该点所走的步数
	int x;
	int y;
	int step;
};
int visit[8][8];
int to[8][2] = { -1,-2,-2,-1,-1,2,-2,1,1,2,2,1,1,-2,2,-1 };//每走一步坐标的变化可能

int check(int x, int y)
{//判断走的这一步是否有效
	if (x < 0 || y < 0 || x >= 8 || y >= 8)
		return 1;//超出棋盘范围，这一步无效
	if (visit[x][y])
		return 1;//这一点之前已走到，无需再走
	return 0;
}

int bfs(int sx, int sy, int ex, int ey, int visit[8][8])
{
	node cur;
	cur.x = sx, cur.y = sy, cur.step = 0;
	visit[sx][sy] = 1;
	deque<node> q;
	q.push_back(cur);
	while (!q.empty())
	{
		cur = q.front();
		q.pop_front();
		if (cur.x == ex && cur.y == ey)
			return cur.step;//每个点走的步数一样，哪个点最先走到终点其步数即为最小步数
		for (int i = 0; i < 8; i++)
		{
			node next = cur;
			next.x = next.x + to[i][0];
			next.y = next.y + to[i][1];
			if (check(next.x, next.y))
				continue;//不合法则不入队
			next.step = next.step + 1;
			visit[next.x][next.y] = 1;
			q.push_back(next);
		}
	}
}

int main()
{
	vector<string>start;
	vector<string>end;
	string st, ed;
	while (cin>>st>>ed)
	{//cin输入时两个字符串之间以空格进行区分，输入ctrl+z加回车表示输入结束
		//cout << st << ed << endl;
		start.push_back(st);
		end.push_back(ed);
	}
	for (int i = 0; i < start.size(); i++)
	{//对每组数据进行处理
		int sx = start[i][0] - 'a';
		int sy = start[i][1] - '1';
		int ex = end[i][0] - 'a';
		int ey = end[i][1] - '1';
		memset(visit, 0, sizeof(visit));
		int step = bfs(sx, sy, ex, ey, visit);
		cout << "to get from " << start[i] << " to " << end[i] << " takes " << step << " knight moves." << endl;
	}
	return 0;
}
