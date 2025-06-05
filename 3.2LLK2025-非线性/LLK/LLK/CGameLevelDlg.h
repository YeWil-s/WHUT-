#pragma once
#include "afxdialogex.h"
#include "CGameDlg.h"


// CGameLevelDlg 对话框

class CGameLevelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameLevelDlg)

public:
	CGameLevelDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameLevelDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LEVEL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void SetLevel(int l);
	afx_msg void OnBnClickedBtnEasy();
	afx_msg void OnBnClickedPrbTime();
	afx_msg void OnBnClickedBtnHard();
};
