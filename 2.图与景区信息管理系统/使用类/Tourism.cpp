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
		cout << "----------景区信息管理系统----------" << endl;
		cout << "1.创建景区景点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;
		cout << "请输入操作序号：";
		cin >> c;
		switch (c)
		{
			//创建景区景点图
		case 1:
		{
			CreateGraph();
			system("pause");
			break;
		}
		//查询景点信息
		case 2:
		{
			if (!ALREADY_PREPARED) {
				cout << "没有图的信息，请先初始化图" << endl;
				system("pause");
				continue;
			}
			GetSpotInfo();
			system("pause");
			break;
		}
		//旅游景点导航
		case 3:
		{
			if (!ALREADY_PREPARED) {
				cout << "没有图的信息，请先初始化图" << endl;
				system("pause");
				continue;
			}
			TravelPath();
			system("pause");
			break;
		}
		//搜索最短路径
		case 4:
		{
			if (!ALREADY_PREPARED) {
				cout << "没有图的信息，请先初始化图" << endl;
				system("pause");
				continue;
			}
			FindShortPath();
			system("pause");
			break;
		}
		//铺设电路规划
		case 5:
		{
			if (!ALREADY_PREPARED) {
				cout << "没有图的信息，请先初始化图" << endl;
				system("pause");
				continue;
			}
			DesignPath();
			system("pause");
			break;
		}
		//退出系统
		case 0:
		{
			cout << "退出系统!" << endl;
			exit(0);
		}
		default:
		{
			cout << "请输入正确操作编号 ";
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
		cout << "已经初始化过图，请勿重复构建" << endl;
		return;
	}
	FILE* in = fopen("Vex.txt", "r");
	if (!in) {
		cout << "无法打开文件 Vex.txt " << endl;
		return;
	}
	Graph::Vex v;
	int n;
	if (fscanf(in, "%d", &n) == EOF)
	{
		cout << "读取n失败" << endl;
		return;
	}
	gra.Init();
	cout << " --------------- 创建景区景点图 ---------------  " << endl;
	cout << "顶点数目：" << n << endl;
	cout << "----- 顶点 -----" << endl;
	for (int i = 0;i < n;i++)
	{
		if (fscanf(in, "%d", &v.num) == EOF)
		{
			cout << "读取num失败" << endl;
			return;
		}
		if (fscanf(in, "%s", &v.name) == EOF)
		{
			cout << "读取name失败" << endl;
			return;
		}
		if (fscanf(in, "%s", &v.desc) == EOF)
		{
			cout << "读取desc失败" << endl;
			return;
		}
		cout << v.num << "-" << v.name << endl;
		gra.InsertVex(v);
	}
	fclose(in);
	in = fopen("Edge.txt", "r");
	if (!in) {
		cout << "无法打开文件 Edge.txt " << endl;
		return;
	}
	Graph::Edge e;
	cout << "----- 边 -----" << endl;
	int EdgeNum = 0;
	while (!feof(in))
	{
		if (fscanf(in, "%d", &e.v1) == EOF)
		{
			cout << "读取v1失败" << endl;
			return;
		}
		if (fscanf(in, "%d", &e.v2) == EOF)
		{
			cout << "读取v2失败" << endl;
			return;
		}
		if (fscanf(in, "%d", &e.len) == EOF)
		{
			cout << "读取边长失败" << endl;
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
	cout << "---------------  查询景点信息 --------------- " << endl;
	for (int i = 0;i < gra.GetVexnum();i++)
	{
		cout << gra.GetVex(i).num << "-" << gra.GetVex(i).name << endl;
	}
	int n;
	cout << "输入想要查询的景点编号: ";
	cin >> n;
	Graph::Vex v = gra.GetVex(n);
	printf("%s\n%s\n", v.name, v.desc);
	cout << "----- 周边景区 -----" << endl;
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
	cout << "--------------- 旅游景点导航 -------------- " << endl;
	cout << "请输入起始点编号：";
	int nVex;
	cin >> nVex;
	gra.DFSTraverse(nVex, plist);/*调用函数寻找路径*/
	cout << "导航路线为：" << endl;
	plist = phead;
	int i = 1;
	while (plist->next)
	{
		Graph::Vex sVex =gra.GetVex(plist->vexs[0]);
		cout << "路线" << i++ << ":" << sVex.name;
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
	cout << "--------------- 搜索最短路径 --------------- " << endl;
	for (int i = 0;i < gra.GetVexnum();i++)
	{
		cout << gra.GetVex(i).num << "-" << gra.GetVex(i).name << endl;
	}
	int start = 0;
	int end = 0;
	while (true)
	{
		cout << "请输入起点的编号: ";
		cin >> start;
		cout << "请输入终点的编号: ";
		cin >> end;
		if (start >= 0 && start < gra.GetVexnum() && end >= 0 && end < gra.GetVexnum())
		{
			break;
		}
		cout << "错误编号，重新输入！" << endl;
	}
	
	Graph::Edge aPath[20];
	int num = gra.FindShortPath_D(start, end, aPath);
	Graph::Vex sVex = gra.GetVex(aPath[0].v1);
	int len = 0;
	cout << "最短路线为: ";
	cout << gra.GetVex(start).name;
	for (int i = 0; i < num; i++)
	{
		sVex = gra.GetVex(aPath[i].v2);
		cout << "->" << sVex.name;
		len += aPath[i].len;
	}
	cout << endl;
	cout << "最短距离为： " << len << "m" << endl;
	cout << endl << endl;

}

void Tourism::DesignPath()
{
	cout << "--------------- 铺设电路规划 --------------- " << endl;
	cout << "在以下两个景点之间铺设电路：" << endl;
	int len = 0;
	Graph::Edge aPath[20];
	len = gra.FindMinTree(aPath);
	for (int i = 0; i < gra.GetVexnum() - 1; i++) {
		cout << gra.GetVex(aPath[i].v1).name << " - " << gra.GetVex(aPath[i].v2).name << "\t" << aPath[i].len << "m" << endl;
	}
	cout << "铺设电路的总长度为：" << len << "m";
	cout << endl << endl << endl;
}