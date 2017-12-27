#include <cstdio>
#include <math.h>
#pragma warning(disable: 4996)

struct MatElem
{
	int row, col;
	double value;
	MatElem * pRight;
};

struct CrossList
{
	MatElem ** pRowHead;
	int scale, eleNum;
	void InsertElem(MatElem * node);
	void CreatList();
	double Search(int i, int j);
};

void ExchangeRow(double ** A, int scale, int row1, int row2);
void GaussElimination(double ** A, double * b, double * x, int scale);
bool Gauss_SeidelIteration(CrossList A, double * b, double * x, int scale);

int main(void)
{
	bool flag = 0, changeBit;
	int scale ,eleNum;
	double * b, * x;
	scanf("%d%d", &scale, &eleNum);
	b = new double[scale];
	x = new double[scale];

	//flag = scale > 30000 ? 1 : 0;

	switch (flag)
	{
	case 0:
		CrossList matA;
		MatElem * node;

		matA.scale = scale;
		matA.eleNum = eleNum;
		matA.CreatList();

		for (int i = 0; i < matA.eleNum; i++)
		{
			node = new MatElem;
			scanf("%d%d%lf", &node->row, &node->col, &node->value);
			matA.InsertElem(node);
		}
		for (int i = 0; i < scale; i++)
		{
			scanf("%lf", &b[i]);
		}

		changeBit = Gauss_SeidelIteration(matA, b, x, scale);
		
	case 1:
		if (!changeBit)
		{
			break;
		}
		double ** A;
		MatElem * p;
		A = new double*[scale];
		
		for (int i = 0; i < scale; i++)
		{
			A[i] = new double[scale]();
		}

		for(int i = 0; i < scale; i++)
		{
			p = matA.pRowHead[i];
			while (p)
			{
				A[i][p->col] = p->value;
				p = p->pRight;
			}
		}

		GaussElimination(A, b, x, scale);
		break;
	}

	for (int i = 0; i < scale; i++)
	{
		printf("%lf\n", x[i]);
	}

	return 0;
}

void CrossList::CreatList()
{
	pRowHead = new MatElem*[scale];
	for (int i = 0; i < scale; i++)
	{
		pRowHead[i] = NULL;
	}
}

void CrossList::InsertElem(MatElem * node)
{
	// 行插入
	if (pRowHead[node->row] == NULL || pRowHead[node->row]->col > node->col)
	{
		node->pRight = pRowHead[node->row];
		pRowHead[node->row] = node;
	}
	else
	{
		MatElem * p = pRowHead[node->row];
		while(p->pRight != NULL && p->pRight->col < node->col)
		{
			p = p->pRight;
		}
		node->pRight = p->pRight;
		p->pRight = node;
	}
}

double CrossList::Search(int i, int j)
{
	MatElem * p = pRowHead[i];
	if (p == NULL)
	{
		return 0;
	}
	while (p->col < j && p->pRight)
	{
		p = p->pRight;
	}
	return (p->col == j)? p->value : 0;
}

void ExchangeRow(double ** A, int scale, int row1, int row2)
{
	double temp;
	for (int i = 0; i < scale; i++)
	{
		if (A[row1][i] == A[row2][i])
		{
			continue;
		}
		temp = A[row1][i];
		A[row1][i] = A[row2][i];
		A[row2][i] = temp;
	}
}

void GaussElimination(double ** A, double * b, double * x, int scale)
{
	int pos;
	double s, temp;
	for (int i = 0; i < scale - 1; i++)
	{
		temp = abs(A[i][i]);
		pos = i;
		for (int m = i + 1; m < scale; m++)
		{
			if (temp < abs(A[m][i]))
			{
				temp = abs(A[m][i]);
				pos = m;
			}
		}
		if (i != pos)
		{
			temp = b[pos];
			b[pos] = b[i];
			b[i] = temp;
			ExchangeRow(A, scale, i, pos);
		}
		for (int k = i + 1; k < scale; k++)
		{
			if (A[k][i] == 0)	// 若待消去系数已为0
			{
				continue;
			}
			s = -A[k][i] / A[i][i];
			for (int j = i + 1; j < scale; j++)
			{
				A[k][j] += A[i][j] * s; 
			}
			A[k][i] = 0;
			b[k] += b[i] * s;
		}
	}

	for (int i = scale - 1; i >= 0; i--)
	{
		s = b[i];
		for (int k = i + 1; k < scale; k++)
		{
			s -= A[i][k] * x[k];  
		}
		x[i] = s / A[i][i];
	}
}

bool Gauss_SeidelIteration(CrossList A, double * b, double * x, int scale)
{
	double * prior = new double[scale]();
	double L, U, residual, temp;
	MatElem * p;
	bool stopBit = 0, changeBit = 0;
	int step = 0;

	while (!stopBit)
	{
		step++;
		residual = 0;
		for (int i = 0; i < scale; i++)
		{
			L = 0;
			U = 0;
			temp = 0;
			p = A.pRowHead[i];
			// 利用稀疏性，查找非零A[i][j]再乘相应的x[j]
			while (p)
			{
				temp += p->value * prior[p->col];
				if (p->col < i)
				{
					L += p->value * x[p->col];
				}
				if (p->col > i)
				{
					U += p->value * x[p->col];
				}
				p = p->pRight;
			}
			x[i] = (b[i] - L - U) / A.Search(i, i);
			residual += (temp - b[i]) * (temp - b[i]);
		}
		if (residual < 0.1)
		{
			stopBit = 1;
			break;
		}
		if (step == 100 && residual > 1)	// 若发现迭代收敛较差/不收敛
		{
			stopBit = changeBit = 1;
			break;
		}
		for (int i = 0; i < scale; i++)
		{
			prior[i] = x[i];
		}
	}
	return changeBit;
}