// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include"global.h"
#include <mmsystem.h>
#include"ParamSetting.h"
#pragma comment(lib, "Winmm.lib")


// CGameDlg 对话框
// 定义静态成员变量
CString CGameDlg::ElementPath;
CString CGameDlg::MaskPath;

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_GameRegionTop.y = MAP_TOP;
	m_GameRegionTop.x = MAP_LEFT;
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	m_GameRegion.top = MAP_TOP;
	m_GameRegion.left = MAP_LEFT;
	m_GameRegion.right = MAP_LEFT + PIC_WIDTH * ParamSetting::Cols;
	m_GameRegion.bottom = MAP_TOP + PIC_HEIGHT * ParamSetting::Rows;
	playing = false;
	fiestSelect = false;
	GameMode = 0;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRB_TIME, GameProgress); // 将滚动条和控件绑定在一起
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_S, &CGameDlg::OnBnClickedBtnSTOP)
	ON_BN_CLICKED(IDC_BTN_PROMPT, &CGameDlg::OnBnClickedBtnPrompt)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnBnClickedBtnReset)
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGameDlg 消息处理程序

void CGameDlg::InitBackground()
{

	// 加载原始背景位图
	HANDLE hBmp = ::LoadImageW(NULL, ParamSetting::BGPath,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_bmpBackground.Attach((HBITMAP)hBmp);

	// 获取原始位图尺寸
	BITMAP bm;
	m_bmpBackground.GetBitmap(&bm);
	m_sizeBmp.cx = bm.bmWidth;
	m_sizeBmp.cy = bm.bmHeight;

	// 创建兼容DC
	CClientDC dc(this);

	// 确保 m_dcBG 被正确清理
	if (m_dcBG.GetSafeHdc() != nullptr) {
		m_dcBG.DeleteDC();
	}
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(&m_bmpBackground);

	// 确保 m_dcMem 被正确清理
	if (m_dcMem.GetSafeHdc() != nullptr) {
		m_dcMem.DeleteDC();
	}
	m_dcMem.CreateCompatibleDC(&dc);

	// 获取客户区并创建兼容位图
	GetClientRect(&m_rectClient);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, m_rectClient.Width(), m_rectClient.Height());
	m_dcMem.SelectObject(&bmpMem);

	// 缩放绘制到内存DC
	m_dcMem.StretchBlt(0, 0, m_rectClient.Width(), m_rectClient.Height(),
		&m_dcBG, 0, 0, m_sizeBmp.cx, m_sizeBmp.cy, SRCCOPY);
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	this->ModifyStyleEx(0, WS_EX_APPWINDOW);
	// TODO:  在此添加额外的初始化

	//设置背景
	InitBackground();

	//设置模式
	InitMode(this->GameMode);

	//设置初始按钮状态
	SetButton(TRUE, FALSE, FALSE, FALSE);

	//初始化水果元素和掩码
	InitElement(ParamSetting::ElementPath, ParamSetting::MaskPath);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CGameDlg::UpdateBackground()
{
	CClientDC dc(this);

	// 确保 m_dcMem 被正确清理
	if (m_dcMem.GetSafeHdc() != nullptr) {
		m_dcMem.DeleteDC();
	}
	m_dcMem.CreateCompatibleDC(&dc);

	// 获取客户区并创建兼容位图
	GetClientRect(&m_rectClient);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, m_rectClient.Width(), m_rectClient.Height());
	m_dcMem.SelectObject(&bmpMem);

	// 缩放绘制背景
	m_dcMem.StretchBlt(0, 0, m_rectClient.Width(), m_rectClient.Height(),&m_dcBG, 0, 0, m_sizeBmp.cx, m_sizeBmp.cy, SRCCOPY);
}

void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	dc.BitBlt(0, 0, m_rectClient.Width(), m_rectClient.Height(), &m_dcMem, 0, 0, SRCCOPY);
	// 不为绘图消息调用 CDialogEx::OnPaint()
}

void CGameDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (cx > 0 && cy > 0) // 避免最小化时尺寸为0
	{
		UpdateBackground(); // 更新背景
		Invalidate();      // 触发重绘

		// 调整按钮位置
		CRect rectClient;
		GetClientRect(&rectClient);

		// 示例：调整按钮相对位置
		CWnd* pBtnStart = GetDlgItem(IDC_BTN_START);
		CWnd* pBtnStop = GetDlgItem(IDC_BTN_STOP);
		CWnd* pBtnPrompt = GetDlgItem(IDC_BTN_PROMPT);
		CWnd* pBtnReset = GetDlgItem(IDC_BTN_RESET);

		if (pBtnStart && pBtnStop && pBtnPrompt && pBtnReset)
		{
			// 设置按钮宽高
			int btnWidth = 100;
			int btnHeight = 30;

			// 计算按钮位置（示例：底部对齐，等间距排列）
			int margin = 10;
			int spacing = 20;
			int yPos = rectClient.bottom - btnHeight - margin;

			pBtnStart->MoveWindow(margin, yPos, btnWidth, btnHeight);
			pBtnStop->MoveWindow(margin + btnWidth + spacing, yPos, btnWidth, btnHeight);
			pBtnPrompt->MoveWindow(margin + 2 * (btnWidth + spacing), yPos, btnWidth, btnHeight);
			pBtnReset->MoveWindow(margin + 3 * (btnWidth + spacing), yPos, btnWidth, btnHeight);
		}
	}
}

