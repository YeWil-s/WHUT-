#pragma once
#include "afxdialogex.h"
#include"CGameControl.h"
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;
	CDC m_dcMem;
	CDC m_dcBG;
	CDC m_dcEle;
	CDC m_dcMask;
	CBitmap m_bmpBackground; // 原始背景位图
	CSize   m_sizeBmp;       // 原始位图尺寸
	CRect   m_rectClient;    // 当前客户区矩形
	static CString BGPath ;//背景图片路径
	static CString ElementPath;
	static CString MaskPath;

	CGameControl m_GameC;
	bool playing;
	bool fiestSelect;//第一个点
	void InitBackground();
	CProgressCtrl GameProgress;  //创建一个滚动条对象
	int TimeCount;  //创建一个时间量 
	DECLARE_MESSAGE_MAP()

public:
	void UpdateBackground();
	void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void SetGameMode(int mode);
	void InitMode(int mode);
	void SetButton(bool start, bool stop, bool prompt, bool reset);
	void SetGameProgress(int range);
	void TurnonBGMusic(CString path);
	void TurnoffBGMusic();
	void OnClose();

    private:  
       int m_GameRegionLeft; // 添加 m_GameRegionLeft 成员变量
private:
	int GameMode;
	CPoint m_GameRegionTop;
	CSize m_sizeElem;
	CRect m_GameRegion;
	
	void InitElement(CString ElementPath, CString MaskPath);
	void UpdateMap();
	void DrawTipFrame(int nrow, int ncol);
	void DrawTipLine(stack<Vertex> verList);

public:
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnSTOP();
	afx_msg void OnBnClickedBtnPrompt();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
