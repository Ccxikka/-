/*【实现memcpy】
需要处理重叠的情况：*/

void* mymemcpy(void *dest, const void *src, size_t n) {
	if (dest == nullptr || src == nullptr)
		return nullptr;
	if (dest == src)
		return dest;
	char * de = (char *)dest;
	char * sr = (char *)src;
	if (dest > src && de -sr< n)
	{//内存有重叠，进行反向拷贝，否则源串的部分内容在完成拷贝前就会覆盖，导致拷贝内容出错
		de = de + n-1;//这里记得减1才是反向拷贝的开始地址
		sr = sr + n-1;
		while(n--)
			*de-- = *sr--;			
	}
	else
	{//无重叠则正向拷贝
		while (n--)
			*de++ = *sr++;		
	}
	return dest;
}

//此外为了提高效率，在地址不对齐的情况下是一个字节一个字节拷贝，地址对齐以后使用CPU字长来拷如32bit或64bit：
void* mymemcpy(void *dest, const void *src, size_t n) {
	if (dest == nullptr || src == nullptr)
		return nullptr;
	if (dest == src)
		return dest;
	size_t n1 = n / 4;//size_t为无符号类型
	size_t n2 = n % 4;
	char * de = (char *)dest;
	char * sr = (char *)src;
	if (dest > src && de -sr< n)
	{//内存有重叠，进行反向拷贝，否则源串的部分内容在完成拷贝前就会覆盖，导致拷贝内容出错
		de = de + n-1;//这里记得减1才是反向拷贝的开始地址
		sr = sr + n-1;
		//while(n--)//反向拷贝的时候不能直接以CPU字长拷贝，由于拷贝时还是从某地址起始处，正常拷贝指针类型大小数据，所以若想以CPU字长拷贝，那么拷贝的起始位置需要计算
			//*de-- = *sr--;	
		while(n2--)
			*de-- = *sr--;//先拷贝一字节的
		de = de - 3; sr = sr - 3;//上面while之后de sr均往上移一位，由于之后要拷贝CPU字长的，所以减3
		while (n1--)
		{
			*(int *)de = *(int *)sr;
			de = de - 4;
			sr = sr - 4;
		}
	}
	else
	{//无重叠则正向拷贝
		while (n1--)
		{
			*(int *)de = *(int *)sr;
			de = de + 4;//不能写成((int *)de)++,这样是将de的值变成一个int类型的地址，地址无法加加。
			sr = sr + 4;//如果写成(int *)sr++,应该是char*类型的sr++，然后将地址转换为int *类型，而不是int *类型的指针++，所以写成加4
		}
		while (n2--)
			*de++ = *sr++;
					
	}
	return dest;
}
