/*
当用户在一个会话中发送或接收信息时，如果该会话已经在会话列表中，则会从原来的位置移到列表的最上方；如果没有在会话列表中，则在会话列表最上方插入该会话。

输入描述:
输入的第一行为一个正整数T（T<=10），表示测试数据组数。
接下来有T组数据。每组数据的第一行为一个正整数N（1<=N<=200），表示接收到信息的次数。第二行为N个正整数，按时间从先到后的顺序表示接收到信息的会话id。会话id不大于1000000000。

输出描述:
对于每一组数据，输出一行，按会话列表从上到下的顺序，输出会话id。
相邻的会话id以一个空格分隔，行末没有空格。

输入例子1:
3
5
1 2 3 4 5
6
1 100 1000 1000 100 1
7
1 6 3 3 1 8 1

输出例子1:
5 4 3 2 1
1 100 1000
1 8 3 6
*/

//方法一：使用deque，对于每个列表的元素，不存在则从头部插入，存在则先删除，再从头部插入：
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

void  getsession(vector<int> &line,int linenum, deque<int> &session)
{
	for (int i = 0; i < linenum; i++)
	{
		if (session.size() < 1)
			session.push_front(line[i]);//后来的数先输出，所以从头部插入
		else
		{
			deque<int>::iterator it = find(session.begin(), session.end(), line[i]);
			if (it == session.end())
				session.push_front(line[i]);
			else
			{//有相同的数字，则删除后添加
				session.erase(it);
				session.push_front(line[i]);
			}
		}
	}
	return;
}

int main()
{
	int num;
	cin >> num;
	vector<deque<int>> result;
	for (int i = 0; i < num; i++)
	{
		int linenum;
		cin >> linenum;
		vector<int> line(linenum, 0);
		deque<int> session;
		int j = 0;
		char c;
		cin >> line[j++];
		while ((c=getchar()) !='\n')
		{//输入以空格分割的数字，存入vector
			cin >> line[j++];//当c为空格不是换行时，就继续输入line[j]
		}
		getsession(line,linenum, session);
		result.push_back(session);
	}
	for (int i = 0; i < num; i++)
	{
		int j = 0;
		for (j = 0; j < result[i].size()-1; j++)
			cout << result[i][j] << " ";
		cout << result[i][j] << endl;
	}
	return 0;
}

//方法二：使用map去掉重复的数字，并倒序输出
#include<map>
#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
 
int main(int agrc, char** argv)
{
    int T;
    cin >> T;
    for(int i=0; i<T; ++i)
    {
        int N;
        cin >> N;
        unordered_map<int,int> m;
        for(int i=0; i<N; ++i)
        {
            int id;
            cin >> id;//map以数字为key，以位置为value
            m[id] = i;//map中对于重复出现的数字，更新其下标，表示顺序
        }
        vector<int> v(N,-1);
        for(auto p : m)
        {
            v[p.second] = p.first;//将map中的数字存在相应的位置上，map中已经去掉了相同的数字，相同数字只保存了最后出现的
        }
         
        for(int i=N-1; i>=0; --i)//最后出现的在最前面，所以倒序输出
            if(v[i]!=-1) cout << v[i] << " ";
        cout << endl;
    }
}
