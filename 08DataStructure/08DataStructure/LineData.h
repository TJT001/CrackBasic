#pragma once
#include <iostream>
#include <string>
#include <list>

using namespace std;

#define MAXSIZE 512

// 定义一个线性表
typedef struct LNode *List;

// 定义数据的类型
struct ElementType {
	int i;
	double d;
};
struct LNode {
	ElementType Data[MAXSIZE];
	int Last;
};

struct LNode L;
List PERL;

// 线性表的初始化
List MakeEmpty()
{
	List Ptrl;
	Ptrl = (List)malloc(sizeof(struct LNode));
	Ptrl->Last = -1;
	return Ptrl;
 }

// 查找


// 插入


// 删除

