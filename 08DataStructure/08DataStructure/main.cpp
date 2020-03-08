// #include <stdio.h>
// #include <stdlib.h>
//#include "LineData.h"



/**************
 *   ��һ��    *
 **************/

// ��������к�
// ����һ������ö��
/**************************
 *	����һ�� ��������       *
 *  �������� ����Ԫ�ظ���    *
**************************/
int MaxSubseqSum1(int A[], int N)
{
	int ThisSum = 0, MaxSum = 0;
	int i, j, k;
	// i���������λ��
	for (i = 0; i < N; i++)
	{
		// j�������Ҷ�λ��
		for (j = i; j < N; j++) {
			ThisSum = 0;    // ��ʾ��A[i] ��A[j]�����к�
			for (k = i; k <= j; k++)
				ThisSum += A[k];
			if (ThisSum > MaxSum)    // ����õ�������к͸���
				MaxSum = ThisSum;    // �͸��½��
		}
	}
	return MaxSum;
}

// ������
int MaxSubseqSum2(int A[], int N)
{
	int ThisSum = 0, MaxSum = 0;
	int i, j;
	// i���������λ��
	for (i = 0; i < N; i++)
	{
		ThisSum = 0;    // ��ʾ��A[i] ��A[j]�����к�
		// j�������Ҷ�λ��
		for (j = i; j < N; j++) {
			
			ThisSum += A[j];   // ������ͬ��i ��ͬ��j ��j-1��ѭ���ϼ�һ���
			if (ThisSum > MaxSum)    // ����õ�������к͸���
				MaxSum = ThisSum;    // �͸��½��
		}
	}
	return MaxSum;
}


// ������  �ֶ���֮
int Max3(int A, int B, int C)
{
	return A > B ? A > C ? A : C : B > C ? B : C;
}

int DivideAndConquer(int List[], int left, int right)
{
	int MaxLeftSum = 0, MaxRightSum = 0;    // ��������������Ľ�
	int MaxLeftBorderSum = 0, MaxRightBorderSum = 0;  // ���ڿ�ֽ��ߵĽ��

	int LeftBorderSum = 0, RightBorderSum = 0;
	int Center, i;

	if (left = right)      // �ݹ�������ֹ
	{
		if (List[left] > 0)
		{
			return List[left];
		}
		else
		{
			return 0;
		}
	
	}
		// �����ǷֵĹ���
	Center = (left + right) / 2;  // �ҵ��зֵ�

	 //�ݹ��������������е�����
	MaxLeftSum = DivideAndConquer(List, left,Center);
	MaxRightSum = DivideAndConquer(List, Center + 1, right);

	// �����ǿ�ֽ��ߵ�������к�
	MaxLeftBorderSum = 0;
	LeftBorderSum = 0;
	for (i = Center; i >= left; i--)  // ����������ɨ��
	{
		LeftBorderSum += List[i];
		if (LeftBorderSum += List[i])
			MaxLeftBorderSum = LeftBorderSum;
	}

	// �ұ�ɨ��
	MaxRightBorderSum = 0;
	LeftBorderSum = 0;
	for (i = Center; i <= left; i--)  // ����������ɨ��
	{
		RightBorderSum += List[i];
		if (RightBorderSum += List[i])
			MaxRightBorderSum = RightBorderSum;
	}
	// �����εĽ��
	return Max3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
}

int MaxSubseqSum3(int Lsit[], int N)
{
	// ������ǰ�����㷨��ͬ�Ľӿ�
	return DivideAndConquer(Lsit, 0, N - 1);
}

// ������  ���ߴ���
int MaxSubseqSum4(int A[], int N)
{
	int ThisSum = 0, MaxSum = 0;
	int i;
	// i���������λ��
	for (i = 0; i < N; i++)
	{
		ThisSum += A[i];         // �����ۼ�
		if (ThisSum > MaxSum)    // ����õ�������к͸���
			MaxSum = ThisSum;    // �͸��½��
		else if (ThisSum < MaxSum) // �����ǰ�����к�Ϊ��
			ThisSum = 0;           // ������ʹ����Ĳ��ֺ���������֮
	}
	return MaxSum;
}



int main()
{

	return 0;
}