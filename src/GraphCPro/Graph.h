#pragma once
//存储图的顶点信息
struct Vex {
	int num;//景点编号
	char name[20];//景点名字
	char desc[1024];//景点介绍
};
//存储边信息
struct Edge {
	int vex1;//边的第一个顶点
	int vex2;//边的第二个顶点
	int weight;//权值
};
struct CCgraph {
	int m_aAdjMatrix[20][20];//邻接矩阵
	Vex m_aVexs[20];//顶点信息，包括景点编号、名字和描述
	int m_nVexNum;//顶点个数
};//Graph对象，用于存储景区景点图

typedef struct Path {
	int cVex[20];//保存一条路径
	Path *next;//保存下一条路径
}*PathList;//指向结构体的指针

void Init(void);
bool InsertVex(Vex sVex);
bool InsertEdge(Edge sEdge);
Vex GetVex(int nVex);
int FindEdge(int nVex, Edge aEdge[]);
//使用深度优先搜索遍历图
void DFS(int nVex, bool isVisited[], int& nIndex, PathList& pList);
//通过调用DFS函数，得到深度优先搜索遍历的结果
void DFSTraverse(int nVex, PathList& pList);
//寻找最短路径
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);
//通过prim算法构建最小生成树
void FindMinTree(Edge aPath[]);
