#pragma warning( disable : 4996)
#include "Graph.h";
#include "Tourism.h";
#include<iostream>
#include<cstdint>
using namespace std;
Graph::Edge aEdge[100];
Graph gra;
#define INF INT32_MAX
extern bool ALREADY_PREPARED;

void Tourism::login()
{
	int c;
	while (true)
	{
		cout << "----------������Ϣ����ϵͳ----------" << endl;
		cout << "1.������������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "0.�˳�" << endl;
		cout << "�����������ţ�";
		cin >> c;
		switch (c)
		{
			//������������ͼ
		case 1:
		{
			CreateGraph();
			system("pause");
			break;
		}
		//��ѯ������Ϣ
		case 2:
		{
			if (!ALREADY_PREPARED) {
				cout << "û��ͼ����Ϣ�����ȳ�ʼ��ͼ" << endl;
				system("pause");
				continue;
			}
			GetSpotInfo();
			system("pause");
			break;
		}
		//���ξ��㵼��
		case 3:
		{
			if (!ALREADY_PREPARED) {
				cout << "û��ͼ����Ϣ�����ȳ�ʼ��ͼ" << endl;
				system("pause");
				continue;
			}
			TravelPath();
			system("pause");
			break;
		}
		//�������·��
		case 4:
		{
			if (!ALREADY_PREPARED) {
				cout << "û��ͼ����Ϣ�����ȳ�ʼ��ͼ" << endl;
				system("pause");
				continue;
			}
			FindShortPath();
			system("pause");
			break;
		}
		//�����·�滮
		case 5:
		{
			if (!ALREADY_PREPARED) {
				cout << "û��ͼ����Ϣ�����ȳ�ʼ��ͼ" << endl;
				system("pause");
				continue;
			}
			DesignPath();
			system("pause");
			break;
		}
		//�˳�ϵͳ
		case 0:
		{
			cout << "�˳�ϵͳ!" << endl;
			exit(0);
		}
		default:
		{
			cout << "��������ȷ������� ";
			system("pause");
			break;
		}
		}
	}
}

void Tourism::CreateGraph()
{
	if (ALREADY_PREPARED)
	{
		cout << "�Ѿ���ʼ����ͼ�������ظ�����" << endl;
		return;
	}
	FILE* in = fopen("Vex.txt", "r");
	if (!in) {
		cout << "�޷����ļ� Vex.txt " << endl;
		return;
	}
	Graph::Vex v;
	int n;
	if (fscanf(in, "%d", &n) == EOF)
	{
		cout << "��ȡnʧ��" << endl;
		return;
	}
	gra.Init();
	cout << " --------------- ������������ͼ ---------------  " << endl;
	cout << "������Ŀ��" << n << endl;
	cout << "----- ���� -----" << endl;
	for (int i = 0;i < n;i++)
	{
		if (fscanf(in, "%d", &v.num) == EOF)
		{
			cout << "��ȡnumʧ��" << endl;
			return;
		}
		if (fscanf(in, "%s", &v.name) == EOF)
		{
			cout << "��ȡnameʧ��" << endl;
			return;
		}
		if (fscanf(in, "%s", &v.desc) == EOF)
		{
			cout << "��ȡdescʧ��" << endl;
			return;
		}
		cout << v.num << "-" << v.name << endl;
		gra.InsertVex(v);
	}
	fclose(in);
	in = fopen("Edge.txt", "r");
	if (!in) {
		cout << "�޷����ļ� Edge.txt " << endl;
		return;
	}
	Graph::Edge e;
	cout << "----- �� -----" << endl;
	int EdgeNum = 0;
	while (!feof(in))
	{
		if (fscanf(in, "%d", &e.v1) == EOF)
		{
			cout << "��ȡv1ʧ��" << endl;
			return;
		}
		if (fscanf(in, "%d", &e.v2) == EOF)
		{
			cout << "��ȡv2ʧ��" << endl;
			return;
		}
		if (fscanf(in, "%d", &e.len) == EOF)
		{
			cout << "��ȡ�߳�ʧ��" << endl;
			return;
		}
		printf("<v%d,v%d> %dm\n", e.v1, e.v2, e.len);
		gra.InsertEdge(e);
		aEdge[EdgeNum++] = e;
	}
	fclose(in);
	ALREADY_PREPARED = true;
}

