#include <cstdio>
#define m 3
#pragma warning(disable: 4996)

int MaxSum(int * a, int * max, int * local);
int MinSum(int * a, int * max, int * local);
int Max(int a, int b);
int n;

int main()
{
	int * max, * local, * data, sum = 0;
	int max_sum, temp_sum1, temp_sum2;
	scanf("%d", &n);
	data = new int[n];
	max = new int[m];
	local = new int[m];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &data[i]);
		sum += data[i];
	}
	temp_sum1 = MaxSum(data, max, local);
	temp_sum2 = sum - MinSum(data, max, local);
	max_sum = Max(temp_sum1, temp_sum2);
	printf("%d", max_sum);
	return 0;
}

int Max(int a, int b)
{
	return a > b ? a : b;
}

// 第i轮循环的local[n]表示前i位中,包含a[i]的最大(n+1)段子数组之和
// 第i轮循环的max[n]表示前i位中的最大(n+1)段子数组之和
int MaxSum(int * a, int * max, int * local)
{
	for (int i = 0; i < m; i++)
	{
		local[i] = 0;
		max[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = m - 1; j >= 0; j--)
		{
			if (j > i)
			{
				continue;
			}
			if (j == i)
			{
				local[j] = i == 0 ? a[i] : local[j - 1] + a[i];
				max[j] = local[j];
				continue;
			}
			else if (j == 0)
			{
				local[j] = Max(local[j] + a[i], a[i]);
				//max[j] = local[j];
			}
			else
			{
				local[j] = Max(local[j] + a[i], max[j - 1] + a[i]);
			}
			max[j] = Max(max[j], local[j]);
		}
	}
	return max[m - 1];
}

int MinSum(int * a, int * max, int * local)
{
	for (int i = 0; i < m; i++)
	{
		local[i] = 0;
		max[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = m - 1; j >= 0; j--)
		{
			if (j > i)
			{
				continue;
			}
			if (j == i)
			{
				local[j] = i == 0 ? -a[i] : local[j - 1] - a[i];
				max[j] = local[j];
				continue;
			}
			else if (j == 0)
			{
				local[j] = Max(local[j] - a[i], -a[i]);
				//max[j] = local[j];
			}
			else
			{
				local[j] = Max(local[j] - a[i], max[j - 1] - a[i]);
			}
			max[j] = Max(max[j], local[j]);
		}
	}
	return -max[m - 1];
}