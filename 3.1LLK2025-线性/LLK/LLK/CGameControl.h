#pragma once
#include"CGameLogic.h"

class CGameControl
{
public:
	Vertex selfirst;
	Vertex selfsecond;
	CGameLogic m_GameLogic;
	Vertex helpFirst;   //提示的第一个点
	Vertex helpSecond;  //提示的第二个点

	CGameControl();
	int GetElement(int row, int col);
	bool StartGame(int row, int col, int picnum);

	void SetFirstPoint(int nrow, int ncol);
	void SetSecondPoint(int nrow, int ncol);

	bool Link(stack<Vertex>& verList);
	bool iswin();

	void SetFirstHelpPoint(int nRow, int nCol);
	void SetSecondHelpPoint(int nRow, int nCol);
	bool GetPrompt(stack<Vertex>& verList);
	void ResetMap();
	void ClearMap();
};

