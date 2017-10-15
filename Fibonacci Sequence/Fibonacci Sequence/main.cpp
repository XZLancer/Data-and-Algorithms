#include <stdio.h>
#pragma warning (disable: 4996)

int Fibonacci(int);
int main(void)
{
	int n, num;
	scanf("%d", &n);
	int * m = new int[n];
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &num);
		*(m + i) = Fibonacci(num) % 9973;
	}
	for(int i = 0; i < n; i++)
	{
		printf("%d\n", m[i]);
	}
	delete [] m;
	return 0;
}


int Fibonacci(int n)
{
	if(n == 0)
	{
		return 0;
	}
	else if(n == 1)
	{
		return 1;
	}
	else
	{
		return (Fibonacci(n-1) + Fibonacci(n-2));
	}
}