#include "pch.h"
#include "CGameControl.h"
#include"ParamSetting.h"
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

CGameControl::CGameControl()
{

}

bool CGameControl::StartGame()
{
    int row = gmLogic.rows;
    int col = gmLogic.cols;
    int picnum = gmLogic.picNum;
    if (row * col % (picnum * 2) != 0)return false;
    else gmLogic.InitMap(gmgraph);
    return true;
}

int CGameControl::GetElement(int row, int col)
{
	return gmgraph.Get_v(row * gmLogic.cols + col);
}

//设置第一个点
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
    m_svSelFst.col = nCol;
    m_svSelFst.row = nRow;
}

//设置第二个点
void CGameControl::SetSecPoint(int nRow, int nCol)
{
    m_svSelSec.col = nCol;
    m_svSelSec.row = nRow;
}

bool CGameControl::Link(Vertex avPath[100], int& nVexnum)
{
    int* apath;
    if (gmLogic.IsLink(gmgraph, m_svSelFst, m_svSelSec))
    {
        gmLogic.Clear(gmgraph, m_svSelFst, m_svSelSec);
        apath = gmLogic.getApath(nVexnum);
        for (int i = 0;i < nVexnum;i++)
        {
            avPath[i].col = apath[i] % gmLogic.cols;
            avPath[i].row = apath[i] / gmLogic.rows;
            avPath[i].info = gmgraph.Get_v(apath[i]);
        }
        return true;
    }
    return false;
}

bool CGameControl::iswin()
{
    return gmLogic.IsBlank(gmgraph);
}

void CGameControl::ClearMap()
{
    gmLogic.ClearMap(gmgraph);
}

bool CGameControl::getPrompt(Vertex avPath[100], int& nVexnum)
{
   // 查找一条有效的提示路径
   if (gmLogic.getPrompt(gmgraph))
   {
       // 获取路径顶点的整数数组
       int* apath = gmLogic.getApath(nVexnum);
       for (int i = 0; i < nVexnum; i++)
       {
           avPath[i].col = apath[i] % gmLogic.cols;
           avPath[i].row = apath[i] / gmLogic.cols;
           avPath[i].info = gmgraph.Get_v(apath[i]);
       }
       return true;
   }
   return false;
}

void CGameControl::Resert(void)
{
    gmLogic.Resert(gmgraph);
}
