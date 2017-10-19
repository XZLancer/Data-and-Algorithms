#include <cstdio>
#pragma warning (disable: 4996)

struct Node
{
	Node()
	{
		pNext = NULL;
	}
	void init(int row, int col, int elem);

	int iRow, iCol, iElem;
	Node * pNext;
};


class MatLinkList		// the validity of functions need check
{
public:
	MatLinkList(){}
	~MatLinkList();
	void InitHead(int row, int col, int elem);
	Node & GetHead();
	void Sort();
	void PrintMat();
	void GetRowInfo(int * pRowInfo, int & iRealRowNum);
	bool Insert(int pos, int row, int col, int elem);		// insert an element(begin with 0)
	bool Delete(int pos);
protected:
	Node head;
};

// Declaration of functions
void matSum(MatLinkList & matA, MatLinkList & matB);
void matMul(MatLinkList & matA, int * pRowInfo, int & iRealRowNum);

int main(void)
{
	int iRowNum, iColNum, iElemNum;		// the number of rows&columns(the same) and elements
	int iRow, iCol, iElem;						// the information of one node;
	int * pRowInfo, iRealRowNum;
	MatLinkList matrix, matrix_T;
	

	scanf("%d%d%d", &iRowNum, &iColNum, &iElemNum);

	pRowInfo = new int [iRowNum];
	
	// record the data
	for (int i = 0; i < iElemNum; i++)			
	{
		scanf("%d%d%d", &iRow, &iCol, &iElem);
		if (0 == iElem)			
		{
			iElemNum--;		// reset i and the number of elements 
			i--;
			continue;			// skip if the element is 0	
		}
		matrix.Insert(i, iRow, iCol, iElem);
		matrix_T.Insert(i, iCol, iRow, iElem);		// record of transpose
	}

	// record the mat info in head
	matrix.InitHead(iRowNum, iColNum, iElemNum);	
	matrix_T.InitHead(iColNum, iRowNum, iElemNum);

	matrix.Sort();
	matrix_T.Sort();

	// print the transpose of the matrix
	matrix_T.PrintMat();

	// get the number of elements in every row
	matrix.GetRowInfo(pRowInfo, iRealRowNum);

	matSum(matrix, matrix_T);

	matMul(matrix, pRowInfo, iRealRowNum);

	delete [] pRowInfo;
	pRowInfo = NULL;
	return 0;
}


MatLinkList::~MatLinkList()
{
	for (int i = 0; i < head.iElem; i++)
	{
		Delete(0);
	}
}


void Node::init(int row, int col, int elem)
{
	iRow = row;
	iCol = col;
	iElem = elem;
}


void MatLinkList::InitHead(int row, int col, int elem)
{
	head.iRow = row;
	head.iCol = col;
	head.iElem = elem;
}


Node & MatLinkList::GetHead()
{
	return head;
}


void MatLinkList::Sort()
{
	Node * p, * pPrior, * pTemp;
	for (int i = 0; i < (head.iElem - 1); i++)
	{
		p = &head;			// initialize p and pPrior
		pPrior = &head;
		for (int j = 0; j < (head.iElem - 1 - i); j++)		
		{
			pPrior = p;
			p = p->pNext;
			if (p->iRow > p->pNext->iRow)		// sort by row number
			{
				pTemp = p->pNext->pNext;
				pPrior->pNext = p->pNext;
				p->pNext->pNext = p;
				p->pNext = pTemp;

				p = pPrior->pNext;				// set p to the original place
			}
			else if(p->iRow == p->pNext->iRow)
			{
				if(p->iCol > p->pNext->iCol)	// sort by column number
				{
					{
						pTemp = p->pNext->pNext;
						pPrior->pNext = p->pNext;
						p->pNext->pNext = p;
						p->pNext = pTemp;

						p = pPrior->pNext;		// set p to the original place
					}
				}
			}
		}
	}
}


void MatLinkList::PrintMat()
{
	Node * p = &head;
	for (int i = 0; i < head.iElem; i++)
	{
		p = p->pNext;
		printf("%d %d %d\n", p->iRow, p->iCol, p->iElem);
	}
}


void MatLinkList::GetRowInfo(int * pRowInfo, int & iRealRowNum)
{
	Node * p = &head;
	int temp = 1, j = 0;

	for (int i = 0; i < (head.iElem - 1); i++)
	{
		p = p->pNext;
		if (p->iRow == p->pNext->iRow)
		{
			temp++;
			if (i != head.iElem - 2)
			{
				continue;
			}	
		}
		else if (i == head.iElem - 2)
		{
			pRowInfo[j + 1] = 1;
			iRealRowNum = j + 2;
		}
		pRowInfo[j] = temp;
		j++;
		temp = 1;
	}
	if (head.iElem == 1 && j == 0)		// if there is only one element(nonzero)
	{
		pRowInfo[0] = 1;
		iRealRowNum = 1;
	}
	else
	{
		iRealRowNum = (iRealRowNum == j + 1) ? (j + 1) : j;
	}
}


