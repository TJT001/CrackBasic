#pragma once
#include <iostream>
#include <string>
#include <list>

using namespace std;

#define MAXSIZE 512

// ����һ�����Ա�
typedef struct LNode *List;

// �������ݵ�����
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

// ���Ա�ĳ�ʼ��
List MakeEmpty()
{
	List Ptrl;
	Ptrl = (List)malloc(sizeof(struct LNode));
	Ptrl->Last = -1;
	return Ptrl;
 }

// ����


// ����


// ɾ��

