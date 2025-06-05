#include "pch.h"
#include "CGameLogic.h"
#include <Windows.h> 

CGameLogic::~CGameLogic()
{
	if (GameMap != NULL)
	{
		for (int i = 0;i < rows;i++)
		{
			delete[] GameMap[i];
		}
		delete[]GameMap;
	}
	
}

int CGameLogic::GetElement(int nrow, int ncol)
{
	return GameMap[nrow][ncol];
}

void CGameLogic::InitMap(int nrow, int ncol, int npic)
{
	/*INI*/
	this->GameMap = new int* [nrow];
	for (int i = 0;i < nrow;i++)
	{
		GameMap[i] = new int[ncol];
	}

	int nReapeatNum = (nrow * ncol) / npic;
	int ncount = 0;
	for (int i = 0;i < npic;i++)
	{
		for (int j = 0;j < nReapeatNum;j++)
		{
			GameMap[ncount / ncol][ncount % ncol] = i;
			ncount++;
		}
	}
    //打乱图片
	srand((int)time(NULL));
	int nvexNum = nrow * ncol;
	for (int i = 0;i < nvexNum;i++)
	{
		int nIndex1 = rand() % nvexNum;
		int nIndex2 = rand() % nvexNum;
		int nTmp = GameMap[nIndex1 / ncol][nIndex1 % ncol];
		GameMap[nIndex1 / ncol][nIndex1 % ncol] = GameMap[nIndex2 / ncol][nIndex2 % ncol];
		GameMap[nIndex2 / ncol][nIndex2 % ncol] = nTmp;
	}
}

bool CGameLogic::LinkX(int row, int col1, int col2)
{
	if (col1 > col2)
	{
		int temp = col1;
		col1 = col2;
		col2 = temp;
	}
	for (int i = col1 + 1;i <= col2;i++)
	{
		if (i == col2)return true;
		if (GameMap[row][i] != BLANK)return false;
	}
	return false;
}

bool CGameLogic::LinkY(int row1, int row2, int col)
{
	if (row1 > row2)
	{
		int temp = row1;
		row1 = row2;
		row2 = temp;
	}
	for (int i = row1 + 1;i <= row2;i++)
	{
		if (i == row2)return true;
		if (GameMap[i][col] != BLANK)return false;
	}
	return false;
}

bool CGameLogic::LinkInRow(Vertex v1, Vertex v2)
{
	int row = v1.row;
	int col1 = v1.col;
	int col2 = v2.col;
	return LinkX(row, col1, col2);
}

bool CGameLogic::LinkInCol(Vertex v1, Vertex v2)
{
	int row1 = v1.row;
	int row2 = v2.row;
	int col = v1.col;
	return LinkY(row1, row2, col);
}

bool CGameLogic::LinkOneCorner(Vertex v1, Vertex v2)
{
	if (GameMap[v1.row][v2.col] == BLANK)
	{
		if (LinkX(v1.row, v1.col, v2.col) && LinkY(v1.row, v2.row, v2.col))
		{
			Vertex v = { v1.row,v2.col,BLANK };
			verList.push(v);
			return true;
		}
	}
	if (GameMap[v2.row][v1.col] == BLANK)
	{
		if (LinkX(v2.row, v1.col, v2.col) && LinkY(v1.row, v2.row, v1.col))
		{
			Vertex v = { v2.row,v1.col,BLANK };
			verList.push(v);
			return true;
		}
	}
	return false;
}

bool CGameLogic::LinkTwoCorner(Vertex v1, Vertex v2)
{
	for (int ncol = 0;ncol < ParamSetting::Cols;ncol++)
	{
		if (GameMap[v1.row][ncol] == BLANK && GameMap[v2.row][ncol] == BLANK)
		{
			if (LinkY(v1.row, v2.row, ncol))
			{
				if (LinkX(v1.row, v1.col, ncol) && LinkX(v2.row, v2.col, ncol))
				{
					Vertex vx1 = { v1.row,ncol,BLANK };
					Vertex vx2 = { v2.row,ncol,BLANK };
					verList.push(vx1);
					verList.push(vx2);
					return true;
				}
			}
		}
	}
	for (int nRow = 0; nRow < ParamSetting::Rows; nRow++)
	{
		if (GameMap[nRow][v1.col] == BLANK && GameMap[nRow][v2.col] == BLANK)
		{
			if (LinkX(nRow, v1.col, v2.col))
			{
				if (LinkY(nRow, v1.row, v1.col) && LinkY(nRow, v2.row, v2.col))
				{
					Vertex vx1 = { nRow,v1.col,BLANK };
					Vertex vx2 = { nRow,v2.col,BLANK };
					verList.push(vx1);
					verList.push(vx2);
					return true;
				}
			}
		}
	}
	return false;
}

