//【实现strlen】
int mystrlen(const char *str) {
	if (str ==nullptr)
		return 0;
	int len = 0;
	while (*str++ != '\0')
		len++;
	return len;
}

//如果要求不使用额外变量就需要用递归版
int mystrlen(const char *str) {
	if (str ==nullptr)
		return 0;
	return (*str == '\0') ? 0 : 1 + mystrlen(++str);//这里要使用++str，如果用str++的话参数值还是str，不是str+1
}

//【实现strcmp】
#include <cassert>
using namespace std;

int mystrcmp(const char *str1, const char *str2) {
	assert(str1!=nullptr &&  str2!=nullptr);//assert表达式为真继续后面的程序，否则打印错误信息终止程序运行
	while (*str1 == *str2 && (*str1) != '\0')
	{//不能在while里加加，否则两者不等时str1和str2还是加加了，那么两者就指向了下一个字符，而不是当前不相等的那个字符。
		str1++;
		str2++;
	}
	if (*str1 == *str2)//退出循环因为两者不等或str1为空，因此若两者相等说明均为空结束
		return 0;
	//使用*(unsigned char*)str1而不是用*str1。这是因为传入的参数为有符号数，有符号字符值的范围是-128~127，无符号字符值的范围是0~255，而字符串的ASCII没有负值，若不转化为无符号数则会出现错误。
	return *(unsigned char*)str1 > *(unsigned char*)str2 ? 1 : -1;//比较ASCII码
}

//【实现strcat】
char* mystrcat(char *str1, const char *str2) {
	if (str1 == nullptr)
		return nullptr;
	if (str2 == nullptr)
		return str1;
	char * p = str1;//后续需要移动指针str1，需要一个指针来保存初始地址
	while (*p != '\0')
		p++;
	while (*str2 != '\0')//这里也可以直接写成while(*p++ = *str2++);while里面为空，另外这样写的话后面的*p='\0'就不需要了
	{
		*p= *str2;
		p++;
		str2++;
	}
	*p = '\0';
	return str1;
}

/*【实现strcpy】
strcpy和strncpy都需要程序员来保证dst有足够的空间来容纳将被拷贝的字符串，如果dst空间不足，得到的结果是未定义的；同样也需要程序员来保证他们的空间没有重叠。strncpy只是增加了一个拷贝长度的参数，针对这个参数也要做一些判断：如果src长度不足n，那么dst不足n的部分将会用null byte来补齐。
strcpy是高危函数，因为它遇到’\0’才停止运行，遇到没有’\0’的字符串，它就会一直运行下去。*/

char* mystrcpy(char *str1, const char *str2) {
	if (str1 == nullptr || str2 == nullptr)
		return nullptr;
	char *p = str1;
	while ( (*p++ = *str2++) !='\0');//strcpy会拷贝’\0’结束符
	return str1;
}

char* mystrncpy(char *str1, const char *str2, size_t n) {//拷贝指定个数个字符
	if (str1 == nullptr || str2 == nullptr)
		return nullptr;
	char *p = str1;
	size_t i = 0;
	for (i = 0; i < n && str2[i] != '\0'; i++)
		p[i] = str2[i];//此处str2还没有到\0，但是已经到n之后，并不会添加一个\0到p的末尾
	for (; i < n; i++)//源串不足n个字节的使用\0补齐，但是n在源串长度内时并不会在末尾添加\0结束符
		p[i] = '\0';
	return str1;
}
