#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Tourism.h"
#include"Graph.h"

using namespace std;

int main(void) {
	int choice;
	while (true) {
		cout << "==== ������Ϣ����ϵͳ ====" << endl;
		cout << "1.������������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "0.�˳�" << endl;
		cout << "�����������ţ�0~5����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			CreateGraph();
			system("pause");
			break;
		case 2:
			system("cls");
			GetSpotInfo();
			system("pause");
			break;
		case 3:
			system("cls");
			TravelPath();
			system("pause");
			break;
		case 4:
			system("cls");
			FindShortPath();
			system("pause");
			break;
		case 5:
			system("cls");
			DesignPath();
			system("pause");
			break;
		case 0:
			cout << "�˳�ϵͳ" << endl;
			exit(0);
			break;
		default:
			cout << "��������� Ĭ���˳�ϵͳ" << endl;
			exit(0);
			break;
		}
	}
}