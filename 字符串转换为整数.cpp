#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。
当我们寻找到的第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字组合起来，作为该整数的正负号；假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成整数。
该字符串除了有效的整数部分之后也可能会存在多余的字符，这些字符可以被忽略，它们对于函数不应该造成影响。
注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换。
在任何情况下，若函数不能进行有效的转换时，请返回 0。
*/
int myAtoi(string str) {
	if (str.length() < 1)
		return 0;
	bool neg = false;
	int i = 0;
	long long res = 0;
	for (i = 0; i < str.length() && str[i] == ' '; i++);
	if (i < str.length())
	{
		if (str[i] == '-')
		{
			neg = true;
			i++;
		}			
		else if (str[i] == '+')
		{
			neg = false;
			i++;
		}
		while (i < str.length() && str[i] >= '0' && str[i] <= '9')
		{
			res = res * 10 + str[i] - '0';
			if (neg && (-1)*res < INT_MIN)//因为要表示比INT_MIN还小及比INT_MAX还大的数，所以res的类型应该大于int
				return INT_MIN;//如果比int能表示的最小数还小，则直接返回
			if (!neg && res > INT_MAX)
				return INT_MAX;
			i++;
		}
		res = neg ? (-1)*res : res;
		return int(res);//最后转换为int类型返回
	}
	else
		return 0;

}

int main()
{
	string s = "-123456678";
	cout<<myAtoi(s);
	return 0;
}
