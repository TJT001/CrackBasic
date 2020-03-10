#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1

//typedef int Position;
//typedef int ElementType;
//
//
//struct QNode {
//	ElementType *Data;   // �洢Ԫ�ص�����
//	Position Front, Rear;  // ջͷ��ջβָ��
//	int MaxSize;   // ���е��������
//};
//
//typedef struct QNode* Queue;
//
//// ����һ������
//Queue CreateQueue(int MaxSize)
//{
//	Queue Q = (Queue)malloc(sizeof(struct QNode*));
//	Q->Data = (ElementType*)malloc(MaxSize * sizeof(ElementType));
//	Q->Front = Q->Rear = 0;
//	Q->MaxSize = MaxSize;
//	return Q;
//}
//
//// �Ƿ���
//bool Isfull(Queue Q)
//{
//	return ((Q->Rear + 1) % Q->MaxSize == Q->Front);
//}
//
//// ���������������
//bool AddQ(Queue Q,ElementType x)
//{
//	if (Isfull(Q))
//	{
//		printf("��������\n");
//		return false;
//	}
//	else
//	{
//		Q->Rear = ((Q->Rear + 1) % Q->MaxSize);
//		Q->Data[Q->Rear] = x;
//		return true;
//	}
//}
//
//// �����Ƿ�Ϊ��
//bool IsEmpty(Queue Q)
//{
//	return (Q->Front == Q->Rear);
//}
//
//// ɾ�������е�Ԫ��
//ElementType DeleteQ(Queue Q)
//{
//	if (IsEmpty(Q))
//	{
//		printf("�����ѿ�\n");
//		return ERROR;
//	}
//	else
//	{
//		Q->Front = (Q->Front + 1) % Q->MaxSize;
//		return  Q->Data[Q->Front];
//	}
//}


/******************************
*							  *
*	���е���ʽʵ��			      *
*							  *
*******************************/

typedef struct Node* ptrToNode;
typedef int ElementType;

struct Node {
	ElementType Data;   // �洢Ԫ�ص�����
	ptrToNode Next;  // ջͷ��ջβָ��
};

typedef ptrToNode Position;

struct QNode {
	Position Front, Rear;  // ���е�ͷβָ��
	int MaxSize;           // �������
};

typedef struct QNode* Queue;

// �����Ƿ�Ϊ��
bool IsEmpty(Queue Q)
{
	return (Q->Front == NULL);
}


// ɾ�������е�Ԫ��
ElementType DeleteQ(Queue Q)
{
	Position frontCell;
	ElementType frontElem;

	if (IsEmpty(Q))
	{
		printf("�����ѿ�\n");
		return ERROR;
	}
	else
	{
		frontCell = Q->Front;
		if (Q->Front == Q->Rear)   // ��������ֻ��һ��Ԫ��
			Q->Front = Q->Rear = NULL;
		else
			Q->Front = Q->Front->Next;
		frontElem = frontCell->Data;
		free(frontCell);
		return frontElem;
	}
}


//Ӧ��ʵ����ʹ��������ʵ�ֶ���ʽ�ļӷ�
struct PolyNode {
	int coef;        // ϵ��
	int expon;       // ָ��
	struct PolyNode* link;
};

typedef struct PolyNode* Polynomial;
Polynomial P1, P2;

// ����ʽ���
Polynomial PolyAdd(Polynomial P1, Polynomial P2)
{
	Polynomial front, rear, temp;
	int sum;
	// �Ȳ���һ����ʱ�Ŀսڵ���Ϊ�ṹ����ʽ����ͷ
	rear = (Polynomial)malloc(sizeof(struct PolyNode));
	front = rear;      // ��front��¼�������ʽ����ͷ�ڵ�
	while (P1 && P2)
	{
		switch (Compare(P1->expon,P2->expon))
		{
		case 1:
			Attach(P1->coef, P1->expon, &rear);
			P1 = P1->link;
			break;
		case 0:
			sum = P1->coef + P2->coef;
			if (sum)
				Attach(sum, P1->expon, &rear);
			P1 = P1->link;
			P2 = P2->link;
			break;
		case -1:
			Attach(P2->coef, P2->expon, &rear);
			P2 = P2->link;
			break;
		default:
			break;
		}
	}
	// ��δ���������һ������ʽ�����нڵ�һ�θ��Ƶ��������ʽ��ȥ
	for (; P1; P1 = P1->link)
		Attach(P1->coef, P1->expon, &rear);
	for (; P2; P2 = P2->link)
		Attach(P2->coef, P2->expon, &rear);
	rear->link = NULL;
	front = front->link;     // ��frontָ��������ʽ �ĵ�һ��������
	free(temp);              // �ͷſսڵ�
	return front;
}

signed int Compare(Polynomial P1, Polynomial P2)
{
	if (P1->expon > P2->expon)
	{
		return 1;
	}
	else if (P1->expon < P2->expon)
	{
		return -1;
	}
	else if ((P1->expon = P2->expon))
	{
		return 0;
	}
}

void Attach(int c, int e, Polynomial* pRear)
{
	// ���ڱ���������Ҫ�ı䵱ǰ������ʽ��β��ָ���ֵ
	// ���Ժ������������ǽڵ�ָ��ĵ�ַ�� *pRearָ��β��

	Polynomial P;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->coef = c;
	P->expon = e;
	P->link = NULL;

	// ��ָ����½ڵ���뵽��ǰ������ʽβ��ĺ���
	(*pRear)->link = P;
	*pRear = P;        // �޸�Rear��ֵ
}