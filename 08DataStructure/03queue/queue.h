#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1

//typedef int Position;
//typedef int ElementType;


//struct QNode {
//	ElementType *Data;   // 存储元素的数组
//	Position Front, Rear;  // 栈头和栈尾指针
//	int MaxSize;   // 队列的最大容量
//};
//
//typedef struct QNode* Queue;
//
//// 创建一个队列
//Queue CreateQueue(int MaxSize)
//{
//	Queue Q = (Queue)malloc(sizeof(struct QNode*));
//	Q->Data = (ElementType*)malloc(MaxSize * sizeof(ElementType));
//	Q->Front = Q->Rear = 0;
//	Q->MaxSize = MaxSize;
//	return Q;
//}
//
//// 是否满
//bool Isfull(Queue Q)
//{
//	return ((Q->Rear + 1) % Q->MaxSize == Q->Front);
//}
//
//// 向队列中增加数据
//bool AddQ(Queue Q,ElementType x)
//{
//	if (Isfull(Q))
//	{
//		printf("队列已满\n");
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
//// 队列是否为空
//bool IsEmpty(Queue Q)
//{
//	return (Q->Front == Q->Rear);
//}
//
//// 删除队列中的元素
//ElementType DeleteQ(Queue Q)
//{
//	if (IsEmpty(Q))
//	{
//		printf("队列已空\n");
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
*	队列的链式实现			      *
*							  *
*******************************/

typedef struct Node* ptrToNode;
typedef int ElementType;

struct Node {
	ElementType Data;   // 存储元素的数据
	ptrToNode Next;  // 栈头和栈尾指针
};

typedef ptrToNode Position;

struct QNode {
	Position Front, Rear;  // 队列的头尾指针
	int MaxSize;           // 最大容量
};

typedef struct QNode* Queue;

// 队列是否为空
bool IsEmpty(Queue Q)
{
	return (Q->Front == NULL);
}


// 删除队列中的元素
ElementType DeleteQ(Queue Q)
{
	Position frontCell;
	ElementType frontElem;

	if (IsEmpty(Q))
	{
		printf("队列已空\n");
		return ERROR;
	}
	else
	{
		frontCell = Q->Front;
		if (Q->Front == Q->Rear)   // 若队列中只有一个元素
			Q->Front = Q->Rear = NULL;
		else
			Q->Front = Q->Front->Next;
		frontElem = frontCell->Data;
		free(frontCell);
		return frontElem;
	}
}