#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1

//typedef int Position;
//typedef int ElementType;


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