#define _CRT_SECURE_NO_WARNINGS
#include"Tourism.h"
#include"Graph.h"
#include<iostream>
#include<cstring>
using namespace std;
extern CCgraph m_Graph;
//创建景区顶点
void CreateGraph(void) {
	Init();
	cout << "==== 创建景区管理图 ====" << endl;
	int num;
	FILE *InVex = fopen("D:\\Vex.txt.txt", "r");
	fscanf_s(InVex, "%d", &num);
	cout << "顶点数目：" << num << endl;
	cout << "----- 顶点 -----" << endl;
	for (int i = 0; i < num; i++) {
		Vex vex;
		fscanf_s(InVex, "%d", &(vex.num));
		fscanf(InVex, "%s", &(vex.name));
		fscanf(InVex, "%s", &(vex.desc));
		cout << vex.num << "-" << vex.name << endl;
		InsertVex(vex);
	}
	fclose(InVex);
	cout << "----- 边 -----" << endl;
	FILE *InEdge = fopen("D:\\Edge.txt.txt", "r");
	while (!feof(InEdge)) {
		Edge edge;
		fscanf_s(InEdge, "%d %d %d", &edge.vex1, &edge.vex2, &edge.weight);
		cout << "<v" << edge.vex1 << ",v" << edge.vex2 << ">" << edge.weight << endl;
		InsertEdge(edge);
	}fclose(InEdge);
}
//查询景点信息 直接查询
void GetSpotInfo(void)
{
	if (m_Graph.m_nVexNum == 0) {
		cout << "景区无信息 请首先创建景区信息" << endl;
		return;
	}
	cout << "===== 查询景点信息 =====" << endl;
	int i;
	for (i = 0; i < m_Graph.m_nVexNum; i++)
		cout << m_Graph.m_aVexs[i].num << "-" << m_Graph.m_aVexs[i].name << endl;
	cout << "请输入想要查询的景点编号：";
	int Num;
	cin >> Num;
	if (Num >= m_Graph.m_nVexNum) {
		cout << "编号输入错误 默认退出" << endl;
		return;
	}
	Vex vex = GetVex(Num);
	cout << vex.desc/*描述*/ << endl;
	cout << "----- 周围景区 ------" << endl;
	Edge aEdge[100];
	int sum_Edge = FindEdge(Num, aEdge);
	for (i = 0; i < sum_Edge; i++) {
		if (aEdge[i].weight != 32767) {
			cout << m_Graph.m_aVexs[aEdge[i].vex1].name << "->" <<
				m_Graph.m_aVexs[aEdge[i].vex2].name << " " << aEdge[i].weight << "m" << endl;
		}
	}
}
//导航
void TravelPath() {
	if (m_Graph.m_nVexNum == 0) {
		cout << "景区无信息 请首先创建景区信息" << endl;
		return;
	}
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		Vex svex = GetVex(i);
		cout << i << "-" << svex.name << endl;
	}
	cout << "请输入起始点编号： ";
	int Num;
	cin >> Num;
	if (Num < 0 || Num >= m_Graph.m_nVexNum) {
		cout << "您输入的编号错误，默认退出！" << endl;
		return;
	}
	cout << "导航路线为：" << endl;
	PathList pList = (PathList)malloc(sizeof( Path));
	PathList Head = pList;
	//调用DFSTraverse函数
	DFSTraverse(Num, pList);
	pList = Head;
	int j = 1;
	while (pList->next != NULL) {
		cout << "路线" << j << "：";
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
	cout << "\n======搜索最短路径======\n";

	int nVexNum = m_Graph.m_nVexNum;

	if (nVexNum == 0)
	{
		cout << "请先创建图！" << endl;
		return;
	}

	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << "*\t" << i << "-" << sVex.name << "\t\t*" << endl;
	}
	cout << "========================\n";

	// 输入两个景点的编号
	int start_place, end_place;
	cout << "请输入起点的编号：";
	cin >> start_place;
	cout << "请输入终点的编号：";
	cin >> end_place;

	if (start_place < 0 || start_place >= m_Graph.m_nVexNum || end_place < 0 || end_place >= m_Graph.m_nVexNum)
	{
		cout << "输入错误！请重新输入！！！" << endl;
		return;
	}

	Edge aPath[20]; // 边信息数组，依次保存最短的路径

	for (int i = 0; i < 20; i++)
	{
		// 初始化边信息数组
		aPath->vex1 = -1;
		aPath->vex2 = -1;
		aPath->weight = -1;
	}

	// 搜索最短路径
	int index = FindShortPath(start_place, end_place, aPath);
	int length = 0; // 最短路径总长度
	Vex sVex = GetVex(aPath[0].vex1);

	// 得到最短路径和最短距离
	cout << "\n最短路径为：" << sVex.name;

	for (int i = 0; i < index; i++)
	{
		sVex = GetVex(aPath[i].vex2);
		cout << "->" << sVex.name;
		length += aPath[i].weight;
	}

	cout << endl;
	cout << "最短距离为:" << length << "米" << endl
		<< endl;
}


void DesignPath()
{
	cout << "在以下两个景点之间铺设电路";
	cout << "\n=======铺设电路规划=======" << endl;

	Edge aPath[20];

	FindMinTree(aPath); // 构建最小树

	int nVexNum = m_Graph.m_nVexNum;

	if (nVexNum == 0)
	{
		cout << "请先创建图！" << endl;
		return;
	}

	// 输出铺设线路图
	int nAllLength = 0;

	for (int i = 0; i < m_Graph.m_nVexNum - 1; i++)
	{
		Vex nVex1 = GetVex(aPath[i].vex1);
		Vex nVex2 = GetVex(aPath[i].vex2);

		cout << "\t" << nVex1.name << "-" << nVex2.name << ":" << aPath[i].weight << "m" << endl;
		nAllLength += aPath[i].weight;
	}
	cout << "==========================\n";
	cout << "铺设电路的总长度是：" << nAllLength << "m" << endl
		<< endl;
}
