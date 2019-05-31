/*
描述：有编号分别为a,b,c的三件物品，它们的重量分别是1，2，2，它们的价值分别是6，10，20，他们的数目分别是10，5，2，现在给你个承重为 8 的背包，如何让背包里装入的物品具有最大的价值总和？
多重背包和01背包、完全背包的区别：多重背包中每个物品的个数都是给定的，可能不是一个，绝对不是无限个。

解法一：
初始化时，只考虑一件物品a时：f[1][j] = min{num[1], j/weight[1]} * value[1]。
计算考虑i件物品承重限制为y时最大价值f[i][y]时，递推公式考虑两种情况:
1）	第 i 件物品一件也不放，就是f[i-1][y];
2）	要么第 i 件物品放 k 件，其中 1 <= k <= min{(y/weight[i]), num[i]}，考虑这一共 k+1 种情况取其中的最大价值即为f[i][y]的值，即:f[i][y] = max{f[i-1][y], (f[i-1][y-k*weight[i]]+k*value[i])}。 这里为什么不能像完全背包一样直接考虑f[i][y-weight[i]]+value[i]呢？因为这样不容易判断第 i 件物品的个数是否超过限制数量 num[i]。
 */
void package(int *w, int *v, int *num, int n, int c)
{
	int *result = new int[n];//结果输出，当获取最大重量时，分别是哪几个物品在包中
	int **f = new int*[n];//状态矩阵
	for (int i = 0; i < n; i++)
	{//分配内存
		f[i] = new int[c + 1];
		result[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{//初始化矩阵
		for (int j = 0; j <= c; j++)
			f[i][j] = 0;
	}
	for (int i = w[0]; i <= c; i++)
	{//初始化第一行
		int count = i / w[0] < num[0] ? i / w[0] : num[0];//背包数量有限，取较小者
		f[0][i] = count *v[0];
	}
	for (int i = 1; i < n; i++)
	{//i表示物品下标
		for (int j = 0; j <= c; j++)
		{//j表示背包容量
			if (j < w[i])
				f[i][j] = f[i - 1][j];
			else
			{
				int count = j / w[i] < num[i] ? j / w[i] : num[i];//取两者中的较小者
				f[i][j] = f[i - 1][j];
				for (int k = 0; k <= count; k++)
				{//逐个比较第i个物品拿几个时，价值最大
					if ((j - k * w[i] >= 0) && (f[i - 1][j - k * w[i]] + k * v[i]) > f[i][j])
						f[i][j] = f[i - 1][j - k * w[i]] + k * v[i];
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{//输出状态矩阵
		for (int j = 0; j <= c; j++)
			cout << f[i][j]<<" ";
		cout << endl;
	}
	cout << "maxvalue:" << f[n - 1][c] << endl;//最大值为矩阵最右下角的值
	int j = c;
	for (int i = n - 1; i > 0; i--)
	{//计算分别都是哪些物品在包中
		int count = min(num[i], j/w[i]);//计算两者中的较小者，需要包含algorithm头文件
		for (int k = 0; k <= count; k++)
		{
			if (j>=k*w[i] && f[i][j] == f[i - 1][j - k * w[i]] + k * v[i])
			{//相等则说明拿了count个
				result[i] = k;
				j = j - k * w[i];
				break;
			}
		}
	}
	result[0] = f[0][j] / v[0];
	for (int i = 0; i < n; i++)
	{
			cout << result[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{//清理动态分配内存
		delete[] f[i];
		f[i] = nullptr;
	}
	delete[] f; delete[] result;
	f = nullptr; result = nullptr;
}
int main() {
	int w[3] = { 1,2,2 };
	int v[3] = { 6,10,20};
	int num[3] = { 10,5,2 };
	package(w, v, num, 3, 8);
	return 0;
}

 
/*
解法二：
初始化时同一，递推时：
对于第i件物品，当y/weight[i]<=num[i]时，说明第i件物品此时可以任意拿，因此相当于前面的完全背包，此时：f[i][y] = max{f[i-1][y], (f[i][y-weight[i]]+value[i])};
当y/weight[i]>num[i]时，可容纳的数量超出了num[i]个，但是只能拿num[i]个，此时令total=num[i]*weight[i], 当背包容量为total时，其最大价值已由f[i][total]表示出，因此此时f[i][y] = max{f[i-1][y], (f[i][total]+f[i-1][y-total])}; 表示此时物品i已全部拿完，剩余的容量用于拿除i以外的其他物品，因此加上f[i-1][y-total]。
因此递推公式为：
f[i][y] = max{f[i-1][y], (f[i][y-weight[i]]+value[i])} ，y/weight[i]<=num[i]时
f[i][y] = max{f[i-1][y], (f[i][total]+f[i-1][y-total])} , y/weight[i]>num[i]时, total=num[i]*weight[i].
*/

void package(int *w, int *v, int *num, int n, int c)
{
	int *result = new int[n];//结果输出，当获取最大重量时，分别是哪几个物品在包中
	int **f = new int*[n];//状态矩阵
	for (int i = 0; i < n; i++)
	{//分配内存
		f[i] = new int[c + 1];
		result[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{//初始化矩阵
		for (int j = 0; j <= c; j++)
			f[i][j] = 0;
	}
	for (int i = w[0]; i <= c; i++)
	{//初始化第一行
		int count = i / w[0] < num[0] ? i / w[0] : num[0];//背包数量有限，取较小者
		f[0][i] = count *v[0];
	}
		
	for (int i = 1; i < n; i++)
	{//i表示物品下标
		for (int j = 0; j <= c; j++)
		{//j表示背包容量
			if (j >= w[i])
			{
				if (j / w[i] <= num[i])
					f[i][j] = f[i - 1][j] > (f[i][j - w[i]] + v[i]) ? f[i - 1][j] : f[i][j - w[i]] + v[i];//此时可以任意拿，相当于完全背包
				else//此时则最多只能拿num[i]个
					f[i][j] = f[i - 1][j] > (f[i][w[i] * num[i]] + f[i - 1][j - w[i] * num[i]]) ? f[i - 1][j] : f[i][w[i] * num[i]] + f[i - 1][j - w[i] * num[i]];
			}
			else
				f[i][j] = f[i - 1][j];			
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= c; j++)
			cout << f[i][j]<<" ";
		cout << endl;
	}
	cout << "maxvalue:" << f[n - 1][c] << endl;//最大值为矩阵最右下角的值
	int j = c;
	for (int i = n - 1; i > 0; i--)
	{//计算分别都是哪些物品在包中，过程和解法一相同
		int count = min(num[i], j/w[i]);//计算两者中的较小者，需要包含algorithm头文件
		for (int k = 0; k <= count; k++)
		{
			if (j>=k*w[i] && f[i][j] == f[i - 1][j - k * w[i]] + k * v[i])
			{
				result[i] = k;
				j = j - k * w[i];
				break;
			}
		}
	}
	result[0] = f[0][j] / v[0];
	for (int i = 0; i < n; i++)
			cout << result[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
	{//清理动态分配内存
		delete[] f[i];
		f[i] = nullptr;
	}
	delete[] f; delete[] result;
	f = nullptr; result = nullptr;
}

int main() {
	int w[3] = { 1,2,2 };
	int v[3] = { 6,10,20};
	int num[3] = { 10,5,2 };
	package(w, v, num, 3, 8);
	return 0;
}

/*
解法三：
由01背包的分析可知，01背包中允许放入的物品有重复，即01背包中如果考虑要放入的物品的重量和价格相同，不影响最终的结果，因为可以考虑把多重背包问题中限制数目的物品拆分成单独的一件件物品，作为01背包问题考虑。因此问题解法和01背包一致。即将有数目限制的物品转换为该数目的多个相同物品，然后使用01背包算法。
该种情况下获得背包中每个物品的数目：
*/
while (i < n)
{
	cin >> w >> v >> n1;
	N[i] = n1;
	while (n1--)
	{//限定数目个都装进数组中
		W.push_back(w);
		V.push_back(v);
	}
	i++;
}
vector<int> res;
for (int i = 0; i < W.size(); i++)
	res.push_back(0);//结果初始化为0
int value = knapsack_limitnum(W, V, res, C);//01背包函数
cout << value << endl;
i = 0;
int j = 0;
int count = 0, sum = N[i];//N[i]为第一个物品数量
while (j < res.size())
{//res为所有物品的结果，相同物品放在一起
	if (j < sum)
	{
		if (res[j])//查看每一种物品拿了几个，01背包中拿了就置1，没有就置0
			count++;//相同物品，置1时加加
	}
	else {//下一个物品
		cout << count << " ";
		i++;
		sum += N[i];//下一个物品数目
		count = (res[j]) ? 1 : 0;
	}
	j++;
}

