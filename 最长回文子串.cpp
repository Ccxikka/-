#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
正读和反读都相同的字符序列为“回文”，如“abba”、“abccba”是“回文”，“abcde”和“ababab”则不是“回文”。
*/

/*
方法一：动态规划法：使用一个矩阵记录每个子串是不是回文，字符串的任意单个字符组成的字符串肯定都是回文，即矩阵的对角线都为true，
判断任意子串是不是回文，即求state[i][j]，如果i + 1 = j，那么state[i][j] = (s[i] == s[j])，
否则，state[i][j] = (s[i] == s[j]) && state[i + 1][j - 1]//即如果s[i][j]为回文，那么s[i+1][j-1]也一定为回文
可使用以为数组代替矩阵进行状态记录，由于state[i][j]和state[i+1][j-1]相关，所以i.j均从后往前进行循环，否则数组内容会被覆盖
时间复杂度O（n^2）,空间复杂度O（n）
*/
string longestPalindrome(string s) {
	string res = "";
	int len = s.length();
	if (len < 1)
		return res;
	vector<bool> f(len, false);
	f[len - 1] = true;
	res = s.substr(len - 1, 1);
	for (int i = len - 2; i >= 0; i--)
	{//从后往前，这样只需要一个一维数组保存状态
		for (int j = len - 1; j >= i; j--)
		{//从后往前
			if (i == j)
				f[j] = true;
			else if (s[i] == s[j])
			{
				if (i + 1 == j)//两者相邻且相等，为一个回文
					f[j] = true;
				else
					f[j] = f[j - 1];//中间的子串为回文则为回文，否则不为回文，由于是从后往前，所以j-1以前的数据是上一轮的，上一轮的i为此轮i+1，所以f[j-1]即为二维数组中的f[i+1][j-1]
			}
			else
				f[j] = false;//两者不相等则不可能为一个回文
			if (f[j] && (j - i + 1) > res.length())//以i开头，j结尾的串为一个回文串，且长度大于res时，则更新最长子串
				res = s.substr(i, j - i + 1);
		}
	}
	cout << res << endl;
	return res;		
}

/*
方法二：从中心扩展：遍历到数组的某一个元素时，以这个元素为中心，向两边进行扩展，如果两边的元素相同则继续扩展，否则停止扩展
注意如1221类的字符串，其对称中心为22，对于这种类型，可考虑两种方法：
1）对1，2，2，1进行填充，比如用#进行填充如下，因此1221变为#1#2#2#1#，然后逐个遍历扩展
2）每次处理时找到连续相同的字符，以以连续的相同字符为中心
时间复杂度O（n^2）,空间复杂度为O（1）
*/
string longestPalindrome_2(string s) {
	string res = "";
	int len = s.length();
	if (len < 1)
		return res;
	int j=0;
	for (int i = 0; i < len; i = j+1)
	{//从头开始遍历，以每个元素为中心进行扩展
		j = i + 1;
		for (; j < len && s[j] == s[i]; j++);//找到第一个不相等的位置
		j--;//s[i]和s[j]的元素相等
		int count = j - i + 1;//回文子串的长度
		int l = i - 1, r = j + 1;
		while (l >= 0 && r < len && s[l--] == s[r++])//往外扩展，相等则子串长度加2
			count = count + 2;
		if (count > res.length())
			res = s.substr(i - (count - (j - i + 1)) / 2, count);//获得子串
	}
	cout << res << endl;
	return res;
}

/*
使用Manacher算法实现：
在原字符串的每个相邻两个字符中间插入一个分隔符，同时在首尾也要添加一个分隔符，分隔符的要求是不在原串中出现，一般情况下可以用#号，使得源串长度为奇数。
用一个辅助数组Len[i]表示以字符T[i]为中心的最长回文字串的最右字符到T[i]的长度，比如以T[i]为中心的最长回文字串是T[l,r],那么Len[i]=r-i+1
https://segmentfault.com/a/1190000003914228
同样是遍历每个字符，以字符为中心进行扩展，不同的地方为：每次遍历时记录最长回文子串的中心pos及子串最右下边，
新遍历一个字符时，如果在这个最长回文子串外部，则直接扩展，
如果当前字符在这个最长回文子串内部，由于回文子串具有对称性，因此可设以其为中心的串长度为该字符关于pos对称的字符和字符和maxright距离的较小者，然后再开始往外扩展
这种方法可以减少每次每个字符向外的扩展次数。
时间复杂度是O(n)，空间复杂度是O(n)
*/
string longestPalindrome_3(string s) {
	string res = "";
	int len = s.length();
	if (len < 1)
		return res;
	string news(s);
	for (int i = 0; i < news.length(); i = i + 2)
		news.insert(i,1,'#');
	news.append(1, '#');//在每个元素后面及串的首尾处插入#,将源串元素个数变为2*len -1个，使得不用考虑奇偶
	int pos = 0, maxright = 0,maxlen = 1;
	vector<int> rl(2 * len + 1, 0);//保存以每个字符为中心的最长回文子串的长度
	rl[0] = 1;
	for (int i = 1; i < 2 * len + 1; i++)
	{//遍历每个字符
		if (i > maxright)
			rl[i] = 1;//在最长回文子串外部，直接扩展
		else
			rl[i] = min(rl[2 * pos - i], maxright - i);//在内部，则等于两者中的较小者，2 * pos - i为i关于pos的对称点
		//进行扩展操作
		int l = i - rl[i] / 2 - 1, r = i + rl[i] / 2 + 1, count = rl[i];
		while (l >= 0 && r < 2 * len + 1 && news[l--] == news[r++])
			count = count + 2;
		rl[i] = count;
		if (count > maxlen)
		{//记录最长回文串长度及串的中心
			pos = i;
			maxright = r - 1;
			maxlen = count;
		}
	}
	res = news.substr(pos - rl[pos] / 2, rl[pos]);//获得子串
	cout << res << endl;
	string resu;
	for (int i = 0; i < res.length(); i++)
	{
		if (res[i] != '#')//去掉#得到源串的最长回文子串
			resu.append(1, res[i]);
	}
	cout << resu << endl;
	return resu;
}

int main()
{
	string s = "aba";
	longestPalindrome_3(s);
	return 0;
}
