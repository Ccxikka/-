/*描述：有编号分别为a,b,c,d的四件物品，它们的重量分别是2,3,4,7，它们的价值分别是1,3,5,9，每件物品数量无限个，现在给你个承重为10的背包，如何让背包里装入的物品具有最大的价值总和？
完全背包问题与01背包问题的区别在于每一件物品的数量都有无限个，而01背包每件物品数量只有一个。

问题解法：其实和01背包问题一样，只是初始化的值和递推公式需要稍微变化一下。
初始化时，当只考虑一件物品a时，f[1][j] = j/weight[a] * value[a]。 
递推公式计算时，f[i][y] = max{f[i-1][y], (f[i][y-weight[i]]+value[i])}，注意这里当考虑放入一个物品 i 时应当考虑还可能继续放入 i，因此这里是f[i][y-weight[i]]+value[i], 而不是f[i-1][y-weight[i]]+value[i]。
 */

int packages_full(int C, vector<int> &W, vector<int> &V, int n, vector<int> &inp)
{//参数inp用于保存哪些物品在背包中
	vector<vector<int> > F(n, vector<int>(C + 1));//F[i][j]记录背包可用重量为j时，前i个物品的最大价值
	for (int i = 0; i < n; i++)//初始化表格
	{
		for (int j = 0; j < F[0].size(); j++)
			F[i][j] = 0;
	}
	for (int j = 1; j < F[0].size(); j++)//初始化第一行
		F[0][j] = (j < W[0]) ? 0 : ((j / W[0])*V[0]);//每个物品不止一个
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < F[0].size(); j++)
		{
			if (j < W[i])
				F[i][j] = F[i - 1][j];//装不下该物品
			else
				F[i][j] = (F[i - 1][j] < F[i][j - W[i]] + V[i]) ? F[i][j - W[i]] + V[i] : F[i - 1][j];//可装下该物品。状态转移方程
		}
	}
	int result = F[n - 1][F[0].size() - 1];//最大价值
	//cout << result << endl;
	//inp标记哪些物品在包中
	int j = C;
	int i = n - 1;
	while (i)
	{
		while (j > 0 && F[i][j] == F[i][j - W[i]] + V[i])
		{//注意这里使用while，因为i物品可能拿了多次，如果用if则只会判断一次
			inp[i]++;//相等则加一次，说明物品i又拿了一次
			j -= W[i];
		}
		i--;
	}
	inp[0] = F[0][j] / V[0];//对于第一个物品的计算
	return result;
}
int main() {
	vector<int> W{ 4,5,6,2,2 };
	vector<int> V{ 6,4,5,3,6 };
	int C = 10;
	int n = W.size();
	vector<int> inp1(n, 0);//标记是否在包中
	cout << "3、完全背包最大总价值：" << packages_full(C, W, V, n, inp1) << endl;
	cout << "输出在背包中物品： ";
	for (int i = 0; i < inp1.size(); i++)
		cout << inp1[i] << " ";
	cout << endl;
	return 0;
}

