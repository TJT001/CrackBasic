#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;
typedef struct SNode* ptrToStack;

struct SNode {
	ElementType Data;  // �洢ջ��Ԫ��
	ptrToStack Next;   // ջ��ָ��
};

typedef ptrToStack Stack;
#define ERROR -1

// ����һ��ջ
Stack Create( )
{
	Stack s = (Stack)malloc(sizeof(struct SNode));
	s->Next = NULL;
	return s;
}

// վ�Ƿ�Ϊ��
bool IsEmpty(Stack S)
{
	// ע��˫�Ⱥ�
	return (S->Next == NULL);

}

// ��ջ
bool Push(Stack S, ElementType X)
{
	// ��Ԫ��ѹ���ջ S
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
		printf("��ջ��\n");
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
