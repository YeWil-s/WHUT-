#pragma once
#include "afxdialogex.h"


// CHelpDlg 对话框

class CHelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDlg)

public:
	CHelpDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHelpDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HELP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	BOOL OnInitDialog();

	BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()
private:
	CImage m_bgImage;  // 使用CImage（支持多种格式，推荐）
};
