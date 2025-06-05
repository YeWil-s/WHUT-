#pragma once  
#include "ParamSetting.h" 
#include"global.h"
#include"CGraph.h"
#include <stack>  
using namespace std; 

class CGameLogic  
{  
public:  
	int rows;  //��
	int cols;  //��
	int picNum;  //ͼƬ����

	CGameLogic();
	void InitMap(CGraph& g);
	void UpdateArc(CGraph& g, int row, int col);//����ĳһ������Ļ���Ϣ

	void Clear(CGraph& g, Vertex V1, Vertex V2);
	bool IsLink(CGraph& g, Vertex V1, Vertex V2);
	bool SearchPath(CGraph& g, int nV0, int nV1);//	��Ѱ·��
	void PushVertex(int nV);//���һ��·������
	void PopVertex();//	ȡ��һ������
	bool IsExsit(int nVi);//�ж϶����Ƿ�����·���д���
	bool IsCornor(void);//	�жϹյ����Ч��
	int* getApath(int &num);
	bool IsBlank(CGraph& g);
	void ClearMap(CGraph& g);
	void ClearApath();
	bool getPrompt(CGraph& g);
	void Resert(CGraph& g);
private:  
	int m_anPath[100];
	int m_nVexNum;
	int m_nCorner;
};
