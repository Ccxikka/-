#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

void getall(string oristr, int begin, int size, set<string>& allstr, string add)
{
	int j = 0;
	if (size <0)
		return;
	if (size == 0)
	{
		allstr.insert(add);
		//cout << add << endl;
		return;
	}
	string curstr(oristr,begin);
	if (size > curstr.size())
		return;
	if (size == curstr.size())
	{
		allstr.insert(add + curstr);
		//cout << add + curstr << endl;
		return;
	}
	else
	{
		getall(oristr, begin + 1, size - 1, allstr, add + curstr[0]);
		getall(oristr, begin + 1, size, allstr, add);
	}

}

vector<string> Permutation(string str) {
	set<string> allstr;
	vector<string> str1;
	if (str.size() < 1)
		return str1;
	string add;
	for (int i = str.size(); i > 0; i--)
		getall(str, 0, i, allstr, add);
	for (set<string>::iterator it = allstr.begin(); it != allstr.end(); it++)
	{
		str1.push_back(*it);
		cout << *it << endl;
	}		
	return str1;
}

// ====================测试代码====================
void Test(char* pStr)
{
	if (pStr == nullptr)
		printf("Test for nullptr begins:\n");
	else
		printf("Test for %s begins:\n", pStr);

	Permutation(pStr);

	printf("\n");
}

int main(int argc, char* argv[])
{
	char string4[] = "abc";
	Test(string4);

	return 0;
}
