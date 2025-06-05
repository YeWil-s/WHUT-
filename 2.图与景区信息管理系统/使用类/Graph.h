#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#define OK 1;
#define INF INT32_MAX
#include<iostream>

class Graph
{
public:
	typedef struct Vex {
		int num;
		char name[20];
		char desc[1024];
	}v;

	typedef struct Edge {
		int v1;
		int v2;
		int len;
	}e;

	typedef struct Path {
		int vexs[20];  //保存一条路径
		Path* next;  //下一条路径
	}*PathList;
	/*构造函数*/
	Graph() {
		Init();
	}
	/*获得图信息*/
	int get_adjMartix(int i, int j) {
		return  m_AdjMartix[i][j];
	}
	/*获取顶点信息*/
	Vex get_vex(int i) {
		return m_aVexs[i];
	}
	/*获取顶点数目*/
	int get_vexNum() {
		return m_nVexNum;
	}

	void Init();
	int InsertVex(Vex sVex);// 将顶点添加到顶点数组中。
	int InsertEdge(Edge sEdge);// 将边保存到邻接矩阵中。
	Vex GetVex(int nVex) const;// 查询指定顶点信息。
	int FindEdge(int nVex, Edge aEdge[]) const;// 查询与指定顶点相连的边。
	int GetVexnum(void) const;// 获取当前顶点数
	void DFS(int nVex, bool bVisted[], int& nIndex, PathList& pList);//深度遍历
	void DFSTraverse(int nVex, PathList& pList);//调用dfs
	int FindShortPath_D(int nVexStart, int nVexEnd, Edge aPath[]) const;//dijistra找最短路径
	int FindMinTree(Edge aPath[]) const;//最小生成树

private:
	int m_AdjMartix[20][20];//边
	Vex m_aVexs[20];//顶点
	int m_nVexNum;//顶点个数
};

#endif // !GRAPH_H