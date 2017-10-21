struct SNode{
	int data;
	SNode *next;
	SNode():data(0),next(NULL){}
};

void mergeList(LinkList &HA,LinkList &HB,LinkList &HC){
SNode * pHA = &HA.head, * pHB = &HB.head, * pHC = &HC.head;
while (pHA != NULL && pHB != NULL)
{
	pHA = pHA->next;
	while (pHA != NULL && pHB != NULL)
	{
		if (pHB->data >= pHA->data)
		{
			pHC->next = pHA;
			pHC = pHC->next;
			break;		// pHA = pHA->next
		}
		else
		{
			pHC->next = pHB;
			pHC = pHC->next;
			pHB = pHB->next;
		}
	}
}
if (pHA != NULL)
{
	pHC->next = pHA;
}
if (pHB != NULL)
{
	pHC->next = pHB;
}
HA.head.next = NULL;
HB.head.next = NULL;
}

void mergeList(LinkList &HA,LinkList &HB,LinkList &HC)
{
SNode * pHA = HA.head, * pHB = HB.head, * pHC = HC.head;
if (pHA == NULL || pHB == NULL)			// 若两者中存在空表
{
	if (pHA == NULL && pHB != NULL)
	{
		pHB = pHB->next;
		pHC = pHB;
		HB.head = NULL;
		return;
	}
	else if (pHA != NULL && pHB == NULL)
	{
		pHA = pHA->next;
		pHC = pHA;
		HA.head = NULL;
		return;
	}
	else
	{
		return;
	}
}

// 若两者均非空表
pHB = pHB->next;
while (pHA != NULL && pHB != NULL)	// 当指针不指向表尾时
{
	pHA = pHA->next;
	while (pHA != NULL && pHB != NULL)
	{
		if (pHB->data >= pHA->data)	// 若当前结点HB.data>=HA.data
		{
			if (pHC == HC.head)		// 若pHC为HC头指针
			{
				pHC = pHA;
			}
			else
			{
				pHC->next = pHA;
				pHC = pHC->next;
			}						
			break;					// 之后pHA向后移，并判断是否为空
		}
		else						// 若当前结点HB.data<HA.data
		{
			if (pHC == HC.head)
			{
				pHC = pHB;
			}
			else
			{
				pHC->next = pHB;
				pHC = pHC->next;
			}
			pHB = pHB->next;		// 之后pHB向后移，并判断是否为空
		}
	}
}
// 上述操作后pHA和pHB中必有一者为空，则将其中不为空者（若存在）
// 指向的后续data均按序合并到HC中即可。
if (pHA != NULL)
{
	pHC->next = pHA;
}
if (pHB != NULL)
{
	pHC->next = pHB;
}
HA.head = NULL;
HB.head = NULL;
}

void inverseLinkList(LinkList &HL){
//LinkList和SNode定义同上一题，链表不带表头
	SNode * pPrior = NULL, *pNext;
	while (HL.head != NULL)
	{
		pNext = HL.head->next;		// 标记下一元素
		HL.head->next = pPrior;		// 将当前结点的next指针指向前驱元素
		pPrior = HL.head;			// 将当前结点标记为前驱元素
		HL.head = pNext;			// 当前结点后移
	}
	// 循环结束后HL.head为空,pPrior所指向的前驱元素为第一个元素(即原链表最后一个元素)
	HL.head = pPrior;
}
	
	