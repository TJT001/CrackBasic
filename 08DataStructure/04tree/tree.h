#pragma once
#include <iostream>

// ����洢
typedef struct TreeNode *BinTree;
typedef BinTree Position;
typedef int ElementType;

struct TreeNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

// �������ı���

/****** ������� ******/
void InorderTraversal(BinTree BT)
{
	if (BT)
	{
		InorderTraversal(BT->Left);
		// �˴�����BT�ڵ�ķ��ʾ��Ǵ�ӡ����
		printf("%d\n", BT->Data);
		InorderTraversal(BT->Right);
	}
}

/****** ǰ����� ******/
void PreorderTraversal(BinTree BT)
{
	if (BT)
	{
		printf("%d\n", BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}

/****** ������� ******/
void PostorderTraversal(BinTree BT)
{
	PostorderTraversal(BT->Left);
	PostorderTraversal(BT->Right);
	printf("%d", BT->Data);
}

// �����������Ĳ���
BinTree Insert(BinTree BST, ElementType X)
{
	if (!BST) // ��ԭ��Ϊ�գ����ɲ�����һ���ڵ�Ķ���������
	{
		BST = (BinTree)malloc(sizeof(TreeNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else
	{
		if (X < BST->Data)
			BST->Left = Insert(BST->Left, X);   // �ݹ����������
		else if (X > BST->Data)
		{
			BST->Right = Insert(BST->Right, X);  // �ݹ����������
		}
	}
	return BST;
}

// ��������������ɾ��
BinTree Delete(BinTree BST, ElementType X)
{
	Position Tmp = NULL;
	if (!BST)
	{
		printf("Ҫɾ����Ԫ��δ�ҵ�\n");
	}
	else
	{
		if (X < BST->Data)
			BST->Left = Delete(BST->Left, X);  // ��������ʼ�ݹ�ɾ��
		else if (X > BST->Data)
			BST->Right = Delete(BST->Right, X); // �������ݹ�ɾ��
		else
		{
			// BST����Ҫɾ���Ľڵ�
			// �����ɾ���Ľڵ������������ӽڵ�
			if (BST->Left && BST->Right)
			{
				// ��������������С��Ԫ�����ɾ���ڵ�
				// Tmp = FindMin(BST->Right);
				BST->Data = Tmp->Data;
				// ����������ɾ����С��Ԫ��
				BST->Right = Delete(BST->Right, BST->Data);
			}
			else
			{
				// ��ɾ���ڵ���һ�������޽ڵ�
				Tmp = BST;
				if (!BST->Left)  // ֻ���Һ��ӻ����޽ڵ�
					BST = BST->Right;
				else
					BST = BST->Left;
				free(Tmp);
			}
		}
	}
	return BST;
}

// ƽ�������

typedef struct AVLNode* Position;
typedef Position AVLTree;
struct AVLNode {
	ElementType Data;   // �������
	AVLTree Left;       // ָ��������
	AVLTree Right;      // ָ��������
	int Height;         // ����
};

int Max(int a, int b)
{
	return a > b ? a : b;
}

// ��ȡ�߶�
int getHeight(AVLTree A)
{
	if (A = NULL)
		return 0;
	int leftHeight = getHeight(A->Left);
	int rightHeight = getHeight(A->Right);
	return Max(leftHeight, rightHeight);
}

// ���
AVLTree singleLeftRotation(AVLTree A)
{
	// A������һ���������ڵ�
	// ��A��B����诣�����A��B�ĸ߶ȣ������µĸ��ڵ�
	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(getHeight(A->Left), getHeight(A->Right)) + 1;
	B->Height = Max(getHeight(B->Left), A->Height) + 1;

	return B;
}

// �ҵ��
AVLTree singleRightRotation(AVLTree A)
{
	// A������һ���������ڵ�
	// ��A��B����诣�����A��B�ĸ߶ȣ������µĽڵ�
	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Right = A;
	A->Height = Max(getHeight(A->Right), getHeight(A->Left)) + 1;
	B->Height = Max(getHeight(B->Right), A->Height) + 1;
	return B;
}

// �����
AVLTree doubleLeftRightRotation(AVLTree A)
{
	// ������һ���ӽڵ�B��B������һ���ҽڵ�C
	// ��A �� B �����ε�诣�����C
	A->Left = singleLeftRotation(A->Left);
	// ��A��C����诣� C������
	return singleLeftRotation(A);
}

// ƽ��������Ĳ���
AVLTree Insert(AVLTree T, ElementType X)
{  // ��x����AVL�� T �У����ҷ��ص������AVL��
	if (!T)  // ���������ǿ��������½�һ�������ڵ�Ŀ���
	{
		T = (AVLTree)malloc(sizeof(AVLTree));
		T->Data = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	}
	else if (X < T->Data)
	{
		// ����T��������
		T->Left = Insert(T->Left, X);
		// �����Ҫ����
		if (getHeight(T->Left) - getHeight(T->Right) == 2)
			if (X < T->Left->Data)
				T = singleLeftRotation(T);   // ���
			else
				T = doubleLeftRightRotation(T);  // ����˫�
	}
	else if (X > T->Data)
	{
		// ����T��������
		T->Right = Insert(T->Right, X);
		// �����Ҫ����
		if (getHeight(T->Left) - getHeight(T->Right) == 2)
			if (X < T->Right->Data)
				T = singleRightRotation(T);
			else
				T = doubleLeftRightRotation(T);   // ����˫�
	}

	// ���������ĸ߶�
	T->Height = Max(getHeight(T->Left), getHeight(T->Right)) + 1;
	return T;
}