#pragma once
#include <iostream>

// 链表存储
typedef struct TreeNode *BinTree;
typedef BinTree Position;
typedef int ElementType;

struct TreeNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

// 二叉树的遍历

/****** 中序遍历 ******/
void InorderTraversal(BinTree BT)
{
	if (BT)
	{
		InorderTraversal(BT->Left);
		// 此处假设BT节点的访问就是打印数据
		printf("%d\n", BT->Data);
		InorderTraversal(BT->Right);
	}
}

/****** 前序遍历 ******/
void PreorderTraversal(BinTree BT)
{
	if (BT)
	{
		printf("%d\n", BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}

/****** 后序遍历 ******/
void PostorderTraversal(BinTree BT)
{
	PostorderTraversal(BT->Left);
	PostorderTraversal(BT->Right);
	printf("%d", BT->Data);
}
