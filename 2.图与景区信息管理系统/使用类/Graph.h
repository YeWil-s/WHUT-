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
		int vexs[20];  //����һ��·��
		Path* next;  //��һ��·��
	}*PathList;
	/*���캯��*/
	Graph() {
		Init();
	}
	/*���ͼ��Ϣ*/
	int get_adjMartix(int i, int j) {
		return  m_AdjMartix[i][j];
	}
	/*��ȡ������Ϣ*/
	Vex get_vex(int i) {
		return m_aVexs[i];
	}
	/*��ȡ������Ŀ*/
	int get_vexNum() {
		return m_nVexNum;
	}

	void Init();
	int InsertVex(Vex sVex);// ��������ӵ����������С�
	int InsertEdge(Edge sEdge);// ���߱��浽�ڽӾ����С�
	Vex GetVex(int nVex) const;// ��ѯָ��������Ϣ��
	int FindEdge(int nVex, Edge aEdge[]) const;// ��ѯ��ָ�����������ıߡ�
	int GetVexnum(void) const;// ��ȡ��ǰ������
	void DFS(int nVex, bool bVisted[], int& nIndex, PathList& pList);//��ȱ���
	void DFSTraverse(int nVex, PathList& pList);//����dfs
	int FindShortPath_D(int nVexStart, int nVexEnd, Edge aPath[]) const;//dijistra�����·��
	int FindMinTree(Edge aPath[]) const;//��С������

private:
	int m_AdjMartix[20][20];//��
	Vex m_aVexs[20];//����
	int m_nVexNum;//�������
};

#endif // !GRAPH_H