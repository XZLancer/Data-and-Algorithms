#include <cstdio>
#pragma warning(disable: 4996)

void QuickSort(int * A, int low, int high);

int main(void)
{
	int len, high, low, high_temp, low_temp;
	long long num1 = 0, num2 = 0;

	scanf("%d%d%d",	&len, &low_temp, &high_temp);
	int * A = new int[len];
	for (int i = 0; i < len; i++)
	{
		scanf("%d", &A[i]);
	}

	QuickSort(A, 0, len - 1);

	for (int i = 0; i < len - 2; i++)
	{
		high = high_temp - A[i];
		low = low_temp - A[i];
		for (int j = i + 1, k = len - 1; k > j;)
		{
			if (A[j] + A[k] > high)		// 查找两数之和 > high的数量
			{
				num1 += (k-j);
				k--;
			}
			else
			{
				j++;
			}
		}
		for (int j = i + 1, k = len - 1; k > j;)
		{
			if (A[j] + A[k] >= low)		// 查找两数之和 >= low的数量
			{
				num2 += (k-j);
				k--;
			}
			else
			{
				j++;
			}
		}
	}
	num1 = num2 - num1;
	printf("%ld", num1);
	return 0;
}

void QuickSort(int * A, int low, int high)
{
	if (low >= high)
	{
		return;
	}
	int first = low;
	int last = high;
	int key = A[first];		// 以数组第一个作为key
	
	while (first < last)
	{
		while (first < last && A[last] >= key)
		{
			last--;
		}
		A[first] = A[last];		// 将比key值小的移到前面
		A[first] = A[last];
		while (first < last && A[first] <= key)
		{
			first++;
		}
		A[last] = A[first];		// 将比key值大的移到后面
		A[last] = A[first];
	}
	A[first] = key;		// 将key值归位
	QuickSort(A, low, first - 1);		// 对以key值划分的两个数组进行递归排序
	QuickSort(A, first + 1, high);
}