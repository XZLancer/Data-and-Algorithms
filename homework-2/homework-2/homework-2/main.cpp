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
	//Node * pRowPointer;
	//Node * pColPointer;
};


class MatLinkList		// the validity of functions need check
{
public:
	MatLinkList(){}
	~MatLinkList();
	void InitHead(int row, int col, int elem);
	Node getHead();
	void Sort();
	bool Insert(int pos, int row, int col, int elem);		// insert an element(begin with 0)
	bool Delete(int pos);
private:
	Node head;
};


int main(void)
{
	int iRowNum, iColNum, iElemNum, iTemp;		// the number of rows&columns(the same) and elements
	int iRow, iCol, iElem;						// the information of one node;
	MatLinkList matrix, matrix_T, matrixSum;

	scanf("%d%d%d", &iRowNum, &iColNum, &iTemp);
	iElemNum = iTemp;

	for (int i = 0; i < iTemp; i++)			// record the data
	{
		scanf("%d%d%d", &iRow, &iCol, &iElem);
		if (0 == iElem)			
		{
			continue;			// skip if the element is 0
			iElemNum -= 1;		// reset the number of elements
		}
		matrix.Insert(i, iRow, iCol, iElem);
		matrix_T.Insert(i, iCol, iRow, iElem);		// implementation of transpose
	}

	matrix.InitHead(iRowNum, iColNum, iElemNum);	// record the mat info in head
	matrix_T.InitHead(iColNum, iRowNum, iElemNum);

	matrix.Sort();
	matrix_T.Sort();

	Node * p = &matrix_T.getHead();
	for (int i = 0; i < matrix.getHead().iElem; i++)
	{
		p = p->pNext;
		printf("%d %d %d\n", p->iRow, p->iCol, p->iElem);
	}

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


Node MatLinkList::getHead()
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


void matSum(MatLinkList matA, MatLinkList matB, MatLinkList matC)
{
	Node * pMatA = &matA.getHead(), * pMatB = &matB.getHead();
	for (int i = 0; i < matA.getHead().iElem; i++)
	{
		// pMatA
		pMatA = pMatA->pNext;
		for (int j = 0; j < matB.getHead().iElem; j++)
		{
			pMatB = pMatB->pNext;
			if(pMatA->iRow == pMatB->iRow && pMatA->iCol == pMatB->iCol)
			{
				matC.Insert(i, pMatA->iRow, pMatA->iCol, pMatA->iElem+pMatB->iElem);
			}

		}

	}
}


void matMul(MatLinkList matA, MatLinkList matB)
{

}

