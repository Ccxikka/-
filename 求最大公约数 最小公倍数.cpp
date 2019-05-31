/*质数又称素数。一个大于1的自然数，除了1和它自身外，不能被其他自然数整除的数叫做质数；否则称为合数。

0和1既不是质数也不是合数，最小的质数是2

方法一：假如n是合数，必然存在非1的两个约数p1和p2，其中p1<=sqrt(n)，p2>=sqrt(n)，因此只需判断该数能否被1到sqrt(n)的数整除即可：
*/
#include <math.h>
using namespace std;

bool isprime(int n)
{
	if (n <= 3)
		return n > 1;//小于等于3的自然数只有2和3是质数
	int mid = int(sqrt(n));
	for (int i = 2; i <= mid; i++)
	{
		if (n%i == 0)
			return false;
	}
	return true;
}

//方法二：质数有一个特点，就是它总是等于 6x-1 或者 6x+1，其中 x 是大于等于1的自然数。论证：首先 6x 肯定不是质数，因为它能被 6 整除；其次 6x+2 肯定也不是质数，因为它还能被2整除；依次类推，6x+3 肯定能被 3 整除；6x+4 肯定能被 2 整除。那么，就只有 6x+1 和 6x+5 (即等同于6x-1) 可能是质数了。所以循环的步长可以设为 6，然后每次只判断 6 两侧的数即可
#include <math.h>
using namespace std;

bool isprime(int n)
{
	if (n <= 3)
		return n > 1;//小于等于3的自然数只有2和3是质数
	if (n % 6 != 1 && n % 6 != 5)//n为6x+1或6x+5,
		return false;
	int mid = int(sqrt(n));//取平方根
	for (int i = 5; i <= mid; i+=6)
	{//经过上面的if之后，n只能分解成(6x-1)(6y-1),(6x-1)(6y+1),(6x+1)(6y-1),(6x+1)(6y+1)这四种形式，因此判断其因子中有没有6x+5(等同于6x-1)或者6x+1(这里i从5开始，i+2则为6x+1)
		if(n % i == 0 || n %(i+2) == 0)//判断能否被6x+5及6x+1整除
			return false;
	}
	return true;
}
