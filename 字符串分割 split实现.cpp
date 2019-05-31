#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> mysplit(const string& s, const char ch)
{
	vector<string> res;
	if (s.length() < 1)
		return res;
	int i = 0, j = 0;
	while (j < s.length() && s[j] == ch)
		j++;//找到开头第一个不等于分割字符的字符
	i = j;
	while (j < s.length())
	{
		if (s[j] == ch)
		{
			string sub = s.substr(i, j - i);//找到一个分隔符，获取前面的子串
			res.push_back(sub);
			while (j<s.length() && s[j] == ch)//连续的分隔符当做一个分隔符
				j++;
			i = j;
		}
		else
			j++;
	}
	if (j > i)
	{//满足条件时说明还有最后一个子串，否则没有
		string sub = s.substr(i, j - i);//最后的子串
		res.push_back(sub);
	}	
	return res;
}

int main()
{
	string s = " aaa hello, I am a student, come from shangdongaaa";
	vector<string> res1 = mysplit(s, 'a');
	for (auto a : res1) {//使用auto直接遍历容器
		cout << a << endl;
	}
	return 0;
}
