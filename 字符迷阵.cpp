/*
在这题的规则中，单词是如下规定的：
1. 在字符迷阵中选取一个字符作为单词的开头；
2. 选取右方、下方、或右下45度方向作为单词的延伸方向；
3. 以开头的字符，以选定的延伸方向，把连续得到的若干字符拼接在一起，则称为一个单词。
 
现在的问题是，给出一个字符迷阵，及一个要寻找的单词，问能在字符迷阵中找到多少个该单词的合法方案。
输入描述:
输入的第一行为一个正整数T，表示测试数据组数。 接下来有T组数据。每组数据的第一行包括两个整数m和n，表示字符迷阵的行数和列数。接下来有m行，每一行为一个长度为n的字符串，按顺序表示每一行之中的字符。再接下来还有一行包括一个字符串，表示要寻找的单词。  
数据范围：对于所有数据，都满足1<=T<=9，且输入的所有位于字符迷阵和单词中的字符都为大写字母。要寻找的单词最短为2个字符，最长为9个字符。字符迷阵和行列数，最小为1，最多为99。 对于其中50%的数据文件，字符迷阵的行列数更限制为最多为20。
输出描述:
对于每一组数据，输出一行，包含一个整数，为在给定的字符迷阵中找到给定的单词的合法方案数。
输入例子1:
3
10 10
AAAAAADROW
WORDBBBBBB
OCCCWCCCCC
RFFFFOFFFF
DHHHHHRHHH
ZWZVVVVDID
ZOZVXXDKIR
ZRZVXRXKIO
ZDZVOXXKIW
ZZZWXXXKIK
WORD
3 3
AAA
AAA
AAA
AA
5 8
WORDSWOR
ORDSWORD
RDSWORDS
DSWORDSW
SWORDSWO
SWORD
输出例子1:
4
16
5
*/

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

int getresult(vector<string>&tang, int m, int n, string& word) 
{
	int result = 0;
	int length = word.length();
	bool add = true;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (tang[i][j] == word[0])
			{//第一个字母相等才判断
				if (i + length - 1 < m && j + length - 1 < n)
				{//以该字母为首字母的单词长度是否满足
					add = true;
					for (int k = 1; k < length; k++)
					{
						if (tang[i + k][j + k] != word[k])
						{//斜向
							add = false;
							break;
						}
					}
					result = add ? result + 1 : result;
				}
				if (i + length - 1 < m)
				{
					add = true;
					for (int k = 1; k < length; k++)
					{//向下
						if (tang[i + k][j] != word[k])
						{
							add = false;
							break;
						}
					}
					result = add ? result + 1 : result;
				}
				if (j + length - 1 < n)
				{//向右
					add = true;
					for (int k = 1; k < length; k++)
					{
						if (tang[i][j+k] != word[k])
						{
							add = false;
							break;
						}
					}
					result = add ? result + 1 : result;
				}
			}
		}
	}
	return result;
}

int main()
{
	int num;
	cin >> num;
	vector<int> result(num, 0);
	for (int i = 0; i < num; i++)
	{
		int m, n;
		cin >> m >> n;
		vector<string> tang(m,"");
		string s;
		for (int j = 0; j < m; j++)
		{
			cin >> s;
			tang[j]= s;
			//cout << tang[j] << endl;
		}
		string word;
		cin >> word;
		result[i] = getresult(tang,m,n,word);
	}
	for (int i = 0; i < num; i++)
		cout << result[i] << endl;
	return 0;
}
