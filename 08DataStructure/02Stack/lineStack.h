#pragma once
#include <iostream>

typedef int Position;
typedef int ElementType;

struct SNode {
	ElementType *Data; // �洢Ԫ�ص�����
	Position Top;      // ջ��ָ��
	int MaxSize;       // ջ�����������
};

typedef SNode* Stack;
#define ERROR -1

// ����һ��ջ
Stack Create(int MaxSize)
{
	Stack s = (Stack)malloc(sizeof(struct SNode));
	s->Data = (ElementType*)malloc(sizeof(ElementType));
	s->Top = -1;
	s->MaxSize = MaxSize;
	return s;
}

// �ж�վ�Ƿ���
bool Isfull(Stack S)
{
	return S->Top = S->MaxSize - 1;
}

// ��ջ
bool Push(Stack S, ElementType X)
{
	if (Isfull(S))
	{
		std::cout << "ջ����������ʧ��\n" << std::endl;
		return false;
	}
	else
	{
		// ջ���� 1
		return S->Data[++(S->Top)] = X;
	}
}

// վ�Ƿ�Ϊ��
bool IsEmpty(Stack S)
{
	// ע��˫�Ⱥ�
	return (S->Top == -1);
}

ElementType PopStack(Stack S)
{
	if (IsEmpty(S))
	{
		std::cout << "ջ�ѿգ�����ʧ��\n" << std::endl;
	}
	else
	{
		return (S->Data[(S->Top)--]);
	}
}
