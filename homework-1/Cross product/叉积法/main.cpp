#include <stdio.h>
#pragma warning (disable: 4996)
struct Point
{
	float x;
	float y;
};


bool ConvexPoint(Point &, Point &, Point &);


int main(void)
{
	int K, N, polygonNum, vertexNum;		// K:����θ���, N:����αߣ��㣩��
	float x, y;
	Point * pt;
	bool ** ptInfo;							// �������ÿ�������Ϣ
	int * nodeNum;							// �洢����ζ�������
	bool convexFlag;

	scanf("%d", &K);
	ptInfo = new bool*[K];
	nodeNum = new int[K];
	for (polygonNum = 0; polygonNum < K; polygonNum++)
	{
		scanf("%d", &N);
		pt = new Point[N];
		nodeNum[polygonNum] = N;
		ptInfo[polygonNum] = new bool[N];
		for (int i = 0; i < N; i++)
		{
			scanf("%f%f", &x, &y);
			pt[i].x = x;
			pt[i].y = y;
		}
		for (vertexNum = 0; vertexNum < N; vertexNum++)
		{
			if (vertexNum == 0)			// ��Ϊ��һ������
			{
				ptInfo[polygonNum][0] = ConvexPoint(pt[0], pt[N-1], pt[1]);
			}
			else if (vertexNum == N-1)	// ��Ϊ���һ������
			{
				ptInfo[polygonNum][N-1] = ConvexPoint(pt[N-1], pt[N-2], pt[0]);
			}
			else
			{
				ptInfo[polygonNum][vertexNum] = ConvexPoint(pt[vertexNum], pt[vertexNum-1], pt[vertexNum+1]);
			}	
		}
		delete [] pt;
		pt = NULL;
	}
	for (polygonNum = 0; polygonNum < K; polygonNum++)
	{
		convexFlag = true;		// �ٶ�Ϊ͹�����
		for(vertexNum = 0; vertexNum < nodeNum[polygonNum]; vertexNum++)
		{
			if (ptInfo[polygonNum][vertexNum] == 0)
			{
				printf("%d ", vertexNum);
				convexFlag = false;
			}
		}
		if (convexFlag)
		{
			printf("y");
		}
		printf("\n");
	}
	delete [] ptInfo;
	delete [] nodeNum;
	return 0;
}


bool ConvexPoint(Point & pt2, Point & pt1, Point & pt3)
{
	bool convexFlag;
	float crossProduct;
	Point vector1, vector2;
	vector1.x = pt2.x - pt1.x;		// ����pt1pt2������pt2pt3��������������ά��Ϊ0��
	vector1.y = pt2.y - pt1.y;		// ���ڵ㰴˳ʱ��������Ϊ���㣬�������������ϣ�����ֵ>0
	vector2.x = pt3.x - pt2.x;
	vector2.y = pt3.y - pt2.y;
	crossProduct = vector1.x * vector2.y - vector1.y * vector2.x;
	if (crossProduct > 0)
	{
		convexFlag = false;
	}
	else
	{
		convexFlag = true;
	}
	return convexFlag;
}