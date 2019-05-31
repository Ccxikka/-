#include <iostream>
#include <vector>
using namespace std;

/*
给定两个大小为 m 和 n 的有序数组 nums1 和 nums2 。请找出这两个有序数组的中位数。要求算法的时间复杂度为 O(log (m+n))

示例 1:nums1 = [1, 3]，nums2 = [2]。中位数是 2.0
示例 2:nums1 = [1, 2]，nums2 = [3, 4] 中位数是 (2 + 3)/2 = 2.5

解法：
要求O(log(m+n))的时间复杂度，那么必须使用二分法，那么如何进行二分？
考虑将数组num1分为2部分[part1,part3]，将数组num2分为2部分[part2,part4]，然后假设part1包含sz1个元素，part2包含sz2个元素。
那么我们肯定是要找到part1和part2，使得：
sz1+sz2 = len/2，len为两个数组总长
可以以len/2为长度总和，以part1为基准：
当part1变大时，sz1扩大，那么sz2必须减小，因此part2要减小
当part1变小时，sz1减小，那么sz2必须扩大，因此part2要扩大

现在问题是根据什么标准来扩大或减小part1？这里设4个变量：
part1中最右边的元素（即part1最大的元素）为l1
part3中最左边的元素（即part3最小的元素）为r1
part2中最右边的元素（即part2最大的元素）为l2
part4中最左边的元素（即part4最小的元素）为r2
由于part1和part2必须为数组nums1和nums2组成数组的前半部分，那么必须满足：
l1 <= r1（已经满足）
l1 <= r2
l2 <= r1
l2 <= r2（已经满足）
因此，可以根据中间两个条件是否满足来扩大或减小part1

时间复杂度：O(log(min(m,n)))
空间复杂度：O(1)
*/

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
{//找到使两边数字数目相等的位置
	int len1 = nums1.size();
	int len2 = nums2.size();
	if (len1 < 1 && len2 < 1)
		return 0;
	if (len1 > len2)
		return findMedianSortedArrays(nums2, nums1);//保证在size小的数组中进行查找
	int size = len1 + len2;
	int szl1 = 0, szr1 = len1;//初始化
	int sz1 = 0, sz2 = 0;//sz1表示数组1中分配到合并数组左边的数目，sz2为数组2中分配到合并数组左边的数目
	double result = 0;//保存中位数结果
	while (szl1 <= szr1)
	{//使用二分查找确定数目
		sz1 = szl1 + (szr1 - szl1) / 2;
		sz2 = size / 2 - sz1;//两个数组分到左边的数目和应为合并数组的一半
		int l1 = sz1 == 0 ? INT_MIN : nums1[sz1 - 1];//数组1中左边部分的最大值，如果数目为0则为不存在，设一个最小值
		int r1 = sz1 == len1 ? INT_MAX : nums1[sz1];//数组1中右边部分的最小值，如果为0则不存在，设一个最大值
		int l2 = sz2 == 0 ? INT_MIN : nums2[sz2 - 1];//数组2中左边部分的最大值
		int r2 = sz2 == len2 ? INT_MAX : nums2[sz2];//数组2中右边部分的最小值
		if (r1 < l2)//如果l2>r1，说明排序后小的数字个数要多余一半，因此l1应该右移，从而使得l2左移,才能让排序后左边的数目为总数的一半
			szl1 = sz1 + 1;//l1右移，对应地l2左移
		else if (l1 > r2)//如果l1>r2，小于l1和l2的数会超过一半，所以l1应该左移
			szr1 = sz1 - 1;
		else
		{
			if (size % 2)
				result = r1 > r2 ? r2 : r1;//右边较小的数为中位数
			else
			{
				double n1 = l1 > l2 ? l1 : l2;//取左边较大的数
				double n2 = r1 > r2 ? r2 : r1;//右边较小的数
				result = (n1 + n2) / 2;
			}
			break;
		}
	}
	return result;
}

int main()
{
	vector<int> num1{ 1,2,7,10,11,12 };//其他测试用例：一个数组为空、一个数组中只有一个数
	vector<int> num2{ 3,5,8 };
	cout << findMedianSortedArrays(num1, num2) << endl;
	return 0;
}

/*
//归并方式求中位数如下：归并中判断中位数的位置，直到到达中位数的位置，时间复杂度：O(m + n)，空间复杂度：O(1)，时间复杂度比上面的二分差

double find(vector<int>& nums1, vector<int>& nums2) 
{//归并方式
	int len1 = nums1.size();
	int len2 = nums2.size();
	if (len1 < 1 && len2 < 1)
		return 0;
	int size = len1 + len2;
	bool odd = size % 2 == 1 ? true : false;
	int mid = odd ? size / 2 : size / 2 - 1;//中位数的起始位置
	int index1 = 0, index2 = 0,begin = -1;
	double result = 0;
	bool find = false;
	while (index1 < len1 && index2 < len2)
	{
		if (nums1[index1] <= nums2[index2])
		{
			if (++begin == mid)
			{//每判断一次合并数组中的数字就加一个
				if (odd)
					result = nums1[index1];				
				else
					result = (double)(nums1[index1] + nums2[index2])/2;//转成double再除2
				find = true;
				break;				
			}
			index1++;
		}			
		else
		{
			if (++begin == mid)
			{
				if (odd)
					result = nums2[index2];
				else
					result = (double)(nums1[index1] + nums2[index2]) / 2;
				find = true;
				break;
			}
			index2++;
		}
	}
	while (index1 < len1 && !find)
	{
		if (++begin == mid)
		{
			if (odd)
				result = nums1[index1];
			else
			{
				result = nums1[index1];
				result = (result+ nums1[++index1]) / 2;//注意这里也不能写成nums1[index1] + nums1[++index1],因为会先执行++,因此两个index都是++后的index
			}
			find = true;				
			break;
		}
		index1++;
	}
	while (index2 < len2 && !find)
	{
		if (++begin == mid)
		{
			if (odd)
				result = nums2[index2];
			else
			{
				result = nums2[index2];
				result = (result + nums2[++index2]) / 2;
				//result = (nums2[index2] + nums2[++index2]) / 2;//不能这样写，会先执行++,然后两个index2都是自加之后的index
			}
			find = true;				
			break;
		}
		index2++;
	}
	return result;
}

*/
