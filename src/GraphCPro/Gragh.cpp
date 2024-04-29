#define _CRT_SECURE_NO_WARNINGS
#include"Graph.h"
#include"Tourism.h"
#include<cstring>
#include<iostream>
using namespace std;
 CCgraph m_Graph;
//��ʼ��ͼ��Ϣ
void Init(void) {
	m_Graph.m_nVexNum = 0;
	int i;
	for (i = 0; i < 20; i++) {
		m_Graph.m_aVexs[i].num = -1;
		strcpy(m_Graph.m_aVexs[i].name, "");
		strcpy(m_Graph.m_aVexs[i].desc, "");
		for (int j = 0; j < 20; j++) {
			m_Graph.m_aAdjMatrix[i][j] = 0;

		}
	}
}
//�����
bool InsertVex(Vex sVex)
{
	if (m_Graph.m_nVexNum == 32767)
		return false;
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;
	return true;
}
//�����
bool InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_Graph.m_nVexNum ||
		sEdge.vex2 < 0 || sEdge.vex2 >= m_Graph.m_nVexNum)
		return false;
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}
Vex GetVex(int nVex) {
	return m_Graph.m_aVexs[nVex];
}
int FindEdge(int nVex, Edge aEdge[]) {
	int k = 0;
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		if (m_Graph.m_aAdjMatrix[nVex][i] != 0)
		{
			aEdge[k].vex1 = nVex;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_Graph.m_aAdjMatrix[nVex][i];
			k++;
		}
	}
	return k; //������Χ�������Ŀ
}
void DFS(int nVex, bool isVisited[]/*�ڵ�״̬����*/, int& nIndex, PathList& pList) {
	isVisited[nVex] = true;//�޸�Ϊ�ѷ���
	pList->cVex[nIndex++] = nVex;//���ʶ���nVex
	int num = 0;//�����ʹ��Ľڵ���
	for (int i = 0; i < m_Graph.m_nVexNum; i++) {
		if (isVisited[i]) {
			num++;//��ǰ�ڵ㱻���ʹ���num++
		}
	}
	if (num == m_Graph.m_nVexNum) {
		//������нڵ㶼�����ʹ�
		//����һ��·��
		pList->next =(PathList)malloc(sizeof( Path));
		for (int i = 0; i < m_Graph.m_nVexNum; i++) {
			pList->next->cVex[i] = pList->cVex[i];
		}
		pList = pList->next;
		pList->next = NULL;
	}
	else {
		for (int i = 0; i < m_Graph.m_nVexNum; i++) {
			if (!isVisited[i] && (m_Graph.m_aAdjMatrix[nVex][i] > 0)) {
				//�ݹ���õõ�һ��·��
				DFS(i, isVisited, nIndex, pList);
				isVisited[i] = false;//�õ�һ��·���󽫷��ʵ�i����Ϊfalse
				nIndex--;//����
			}
		}
	}

}
void DFSTraverse(int nVex, PathList& pList) {
	bool isVisited[20] = { false };
	int nIndex = 0;
	 DFS( nVex, isVisited,nIndex, pList);
	}

