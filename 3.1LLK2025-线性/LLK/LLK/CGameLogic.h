#pragma once  
#include "ParamSetting.h" 
#include"global.h"
#include <stack>  
using namespace std; 

class CGameLogic  
{  
public:  
   int** GameMap;    // 地图  
   int rows;  //行
   int cols;  //列
   int picNum;  //图片数量


private:  
   stack<Vertex> verList;  //保存图片相连路径

public:
	~CGameLogic();
	int GetElement(int nrow, int ncol);	
	void saveVerList(Vertex v1, Vertex v2);
	stack<Vertex> GetVerList();
	void InitMap(int nrow, int ncol, int npic);
	bool IsLink(Vertex v1, Vertex v2);
	void clear(Vertex v1, Vertex v2);
	void ClearVerList();
	bool GetPrompt(Vertex& V1, Vertex& V2);
	bool isBlank();
	void ResetMap();
	void ClearMap();

private:
	bool LinkInRow(Vertex v1, Vertex v2);
	bool LinkInCol(Vertex v1, Vertex v2);
	bool LinkOneCorner(Vertex v1, Vertex v2);
	bool LinkTwoCorner(Vertex v1, Vertex v2);
	bool LinkY(int row1, int row2, int col);
	bool LinkX(int row, int col1, int col2);
};
