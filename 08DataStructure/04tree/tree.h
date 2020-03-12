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

// 二叉搜索树的插入
BinTree Insert(BinTree BST, ElementType X)
{
	if (!BST) // 若原树为空，生成并返回一个节点的二叉搜索树
	{
		BST = (BinTree)malloc(sizeof(TreeNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else
	{
		if (X < BST->Data)
			BST->Left = Insert(BST->Left, X);   // 递归插入左子树
		else if (X > BST->Data)
		{
			BST->Right = Insert(BST->Right, X);  // 递归插入右子树
		}
	}
	return BST;
}

// 二叉树搜索树的删除
BinTree Delete(BinTree BST, ElementType X)
{
	Position Tmp = NULL;
	if (!BST)
	{
		printf("要删除的元素未找到\n");
	}
	else
	{
		if (X < BST->Data)
			BST->Left = Delete(BST->Left, X);  // 左子树开始递归删除
		else if (X > BST->Data)
			BST->Right = Delete(BST->Right, X); // 右子树递归删除
		else
		{
			// BST就是要删除的节点
			// 如果被删除的节点有左右两个子节点
			if (BST->Left && BST->Right)
			{
				// 从右子树中找最小的元素填充删除节点
				Tmp = FindMin(BST->Right);
				BST->Data = Tmp->Data;
				// 从右子树中删除最小的元素
				BST->Right = Delete(BST->Right, BST->Data);
			}
			else
			{
				// 被删除节点有一个或者无节点
				Tmp = BST;
				if (!BST->Left)  // 只有右孩子或者无节点
					BST = BST->Right;
				else
					BST = BST->Left;
				free(Tmp);
			}
		}
	}
	return BST;
}