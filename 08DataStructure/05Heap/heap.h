#pragma once
#include <iostream>

// 堆的类型定义
typedef struct HNode *Heap;
typedef int ElementType;

struct HNode {
	ElementType *Data;  // 存储元素的数组
	int size;           // 堆中当前元素的个数
	int Capacity;       // 堆的最大容量
};

typedef Heap MaxHeap;   // 最大堆
typedef Heap MinHeap;   // 最小堆

// 该值应该根据具体情况定义为大于堆中所有可能元素的值
#define MAXDATA 1000;

// 创建堆
MaxHeap CreateHeap(int MaxSize)
{
	MaxHeap H = (MaxHeap)malloc(sizeof(HNode));
	H->Data = (ElementType*)malloc((MaxSize + 1) * sizeof(ElementType));
	H->size = 0;
	H->Capacity = MaxSize;
	H->Data[0] = MAXDATA;  // 定义哨兵为大于堆中所有可能元素的值
	return H;
}

// 对是否满
bool Isfull(MaxHeap H)
{
	return (H->size == H->Capacity);
}

// 堆中元素的插入
bool Insert(MaxHeap H, ElementType X)
{
	// 将元素X插入最大堆H，其中H->Data[0]已经被定义为哨兵
	int i = 0;
	if (Isfull(H))
	{
		printf(" 堆已满\n");
	}
	i = ++H->size;  // i指向插入后堆中的最后一个元素的位置
	for (; H->Data[i / 2] < X; i /= 2)
		H->Data[i] = H->Data[i / 2];  // 上滤X
	H->Data[i] = X; // 将X插入
	return true;
}

#define ERROR -1
bool Isempty(MaxHeap H)
{
	return (H->size == 0);
}

// 删除最大值
ElementType DeleteMax(MaxHeap H)
{
	// 从最大堆中取出键值为最大的元素，并删除一个节点
	int Parent, Child;
	ElementType MaxItem, X;

	if (Isempty(H))
	{
		printf("最大堆已空\n");
		return ERROR;
	}
	MaxItem = H->Data[1]; // 取出根节点存放最大值
	// 用最大堆中最后一个元素从根节点开始向上过滤下层节点
	X = H->Data[H->size--];   // 注意当前堆的规模要减小
	for (Parent = 1; Parent * 2 < H->size; Parent = Child)
	{
		Child = Parent * 2;
		if ((Child != H->size) && (H->Data[Child < H->Data[Child + 1]]))
			Child++;           // Child指向左右子节点的较大值
		if (X >= H->Data[Child]) break;
		else // 下滤
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;
	return MaxItem;
}

// 建造最大堆
void PercDown(MaxHeap H, int p)
{
	// 下滤将 H->Data[p]为根的子堆调整为最大值
	int Parent, Child;
	ElementType X;

	X = H->Data[p];   // 取出根节点存放的值
	for (Parent = p; Parent * 2 <= H->size; Parent = Child)
	{
		Child = Parent * 2;
		if (Child != H->size && H->Data[Child] < H->Data[Child + 1])
			Child++; // child指向左右子节点的较大值
		if (X >= H->Data[Child]) break;   // 找到了合适的位置
		else   // 下滤 X
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;
}

void BuildHeap(MaxHeap H)
{
	// 调整 H->Data中的元素，使满足最大堆的有序性
	// 这里假设所有H->Size个元素已经存在H->Data[]中
	int i = 0;
	// 从最后一个结点的父节点开始到根节点1
	for (i = H->size / 2; i > 0; i--)
		PercDown(H, i);
}