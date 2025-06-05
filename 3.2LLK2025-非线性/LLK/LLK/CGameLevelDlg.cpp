// CGameLevelDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGameLevelDlg.h"


// CGameLevelDlg 对话框

IMPLEMENT_DYNAMIC(CGameLevelDlg, CDialogEx)

CGameLevelDlg::CGameLevelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LEVEL_DIALOG, pParent)
{

}

CGameLevelDlg::~CGameLevelDlg()
{
}

void CGameLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameLevelDlg, CDialogEx)
	ON_BN_CLICKED(IDD_BTN_Easy, &CGameLevelDlg::OnBnClickedBtnEasy)
	ON_BN_CLICKED(IDC_PRB_TIME, &CGameLevelDlg::OnBnClickedPrbTime)
	ON_BN_CLICKED(IDD_BTN_Hard, &CGameLevelDlg::OnBnClickedBtnHard)
END_MESSAGE_MAP()


// CGameLevelDlg 消息处理程序



void CGameLevelDlg::SetLevel(int l)
{
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg;
	dlg.SetGameMode(l);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}

void CGameLevelDlg::OnBnClickedBtnEasy()
{
	// TODO: 在此添加控件通知处理程序代码
	SetLevel(2);
}

void CGameLevelDlg::OnBnClickedPrbTime()
{
	// TODO: 在此添加控件通知处理程序代码
	SetLevel(3);

}

void CGameLevelDlg::OnBnClickedBtnHard()
{
	// TODO: 在此添加控件通知处理程序代码
	SetLevel(4);

}