bool MatLinkList::Insert(int pos, int row, int col, int elem)
{
	Node * insNode, * p = &head;
	int j = 0;

	while (j < pos)		// go to the prior position of where to insert
	{
		p = p->pNext;
		j++;
	}

	insNode = new Node;
	insNode->init(row, col, elem);
	insNode->pNext = p->pNext;
	p->pNext = insNode;

	return true;
}


bool MatLinkList::Delete(int pos)
{
	Node * delNode, * p = &head;
	int j = 0;

	while (j < pos)
	{
		p = p->pNext;
		j++;
	}

	delNode = p->pNext;
	p->pNext = delNode->pNext;
	delete delNode;
	delNode = NULL;
	return true;
}


void matSum(MatLinkList & matA, MatLinkList & matB)
{
	Node * pMatB = &matB.GetHead(), * pMatA = matA.GetHead().pNext;

	while (pMatA != NULL && pMatB != NULL)		// if pMatA and pMatB do not point to the list tail
	{
		pMatB = pMatB->pNext;
		while (pMatA != NULL && pMatB != NULL)
		{
			if (pMatB->iRow < pMatA->iRow)
			{
				printf("%d %d %d\n", pMatB->iRow, pMatB->iCol, pMatB->iElem);
				break;		// if print the element in matB, pMatB points to the next
			}
			else if (pMatB->iRow > pMatA->iRow)
			{
				printf("%d %d %d\n", pMatA->iRow, pMatA->iCol, pMatA->iElem);
				pMatA = pMatA->pNext;		// if print the element in matA, pMatA points to the next
			}
			else
			{
				if (pMatB->iCol < pMatA->iCol)
				{
					printf("%d %d %d\n", pMatB->iRow, pMatB->iCol, pMatB->iElem);
					break;
				}
				else if (pMatB->iCol > pMatA->iCol)
				{
					printf("%d %d %d\n", pMatA->iRow, pMatA->iCol, pMatA->iElem);
					pMatA = pMatA->pNext;
				}
				else
				{
					if (pMatB->iElem + pMatA->iElem != 0)
					{
						printf("%d %d %d\n", pMatA->iRow, pMatA->iCol, pMatB->iElem + pMatA->iElem);
					}
					pMatA = pMatA->pNext;		// if make an addition, pMatA and pMatB
					pMatB = pMatB->pNext;		// both point to the next
				}
			}
		}
	}

	// ether pMatA of pMatB points to the list tail
	// print the rest of the elements
	while (pMatA != NULL)
	{
		printf("%d %d %d\n", pMatA->iRow, pMatA->iCol, pMatA->iElem);
		pMatA = pMatA->pNext;
	}
	while (pMatB != NULL)
	{
		printf("%d %d %d\n", pMatB->iRow, pMatB->iCol, pMatB->iElem);
		pMatB = pMatB->pNext;
	}
}


void matMul(MatLinkList & matA, int * pRowInfo, int & iRealRowNum)
{
	Node * pRow = &matA.GetHead(), * pCol;
	Node * pRowHead, * pColHead;

	int sum, k, l, m;
	for (int row = 0; row < iRealRowNum; row++)
	{
		l = 0;
		pCol = &matA.GetHead();
		while (row != 0 && l < pRowInfo[row - 1])
		{
			pRow = pRow->pNext;
			l++;
		}
		pRowHead = pRow;		// record the head in every row;
		for (int col = 0; col < iRealRowNum; col++)
		{
			sum = 0;
			m = 0;

			// move pCol to No.col column's head
			while (col != 0 && m < pRowInfo[col - 1])
			{
				pCol = pCol->pNext;
				m++;
			}
			pColHead = pCol;		// record the head in every colomn
			for (k = 0; k < pRowInfo[row]; k++)
			{
				pRow = pRow->pNext;
				for (int j = 0; j < pRowInfo[col]; j++)
				{
					pCol = pCol->pNext;
					if (pCol->iCol == pRow->iCol)
					{
						sum += pRow->iElem * pCol->iElem;
						break;
					}
				}
				pCol = pColHead;	// reset pCol
			}
			if (sum != 0)
			{
				printf("%d %d %d\n", pRowHead->pNext->iRow, pColHead->pNext->iRow, sum);
			}
			pRow = pRowHead;		// reset pRow
		}
	}
}