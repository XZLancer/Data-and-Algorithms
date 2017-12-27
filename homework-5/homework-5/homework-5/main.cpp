#include <cstdio>
#pragma warning(disable: 4996)

void DFS(bool ** A, bool * flag, int L, bool & found, int node1, int node2);

int main(void)
{
	int L, temp, node1, node2, num;
	bool ** A, ** R, * flag;
	bool found = 0;

	scanf("%d", &L);

	A = new bool*[L];
	R = new bool*[L];
	flag = new bool[L];
	for (int i = 0; i < L; i++)
	{
		flag[i] = 0;
		A[i] = new bool[L];
		R[i] = new bool[L - i];
	}
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			scanf("%d", &temp);
			A[i][j] = temp;
		}
	}

	scanf("%d%d", &node1, &node2);

	for (int i = 0; i < L - 1; i++)
	{
		for (int j = i + 1; j < L; j++)
		{
			num = 0;
			if (i != j && A[i][j] == 0)
			{
				for (int k = 0; k < L; k++)
				{
					if (A[i][k] == 1 && A[j][k] == 1)
					{
						num++;
						if (num >= 3)
						{
							break;
						}
					}
				}
				if (num == 3)
				{
					R[i][j - i] = 1;
				}
			}
		}
	}
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			if (i > j)
			{
				if (R[j][i - j] != 1)
				{
					printf("%d ", 0);	
				}
				else
				{
					printf("%d ", 1);
				}
			}
			else
			{
				if (R[i][j - i] != 1)
				{
					printf("%d ", 0);	
				}
				else
				{
					printf("%d ", 1);
				}
			}
			
		}
		printf("\n");
	}

	DFS(A, flag, L, found, node2, node1);
	if (!found)
	{
		printf("%d", -1);
	}
	else
	{
		printf("%d ", node2);
	}

	return 0;
}

void DFS(bool ** A, bool * flag, int L, bool & found, int node1, int node2)
{
	flag[node1] = 1;
	if (node1 == node2)
	{
		found = 1;
		return;
	}
	for (int i = 0; i < L; i++)
	{
		found = 0;
		if (A[node1][i] == 1 && flag[i] != 1)
		{
			DFS(A, flag, L, found, i, node2);
			if (found)
			{
				printf("%d ", i);
				break;
			}
		}
	}
}
