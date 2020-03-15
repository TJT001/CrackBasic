#pragma once
#include <iostream>

// ʹ���ڽӾ�������ʾͼ
#define MaxVertexNum 100   // ��󶥵���Ϊ100
#define INFINITY    65535  // ˫�ֽ��޷����������ֵ

typedef int Vertex;        // �ö����±��ʾ����Ϊ����
typedef int WeightType;    // ���Ȩֵ��Ϊ����
typedef char DataType;     // ����洢������������Ϊ�ַ���

// �ߵĶ���
typedef struct ENode* PtrToENode;
struct ENode {
	Vertex V1, V2;     // �����
	WeightType Weight; // Ȩ��
};

typedef PtrToENode Edge;

// ͼ�ڵ�Ķ���
typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;   // ������
	int Ne;   // ����
	// �ڽӾ���
	WeightType G[MaxVertexNum][MaxVertexNum];
	DataType Data[MaxVertexNum];   // �涥�������
	// ע���������£����������ݣ���ʱData[]���Բ��ó���
};
// ���ڽӾ���洢��ͼ����
typedef PtrToGNode MGraph;

// ����ͼ
MGraph CreateGraph(int VertexNum)
{
	// ��ʼ��һ����VertexNum �����㵫û�бߵ�ͼ
	Vertex V, W;
	MGraph Graph;
	Graph = (MGraph)malloc(sizeof(GNode)); // ����ͼ
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	// ��ʼ���ڽӾ���Ĭ�϶����Ŵ��㿪ʼ
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Ne; W++)
			Graph->G[V][W] = INFINITY;
	return Graph;
}

// �����
void InsertEdge(MGraph Graph, Edge E)
{
	// ����� V1��V2
	Graph->G[E->V1][E->V2] = E->Weight;

	// ��������ͼ����Ҫ�����V2��V1
	Graph->G[E->V2][E->V1] = E->Weight;
}

// ����ͼ
MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	scanf_s("%d", &Nv);   // ���붥�����
	Graph = CreateGraph(Nv);  // ��ʼ����Nv�����㵫û�б��ͼ

	scanf_s("%d", &(Graph->Ne));   // �������
	if (Graph->Ne != 0)  // �������
	{
		E = (Edge)malloc(sizeof(struct ENode));  // �����߽��

		// ����ߡ���ʽΪ��� �յ� Ȩ�� �����ڽӾ���
		for (i = 0; i < Graph->Ne; i++)
		{
			scanf_s("%d %d %d", &E->V1, &E->V2, &E->Weight);
			// ע�����Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�޸�
			InsertEdge(Graph, E);
		}
	}

	for (V = 0; V < Graph->Nv; V++)
		scanf_s("%c", &(Graph->Data[V]));
	return Graph;
}
