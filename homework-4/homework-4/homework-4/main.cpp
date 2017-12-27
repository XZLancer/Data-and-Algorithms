#include <cstdio>
#pragma warning(disable:4996)

struct Node
{
	int x;
	int y;
};

// splitDirection: 0表示对x轴切分;1表示对y轴切分
// splitLine: 切分直线参数(x=splitLine or y=spilitLine)
struct TreeNode
{
	bool splitDirection;
	int splitLine;
	int nodeNum;
	int x_max, y_max;
	int x_min, y_min;
	Node * data;
	TreeNode * left;
	TreeNode * right;
	TreeNode(bool sd = 0, int sl = 0, Node * d = NULL)
	{
		splitDirection = sd;
		splitLine = sl;
		left = NULL;
		right = NULL;
		data = d;
	}
};

struct KD_Tree
{
	TreeNode * root;
	void Build(TreeNode * p, Node nodeSet[], int leftNum, int rightNum);
	void Search(TreeNode * p, Node queryNode, int queryDistance, int & nodeNum);
	void Delete(TreeNode * p);
	KD_Tree()
	{
		root = NULL;
	}
	~KD_Tree()
	{
		Delete(root);
	}
};

void QuickSort(Node * nodeSet, bool sortFlag, int low, int high);
int ABS(int x);

int main()
{
	int totalNum, queryNum, nodeNum;
	int  queryDistance;
	Node  * nodeSetA, nodeSetB;
	KD_Tree kdTree;

	scanf("%d%d", &totalNum, &queryNum);
	nodeSetA = new Node[totalNum];
	for (int i = 0; i < totalNum; i++)
	{
		scanf("%d%d", &nodeSetA[i].x, &nodeSetA[i].y);
	}

	// 初始化根结点
	kdTree.root = new TreeNode(0);		
	// 保存边界信息
	kdTree.root->y_max = kdTree.root->y_min = nodeSetA[0].y;
	kdTree.root->x_max = kdTree.root->x_min = nodeSetA[0].x;
	for (int i = 1; i < totalNum; i++)
	{
		if (kdTree.root->y_max < nodeSetA[i].y)
			kdTree.root->y_max = nodeSetA[i].y;
		if (kdTree.root->y_min > nodeSetA[i].y)
			kdTree.root->y_min = nodeSetA[i].y;
		if (kdTree.root->x_max < nodeSetA[i].x)
			kdTree.root->x_max = nodeSetA[i].x;
		if (kdTree.root->x_min > nodeSetA[i].x)
			kdTree.root->x_min = nodeSetA[i].x;
	}
	// 构造kd-tree
	kdTree.Build(kdTree.root, nodeSetA, 0, totalNum - 1);		

	for (int i = 0; i < queryNum; i++)
	{
		scanf("%d%d%d", &nodeSetB.x, &nodeSetB.y, &queryDistance);
		nodeNum = 0;
		kdTree.Search(kdTree.root, nodeSetB, queryDistance, nodeNum);
		printf("%d\n", nodeNum);
	}

	delete [] nodeSetA;
	nodeSetA = NULL;
	return 0;
}

// 构造kd-tree, 左子树相应坐标 <= splitLine, 右子树相应坐标 > splitLine
void KD_Tree::Build(TreeNode * p, Node nodeSet[], int leftNum, int rightNum)
{
	if (rightNum - leftNum == 0)
	{
		p->data = &nodeSet[leftNum];
		return;
	}
	int midNum = int((rightNum + leftNum) / 2);
	QuickSort(nodeSet, p->splitDirection, leftNum, rightNum);
	p->splitLine = (p->splitDirection == 0) ? nodeSet[midNum].x : nodeSet[midNum].y;
	p->nodeNum = rightNum - leftNum + 1;		// 保存该结点下的点数
	p->left = new TreeNode(!p->splitDirection);
	p->right = new TreeNode(!p->splitDirection);
	if (p->splitDirection == 0)
	{
		p->left->x_min = nodeSet[leftNum].x;
		p->left->x_max = nodeSet[midNum].x;
		p->right->x_min = nodeSet[midNum].x;
		p->right->x_max = nodeSet[rightNum].x;
		p->left->y_max = p->right->y_max = p->y_max;
		p->left->y_min = p->right->y_min = p->y_min;
	}
	else
	{
		p->left->y_min = nodeSet[leftNum].y;
		p->left->y_max = nodeSet[midNum].y;
		p->right->y_min = nodeSet[midNum].y;
		p->right->y_max = nodeSet[rightNum].y;
		p->left->x_max = p->right->x_max = p->x_max;
		p->left->x_min = p->right->x_min = p->x_min;
	}
	Build(p->left, nodeSet, leftNum, midNum);		// 切分点并入左子树
	Build(p->right, nodeSet, midNum + 1, rightNum);
}

/*void KD_Tree::Search(TreeNode * p, Node queryNode, int queryDistance, int & nodeNum)
{
	if (p->data != NULL)
	{
		if (ABS(p->data->x - queryNode.x) <= queryDistance && ABS(p->data->y - queryNode.y) <= queryDistance)
		{
			nodeNum++;
		}
		return;
	}
	if (p->splitDirection == 0)
	{
		if (queryNode.x + queryDistance <= p->splitLine)
		{
			Search(p->left, queryNode, queryDistance, nodeNum);
		}
		else if(p->splitLine < queryNode.x - queryDistance)
		{
			Search(p->right, queryNode, queryDistance, nodeNum);
		}
		else
		{
			Search(p->left, queryNode, queryDistance, nodeNum);
			Search(p->right, queryNode, queryDistance, nodeNum);
		}
	}
	else
	{
		if (queryNode.y + queryDistance <= p->splitLine)
		{
			Search(p->left, queryNode, queryDistance, nodeNum);
		}
		else if(p->splitLine < queryNode.y - queryDistance)
		{
			Search(p->right, queryNode, queryDistance, nodeNum);
		}
		else
		{
			Search(p->left, queryNode, queryDistance, nodeNum);
			Search(p->right, queryNode, queryDistance, nodeNum);
		}
	}
}*/

void KD_Tree::Search(TreeNode * p, Node queryNode, int queryDistance, int & nodeNum)
{
	if (p->data != NULL)
	{
		if (ABS(p->data->x - queryNode.x) <= queryDistance && ABS(p->data->y - queryNode.y) <= queryDistance)
		{
			nodeNum++;
		}
		return;
	}
	if (p->x_max < (queryNode.x + queryDistance) && p->x_min > (queryNode.x - queryDistance) 
		&& p->y_max < (queryNode.y + queryDistance) && p->y_min > (queryNode.y - queryDistance))
	{
		nodeNum += p->nodeNum;
		return;
	}
	else if(p->x_min > (queryNode.x + queryDistance) || p->x_max < (queryNode.x - queryDistance) 
		|| p->y_min > (queryNode.y + queryDistance) || p->y_max < (queryNode.y - queryDistance))
	{
		return;
	}
	else
	{
		Search(p->left, queryNode, queryDistance, nodeNum);
		Search(p->right, queryNode, queryDistance, nodeNum);
	}
}

void KD_Tree::Delete(TreeNode * p)
{
	if (p->left == NULL && p->right == NULL)
	{
		delete p;
		p = NULL;
		return;
	}
	Delete(p->left);
	Delete(p->right);
}

// 快速排序
void QuickSort(Node * nodeSet, bool sortFlag, int low, int high)
{
	if (low >= high)
	{
		return;
	}
	int first = low;
	int last = high;
	Node key = nodeSet[first];		// 以数组第一个作为key
	if (sortFlag == 0)
	{
		while (first < last)
		{
			while (first < last && nodeSet[last].x >= key.x)
			{
				last--;
			}
			nodeSet[first].x = nodeSet[last].x;		// 将比key值小的移到前面
			nodeSet[first].y = nodeSet[last].y;
			while (first < last && nodeSet[first].x <= key.x)
			{
				first++;
			}
			nodeSet[last].x = nodeSet[first].x;		// 将比key值大的移到后面
			nodeSet[last].y = nodeSet[first].y;
		}
		nodeSet[first] = key;		// 将key值归位
		QuickSort(nodeSet, sortFlag, low, first - 1);		// 对以key值划分的两个数组进行递归排序
		QuickSort(nodeSet, sortFlag, first + 1, high);
	}
	else
	{
		while (first < last)
		{
			while (first < last && nodeSet[last].y >= key.y)
			{
				last--;
			}
			nodeSet[first].x = nodeSet[last].x;		// 将比key值小的移到前面
			nodeSet[first].y = nodeSet[last].y;
			while (first < last && nodeSet[first].y <= key.y)
			{
				first++;
			}
			nodeSet[last].x = nodeSet[first].x;		// 将比key值大的移到后面
			nodeSet[last].y = nodeSet[first].y;
		}
		nodeSet[first] = key;		// 将key值归位
		QuickSort(nodeSet, sortFlag, low, first - 1);		// 对以key值划分的两个数组进行递归排序
		QuickSort(nodeSet, sortFlag, first + 1, high);
	}
}

int ABS(int x)
{
	return (x >= 0) ? x : -x;
}