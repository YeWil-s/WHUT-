#pragma once
#include "afxdialogex.h"


// CSettingDlg 对话框

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

	CImage m_bgImage;
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadioOpen();
	afx_msg void OnBnClickedRadioClose();

	void SetTheme(int theme);
	void SetMap(int row, int col, int picNum);
	void SetBGMusic(bool on);
	bool IsNum(CString s);
	BOOL OnEraseBkgnd(CDC* pDC);


	bool musicOn;
};
