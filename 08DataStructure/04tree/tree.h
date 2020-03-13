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
				// Tmp = FindMin(BST->Right);
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

// 平衡二叉树

typedef struct AVLNode* Position;
typedef Position AVLTree;
struct AVLNode {
	ElementType Data;   // 结点数据
	AVLTree Left;       // 指向左子树
	AVLTree Right;      // 指向右子树
	int Height;         // 树高
};

int Max(int a, int b)
{
	return a > b ? a : b;
}

// 获取高度
int getHeight(AVLTree A)
{
	if (A = NULL)
		return 0;
	int leftHeight = getHeight(A->Left);
	int rightHeight = getHeight(A->Right);
	return Max(leftHeight, rightHeight);
}

// 左单璇
AVLTree singleLeftRotation(AVLTree A)
{
	// A必须有一个左子树节点
	// 将A于B做左单璇，更新A与B的高度，返回新的根节点
	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(getHeight(A->Left), getHeight(A->Right)) + 1;
	B->Height = Max(getHeight(B->Left), A->Height) + 1;

	return B;
}

// 右单璇
AVLTree singleRightRotation(AVLTree A)
{
	// A必须有一个右子树节点
	// 将A与B做左单璇，更新A与B的高度，返回新的节点
	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Right = A;
	A->Height = Max(getHeight(A->Right), getHeight(A->Left)) + 1;
	B->Height = Max(getHeight(B->Right), A->Height) + 1;
	return B;
}

// 左右璇
AVLTree doubleLeftRightRotation(AVLTree A)
{
	// 必须有一个子节点B，B必须有一个右节点C
	// 将A 与 B 做两次单璇，返回C
	A->Left = singleLeftRotation(A->Left);
	// 将A与C做左单璇， C被返回
	return singleLeftRotation(A);
}

// 平衡二叉树的插入
AVLTree Insert(AVLTree T, ElementType X)
{  // 将x插入AVL树 T 中，并且返回调整后的AVL树
	if (!T)  // 如果插入的是空树，就新建一个包含节点的空树
	{
		T = (AVLTree)malloc(sizeof(AVLTree));
		T->Data = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	}
	else if (X < T->Data)
	{
		// 插入T的左子树
		T->Left = Insert(T->Left, X);
		// 如果需要左旋
		if (getHeight(T->Left) - getHeight(T->Right) == 2)
			if (X < T->Left->Data)
				T = singleLeftRotation(T);   // 左单璇
			else
				T = doubleLeftRightRotation(T);  // 左右双璇
	}
	else if (X > T->Data)
	{
		// 插入T的右子树
		T->Right = Insert(T->Right, X);
		// 如果需要右旋
		if (getHeight(T->Left) - getHeight(T->Right) == 2)
			if (X < T->Right->Data)
				T = singleRightRotation(T);
			else
				T = doubleLeftRightRotation(T);   // 左右双璇
	}

	// 最后更新树的高度
	T->Height = Max(getHeight(T->Left), getHeight(T->Right)) + 1;
	return T;
}