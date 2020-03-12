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
				Tmp = FindMin(BST->Right);
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