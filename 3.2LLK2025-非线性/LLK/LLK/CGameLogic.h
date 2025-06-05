#pragma once  
#include "ParamSetting.h" 
#include"global.h"
#include"CGraph.h"
#include <stack>  
using namespace std; 

class CGameLogic  
{  
public:  
	int rows;  //行
	int cols;  //列
	int picNum;  //图片数量

	CGameLogic();
	void InitMap(CGraph& g);
	void UpdateArc(CGraph& g, int row, int col);//更新某一个顶点的弧信息

	void Clear(CGraph& g, Vertex V1, Vertex V2);
	bool IsLink(CGraph& g, Vertex V1, Vertex V2);
	bool SearchPath(CGraph& g, int nV0, int nV1);//	搜寻路径
	void PushVertex(int nV);//添加一个路径顶点
	void PopVertex();//	取出一个顶点
	bool IsExsit(int nVi);//判断顶点是否已在路径中存在
	bool IsCornor(void);//	判断拐点的有效性
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
