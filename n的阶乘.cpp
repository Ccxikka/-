//数据较大时会有溢出，因此使用数组保存结果：
void nmulti(int n)
{
	vector<int> res(1000, 0);
	res[0] = 1;
	int count = 1;//表示已有几位数
	int addbit = 0,j=0;//表示进位
	for (int i = 2; i <= n; i++)
	{
		addbit = 0;
		for (j = 0; j < count; j++)
		{//转化为数组中的每一位乘以i
			int num = res[j] * i +addbit;
			addbit = num / 10;//计算进位
			res[j] = num % 10;//每个数组成员只存一位数字
		}
		while (addbit)//进位不止一个数
		{
			res[j] = addbit%10;
			addbit = addbit / 10;
			j++;
		}
		count = j;//乘一次后结果的位数
	}
	for (int i = count - 1; i >= 0; i--)
		cout << res[i];//倒序输出
	cout << endl;
}
