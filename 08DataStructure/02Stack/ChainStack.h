#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;
typedef struct SNode* ptrToStack;

struct SNode {
	ElementType Data;  // 存储栈中元素
	ptrToStack Next;   // 栈顶指针
};

typedef ptrToStack Stack;
#define ERROR -1

// 创建一个栈
Stack Create( )
{
	Stack s = (Stack)malloc(sizeof(struct SNode));
	s->Next = NULL;
	return s;
}

// 站是否为空
bool IsEmpty(Stack S)
{
	// 注意双等号
	return (S->Next == NULL);

}

// 入栈
bool Push(Stack S, ElementType X)
{
	// 将元素压入堆栈 S
	ptrToStack temCell = NULL;
	temCell = (ptrToStack)malloc(sizeof(struct SNode));
	temCell->Data = X;
	temCell->Next = S->Next;

	S->Next = temCell;
	return true;
}



ElementType PopStack(Stack S)
{
	ptrToStack firstCell;
	ElementType topElem;

	if (IsEmpty(S))
	{
		printf("堆栈空\n");
		return ERROR;
	}
	else
	{
		firstCell = S->Next;
		topElem = firstCell->Data;
		S->Next = firstCell->Next;
		free(firstCell);
		return topElem;
	}

}
