#pragma once
#include <iostream>

// ʹ���ڽӾ�������ʾͼ
//#define MaxVertexNum 100   // ��󶥵���Ϊ100
//#define INFINITY    65535  // ˫�ֽ��޷����������ֵ
//
//typedef int Vertex;        // �ö����±��ʾ����Ϊ����
//typedef int WeightType;    // ���Ȩֵ��Ϊ����
//typedef char DataType;     // ����洢������������Ϊ�ַ���
//
//// �ߵĶ���
//typedef struct ENode* PtrToENode;
//struct ENode {
//	Vertex V1, V2;     // �����
//	WeightType Weight; // Ȩ��
//};
//
//typedef PtrToENode Edge;
//
//// ͼ�ڵ�Ķ���
//typedef struct GNode *PtrToGNode;
//struct GNode {
//	int Nv;   // ������
//	int Ne;   // ����
//	// �ڽӾ���
//	WeightType G[MaxVertexNum][MaxVertexNum];
//	DataType Data[MaxVertexNum];   // �涥�������
//	// ע���������£����������ݣ���ʱData[]���Բ��ó���
//};
//// ���ڽӾ���洢��ͼ����
//typedef PtrToGNode MGraph;
//
//// ����ͼ
//MGraph CreateGraph(int VertexNum)
//{
//	// ��ʼ��һ����VertexNum �����㵫û�бߵ�ͼ
//	Vertex V, W;
//	MGraph Graph;
//	Graph = (MGraph)malloc(sizeof(GNode)); // ����ͼ
//	Graph->Nv = VertexNum;
//	Graph->Ne = 0;
//	// ��ʼ���ڽӾ���Ĭ�϶����Ŵ��㿪ʼ
//	for (V = 0; V < Graph->Nv; V++)
//		for (W = 0; W < Graph->Ne; W++)
//			Graph->G[V][W] = INFINITY;
//	return Graph;
//}
//
//// �����
//void InsertEdge(MGraph Graph, Edge E)
//{
//	// ����� V1��V2
//	Graph->G[E->V1][E->V2] = E->Weight;
//
//	// ��������ͼ����Ҫ�����V2��V1
//	Graph->G[E->V2][E->V1] = E->Weight;
//}
//
//// ����ͼ
//MGraph BuildGraph()
//{
//	MGraph Graph;
//	Edge E;
//	Vertex V;
//	int Nv, i;
//
//	scanf_s("%d", &Nv);   // ���붥�����
//	Graph = CreateGraph(Nv);  // ��ʼ����Nv�����㵫û�б��ͼ
//
//	scanf_s("%d", &(Graph->Ne));   // �������
//	if (Graph->Ne != 0)  // �������
//	{
//		E = (Edge)malloc(sizeof(struct ENode));  // �����߽��
//
//		// ����ߡ���ʽΪ��� �յ� Ȩ�� �����ڽӾ���
//		for (i = 0; i < Graph->Ne; i++)
//		{
//			scanf_s("%d %d %d", &E->V1, &E->V2, &E->Weight);
//			// ע�����Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�޸�
//			InsertEdge(Graph, E);
//		}
//	}
//
//	for (V = 0; V < Graph->Nv; V++)
//		scanf_s("%c", &(Graph->Data[V]));
//	return Graph;
//}


// ͼ���ڽӱ��ʾ��
#define MaxVertexNum 100       // ��󶥵���Ϊ100

typedef int Vertex;            // �ö����±��ʾ���� Ϊ����
typedef int WeightType;        // �ߵ�ȨֵΪ����
typedef char DataType;         // ����洢������������Ϊ�ַ���

// �ߵĶ���
typedef struct ENode *PtrToENode;

struct ENode {
	Vertex V1, V2;       // ����� V1 V2
	WeightType Weight;   // Ȩ��
};

typedef PtrToENode Edge;

// �ڽӵ�Ķ���
typedef struct  AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;        // �ڽӵ���±�
	WeightType Weight;  // ��Ȩ��
	PtrToAdjVNode Next; // ָ����һ���ڽӵ��ָ��
};

// �����ͷ���Ķ���
typedef struct Vnode {
	PtrToAdjVNode FirstEdge;   // �߱�ͷָ��
	DataType Data;             // �涥�������
	// �ܶ������ ���������� ��ʱData���Բ��ó���
} AdjList[MaxVertexNum];

// ͼ�ڵ�Ķ���
typedef struct GNode *PtrToGNode;

struct GNode {
	int Nv;     // ������
	int Ne;     // ����
	AdjList G;  // �ڽӱ�
};
typedef PtrToGNode LGraph;     // ���ڽӵķ�ʽ�洢ͼ����

// ����ͼ 
LGraph CreateGraph(int VertexNum)
{
	// ��ʼ��һ����VertexNumge���㣬����û�бߵ�ͼ
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode)); // ����ͼ
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	// ��ʼ���ڽӱ�ͷָ�룬
	for (V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

// �����
void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;

	// ����� <V1 V2>
	// ΪV2�����µ��ڽӵ�
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;

	// ��V2����V1�ı�ͷ
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	// ��������ͼ����Ҫ����V2��V1
	// ΪV1�����µ�����ͼ
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;

	// ��V1����V2�ı�ͷ
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

// ����ͼ
LGraph BuildGraph()
{
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	scanf_s("%d", &Nv);            // ���붥��ĸ���
	Graph = CreateGraph(Nv);       // ��ʼ��Nv�����㵫û�б��ͼ
	scanf_s("%d", &(Graph->Ne));   // �������
	if (Graph->Ne != 0)            // �������
	{
		E = (Edge)malloc(sizeof(struct ENode));  // �����߽��
		// ����� ��ʽΪ��� �յ� Ȩ�أ������ڽӾ���
		for (i = 0; i < Graph->Ne; i++)
		{
			scanf_s("%d %d %d", E->V1, E->V2, E->Weight);
			InsertEdge(Graph, E);
		}
	}
	// ������������ݵĻ�
	for (V = 0; V < Graph->Nv; V++)
		scanf_s("%c", &(Graph->G[V].Data));

	return Graph;
}

// �ڽӱ�洢��ͼ -DFS
void Visit(Vertex V)
{
	printf("���ڷ��ʶ�����\n", V);
}

// VisitedΪȫ�ֱ��� �Ѿ���ʼ��Ϊ false

bool Visited[] = { false };
void DFS(LGraph Graph, Vertex V, void(*Visit)(Vertex))
{
	// ��VΪ��������ڽӱ�洢��ͼGrraph����DFS����
	PtrToAdjVNode W;
	Visit(V);   // ���ʵ�V������
	Visited[V] = true;  // ���V�Է���
	for (W = Graph->G[V].FirstEdge; W; W = W->Next)   // ��V��ÿ���ڽӵ�W-��ADJV
		if (!Visited[W->AdjV])                        // W->AdjVδ������
			DFS(Graph, V, Visit);                     // ��ݹ����֮
}