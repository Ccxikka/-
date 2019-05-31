/*使用后缀数组，然后求该字符串后缀数组的最长公共前缀
后缀数组就是将文本串的所有后缀按照字典序进行排序，将后缀的起始字符的下标存入SA数组中。
比如字符串“ababa”， 他的后缀有ababa, baba, aba, ba, a
按照字典序排序为a, aba, ababa, ba, baba他们的开始字符的下标分别为5， 3， 1， 4， 2。因此SA[1~5]分别为5,3,1,4,2
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string findstr(string s)
{
	vector<string> suff;
	for (int i = s.length() - 1; i >= 0; i--)
		suff.push_back(s.substr(i));
	sort(suff.begin(), suff.end());
	string res = "";
	int maxlen = 0;
	for (int i = 0; i < suff.size()-1; i++)
	{
		int count = 0, s1 = 0, s2 = 0;
		while (s1 < suff[i].size() && s1 < suff[i + 1].size() && suff[i][s1] == suff[i + 1][s2])
		{
			s1++;
			s2++;
			count++;
		}
		if (count > maxlen)
		{
			maxlen = count;
			res = suff[i].substr(0, s1);
		}
	}
	return res;
}

int main()
{
	string s = "Ask not what your country can do for you, but what you can do for your country";
	cout << findstr(s);
	return 0;
}

