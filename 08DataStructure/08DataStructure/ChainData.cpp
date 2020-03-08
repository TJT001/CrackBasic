#include <iostream>

/*******************
*				   *
*���Ա����ʽ�洢ʵ�� *
*				   *
********************/


// ����Ҫ�߼������ڵ�����Ԫ��������Ҳ����
// ͨ����������������Ԫ��֮����߼���ϵ

// ����һ�����Ա�
//typedef struct LNode* ptrToLNode;
typedef int ElementType;

// ͨ������������洢�ռ�˳�������Ա�ĸ�Ԫ��
struct LNode {
	ElementType Data;   // �ڵ���������
	LNode* Next;        // ָ����һ���ڵ��λ��
};

typedef LNode* Position;
typedef LNode* List;

#define ERROR NULL

// ���
int Length(List Ptr)
{
	int j = 0;
	while (Ptr)
	{
		Ptr = Ptr->Next;
		j++;
	}

	return j;
}

// ����
Position Find(List L, ElementType X)
{
	Position p = L;    // Pָ��L�ĵ�һ���ڵ�
	while (p && p->Data != X)
		p = p->Next;
	if (p)
		return p;
	else
		return ERROR;
}

// ����
bool Insert(List L, ElementType X, Position p)
{
	Position tem, pre;
	// ����p��ǰһ���ڵ�
	for (pre = L; pre && pre->Next != p; pre = pre->Next);
	
	// λ�ü��
	if (pre = NULL)
	{
		printf("�����λ������\n");
		return false;
	}
	else
	{
		tem = (Position)malloc(sizeof(struct LNode));
		tem->Data = X;
		tem->Next = p;
		pre->Next = tem;
		return true;
	}
}

// ��ͷ�ڵ��ɾ��
bool Delete(List L, Position p)
{
	Position pre;
	for (pre = NULL; pre && pre->Next != p; pre = pre->Next);
	
	if (pre == NULL || p == NULL)   // p��ָ�Ľڵ㲻��L��
	{
		printf("ɾ���ĵ�λ������\n");
		return false;
	}
	else
	{
		// �ҵ���p��ǰһ���ڵ�
		// ��p�Ľڵ�ɾ��
		pre->Next = p->Next;
		free(p);
		return true;
	}
}