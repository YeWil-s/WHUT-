#include "pch.h"
#include "CGameLogic.h"
#include <Windows.h> 

CGameLogic::CGameLogic()
{
	rows = ParamSetting::Rows;
	cols = ParamSetting::Cols;
	picNum = ParamSetting::PicNum;
}

void CGameLogic::InitMap(CGraph& g)
{
	// 获取地图大小和花色
	int nRows = ParamSetting::Rows;
	int nCols = ParamSetting::Cols;
	int nPicNum = ParamSetting::PicNum;
	// 开辟内存区域
	int* pGameMap = new int[nRows * nCols];
    //花色
	if ((nRows * nCols) % (nPicNum * 2) != 0)
	{
		delete[]pGameMap;
	}
	int nRepeatNum = nRows * nCols / nPicNum;
	int nCount = 0;
	for (int i = 0; i < nPicNum; i++)
	{
		for (int j = 0; j < nRepeatNum; j++)
		{
			pGameMap[nCount++] = i;
		}
	}
	//设置种子
	srand((int)time(NULL));
	//随机任意交换两个数字
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++)
	{
		// 随机得到两个坐标
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		// 交换两个数值
		int nTmp = pGameMap[nIndex1];
		pGameMap[nIndex1] = pGameMap[nIndex2];
		pGameMap[nIndex2] = nTmp;
	}
	//INI-Vex
	for (int i = 0; i < nVertexNum; i++)
	{
		g.Add_v(pGameMap[i]);
	}
	//INI-Edge
	for (int i = 0;i < nVertexNum;i++)
	{
		for (int j = 0;j < nVertexNum;j++)
		{
			UpdateArc(g, i, j);
		}
	}
	delete[]pGameMap;
}

void CGameLogic::UpdateArc(CGraph& g, int row, int col)
{
	int nRows = ParamSetting::Rows; 
	int nCols = ParamSetting::Cols;
	int nV1Index = row * nCols + col;
	if (col > 0)  //与左边的相连通
	{
		int nV2Index = nV1Index - 1;
		if (g.Get_v(nV2Index) == g.Get_v(nV1Index) || g.Get_v(nV1Index) == BLANK || g.Get_v(nV2Index) == BLANK)
		{
			g.Add_e(nV1Index, nV2Index);
		}
	}
	if (col < nCols - 1)  //与右的相连通
	{
		int nV2Index = nV1Index + 1;
		if (g.Get_v(nV2Index) == g.Get_v(nV1Index) || g.Get_v(nV1Index) == BLANK || g.Get_v(nV2Index) == BLANK)
		{
			g.Add_e(nV1Index, nV2Index);
		}
	}
	if (row > 0)  //与正上方的相连通
	{
		int nV2Index = nV1Index - nCols;
		if (g.Get_v(nV2Index) == g.Get_v(nV1Index) || g.Get_v(nV1Index) == BLANK || g.Get_v(nV2Index) == BLANK)
		{
			g.Add_e(nV1Index, nV2Index);
		}
	}
	if (row < nRows - 1)  //与正下方的相连通
	{
		int nV2Index = nV1Index + nCols;
		if (g.Get_v(nV2Index) == g.Get_v(nV1Index) || g.Get_v(nV1Index) == BLANK || g.Get_v(nV2Index) == BLANK)
		{
			g.Add_e(nV1Index, nV2Index);
		}
	}
}

void CGameLogic::Clear(CGraph& g, Vertex V1, Vertex V2)
{
	int v1 = V1.row * ParamSetting::Cols + V1.col;
	int v2 = V2.row * ParamSetting::Cols + V2.col;

	g.UpdateVertex(v1, BLANK);
	g.UpdateVertex(v2, BLANK);

	UpdateArc(g, V1.row, V1.col);
	UpdateArc(g, V2.row, V2.col);
}

//判断是否连通
bool CGameLogic::IsLink(CGraph& g, Vertex V1, Vertex V2)
{	
	ClearApath();
	int v1 = V1.row * ParamSetting::Cols + V1.col;
	int v2 = V2.row * ParamSetting::Cols + V2.col;
	// 压入第一个点
	PushVertex(v1);  // 调用PushVertex函数将第一个点索引添加到路径数组

	// 搜寻两点之间的路径
	if (SearchPath(g, v1, v2)) 
	{
		return true;
	}
	// 取出压入的顶点
	PopVertex();  // 调用PopVertex函数从路径数组中取出第一个点的索引

	return false;
}

