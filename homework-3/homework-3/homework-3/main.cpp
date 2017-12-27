#include <cstdio>
#pragma warning (disable: 4996)

struct Haar_wavelet
{
	int L;
	int N;
	float * func;
	float * coefficient;
	float * WaveletTransform(int m);
	~Haar_wavelet()
	{
		delete [] coefficient;
		delete [] func;
		coefficient = NULL;
		func = NULL;
	}
};
int power(int x, int y);


int main(void)
{
	Haar_wavelet wavelet;
	float * coefficient;
	scanf("%d", &wavelet.L);
	wavelet.N = int(power(2, wavelet.L));
	wavelet.func = new float[wavelet.N];
	wavelet.coefficient = new float[wavelet.N];
	for (int i = 0; i < wavelet.N; i++)
	{
		scanf("%f", &wavelet.func[i]);
	}
	coefficient = wavelet.WaveletTransform(wavelet.L);
	for (int i = 0; i < wavelet.N; i++)
	{
		printf("%.4f ", coefficient[i]);
	}
	return 0;
}

float * Haar_wavelet::WaveletTransform(int m)
{
	if (m == 1)
	{
		for (int i = 0; i < N; i++)
		{
			if (i < N/2)
			{
				coefficient[i] = (func[2 * i] + func[2 * i + 1]) / 2;
			}
			else
			{
				coefficient[i] = -(func[2 * i - N] - func[2 * i - N + 1]) / 2;
			}
		}
		return coefficient;
	}
	else
	{
		coefficient = Haar_wavelet::WaveletTransform(m-1);
		for (int j = 0; j < N; j++)
		{
			func[j] = coefficient[j];
		}
		for (int i = 0; i < N; i++)
		{	
			if (i < int(N/power(2, m)))
			{
				coefficient[i] = (func[2*i] +
								 func[2*i+1]) / 2;
			}
			else if (i >= int(N/power(2, m)) && i < int(N/power(2, m-1)))
			{
				coefficient[i] = -(func[2*(i-int(N/power(2, m)))] -
								 func[2*(i-int(N/power(2, m))) + 1]) / 2;
			}
			else
			{
				coefficient[i] = func[i];
			}
		}
		return coefficient;
	}
	
}

int power(int x, int y)
{
	int temp = x;
	if (y == 0)
	{
		return 1;
	}
	for (int i = 0; i < y-1; i++)
	{
		temp *= x;
	}
	return temp;
}