void Tourism::GetSpotInfo()
{
	Graph::Edge e[20];
	cout << "---------------  ��ѯ������Ϣ --------------- " << endl;
	for (int i = 0;i < gra.GetVexnum();i++)
	{
		cout << gra.GetVex(i).num << "-" << gra.GetVex(i).name << endl;
	}
	int n;
	cout << "������Ҫ��ѯ�ľ�����: ";
	cin >> n;
	Graph::Vex v = gra.GetVex(n);
	printf("%s\n%s\n", v.name, v.desc);
	cout << "----- �ܱ߾��� -----" << endl;
	int k = gra.FindEdge(n, e);
	for (int i = 0;i < k;i++)
	{
		cout << v.name << "->" << gra.GetVex(e[i].v2).name << " " << e[i].len << "m" << endl;
	}
	cout << endl;
}

void Tourism::TravelPath()
{
	Graph::PathList plist, phead;
	plist = (Graph::Path*)malloc(sizeof(Graph::Path));
	phead = plist;
	cout << "--------------- ���ξ��㵼�� -------------- " << endl;
	cout << "��������ʼ���ţ�";
	int nVex;
	cin >> nVex;
	gra.DFSTraverse(nVex, plist);/*���ú���Ѱ��·��*/
	cout << "����·��Ϊ��" << endl;
	plist = phead;
	int i = 1;
	while (plist->next)
	{
		Graph::Vex sVex =gra.GetVex(plist->vexs[0]);
		cout << "·��" << i++ << ":" << sVex.name;
		for (int j = 1; j < gra.GetVexnum(); j++)
		{
			cout << " -> " << gra.GetVex(plist->vexs[j]).name;
		}
		cout << endl;
		Graph::Path* temp = plist;
		plist = plist->next;
		free(temp);
	}
	cout << "----------------finish------------------" << endl;
	free(plist);
	plist = NULL;
	phead = NULL;
}

void Tourism::FindShortPath()
{
	cout << "--------------- �������·�� --------------- " << endl;
	for (int i = 0;i < gra.GetVexnum();i++)
	{
		cout << gra.GetVex(i).num << "-" << gra.GetVex(i).name << endl;
	}
	int start = 0;
	int end = 0;
	while (true)
	{
		cout << "���������ı��: ";
		cin >> start;
		cout << "�������յ�ı��: ";
		cin >> end;
		if (start >= 0 && start < gra.GetVexnum() && end >= 0 && end < gra.GetVexnum())
		{
			break;
		}
		cout << "�����ţ��������룡" << endl;
	}
	
	Graph::Edge aPath[20];
	int num = gra.FindShortPath_D(start, end, aPath);
	Graph::Vex sVex = gra.GetVex(aPath[0].v1);
	int len = 0;
	cout << "���·��Ϊ: ";
	cout << gra.GetVex(start).name;
	for (int i = 0; i < num; i++)
	{
		sVex = gra.GetVex(aPath[i].v2);
		cout << "->" << sVex.name;
		len += aPath[i].len;
	}
	cout << endl;
	cout << "��̾���Ϊ�� " << len << "m" << endl;
	cout << endl << endl;

}

void Tourism::DesignPath()
{
	cout << "--------------- �����·�滮 --------------- " << endl;
	cout << "��������������֮�������·��" << endl;
	int len = 0;
	Graph::Edge aPath[20];
	len = gra.FindMinTree(aPath);
	for (int i = 0; i < gra.GetVexnum() - 1; i++) {
		cout << gra.GetVex(aPath[i].v1).name << " - " << gra.GetVex(aPath[i].v2).name << "\t" << aPath[i].len << "m" << endl;
	}
	cout << "�����·���ܳ���Ϊ��" << len << "m";
	cout << endl << endl << endl;
}