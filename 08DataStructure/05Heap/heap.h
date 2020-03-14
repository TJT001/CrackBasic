#pragma once
#include <iostream>

// �ѵ����Ͷ���
typedef struct HNode *Heap;
typedef int ElementType;

struct HNode {
	ElementType *Data;  // �洢Ԫ�ص�����
	int size;           // ���е�ǰԪ�صĸ���
	int Capacity;       // �ѵ��������
};

typedef Heap MaxHeap;   // ����
typedef Heap MinHeap;   // ��С��

// ��ֵӦ�ø��ݾ����������Ϊ���ڶ������п���Ԫ�ص�ֵ
#define MAXDATA 1000;

// ������
MaxHeap CreateHeap(int MaxSize)
{
	MaxHeap H = (MaxHeap)malloc(sizeof(HNode));
	H->Data = (ElementType*)malloc((MaxSize + 1) * sizeof(ElementType));
	H->size = 0;
	H->Capacity = MaxSize;
	H->Data[0] = MAXDATA;  // �����ڱ�Ϊ���ڶ������п���Ԫ�ص�ֵ
	return H;
}

// ���Ƿ���
bool Isfull(MaxHeap H)
{
	return (H->size == H->Capacity);
}

// ����Ԫ�صĲ���
bool Insert(MaxHeap H, ElementType X)
{
	// ��Ԫ��X��������H������H->Data[0]�Ѿ�������Ϊ�ڱ�
	int i = 0;
	if (Isfull(H))
	{
		printf(" ������\n");
	}
	i = ++H->size;  // iָ��������е����һ��Ԫ�ص�λ��
	for (; H->Data[i / 2] < X; i /= 2)
		H->Data[i] = H->Data[i / 2];  // ����X
	H->Data[i] = X; // ��X����
	return true;
}

#define ERROR -1
bool Isempty(MaxHeap H)
{
	return (H->size == 0);
}

// ɾ�����ֵ
ElementType DeleteMax(MaxHeap H)
{
	// ��������ȡ����ֵΪ����Ԫ�أ���ɾ��һ���ڵ�
	int Parent, Child;
	ElementType MaxItem, X;

	if (Isempty(H))
	{
		printf("�����ѿ�\n");
		return ERROR;
	}
	MaxItem = H->Data[1]; // ȡ�����ڵ������ֵ
	// �����������һ��Ԫ�شӸ��ڵ㿪ʼ���Ϲ����²�ڵ�
	X = H->Data[H->size--];   // ע�⵱ǰ�ѵĹ�ģҪ��С
	for (Parent = 1; Parent * 2 < H->size; Parent = Child)
	{
		Child = Parent * 2;
		if ((Child != H->size) && (H->Data[Child < H->Data[Child + 1]]))
			Child++;           // Childָ�������ӽڵ�Ľϴ�ֵ
		if (X >= H->Data[Child]) break;
		else // ����
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;
	return MaxItem;
}

// ��������
void PercDown(MaxHeap H, int p)
{
	// ���˽� H->Data[p]Ϊ�����Ӷѵ���Ϊ���ֵ
	int Parent, Child;
	ElementType X;

	X = H->Data[p];   // ȡ�����ڵ��ŵ�ֵ
	for (Parent = p; Parent * 2 <= H->size; Parent = Child)
	{
		Child = Parent * 2;
		if (Child != H->size && H->Data[Child] < H->Data[Child + 1])
			Child++; // childָ�������ӽڵ�Ľϴ�ֵ
		if (X >= H->Data[Child]) break;   // �ҵ��˺��ʵ�λ��
		else   // ���� X
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;
}

void BuildHeap(MaxHeap H)
{
	// ���� H->Data�е�Ԫ�أ�ʹ�������ѵ�������
	// �����������H->Size��Ԫ���Ѿ�����H->Data[]��
	int i = 0;
	// �����һ�����ĸ��ڵ㿪ʼ�����ڵ�1
	for (i = H->size / 2; i > 0; i--)
		PercDown(H, i);
}