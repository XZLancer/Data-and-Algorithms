#include <cstdio>
#include <cmath>
#include <complex>
#pragma warning(disable: 4996)
#define N 4

using std::complex;

enum Func
{
	prototype,
	partialX,
	partialY
};

void Partial(double A[][N], double pX[][N], double pY[][N]);
complex<double> FuncValue(double A[][N], Func, complex<double> x, complex<double> y);
void JacobianMat(complex<double> x, complex<double> y,
				 double pX1[][N], double pY1[][N], 
				 double pX2[][N], double pY2[][N]);
void NewtonMethod(double A[][N], double B[][N], complex<double> J[][2], complex<double> x[2], complex<double> y[2],
				  double pX1[][N], double pY1[][N], double pX2[][N], double pY2[][N]);

int main(void)
{
	double A[N][N], B[N][N], pX1[N][N], pY1[N][N], pX2[N][N], pY2[N][N];
	complex<double> x[2], y[2], J[2][2];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%lf", &A[i][j]);
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%lf", &B[i][j]);
		}
	}
	Partial(A, pX1, pY1);
	Partial(B, pX2, pY2);
	NewtonMethod(A, B, J, x, y, pX1, pY1, pX2, pY2);

	printf("%.15lf %.15lf\n", x[1].real(), x[1].imag());
	printf("%.15lf %.15lf", y[1].real(), y[1].imag());

	return 0;
}

void Partial(double A[][N], double pX[][N], double pY[][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			pX[i][j] = i * A[i][j]; 
			pY[i][j] = j * A[i][j];
		}
	}
}

complex<double> FuncValue(double A[][N], Func mark, complex<double> x, complex<double> y)
{
	complex<double> value = 0;
	switch (mark)
	{
	case prototype:
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (A[i][j] == 0)
					continue;
				else
					value += A[i][j] * pow(x, i) * pow(y, j);
			}
		}
		break;
	case partialX:
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (A[i][j] == 0)
					continue;
				else
					value += i * A[i][j] * pow(x, i - 1) * pow(y, j);
			}
		}
		break;
	case partialY:
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (A[i][j] == 0)
					continue;
				else
					value += j * A[i][j] * pow(x, i) * pow(y, j - 1);
			}
		}
		break;
	default:
		break;
	}

	return value;
}

// 直接求出Jacobi矩阵的逆
void JacobianMat(complex<double> J[][2], complex<double> x, complex<double> y,
				 double pX1[][N], double pY1[][N], 
				 double pX2[][N], double pY2[][N])
{
	complex<double> det;
	J[0][0] = FuncValue(pY2, partialY, x, y);
	J[1][1] = FuncValue(pX1, partialX, x, y);
	J[0][1] = -FuncValue(pY1, partialY, x, y);
	J[1][0] = -FuncValue(pX2, partialX, x, y);
	det = J[1][1] * J[0][0] - J[0][1] * J[1][0];
	J[0][0] /= det;
	J[1][1] /= det;
	J[0][1] /= det;
	J[1][0] /= det;
}

void NewtonMethod(double A[][N], double B[][N], complex<double> J[][2], complex<double> x[2], complex<double> y[2],
				  double pX1[][N], double pY1[][N], double pX2[][N], double pY2[][N])
{
	complex<double> f1, f2;
	double residual = 1, temp;
	int iter = 0, step = 0;
	x[0] = y[0] = complex<double> (-1, -1);
	while (residual > 1e-6)
	{
		step++;
		JacobianMat(J, x[0], y[0], pX1, pY1, pX2, pY2);
		x[1] = x[0] - (J[0][0] * FuncValue(A, prototype, x[0], y[0]) + 
			   J[0][1] * FuncValue(B, prototype, x[0], y[0]));
		y[1] = y[0] - (J[1][0] * FuncValue(A, prototype, x[0], y[0]) + 
			   J[1][1] * FuncValue(B, prototype, x[0], y[0]));
		f1 = FuncValue(A, prototype, x[1], y[1]);
		f2 = FuncValue(B, prototype, x[1], y[1]);
		x[0] = x[1];
		y[0] = y[1];
		residual = abs(f1) > abs(f2) ? abs(f1) : abs(f2);
		if (step == 100 && residual > 1)
		{
			iter++;
			temp = iter%2 == 0 ? pow(10, iter) : -pow(10, iter);
			x[0] = complex<double> (temp, temp);
			y[0] = complex<double> (temp, temp);
			step = 0;
		}
	}
}
