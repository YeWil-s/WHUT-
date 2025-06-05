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
	// ��ȡ��ͼ��С�ͻ�ɫ
	int nRows = ParamSetting::Rows;
	int nCols = ParamSetting::Cols;
	int nPicNum = ParamSetting::PicNum;
	// �����ڴ�����
	int* pGameMap = new int[nRows * nCols];
    //��ɫ
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
	//��������
	srand((int)time(NULL));
	//������⽻����������
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++)
	{
		// ����õ���������
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		// ����������ֵ
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
	if (col > 0)  //����ߵ�����ͨ
	{
		int nV2Index = nV1Index - 1;
		if (g.Get_v(nV2Index) == g.Get_v(nV1Index) || g.Get_v(nV1Index) == BLANK || g.Get_v(nV2Index) == BLANK)
		{
			g.Add_e(nV1Index, nV2Index);
		}
	}
	if (col < nCols - 1)  //���ҵ�����ͨ
	{
		int nV2Index = nV1Index + 1;
		if (g.Get_v(nV2Index) == g.Get_v(nV1Index) || g.Get_v(nV1Index) == BLANK || g.Get_v(nV2Index) == BLANK)
		{
			g.Add_e(nV1Index, nV2Index);
		}
	}
	if (row > 0)  //�����Ϸ�������ͨ
	{
		int nV2Index = nV1Index - nCols;
		if (g.Get_v(nV2Index) == g.Get_v(nV1Index) || g.Get_v(nV1Index) == BLANK || g.Get_v(nV2Index) == BLANK)
		{
			g.Add_e(nV1Index, nV2Index);
		}
	}
	if (row < nRows - 1)  //�����·�������ͨ
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

//�ж��Ƿ���ͨ
bool CGameLogic::IsLink(CGraph& g, Vertex V1, Vertex V2)
{	
	ClearApath();
	int v1 = V1.row * ParamSetting::Cols + V1.col;
	int v2 = V2.row * ParamSetting::Cols + V2.col;
	// ѹ���һ����
	PushVertex(v1);  // ����PushVertex��������һ����������ӵ�·������

	// ��Ѱ����֮���·��
	if (SearchPath(g, v1, v2)) 
	{
		return true;
	}
	// ȡ��ѹ��Ķ���
	PopVertex();  // ����PopVertex������·��������ȡ����һ���������

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
	// ����ͼ��nV0�У���0�е�nVexnum�У�ֵΪtrue�ĵ�
	for (int nVi = 0; nVi < nVexnum; nVi++)
	{
		if (g.GetArc(nV0, nVi) && !IsExsit(nVi))
		{
			// ѹ�뵱ǰ���㣬����Ϊ·����һ����Ч����
			PushVertex(nVi);
			// �жϹյ����Ƿ����2
			if (m_nCorner > 2)
			{
				PopVertex();
				continue;  // ��������·�������²��ұ��·��
			}
			// ���м䶥�㲻��nV1ʱ��������Ѱ��һ������������ͨ�Ķ���
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
			else  // ���(nVi == nV1)����ʾ�Ѿ��ҵ���һ����ͨ·�����򷵻�true
			{
				return true;
			}
			// ȡ��ѹ��Ķ��㣬��PushVertex()��Ӧ
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
		if (m_nVexNum >= 3)  // �������ﵽ3�������ϲ��жϹյ�
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
		if (m_nVexNum >= 3)  // �������ﵽ3�������ϲ��жϹյ�
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
			return true;  // �ҵ���ͬ���㣬����true
		}
	}
	return false;  // ����������δ�ҵ�������false
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
	// �õ�������
	int nVexnum = g.GetVexnum();

	for (int i = 0; i < nVexnum; i++)
	{
		// �õ���һ���ǿն���
		if (g.Get_v(i) == BLANK)
		{
			continue;
		}
		Vertex v1;
		v1.col = i % cols;
		v1.row = i / cols;
		v1.info = g.Get_v(i);
		// �����õ��ڶ���ͬɫ����
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
	// ����������������е����������ֵ
	for (int i = 0; i < 1000; i++)
	{
		// ����õ���������
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		// ����������ֵ
		g.ChangeVertex(nIndex1, nIndex2);
	}

	// ���»���Ϣ
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			UpdateArc(g, i, j);
		}
	}
}
