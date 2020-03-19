#pragma once
#include <iostream>

// ð������

typedef int ElementType;

void Bubble_Sort(ElementType A[], int N)
{
	int p, i;
	ElementType tmp;

	for (p = 1; p < N; p++)
	{
		tmp = A[p];        // ȡ�������������еĵ�һ��Ԫ��
		for (i = p; i > 0 && A[i - 1] > tmp; i--)
			A[i] = A[i - 1];   // ������������������Ԫ�رȽϲ�����
		A[i] = tmp;            // �Ž����ǵ�λ��
	}
}

// ϣ������
void ShellSort(ElementType A[], int N)
{
	// ϣ������  ��Sedgewick ��������
	int Si, D, P, i;
	ElementType Tmp;

	// ����ֻ�г�һС��������
	int Sedgewick[] = { 929,505,209,109,41,19,5,1,0 };

	for (Si = 0; Sedgewick[Si] >= N; Si++);   // ��ʼ������Sedgewick[Si]���ܳ��������г���
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

// ������
void Swap(ElementType *a, ElementType *b)
{
	ElementType t = *a;
	*a = *b;
	*b = t;
}

void PerDown(ElementType A[], int p, int N)
{
	// ��N��Ԫ�ص���������A[p]Ϊ�����Ӷѵ���Ϊ����
	int Parent, Child;
	ElementType X;

	X = A[p];  // ȡ�����ڵ��ŵ�ֵ
	for (Parent = p; (Parent * 2 + 1) < N; Parent = Child)
	{
		Child = Parent * 2 +1;
		if ((Child != N - 1) && (A[Child] < A[Child + 1]))
			Child++;                   // Childָ�������ӽڵ�Ľϴ�ֵ
		if (X > A[Child]) break;       // �ҵ��˺��ʵ�λ��
		else   // ����
			A[Parent] = A[Child];
	}

	A[Parent] = X;
}

void HeapSort(ElementType A[], int N)
{
	// ������
	int i;
	for (i = N / 2 - 1; i > N; i--) // �������ֵ
		PerDown(A, i, N);
	for (i = N - 1; i > 0; i--)
		// ɾ�����ֵ��
		Swap(&A[0], &A[i]);
	PerDown(A, 0, i);
}