bool CGameLogic::SearchPath(CGraph& g, int nV0, int nV1)
{
	if (g.Get_v(nV0) != BLANK && g.Get_v(nV0) != g.Get_v(nV1))
	{
		PushVertex(nV0);
		return false;
	}
	int nVexnum = g.GetVexnum();
	// 遍历图中nV0行，从0列到nVexnum列，值为true的点
	for (int nVi = 0; nVi < nVexnum; nVi++)
	{
		if (g.GetArc(nV0, nVi) && !IsExsit(nVi))
		{
			// 压入当前顶点，假设为路径的一个有效顶点
			PushVertex(nVi);
			// 判断拐点数是否大于2
			if (m_nCorner > 2)
			{
				PopVertex();
				continue;  // 放弃该条路径，重新查找别的路径
			}
			// 当中间顶点不是nV1时，继续搜寻下一个相邻且相连通的顶点
			if (nVi != nV1)
			{
				if (g.Get_v(nVi) != BLANK )
				{
					PopVertex();
					continue;
				}
				if (SearchPath(g, nVi, nV1))
				{
					return true;
				}
			}
			else  // 如果(nVi == nV1)，表示已经找到了一条连通路径，则返回true
			{
				return true;
			}
			// 取出压入的顶点，与PushVertex()对应
			PopVertex();
		}
	}
	return false;
}

void CGameLogic::PushVertex(int nV)
{
	if (m_nVexNum < 100)
	{
		m_anPath[m_nVexNum++] = nV;
		if (m_nVexNum >= 3)  // 顶点数达到3个及以上才判断拐点
		{
			if (IsCornor())
			{
				m_nCorner++;
			}
		}
	}
}
 
void CGameLogic::PopVertex()
{
	if (m_nVexNum > 0)
	{
		if (m_nVexNum >= 3)  // 顶点数达到3个及以上才判断拐点
		{
			if (IsCornor())
			{
				m_nCorner--;
			}
		}
		m_nVexNum--;
	}
}

bool CGameLogic::IsExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; ++i)
	{
		if (m_anPath[i] == nVi)
		{
			return true;  // 找到相同顶点，返回true
		}
	}
	return false;  // 遍历完数组未找到，返回false
}

bool CGameLogic::IsCornor(void) {
	if (m_nVexNum >= 3)
	{
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2])
		{
			return true;
		}
	}
	return false;
}

int* CGameLogic::getApath(int& num)  
{  
   int copyPath[100];
   num = m_nVexNum;
   for (int i = 0; i < m_nVexNum; ++i)
   {  
       copyPath[i] = m_anPath[i];  
   }  
   return copyPath;  
}

bool CGameLogic::IsBlank(CGraph& g)
{
	for (int i = 0;i < g.GetVexnum();i++)
	{
		if (g.Get_v(i) != BLANK)
		{
			return false;
		}
	}
	return true;
}

void CGameLogic::ClearMap(CGraph& g)
{
	for (int i = 0;i < g.GetVexnum();i++)
	{
		g.UpdateVertex(i, BLANK);
	}
}

void CGameLogic::ClearApath()
{
	for (int i = 0;i < 100;i++)
	{
		m_anPath[i] = BLANK;
	}
	m_nVexNum = 0;
	m_nCorner = 0;
}

bool CGameLogic::getPrompt(CGraph& g)
{
	// 得到顶点数
	int nVexnum = g.GetVexnum();

	for (int i = 0; i < nVexnum; i++)
	{
		// 得到第一个非空顶点
		if (g.Get_v(i) == BLANK)
		{
			continue;
		}
		Vertex v1;
		v1.col = i % cols;
		v1.row = i / cols;
		v1.info = g.Get_v(i);
		// 遍历得到第二个同色顶点
		for (int j = 0; j < nVexnum; j++)
		{
			Vertex v2;
			v2.col = j % cols;
			v2.row = j / cols;
			v2.info = g.Get_v(j);
			if (IsLink(g,v1,v2))
			{
				return true;
			}
		}
	}
	return false;
}

void CGameLogic::Resert(CGraph& g)
{
	int MAX_VERTEX_NUM = cols * rows;
	// 随机交换顶点数组中的两个顶点的值
	for (int i = 0; i < 1000; i++)
	{
		// 随机得到两个坐标
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		// 交换两个数值
		g.ChangeVertex(nIndex1, nIndex2);
	}

	// 更新弧信息
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			UpdateArc(g, i, j);
		}
	}
}
