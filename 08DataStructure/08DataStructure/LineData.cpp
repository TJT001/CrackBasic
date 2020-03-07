#pragma once
#include <iostream>
#include <string>
#include <list>

using namespace std;

#define MAXSIZE 512

// 定义一个线性表
typedef struct LNode *List;
typedef int Position;
typedef int ElementType;

// 通过数组的连续存储空间顺序存放线性表的各元素
struct LNode {
	ElementType Data[MAXSIZE];
	int Last;
};

struct LNode L;

// 线性表的初始化
List MakeEmpty()
{
	List Ptrl;
	Ptrl = (List)malloc(sizeof(struct LNode));
	Ptrl->Last = -1;
	return Ptrl;
 }

// 查找
#define ERROR -1

Position find(int i, ElementType X)
{
	Position i = 0;
	while (i < L.Last && L.Data[i] != X)
	{
		i++;
	}
	if (i > L.Last) return ERROR;
	else  return i;    //在表外返回错误
	
}

// 插入
bool Insert(List L, ElementType X, Position P)
{
	// 检查空间是否已满
	if (P = MAXSIZE - 1)
	{
		printf("空间已满\n");
		return false;
	}

	// 检查位置是否合法
	if (P > L->Last || P < 0)
	{
		printf("位置不合法\n");
		return false;
	}
	for (int i = L->Last; i >= P; i--)
	{
		// 将位置p及以后的元素顺序向后移动
		L->Data[i + 1] = L->Data[i];
	}
		L->Data[P] = X;   // 新的元素插入
		L->Last++;
		return true;
}

// 删除
bool Delete(List L, ElementType X, Position P)
{
	// 检查位置是否合法
	// 检查位置是否合法
	if (P > L->Last || P < 0)
	{
		printf("没有该元素\n");
		return false;
	}
	// 位置P的后一个元素向前移动
	for (int i = P+1; i <= L->Last; i++)
	{
		L->Data[i-1] = L->Data[i];
	}
	// 总长度 - 1；
	L->Last--;
	return true;
}