void CGameDlg::SetGameMode(int mode) {
	this->GameMode = mode;
}

void CGameDlg::InitMode(int mode) {
	CProgressCtrl* pProgressCtrl = (CProgressCtrl*)GetDlgItem(IDC_PRB_TIME);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TIME);
	if (mode == 1) {
		this->SetWindowTextW(_T("欢乐连连看——基本模式"));
		pEdit->EnableWindow(FALSE);
	}
	else if (mode == 0) {
		this->SetWindowTextW(_T("欢乐连连看——休闲模式"));
		pProgressCtrl->ShowWindow(SW_HIDE);
		pEdit->ShowWindow(SW_HIDE);
	}
	else {
		this->SetWindowTextW(_T("欢乐连连看——关卡模式"));
		pEdit->EnableWindow(FALSE);
	}
}

void CGameDlg::SetButton(bool start, bool stop, bool prompt, bool reset)
{
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(start);
	this->GetDlgItem(IDC_BTN_STOP)->EnableWindow(stop);
	this->GetDlgItem(IDC_BTN_PROMPT)->EnableWindow(prompt);
	this->GetDlgItem(IDC_BTN_RESET)->EnableWindow(reset);
}

void CGameDlg::SetGameProgress(int range)
{
	GameProgress.SetRange(0, range);
	GameProgress.SetStep(-1);
	GameProgress.SetPos(range);
	TimeCount = range;
	this->SetTimer(1, 1000, NULL);
}

void CGameDlg::TurnonBGMusic(CString path)
{
	if (mciSendString(_T("open ") + path + _T(" alias BGM"), NULL, 0, NULL) != 0)
	{
		ASSERT(0);
	}
	mciSendString(_T("play BGM repeat"), NULL, 0, NULL);
}

void CGameDlg::TurnoffBGMusic()
{
	mciSendString(_T("stop BGM"), NULL, 0, NULL);
	mciSendString(_T("close BGM"), NULL, 0, NULL);
}

void CGameDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和 / 或调用默认值
	TurnoffBGMusic();
	CDialogEx::OnClose();
}

void CGameDlg::InitElement(CString ElementPath, CString MaskPath)
{
	CClientDC dc(this);
	HANDLE hBmp = ::LoadImageW(NULL, ElementPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcEle.CreateCompatibleDC(&dc);
	m_dcEle.SelectObject(hBmp);
	
	HANDLE hMask = ::LoadImageW(NULL, MaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);
}

void CGameDlg::UpdateMap()
{
	int row = ParamSetting::Rows;
	int col = ParamSetting::Cols;
	int nTop = MAP_TOP;
	int nLeft = MAP_LEFT;
	int nElemW = PIC_WIDTH;
	int nElemH = PIC_HEIGHT;
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < col;j++)
		{
			int nElemVal = m_GameC.GetElement(i, j);
			m_dcMem.BitBlt(nLeft + j * nElemH, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemH, nTop + i * nElemH, nElemW, nElemH, &m_dcEle, 0, nElemVal * nElemH, SRCAND);
		}
	}

}

void CGameDlg::OnBnClickedBtnStart()
{
	bool status = m_GameC.StartGame();
	if (status)
	{
		playing = true;
		fiestSelect = true;

		SetButton(FALSE, TRUE, TRUE, TRUE);
		UpdateMap();
		//如果不是休闲模式，则设置滚动条和定时器
		switch (this->GameMode)
		{
		case 1:
		case 2:SetGameProgress(EASY);
			break;
		case 3:SetGameProgress(MED);
			break;
		case 4:SetGameProgress(HARD);
			break;
		default:break;
		}
		//打开背景音乐:
		if (ParamSetting::BGMusicOn)
			TurnonBGMusic(ParamSetting::BGMSoundPath);
	}
	else AfxMessageBox(L"行列和图片个数不匹配，无法绘制地图！", MB_OKCANCEL);
	InvalidateRect(FALSE);
}

void CGameDlg::OnBnClickedBtnSTOP()
{
	// TODO: 在此添加控件通知处理程序代码
	if (playing)
	{
		this->GetDlgItem(IDC_BTN_STOP)->SetWindowText(L"重新开始");
		playing = false;
	}
	else
	{
		this->GetDlgItem(IDC_BTN_STOP)->SetWindowText(L"暂停游戏");
		playing = true;
	}
}

