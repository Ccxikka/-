/*1）更相减损法： 
①先判断两个数的大小，如果两数相等，则这个数本身就是就是它的最大公约数。 
②如果不相等，则用大数减去小数，然后用这个较小数与它们相减的结果相比较，如果相等，则这个差就是它们的最大公约数，而如果不相等，则继续执行②操作。
一直到减数和差值相同时，则这个相同的数就是它们的最大公约数
*/
int maxdivider(int x, int y)
{
	while (x != y)
	{
		if (x > y)
			x = x - y;
		else
			y = y - x;
	}
	return x;
}

/*
2）辗转相除法： 
①当两个数相等时，其中任意一个就是它们的最大公约数，因为它们的余数为0； 
②当两个数不相等时，用较大数除以较小数，当余数不为0时，这时 
使较小数作为被除数，余数作为除数，继续 ②的操作，直至余数为0,也就是这两个数相等时，其中任一数为最大公约数。
*/
int maxdivider(int x, int y)
{
	while (x * y)//当其中一个为0时，终止循环  
	{
		if (x > y)//将较大数模较小数的结果（余数）赋给较大的值，直到两个数相等  
			x %= y;
		else if (x < y)
			y %= x;
	}
	return x > y ? x : y;
}

/*
3）	递归及移位运算
gcb(a,b)是求a,b的最大公约数的函数
当a和b均为偶数，gcb(a,b) = 2*gcb(a/2, b/2) = 2*gcb(a>>1, b>>1)
当a为偶数，b为奇数，gcb(a,b) = gcb(a/2, b) = gcb(a>>1, b)
当a为奇数，b为偶数，gcb(a,b) = gcb(a, b/2) = gcb(a, b>>1)
当a和b均为奇数，利用更相减损术运算一次，gcb(a,b) = gcb(b, a-b)， 此时a-b的结果必然是偶数，又可以继续进行移位运算。
*/
int maxdivider(int x, int y)
{
	if (x == y)
		return x;
	if (x < y)
		return maxdivider(y, x);//保证较大的数始终在前面
	if (!(x & 1) && !(y & 1))//两数都是偶数
		return maxdivider(x >> 1, y >> 1) << 1;
	else if (!(x & 1) && (y & 1))//x为偶数，y为奇数
		return maxdivider(x >> 1, y);
	else if((x & 1) && !(y & 1))//x为奇数，y为偶数
		return maxdivider(x , y >> 1);
	else//两者都为奇数
		return maxdivider(x-y, y);
}

/*
2.最小公倍数就是几个数公有的倍数中最小的一个。 
如果求a和b的最小公倍数，可先求出它们的最大公约数，最小公倍数就是 a*b/最大公约数
*/
