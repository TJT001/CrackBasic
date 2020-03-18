#pragma once
#include <iostream>

// 使用邻接矩阵来表示图
//#define MaxVertexNum 100   // 最大顶点设为100
//#define INFINITY    65535  // 双字节无符号整数最大值
//
//typedef int Vertex;        // 用顶点下标表示顶点为整型
//typedef int WeightType;    // 变得权值设为整型
//typedef char DataType;     // 顶点存储的数据类型设为字符型
//
//// 边的定义
//typedef struct ENode* PtrToENode;
//struct ENode {
//	Vertex V1, V2;     // 有向边
//	WeightType Weight; // 权重
//};
//
//typedef PtrToENode Edge;
//
//// 图节点的定义
//typedef struct GNode *PtrToGNode;
//struct GNode {
//	int Nv;   // 顶点数
//	int Ne;   // 边数
//	// 邻接矩阵
//	WeightType G[MaxVertexNum][MaxVertexNum];
//	DataType Data[MaxVertexNum];   // 存顶点的数量
//	// 注意多数情况下，顶点无数据，此时Data[]可以不用出现
//};
//// 以邻接举阵存储的图类型
//typedef PtrToGNode MGraph;
//
//// 创建图
//MGraph CreateGraph(int VertexNum)
//{
//	// 初始化一个有VertexNum 个顶点但没有边的图
//	Vertex V, W;
//	MGraph Graph;
//	Graph = (MGraph)malloc(sizeof(GNode)); // 建立图
//	Graph->Nv = VertexNum;
//	Graph->Ne = 0;
//	// 初始化邻接矩阵。默认顶点编号从零开始
//	for (V = 0; V < Graph->Nv; V++)
//		for (W = 0; W < Graph->Ne; W++)
//			Graph->G[V][W] = INFINITY;
//	return Graph;
//}
//
//// 插入边
//void InsertEdge(MGraph Graph, Edge E)
//{
//	// 插入边 V1，V2
//	Graph->G[E->V1][E->V2] = E->Weight;
//
//	// 若是无向图，还要插入边V2，V1
//	Graph->G[E->V2][E->V1] = E->Weight;
//}
//
//// 构建图
//MGraph BuildGraph()
//{
//	MGraph Graph;
//	Edge E;
//	Vertex V;
//	int Nv, i;
//
//	scanf_s("%d", &Nv);   // 读入顶点个数
//	Graph = CreateGraph(Nv);  // 初始化有Nv个顶点但没有变得图
//
//	scanf_s("%d", &(Graph->Ne));   // 读入边数
//	if (Graph->Ne != 0)  // 读入边数
//	{
//		E = (Edge)malloc(sizeof(struct ENode));  // 建立边结点
//
//		// 读入边。格式为起点 终点 权重 插入邻接矩阵
//		for (i = 0; i < Graph->Ne; i++)
//		{
//			scanf_s("%d %d %d", &E->V1, &E->V2, &E->Weight);
//			// 注意如果权重不是整型，Weight的读入格式要修改
//			InsertEdge(Graph, E);
//		}
//	}
//
//	for (V = 0; V < Graph->Nv; V++)
//		scanf_s("%c", &(Graph->Data[V]));
//	return Graph;
//}


// 图的邻接表表示法
#define MaxVertexNum 100       // 最大顶点数为100

typedef int Vertex;            // 用顶点下标表示顶点 为整型
typedef int WeightType;        // 边的权值为整型
typedef char DataType;         // 顶点存储的数据类型设为字符型

// 边的定义
typedef struct ENode *PtrToENode;

struct ENode {
	Vertex V1, V2;       // 有向边 V1 V2
	WeightType Weight;   // 权重
};

typedef PtrToENode Edge;

// 邻接点的定义
typedef struct  AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;        // 邻接点的下标
	WeightType Weight;  // 边权重
	PtrToAdjVNode Next; // 指向下一个邻接点的指针
};

// 顶点表头结点的定义
typedef struct Vnode {
	PtrToAdjVNode FirstEdge;   // 边表头指针
	DataType Data;             // 存顶点的数据
	// 很多情况下 顶点无数据 此时Data可以不用出现
} AdjList[MaxVertexNum];

// 图节点的定义
typedef struct GNode *PtrToGNode;

struct GNode {
	int Nv;     // 顶点数
	int Ne;     // 边数
	AdjList G;  // 邻接表
};
typedef PtrToGNode LGraph;     // 以邻接的方式存储图类型

// 创建图 
LGraph CreateGraph(int VertexNum)
{
	// 初始化一个有VertexNumge顶点，但是没有边的图
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode)); // 建立图
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	// 初始化邻接表头指针，
	for (V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

// 插入边
void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;

	// 插入边 <V1 V2>
	// 为V2建立新的邻接点
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;

	// 将V2插入V1的表头
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	// 若是无向图，还要插入V2，V1
	// 为V1建立新的无向图
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;

	// 将V1插入V2的表头
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

// 构建图
LGraph BuildGraph()
{
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	scanf_s("%d", &Nv);            // 读入顶点的个数
	Graph = CreateGraph(Nv);       // 初始化Nv个顶点但没有变得图
	scanf_s("%d", &(Graph->Ne));   // 读入边数
	if (Graph->Ne != 0)            // 如果边数
	{
		E = (Edge)malloc(sizeof(struct ENode));  // 建立边结点
		// 读入边 格式为起点 终点 权重，插入邻接矩阵
		for (i = 0; i < Graph->Ne; i++)
		{
			scanf_s("%d %d %d", E->V1, E->V2, E->Weight);
			InsertEdge(Graph, E);
		}
	}
	// 如果顶点有数据的话
	for (V = 0; V < Graph->Nv; V++)
		scanf_s("%c", &(Graph->G[V].Data));

	return Graph;
}

// 邻接表存储的图 -DFS
void Visit(Vertex V)
{
	printf("正在访问顶点数\n", V);
}

// Visited为全局变量 已经初始化为 false

bool Visited[] = { false };
void DFS(LGraph Graph, Vertex V, void(*Visit)(Vertex))
{
	// 以V为出发点对邻接表存储的图Grraph进行DFS搜索
	PtrToAdjVNode W;
	Visit(V);   // 访问第V个顶点
	Visited[V] = true;  // 标记V以访问
	for (W = Graph->G[V].FirstEdge; W; W = W->Next)   // 对V的每个邻接点W-》ADJV
		if (!Visited[W->AdjV])                        // W->AdjV未被访问
			DFS(Graph, V, Visit);                     // 则递归访问之
}