int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]) {
	int nShortPath[20][20];//���·�����б�ʾ�յ㣬�б�ʾ����㵽�յ�����·����ÿһ��
	int nShortDistance[20];//�������㵽��һ�������̾���
	bool aVisited[20];//�ж�ĳ���Ƿ��������·����
	int v;//ÿһ���ҵ��Ŀ��Լ��뼯�ϵĶ���
	//��ʼ��
	for (v = 0; v < m_Graph.m_nVexNum; v++) {
		aVisited[v] = false;
		if (m_Graph.m_aAdjMatrix[nVexStart][v] != 0) {
			//�������v��nVexStart����������̾�������Ϊ������֮��ľ���
			nShortDistance[v] = m_Graph.m_aAdjMatrix[nVexStart][v];
		}
		else {
			//���������������̾�������Ϊ���ֵ
			nShortDistance[v] = 0x7FFFFFFF;
		}
		nShortPath[v][0] = nVexStart;//��ʼ��ΪnVexStart
		//��ʼ�����·��
		for (int w = 1; w < m_Graph.m_nVexNum; w++) {
			nShortPath[v][w] = -1;
		}
	}
	//��ʼ������nVexStart������뵽������
	aVisited[nVexStart] = true;
	int min;//�ݴ�·������Сֵ
	for (int i=1; i < m_Graph.m_nVexNum; i++) {
		min = 0x7FFFFFFF;
		bool bAdd = false;//�ж��Ƿ��ж�����Լ��뼯��
		for (int w = 0; w < m_Graph.m_nVexNum; w++) {
			if (!aVisited[w] && nShortDistance[w] < min) {
				v = w;//w�������nVexStart�������                                      
				min = nShortDistance[w];//w��nVexStart����̾���Ϊmin
				bAdd = true;
			}
		}
		//���û�ж�����Լ��뵽���ϣ�������ѭ��
		if (!bAdd) {
			break;
		}
		aVisited[v] = true;//��w������뵽����
		nShortPath[v][i] = v;//ÿ���ҵ����·���󣬾��൱�ڴ�ԭ��������յ㣬����nShortPath[v][i]=v

		for (int w = 0; w < m_Graph.m_nVexNum; w++) {
			//��w��Ϊ�м�����nVexStart�����ж������̾���
			if (!aVisited[w] && (min + m_Graph.m_aAdjMatrix[v][w] < nShortDistance[w]) && (m_Graph.m_aAdjMatrix[v][w] > 0))
			{
				//������µ���̾��룬��������·��������
				nShortDistance[w] = min + m_Graph.m_aAdjMatrix[v][w];
				for (int i = 0; i < m_Graph.m_nVexNum; i++) {
					//���ͨ��w���ﶥ��i�ľ���Ƚ϶̣���w�����·����ֵ��i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}
	int nIndex = 0;
	int nVex1 = nVexStart;

	// �����·�����浽�ߵĽṹ��������
	for (int i = 1; i < m_Graph.m_nVexNum; i++)
	{
		if (nShortPath[nVexEnd][i] != -1)
		{
			aPath[nIndex].vex1 = nVex1;
			aPath[nIndex].vex2 = nShortPath[nVexEnd][i];
			aPath[nIndex].weight = m_Graph.m_aAdjMatrix[nVex1][aPath[nIndex].vex2];
			nVex1 = nShortPath[nVexEnd][i];
			nIndex++;
		}
	}
	return nIndex;
}

//ͨ��Prim�㷨������С������
void FindMinTree(Edge aPath[])
{
	bool aVisited[20] = { false }; // �ж�ĳ�����Ƿ�����С��������
	aVisited[0] = true;			 // ��0�Ŷ��㿪ʼ�����뵽������
	int min;
	int nVex1, nVex2;

	for (int k = 0; k < m_Graph.m_nVexNum - 1; k++)
	{
		min = 0X7FFFFFFF;

		for (int i = 0; i < m_Graph.m_nVexNum; i++)
		{
			// �Ӽ�����ȡһ������
			if (aVisited[i])
			{
				for (int j = 0; j < m_Graph.m_nVexNum; j++)
				{
					// �Ӳ��ڼ��ϵĶ�����ȡ��һ������
					if (!aVisited[j])
					{
						if ((m_Graph.m_aAdjMatrix[i][j] < min) && (m_Graph.m_aAdjMatrix[i][j] != 0))
						{
							nVex1 = i;
							nVex2 = j;
							// �ҳ���̱�
							min = m_Graph.m_aAdjMatrix[i][j];
						}
					}
				}
			}
		}

		// ������̱ߵ���������
		aPath[k].vex1 = nVex1;
		aPath[k].vex2 = nVex2;
		aPath[k].weight = m_Graph.m_aAdjMatrix[nVex1][nVex2];

		// ������������뼯��
		aVisited[nVex1] = true;
		aVisited[nVex2] = true;
	}
}
