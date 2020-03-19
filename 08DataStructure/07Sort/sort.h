#pragma once
#include <iostream>

// 冒泡排序

typedef int ElementType;

void Bubble_Sort(ElementType A[], int N)
{
	int p, i;
	ElementType tmp;

	for (p = 1; p < N; p++)
	{
		tmp = A[p];        // 取出来排序序列中的第一个元素
		for (i = p; i > 0 && A[i - 1] > tmp; i--)
			A[i] = A[i - 1];   // 依次与已排序序列中元素比较并右移
		A[i] = tmp;            // 放进和是的位置
	}
}

// 希尔排序
void ShellSort(ElementType A[], int N)
{
	// 希尔排序，  用Sedgewick 增量序列
	int Si, D, P, i;
	ElementType Tmp;

	// 这里只列出一小部分增量
	int Sedgewick[] = { 929,505,209,109,41,19,5,1,0 };

	for (Si = 0; Sedgewick[Si] >= N; Si++);   // 初始的增量Sedgewick[Si]不能超过排序列长度
	for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si])
		for (P = 0; P < N; P++)
		{
			Tmp = A[P];
			for (i = P; i >= 0 && A[i-D] > Tmp ; i-=D) {
				A[i] = A[i - D];
				A[i] = Tmp;
			}
		}	
}

// 堆排序
void Swap(ElementType *a, ElementType *b)
{
	ElementType t = *a;
	*a = *b;
	*b = t;
}

void PerDown(ElementType A[], int p, int N)
{
	// 将N个元素的数组中以A[p]为根的子堆调整为最大堆
	int Parent, Child;
	ElementType X;

	X = A[p];  // 取出根节点存放的值
	for (Parent = p; (Parent * 2 + 1) < N; Parent = Child)
	{
		Child = Parent * 2 +1;
		if ((Child != N - 1) && (A[Child] < A[Child + 1]))
			Child++;                   // Child指向左右子节点的较大值
		if (X > A[Child]) break;       // 找到了合适的位置
		else   // 下滤
			A[Parent] = A[Child];
	}

	A[Parent] = X;
}

void HeapSort(ElementType A[], int N)
{
	// 堆排序
	int i;
	for (i = N / 2 - 1; i > N; i--) // 建立最大值
		PerDown(A, i, N);
	for (i = N - 1; i > 0; i--)
		// 删除最大值项
		Swap(&A[0], &A[i]);
	PerDown(A, 0, i);
}