// #include <stdio.h>
// #include <stdlib.h>
//#include "LineData.h"



/**************
 *   第一周    *
 **************/

// 求最大子列和
// 方法一：暴力枚举
/**************************
 *	参数一： 子列数组       *
 *  参数二： 子列元素个数    *
**************************/
int MaxSubseqSum1(int A[], int N)
{
	int ThisSum = 0, MaxSum = 0;
	int i, j, k;
	// i是子列左端位置
	for (i = 0; i < N; i++)
	{
		// j是子列右端位置
		for (j = i; j < N; j++) {
			ThisSum = 0;    // 表示从A[i] 到A[j]的子列和
			for (k = i; k <= j; k++)
				ThisSum += A[k];
			if (ThisSum > MaxSum)    // 如果得到这个子列和更大
				MaxSum = ThisSum;    // 就更新结果
		}
	}
	return MaxSum;
}

// 方法二
int MaxSubseqSum2(int A[], int N)
{
	int ThisSum = 0, MaxSum = 0;
	int i, j;
	// i是子列左端位置
	for (i = 0; i < N; i++)
	{
		ThisSum = 0;    // 表示从A[i] 到A[j]的子列和
		// j是子列右端位置
		for (j = i; j < N; j++) {
			
			ThisSum += A[j];   // 对于相同的i 不同的j 在j-1次循环上加一项即可
			if (ThisSum > MaxSum)    // 如果得到这个子列和更大
				MaxSum = ThisSum;    // 就更新结果
		}
	}
	return MaxSum;
}


// 方法三  分而治之
int Max3(int A, int B, int C)
{
	return A > B ? A > C ? A : C : B > C ? B : C;
}

int DivideAndConquer(int List[], int left, int right)
{
	int MaxLeftSum = 0, MaxRightSum = 0;    // 存在左右子问题的解
	int MaxLeftBorderSum = 0, MaxRightBorderSum = 0;  // 存在跨分界线的结果

	int LeftBorderSum = 0, RightBorderSum = 0;
	int Center, i;

	if (left = right)      // 递归条件终止
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
		// 下面是分的过程
	Center = (left + right) / 2;  // 找到中分点

	 //递归调用求得两边子列的最大和
	MaxLeftSum = DivideAndConquer(List, left,Center);
	MaxRightSum = DivideAndConquer(List, Center + 1, right);

	// 下面是跨分界线的最大子列和
	MaxLeftBorderSum = 0;
	LeftBorderSum = 0;
	for (i = Center; i >= left; i--)  // 从中线向左扫描
	{
		LeftBorderSum += List[i];
		if (LeftBorderSum += List[i])
			MaxLeftBorderSum = LeftBorderSum;
	}

	// 右边扫描
	MaxRightBorderSum = 0;
	LeftBorderSum = 0;
	for (i = Center; i <= left; i--)  // 从中线向左扫描
	{
		RightBorderSum += List[i];
		if (RightBorderSum += List[i])
			MaxRightBorderSum = RightBorderSum;
	}
	// 返回治的结果
	return Max3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
}

int MaxSubseqSum3(int Lsit[], int N)
{
	// 保持与前两种算法相同的接口
	return DivideAndConquer(Lsit, 0, N - 1);
}

// 方法四  在线处理
int MaxSubseqSum4(int A[], int N)
{
	int ThisSum = 0, MaxSum = 0;
	int i;
	// i是子列左端位置
	for (i = 0; i < N; i++)
	{
		ThisSum += A[i];         // 向右累加
		if (ThisSum > MaxSum)    // 如果得到这个子列和更大
			MaxSum = ThisSum;    // 就更新结果
		else if (ThisSum < MaxSum) // 如果当前的子列和为负
			ThisSum = 0;           // 不可能使后面的部分和增大，抛弃之
	}
	return MaxSum;
}



int main()
{

	return 0;
}