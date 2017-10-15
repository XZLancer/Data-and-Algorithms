#include <stdio.h>
#pragma warning (disable: 4996)
struct Point
{
	float x;
	float y;
};

bool ConvexPoint(Point, Point, Point);


int main(void)
{
	int K, N, polygonNum, vertexNum;		// K:����θ���, N:����α���
	float x, y;
	Point * pt;
	int ** ptInfo;
	int * nodeNum;
	bool convexFlag;

	scanf("%d", &K);
	ptInfo = new int*[K];
	nodeNum = new int[K];
	for (polygonNum = 0; polygonNum < K; polygonNum++)
	{
		scanf("%d", &N);
		pt = new Point[N];
		nodeNum[polygonNum] = N;
		ptInfo[polygonNum] = new int[N];
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


bool ConvexPoint(Point pt2, Point pt1, Point pt3)
{
	float A, B, C, k, posJudge;	// ֱ��Ax + By + C = 0��б��Ϊk
	bool convexFlag;
	if(pt1.x == pt3.x)			// ��ֱ�ߴ�ֱ
	{
		if(pt1.y <= pt3.y)		// ֱ�߷������ϣ����Ϊ͹��
		{
			convexFlag = (pt2.x <= pt1.x) ? true : false;
		}
		else					// ֱ�߷������£��Ҳ�Ϊ͹��
		{
			convexFlag = (pt2.x >= pt1.x) ? true : false;
		}

	}
	else if(pt1.y == pt3.y)		// ��ֱ��ˮƽ
	{
		if (pt1.x <= pt3.x)		// ֱ�߷������ң��Ϸ�Ϊ͹��
		{
			convexFlag = (pt2.y >= pt1.y) ? true : false;
		}
		else					// ֱ�߷��������·�Ϊ͹��
		{
			convexFlag = (pt2.y <= pt1.y) ? true : false;
		}
	}
	else
	{
		A = pt1.y - pt3.y;
		B = -(pt1.x - pt3.x);
		C = pt1.x * pt3.y - pt1.y * pt3.x;
		posJudge = (A * pt2.x + B * pt2.y + C) * B;
		k = -(A / B);
		if(posJudge == 0)			// ������ֱ�߷��̺���Ϊ��
		{
			convexFlag = true;
			return convexFlag;
		}
		else if(posJudge > 0)		// ������ֱ�߷��̺���Ϊ��
		{
			if(pt1.y <= pt3.y)		// ֱ�߷�������
			{
				convexFlag = (k > 0) ? true : false;
			}
			else
			{
				convexFlag = (k < 0) ? true : false;
			}
		}
		else						// ������ֱ�߷��̺���Ϊ��
		{
			if(pt1.y <= pt3.y)		// ֱ�߷�������
			{
				convexFlag = (k < 0) ? true : false;
			}
			else
			{
				convexFlag = (k > 0) ? true : false;
			}
		}
	}
	return convexFlag;
}