bool CGameLogic::IsLink(Vertex v1, Vertex v2)
{
	if (v1.row == v2.row && v1.col == v2.col)
	{
		return false;
	}
	if (GetElement(v1.row, v1.col) != GetElement(v2.row, v2.col))
	{
		return false;
	}
	ClearVerList();
	verList.push(v1);

	if (v1.row == v2.row)
	{
		if (LinkInRow(v1, v2))
		{
			verList.push(v2);
			return true;

		}
		else if (v1.row == 0)
		{
			verList.push({ v1.row - 1, v1.col, 0 });
			verList.push({ v2.row - 1, v2.col, 0 });
			verList.push(v2);
			return true;
		}
		else if (v1.row == ParamSetting::Rows - 1)
		{
			verList.push({ v1.row + 1, v1.col, 0 });
			verList.push({ v2.row + 1, v2.col, 0 });
			verList.push(v2);
			return true;
		}
	}

	if (v1.col == v2.col)
	{
		if (LinkInCol(v1, v2))
		{
			verList.push(v2);
			return true;

		}
		else if (v1.col == 0)
		{
			verList.push({ v1.row , v1.col - 1, 0 });
			verList.push({ v2.row , v2.col - 1, 0 });
			verList.push(v2);
			return true;
		}
		else if (v1.col == ParamSetting::Cols - 1)
		{
			verList.push({ v1.row , v1.col + 1, 0 });
			verList.push({ v2.row , v2.col + 1, 0 });
			verList.push(v2);
			return true;
		}
	}
	if (LinkOneCorner(v1, v2))
	{
		verList.push(v2);
		return true;
	}
	if (LinkTwoCorner(v1, v2))
	{
		verList.push(v2);
		return true;
	}
	return false;
}

void CGameLogic::clear(Vertex v1, Vertex v2)
{
	GameMap[v1.row][v1.col] = BLANK;
	GameMap[v2.row][v2.col] = BLANK;
}

bool CGameLogic::isBlank()
{
	for (int i = 0;i < ParamSetting::Rows;i++)
	{
		for (int j = 0;j < ParamSetting::Cols;j++)
		{
			if (GameMap[i][j] != BLANK)return false;
		}
	}
	return true;
}

stack<Vertex> CGameLogic::GetVerList()
{
	stack<Vertex> copyList = verList;
	return copyList;
}

void CGameLogic::ClearVerList()
{
	stack<Vertex>().swap(verList);
}

bool CGameLogic::GetPrompt(Vertex& V1, Vertex& V2)
{
   for (int row1 = 0; row1 < rows; row1++)
   {
       for (int col1 = 0; col1 < cols; col1++)
       {
           int nFirstElem = GetElement(row1, col1);
		   if (nFirstElem == BLANK)
		   {
			 continue;
		   }
		  
           //设置第一个节点
           V1.row = row1; V1.col = col1; V1.info = nFirstElem;
           for (int row2 = row1; row2 < rows; row2++)
           {
               //取第二点的初始col，如果同行，则从 col1+1位置开始，即下一个元素
               //如果不同行，则从头开始查找，即col为0
               int col = row2 == row1 ? col1 + 1 : 0;
               for (int col2 = col; col2 < cols; col2++)
               {
                   int nSecondElem = GetElement(row2, col2);
                   if (nSecondElem == BLANK) continue;
                   //设置第二个节点
                   V2.row = row2; V2.col = col2; V2.info = nSecondElem;
                   if (IsLink(V1, V2)) {
                       return true;
                   }
               }
           }
       }
   }
   MessageBox(NULL, L"LOGIC::GetPrompt FALSE", L"Prompt", MB_OK);
   return false;
}

void CGameLogic::ResetMap()
{
	//将图片随机打散
	srand((int)time(NULL));
	int nVertexNum = rows * cols;
	for (int i = 0; i < nVertexNum; i++)
	{
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		//两个下表交换
		int nTmp = GameMap[nIndex1 / cols][nIndex1 % cols];
		GameMap[nIndex1 / cols][nIndex1 % cols] = GameMap[nIndex2 / cols][nIndex2 % cols];
		GameMap[nIndex2 / cols][nIndex2 % cols] = nTmp;
	}
}

void CGameLogic::ClearMap()
{
	for (int i = 0; i < ParamSetting::Rows; i++)
	{
		for (int j = 0; j < ParamSetting::Cols; j++)
		{
			GameMap[i][j] = BLANK;
		}
	}
}

void CGameLogic::saveVerList(Vertex v1, Vertex v2)
{
	verList.push(v1);
	verList.push(v2);
}