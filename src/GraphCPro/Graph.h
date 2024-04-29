#pragma once
//�洢ͼ�Ķ�����Ϣ
struct Vex {
	int num;//������
	char name[20];//��������
	char desc[1024];//�������
};
//�洢����Ϣ
struct Edge {
	int vex1;//�ߵĵ�һ������
	int vex2;//�ߵĵڶ�������
	int weight;//Ȩֵ
};
struct CCgraph {
	int m_aAdjMatrix[20][20];//�ڽӾ���
	Vex m_aVexs[20];//������Ϣ�����������š����ֺ�����
	int m_nVexNum;//�������
};//Graph�������ڴ洢��������ͼ

typedef struct Path {
	int cVex[20];//����һ��·��
	Path *next;//������һ��·��
}*PathList;//ָ��ṹ���ָ��

void Init(void);
bool InsertVex(Vex sVex);
bool InsertEdge(Edge sEdge);
Vex GetVex(int nVex);
int FindEdge(int nVex, Edge aEdge[]);
//ʹ�����������������ͼ
void DFS(int nVex, bool isVisited[], int& nIndex, PathList& pList);
//ͨ������DFS�������õ�����������������Ľ��
void DFSTraverse(int nVex, PathList& pList);
//Ѱ�����·��
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);
//ͨ��prim�㷨������С������
void FindMinTree(Edge aPath[]);
