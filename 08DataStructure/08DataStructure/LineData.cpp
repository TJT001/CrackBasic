#pragma once
#include <iostream>
#include <string>
#include <list>

using namespace std;

#define MAXSIZE 512

// ����һ�����Ա�
typedef struct LNode *List;
typedef int Position;
typedef int ElementType;

// ͨ������������洢�ռ�˳�������Ա�ĸ�Ԫ��
struct LNode {
	ElementType Data[MAXSIZE];
	int Last;
};

struct LNode L;

// ���Ա�ĳ�ʼ��
List MakeEmpty()
{
	List Ptrl;
	Ptrl = (List)malloc(sizeof(struct LNode));
	Ptrl->Last = -1;
	return Ptrl;
 }

// ����
#define ERROR -1

Position find(int i, ElementType X)
{
	Position i = 0;
	while (i < L.Last && L.Data[i] != X)
	{
		i++;
	}
	if (i > L.Last) return ERROR;
	else  return i;    //�ڱ��ⷵ�ش���
	
}

// ����
bool Insert(List L, ElementType X, Position P)
{
	// ���ռ��Ƿ�����
	if (P = MAXSIZE - 1)
	{
		printf("�ռ�����\n");
		return false;
	}

	// ���λ���Ƿ�Ϸ�
	if (P > L->Last || P < 0)
	{
		printf("λ�ò��Ϸ�\n");
		return false;
	}
	for (int i = L->Last; i >= P; i--)
	{
		// ��λ��p���Ժ��Ԫ��˳������ƶ�
		L->Data[i + 1] = L->Data[i];
	}
		L->Data[P] = X;   // �µ�Ԫ�ز���
		L->Last++;
		return true;
}

// ɾ��
bool Delete(List L, ElementType X, Position P)
{
	// ���λ���Ƿ�Ϸ�
	// ���λ���Ƿ�Ϸ�
	if (P > L->Last || P < 0)
	{
		printf("û�и�Ԫ��\n");
		return false;
	}
	// λ��P�ĺ�һ��Ԫ����ǰ�ƶ�
	for (int i = P+1; i <= L->Last; i++)
	{
		L->Data[i-1] = L->Data[i];
	}
	// �ܳ��� - 1��
	L->Last--;
	return true;
}
