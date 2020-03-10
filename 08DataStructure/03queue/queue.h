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


//应用实例：使用链表来实现多项式的加法
struct PolyNode {
	int coef;        // 系数
	int expon;       // 指数
	struct PolyNode* link;
};

typedef struct PolyNode* Polynomial;
Polynomial P1, P2;

// 多项式相加
Polynomial PolyAdd(Polynomial P1, Polynomial P2)
{
	Polynomial front, rear, temp;
	int sum;
	// 先产生一个临时的空节点作为结构多项式链表头
	rear = (Polynomial)malloc(sizeof(struct PolyNode));
	front = rear;      // 由front记录结果多项式链表头节点
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
	// 将未处理完的另一个多项式的所有节点一次复制到结果多项式中去
	for (; P1; P1 = P1->link)
		Attach(P1->coef, P1->expon, &rear);
	for (; P2; P2 = P2->link)
		Attach(P2->coef, P2->expon, &rear);
	rear->link = NULL;
	front = front->link;     // 令front指向结果多项式 的第一个非零项
	free(temp);              // 释放空节点
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
	// 由于本函数中需要改变当前结果表达式的尾项指针的值
	// 所以函数传进来的是节点指针的地址， *pRear指向尾项

	Polynomial P;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->coef = c;
	P->expon = e;
	P->link = NULL;

	// 将指向的新节点插入到当前结果表达式尾项的后面
	(*pRear)->link = P;
	*pRear = P;        // 修改Rear的值
}