#include "pch.h"
#include "CGraph.h"
#include"ParamSetting.h"
#include<iostream>

void CGraph::InitGraph()
{
    num_v = 0;  // 初始化顶点数为0
    num_e = 0;
    for (int i = 0; i < 200; ++i) {
        for (int j = 0; j < 200; ++j) {
            E[i][j] = false;
        }
    }
}

int CGraph::Add_v(int info)
{
    if (num_v < 200)
    {
        V[num_v] = info;
        num_v++;
    }
    return num_v;
}

int CGraph::Get_v(int index)
{
    return V[index];
}

void CGraph::Add_e(int v1, int v2)
{
    if (v1 < 200 && v2 < 200)
    {
        E[v1][v2] = true;
        E[v2][v1] = true;
        num_e++;
    }
   
}

int CGraph::GetCols()
{
    return ParamSetting::Cols;
}

void CGraph::UpdateVertex(int nIndex, int info)
{
    V[nIndex] = info;
}

bool CGraph::GetArc(int nV1Index, int nV2Index)
{
    return E[nV1Index][nV2Index];
}

int CGraph::GetVexnum()
{
    return num_v;
}

void CGraph::ClearGraph()
{
    InitGraph();
}

// 调换两个点的位置
void CGraph::ChangeVertex(int nIndex1, int nIndex2)
{
    int Temp = V[nIndex1];
    V[nIndex1] = V[nIndex2];
    V[nIndex2] = Temp;
}