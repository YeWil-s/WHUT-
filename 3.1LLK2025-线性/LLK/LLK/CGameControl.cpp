#include "pch.h"
#include "CGameControl.h"
#include"ParamSetting.h"
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

CGameControl::CGameControl()
{
	m_GameLogic.rows = ParamSetting::Rows;
	m_GameLogic.cols = ParamSetting::Cols;
	m_GameLogic.picNum = ParamSetting::PicNum;
}

int CGameControl::GetElement(int row, int col)
{
	return m_GameLogic.GetElement(row, col);
}

bool CGameControl::StartGame(int row, int col, int picnum)
{
	if (row * col % (picnum*2)  != 0)return false;
	else m_GameLogic.InitMap(row, col, picnum);
	return true;
}

void CGameControl::SetFirstPoint(int nrow, int ncol)
{
	selfirst.row = nrow;
	selfirst.col = ncol;
}

void CGameControl::SetSecondPoint(int nrow, int ncol)
{
	selfsecond.row = nrow;
	selfsecond.col = ncol;
}

bool CGameControl::Link(stack<Vertex>& verList)
{
	if (m_GameLogic.IsLink(selfirst, selfsecond))
	{
		m_GameLogic.clear(selfirst, selfsecond);
		verList = m_GameLogic.GetVerList();
		return true;
	}
}

bool CGameControl::iswin()
{
	return m_GameLogic.isBlank();
}

bool CGameControl::GetPrompt(stack<Vertex>& verList)
{
	Vertex v1, v2;
	if (m_GameLogic.GetPrompt(v1, v2))
	{
		SetFirstHelpPoint(v1.row, v1.col);
		SetSecondHelpPoint(v2.row, v2.col);
		verList = m_GameLogic.GetVerList();
		return true;
	}
	return false;
}

void CGameControl::SetFirstHelpPoint(int nRow, int nCol)
{
	helpFirst.col = nCol;
	helpFirst.row = nRow;
	helpFirst.info = m_GameLogic.GetElement(nRow, nCol);
}

void CGameControl::SetSecondHelpPoint(int nRow, int nCol)
{
	helpSecond.col = nCol;
	helpSecond.row = nRow;
	helpSecond.info = m_GameLogic.GetElement(nRow, nCol);
}

void CGameControl::ResetMap()
{
	m_GameLogic.ResetMap();
}

void CGameControl::ClearMap()
{
	m_GameLogic.ClearMap();
}
