/*01背包问题
描述：有编号分别为a,b,c,d,e的五件物品，它们的重量分别是2,2,6,5,4，它们的价值分别是6,3,5,4,6，每件物品数量只有一个，现在给你个承重为10的背包，背包里装入的物品具有最大的价值总和是多少？具有最大价值时，分别是哪些物品在包里？

思路分析：状态转移方程为：
设背包总容量为C，j为当前背包可用容量，i为前i个物品，第i个物品价值为Vi，第i个物品重量Wi。F[i,j]表示当背包可用容量为j时，在前i个物品中，背包能装下的最大价值，有方程：
F[i,j] = max { F[i−1,j], F[i−1,j−Wi]+Vi }（F[i−1,j] 表示不拿物品i，F[i−1,j−Wi]+Vi 表示拿物品i）
*/

#include<iostream>
using namespace std;
/*
*  W：物品重量数组
*  V：物品价值数组
*  n：物品数量
*  C：背包总容量
*/
void package01(int *w, int *v, int n, int c)
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
		f[0][i] = v[0];//初始化第一行，当背包容量小于第1个物品重量时，背包价值为0，否则为背包价值为第1个物品价值
	for (int i = 1; i < n; i++)
	{//i表示物品下标
		for (int j = 0; j <= c; j++)
		{//j表示背包容量
			if (j - w[i] >= 0 && (f[i - 1][j - w[i]] + v[i]) > f[i - 1][j])
				f[i][j] = f[i - 1][j - w[i]] + v[i];//背包可容纳当前物品，且拿当前物品比不拿价值大时才拿
			else
				f[i][j] = f[i - 1][j];
		}
	}
	cout << "maxvalue:" << f[n - 1][c] << endl;//最大值为矩阵最右下角的值
	int j = c;
	for (int i = n - 1; i > 0; i--)
	{//计算分别都是哪些物品在包中
		if (f[i][j] == f[i - 1][j - w[i]] + v[i])
		{//如果相等，说明拿了物品i
			result[i] = 1;
			j = j - w[i];//减去拿走的重量，计算下一个值
		}
	}
	if (f[0][j])//大于0说明背包容量可以容纳第一个物品，则说明拿了第一个物品。考虑情况：v2>v1,w2=w1,c=w1时，此时拿物品2的价值更大，那么经过上述for循环后，可以确定拿了物品2，且拿走物品2后j=0，此时则无法拿物品1
		result[0] = 1;
	for (int i = 0; i < n; i++)
	{
		if (result[i])
			cout << i << " ";
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
	int w[5] = { 2,2,6,5,4 };
	int v[5] = { 6,3,5,4,6 };
	package01(w, v, 5, 10);
	return 0;
}

/*优化：因为在考虑前i个问题时，只与i-1的结果相关，可以使用一维数组来存放结果，又因为F[i,j]需要参考F[i-1,j]和F[i-1,j-Wi]的值，因此从右到左遍历，避免数据被覆盖。因此有：
F[j] = max { F[j], F[j−Wi]+Vi } j初始化为背包总容量C
在这种情况，求哪些物品在包中的方法就不可用了，仍需要一个二维数组标记path*/

void package02(int *w, int *v, int n, int c)
{
	int *f = new int[c+1];
	for (int i = 0; i <= c; i++)//初始化
	{
		if (i < w[0])
			f[i] = 0;
		else
			f[i] = v[0];
	}
	for (int i = 1; i < n; i++)
	{//i表示物品下标
		for (int j = c; j >= 0; j--)
		{//j表示背包容量
			if (j - w[i] >= 0 && (f[j - w[i]] + v[i]) > f[j])
				f[j] = f[j - w[i]] + v[i];//背包可容纳当前物品，且拿当前物品比不拿时价值大时才拿，若使用path数组，则此处path[i][j]置位1，最后通过从Path[n][c]逆着走向Path[0][0]来获取背包内物品，path[i][j]为1表示取该物品，之后i--,j=j-w[i]依次循环。
		}
	}
	cout << "maxvalue:" << f[c] << endl;//最大值为矩阵最右下角的值
	delete[] f; 
	f = nullptr;
}
