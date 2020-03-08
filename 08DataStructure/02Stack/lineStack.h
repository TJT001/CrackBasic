#pragma once
#include <iostream>

typedef int Position;
typedef int ElementType;

struct SNode {
	ElementType *Data; // 存储元素的数组
	Position Top;      // 栈顶指针
	int MaxSize;       // 栈顶的最大容量
};

typedef SNode* Stack;
#define ERROR -1

// 创建一个栈
Stack Create(int MaxSize)
{
	Stack s = (Stack)malloc(sizeof(struct SNode));
	s->Data = (ElementType*)malloc(sizeof(ElementType));
	s->Top = -1;
	s->MaxSize = MaxSize;
	return s;
}

// 判断站是否满
bool Isfull(Stack S)
{
	return S->Top = S->MaxSize - 1;
}

// 入栈
bool Push(Stack S, ElementType X)
{
	if (Isfull(S))
	{
		std::cout << "栈已满，操作失败\n" << std::endl;
		return false;
	}
	else
	{
		// 栈顶加 1
		return S->Data[++(S->Top)] = X;
	}
}

// 站是否为空
bool IsEmpty(Stack S)
{
	// 注意双等号
	return (S->Top == -1);
}

ElementType PopStack(Stack S)
{
	if (IsEmpty(S))
	{
		std::cout << "栈已空，操作失败\n" << std::endl;
	}
	else
	{
		return (S->Data[(S->Top)--]);
	}
}