void CGameDlg::OnBnClickedBtnPrompt()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!playing) return;
	Vertex avPath[100];
	stack<Vertex> verList;
	int nVexnum = 0;			   // 顶点个数

	bool success = m_GameC.getPrompt(avPath, nVexnum);
	if (success)
	{
		//重新加载地图背景，并更新最新地图
		m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
		UpdateMap();
		DrawTipFrame(avPath[0].row, avPath[0].col);
		DrawTipFrame(avPath[nVexnum-1].row, avPath[nVexnum-1].col);
		for (int i = 0; i < nVexnum; ++i) {
			verList.push(avPath[i]);
		}
		//DrawTipLine(verList);
	}
}

void CGameDlg::OnBnClickedBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!playing)return;
	m_GameC.Resert();
	fiestSelect = true;
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
	UpdateMap();
	InvalidateRect(FALSE);
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	int Rows = ParamSetting::Rows;
	int Cols = ParamSetting::Cols;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!playing) return;

	if (point.y<m_GameRegion.top || point.y>m_GameRegion.bottom || point.x<m_GameRegion.left || point.x>m_GameRegion.right)
	{
		//如果没有在地图的区域内，则不管
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//计算当前点的坐标
	int nRow = (point.y - m_GameRegionTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_GameRegionTop.x) / m_sizeElem.cx;
	if (nRow > Rows - 1 || nCol > Cols - 1) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_GameC.GetElement(nRow, nCol) == BLANK)
	{
		//如果这个区域没有图片，则返回
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (fiestSelect) {
		//如果是此次点击是第一个点，则画边框，并进行设置
		DrawTipFrame(nRow, nCol);
		m_GameC.SetFirstPoint(nRow, nCol);
		PlaySound(ParamSetting::ClickSoundPath, NULL, SND_FILENAME | SND_ASYNC);
	}
	else
	{
		//如果此次点击是第二个点，画边框，并进行设置
		DrawTipFrame(nRow, nCol);
		m_GameC.SetSecPoint(nRow, nCol);
		//同时判断两个点是否相连
		stack<Vertex> verList;
		Vertex verlist[100];
		int nVexNum;
		bool bSuc = m_GameC.Link(verlist, nVexNum);
		for (int i = 0; i < nVexNum; ++i) {
			verList.push(verlist[i]);
		}
		if (bSuc) {
			//如果相连，则画连接线路，
			DrawTipLine(verList);
			PlaySound(ParamSetting::ClearSoundPath, NULL, SND_FILENAME | SND_ASYNC);
			//重新加载地图背景，并更新最新地图
			m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(FALSE);
		if (bSuc && m_GameC.iswin())
		{
			MessageBox(TEXT("恭喜你！获胜！"));
			// 设置按钮
			SetButton(TRUE, FALSE, FALSE, FALSE);
			playing = false;
		}
	}
	fiestSelect = !fiestSelect;//第一次和第二次点击切换标志
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CGameDlg::DrawTipFrame(int nrow, int ncol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_GameRegionTop.x + ncol * m_sizeElem.cx;
	rtTipFrame.top = m_GameRegionTop.y + nrow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

void CGameDlg::DrawTipLine(stack<Vertex> verList)
{
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(255, 255, 255));
	CPen* pOldPen = dc.SelectObject(&penLine);
	Vertex vTop;
	CPoint cp;

	if (!verList.empty())
	{
		vTop = verList.top();
		cp.x = m_GameRegionTop.x + vTop.col * m_sizeElem.cx + m_sizeElem.cx / 2;
		cp.y = m_GameRegionTop.y + vTop.row * m_sizeElem.cy + m_sizeElem.cy / 2;
		dc.MoveTo(cp);
		verList.pop();
		while (!verList.empty())
		{
			vTop = verList.top();
			cp.x = m_GameRegionTop.x + vTop.col * m_sizeElem.cx + m_sizeElem.cx / 2;
			cp.y = m_GameRegionTop.y + vTop.row * m_sizeElem.cy + m_sizeElem.cy / 2;
			dc.LineTo(cp);
			verList.pop();
		}
	}
	dc.SelectObject(pOldPen);
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (playing)
	{
		CString str;
		str.Format(_T("%d"), TimeCount - 1);
		SetDlgItemText(IDC_EDIT_TIME, str);
		UpdateData(false);
		TimeCount--;
		GameProgress.StepIt();

		if (TimeCount == 0)
		{
			KillTimer(1);
			m_GameC.ClearMap();
			m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
			UpdateMap();
			InvalidateRect(FALSE);
			MessageBox(TEXT("时间到！游戏失败！"));
			SetButton(TRUE, FALSE, FALSE, FALSE);
			playing = false;
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}
