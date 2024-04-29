#define _CRT_SECURE_NO_WARNINGS
#include"Tourism.h"
#include"Graph.h"
#include<iostream>
#include<cstring>
using namespace std;
extern CCgraph m_Graph;
//������������
void CreateGraph(void) {
	Init();
	cout << "==== ������������ͼ ====" << endl;
	int num;
	FILE *InVex = fopen("D:\\Vex.txt.txt", "r");
	fscanf_s(InVex, "%d", &num);
	cout << "������Ŀ��" << num << endl;
	cout << "----- ���� -----" << endl;
	for (int i = 0; i < num; i++) {
		Vex vex;
		fscanf_s(InVex, "%d", &(vex.num));
		fscanf(InVex, "%s", &(vex.name));
		fscanf(InVex, "%s", &(vex.desc));
		cout << vex.num << "-" << vex.name << endl;
		InsertVex(vex);
	}
	fclose(InVex);
	cout << "----- �� -----" << endl;
	FILE *InEdge = fopen("D:\\Edge.txt.txt", "r");
	while (!feof(InEdge)) {
		Edge edge;
		fscanf_s(InEdge, "%d %d %d", &edge.vex1, &edge.vex2, &edge.weight);
		cout << "<v" << edge.vex1 << ",v" << edge.vex2 << ">" << edge.weight << endl;
		InsertEdge(edge);
	}fclose(InEdge);
}
//��ѯ������Ϣ ֱ�Ӳ�ѯ
void GetSpotInfo(void)
{
	if (m_Graph.m_nVexNum == 0) {
		cout << "��������Ϣ �����ȴ���������Ϣ" << endl;
		return;
	}
	cout << "===== ��ѯ������Ϣ =====" << endl;
	int i;
	for (i = 0; i < m_Graph.m_nVexNum; i++)
		cout << m_Graph.m_aVexs[i].num << "-" << m_Graph.m_aVexs[i].name << endl;
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	int Num;
	cin >> Num;
	if (Num >= m_Graph.m_nVexNum) {
		cout << "���������� Ĭ���˳�" << endl;
		return;
	}
	Vex vex = GetVex(Num);
	cout << vex.desc/*����*/ << endl;
	cout << "----- ��Χ���� ------" << endl;
	Edge aEdge[100];
	int sum_Edge = FindEdge(Num, aEdge);
	for (i = 0; i < sum_Edge; i++) {
		if (aEdge[i].weight != 32767) {
			cout << m_Graph.m_aVexs[aEdge[i].vex1].name << "->" <<
				m_Graph.m_aVexs[aEdge[i].vex2].name << " " << aEdge[i].weight << "m" << endl;
		}
	}
}
//����
void TravelPath() {
	if (m_Graph.m_nVexNum == 0) {
		cout << "��������Ϣ �����ȴ���������Ϣ" << endl;
		return;
	}
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		Vex svex = GetVex(i);
		cout << i << "-" << svex.name << endl;
	}
	cout << "��������ʼ���ţ� ";
	int Num;
	cin >> Num;
	if (Num < 0 || Num >= m_Graph.m_nVexNum) {
		cout << "������ı�Ŵ���Ĭ���˳���" << endl;
		return;
	}
	cout << "����·��Ϊ��" << endl;
	PathList pList = (PathList)malloc(sizeof( Path));
	PathList Head = pList;
	//����DFSTraverse����
	DFSTraverse(Num, pList);
	pList = Head;
	int j = 1;
	while (pList->next != NULL) {
		cout << "·��" << j << "��";
		for (int i = 0; i < m_Graph.m_nVexNum; i++) {
			cout <<m_Graph.m_aVexs[pList->cVex[i]].name << " ";
		}
		cout << endl;
		pList = pList->next;
		j++;
	}
	free(pList);
	pList = NULL;
	Head = NULL;
}

void FindShortPath(void)
{
	cout << "\n======�������·��======\n";

	int nVexNum = m_Graph.m_nVexNum;

	if (nVexNum == 0)
	{
		cout << "���ȴ���ͼ��" << endl;
		return;
	}

	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << "*\t" << i << "-" << sVex.name << "\t\t*" << endl;
	}
	cout << "========================\n";

	// ������������ı��
	int start_place, end_place;
	cout << "���������ı�ţ�";
	cin >> start_place;
	cout << "�������յ�ı�ţ�";
	cin >> end_place;

	if (start_place < 0 || start_place >= m_Graph.m_nVexNum || end_place < 0 || end_place >= m_Graph.m_nVexNum)
	{
		cout << "����������������룡����" << endl;
		return;
	}

	Edge aPath[20]; // ����Ϣ���飬���α�����̵�·��

	for (int i = 0; i < 20; i++)
	{
		// ��ʼ������Ϣ����
		aPath->vex1 = -1;
		aPath->vex2 = -1;
		aPath->weight = -1;
	}

	// �������·��
	int index = FindShortPath(start_place, end_place, aPath);
	int length = 0; // ���·���ܳ���
	Vex sVex = GetVex(aPath[0].vex1);

	// �õ����·������̾���
	cout << "\n���·��Ϊ��" << sVex.name;

	for (int i = 0; i < index; i++)
	{
		sVex = GetVex(aPath[i].vex2);
		cout << "->" << sVex.name;
		length += aPath[i].weight;
	}

	cout << endl;
	cout << "��̾���Ϊ:" << length << "��" << endl
		<< endl;
}


void DesignPath()
{
	cout << "��������������֮�������·";
	cout << "\n=======�����·�滮=======" << endl;

	Edge aPath[20];

	FindMinTree(aPath); // ������С��

	int nVexNum = m_Graph.m_nVexNum;

	if (nVexNum == 0)
	{
		cout << "���ȴ���ͼ��" << endl;
		return;
	}

	// ���������·ͼ
	int nAllLength = 0;

	for (int i = 0; i < m_Graph.m_nVexNum - 1; i++)
	{
		Vex nVex1 = GetVex(aPath[i].vex1);
		Vex nVex2 = GetVex(aPath[i].vex2);

		cout << "\t" << nVex1.name << "-" << nVex2.name << ":" << aPath[i].weight << "m" << endl;
		nAllLength += aPath[i].weight;
	}
	cout << "==========================\n";
	cout << "�����·���ܳ����ǣ�" << nAllLength << "m" << endl
		<< endl;
}
