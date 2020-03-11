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
