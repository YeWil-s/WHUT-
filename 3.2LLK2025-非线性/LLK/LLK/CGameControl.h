#pragma once
#include"CGameLogic.h"

class CGameControl
{
public:
	CGraph gmgraph;
	CGameLogic gmLogic;

	Vertex m_svSelFst;
	Vertex m_svSelSec;

	CGameControl();
	bool StartGame();
	int GetElement(int row, int col);

	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[100], int& nVexnum);
	bool iswin();
	void ClearMap();
	bool getPrompt(Vertex avPath[100], int& nVexnum);
	void Resert();											// 调用函数，对数据成员m_graph中的数据进行重排
};

