#include <iostream>

/*******************
*				   *
*线性表的链式存储实现 *
*				   *
********************/


// 不需要逻辑上相邻的连个元素物理上也相邻
// 通过链来建立起数据元素之间的逻辑关系

// 定义一个线性表
//typedef struct LNode* ptrToLNode;
typedef int ElementType;

// 通过数组的连续存储空间顺序存放线性表的各元素
struct LNode {
	ElementType Data;   // 节点代表的数据
	LNode* Next;        // 指向下一个节点的位置
};

typedef LNode* Position;
typedef LNode* List;

#define ERROR NULL

// 求表长
int Length(List Ptr)
{
	int j = 0;
	while (Ptr)
	{
		Ptr = Ptr->Next;
		j++;
	}

	return j;
}

// 查找
Position Find(List L, ElementType X)
{
	Position p = L;    // P指向L的第一个节点
	while (p && p->Data != X)
		p = p->Next;
	if (p)
		return p;
	else
		return ERROR;
}

// 插入
bool Insert(List L, ElementType X, Position p)
{
	Position tem, pre;
	// 查找p的前一个节点
	for (pre = L; pre && pre->Next != p; pre = pre->Next);
	
	// 位置检查
	if (pre = NULL)
	{
		printf("插入的位置有误\n");
		return false;
	}
	else
	{
		tem = (Position)malloc(sizeof(struct LNode));
		tem->Data = X;
		tem->Next = p;
		pre->Next = tem;
		return true;
	}
}

// 带头节点的删除
bool Delete(List L, Position p)
{
	Position pre;
	for (pre = NULL; pre && pre->Next != p; pre = pre->Next);
	
	if (pre == NULL || p == NULL)   // p所指的节点不在L中
	{
		printf("删除的的位置有误\n");
		return false;
	}
	else
	{
		// 找到了p的前一个节点
		// 将p的节点删除
		pre->Next = p->Next;
		free(p);
		return true;
	}
}