// CSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CSettingDlg.h"
#include"ParamSetting.h"


// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DIALOG, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_OPEN, &CSettingDlg::OnBnClickedRadioOpen)
	ON_BN_CLICKED(IDC_RADIO_CLOSE, &CSettingDlg::OnBnClickedRadioClose)
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序

BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//添加背景
	if (m_bgImage.Load(_T("theme\\picture\\bg.bmp")) != S_OK) {
		AfxMessageBox(_T("背景图片加载失败！"));
	}

	//增加下拉框数据的初始化
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
	pCombo->InsertString(0, _T("水果乐园主题"));
	pCombo->InsertString(1, _T("只因你太美主题"));
	pCombo->InsertString(2, _T("怪物猎人主题"));
	pCombo->SetCurSel(ParamSetting::ThemeNo);

	//行列图片数据初始化
	CEdit* editRow = (CEdit*)GetDlgItem(IDC_EDIT1);
	CEdit* editCol = (CEdit*)GetDlgItem(IDC_EDIT2);
	CEdit* editPic = (CEdit*)GetDlgItem(IDC_EDIT3);

	CString rows, cols, pics;
	rows.Format(_T("%d"), ParamSetting::Rows);
	cols.Format(_T("%d"), ParamSetting::Cols);
	pics.Format(_T("%d"), ParamSetting::PicNum);

	editRow->SetWindowTextW(rows);
	editCol->SetWindowTextW(cols);
	editPic->SetWindowTextW(pics);

	//背景音乐按钮的初始化
	CButton* radioOpen = (CButton*)GetDlgItem(IDC_RADIO_OPEN);
	CButton* radioClose = (CButton*)GetDlgItem(IDC_RADIO_CLOSE);
	if (ParamSetting::BGMusicOn)
		radioOpen->SetCheck(BST_CHECKED);
	else
		radioClose->SetCheck(BST_CHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE 
}

void CSettingDlg::OnBnClickedOk()
{
	//提取主题信息
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int nIndex = pCombo->GetCurSel();
	SetTheme(nIndex);

	//提取地图信息
	CEdit* editRow = (CEdit*)GetDlgItem(IDC_EDIT1);
	CEdit* editCol = (CEdit*)GetDlgItem(IDC_EDIT2);
	CEdit* editPic = (CEdit*)GetDlgItem(IDC_EDIT3);
	CString row, col, pic;
	int rows, cols, pics;
	editRow->GetWindowText(row);
	if (!IsNum(row)) { 
		AfxMessageBox(_T("地图行数输入应为数字，请重新输入！"));
		editRow->SetFocus();
		editRow->SetSel(0, -1);
		return;
	}
	rows = _ttoi(row);
	if (rows < 1 || rows >10) { 
		AfxMessageBox(_T("地图行数应在1到10之间，请重新输入！"));
		editRow->SetFocus();
		editRow->SetSel(0, -1);
		return;
	}
	editCol->GetWindowText(col);
	if (!IsNum(col)) {  
		AfxMessageBox(_T("地图列数输入应为数字，请重新输入！"));
		editRow->SetFocus();
		editRow->SetSel(0, -1);
		return;
	}
	cols = _ttoi(col);
	if (cols < 1 || cols >12) { 
		AfxMessageBox(_T("地图列数应在1到12之间，请重新输入！"));
		editRow->SetFocus();
		editRow->SetSel(0, -1);
		return;
	}
	editPic->GetWindowText(pic);
	if (!IsNum(pic)) { 
		AfxMessageBox(_T("图片数量输入应为数字，请重新输入！"));
		editRow->SetFocus();
		editRow->SetSel(0, -1);
		return;
	}
	pics = _ttoi(pic);
	if (pics < 1 || pics>16) { }
	if ((rows * cols) % (pics * 2) != 0) { 
		AfxMessageBox(_T("地图行列与图片数量设置不符合规则，请重新调整！"));
		return;
	}
	SetMap(rows, cols, pics);

	//提取背景音乐信息
	SetBGMusic(musicOn);

	CDialogEx::OnOK();
}

void CSettingDlg::OnBnClickedRadioOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	musicOn = true;
}

void CSettingDlg::OnBnClickedRadioClose()
{
	// TODO: 在此添加控件通知处理程序代码
	musicOn = false;
}

void CSettingDlg::SetTheme(int theme)
{
	ParamSetting::ThemeNo = theme;

	switch (theme)
	{
	case 0:
		ParamSetting::ElementPath = _T("theme/picture/fruit_element.bmp");
		ParamSetting::MaskPath = _T("theme/picture/fruit_mask.bmp");
		ParamSetting::BGPath = _T("theme/picture/fruit_bg.bmp");
		ParamSetting::ClickSoundPath = _T("theme/sound/fruit_click.wav");
		ParamSetting::ClearSoundPath = _T("theme/sound/fruit_clear.wav");
		break;
	case 1:
		ParamSetting::ElementPath = _T("theme/picture/cxk_element.bmp");
		ParamSetting::MaskPath = _T("theme/picture/cxk_mask.bmp");
		ParamSetting::BGPath = _T("theme/picture/cxk_bg.bmp");
		ParamSetting::ClickSoundPath = _T("theme/sound/cxk_click.wav");
		ParamSetting::ClearSoundPath = _T("theme/sound/cxk_clear.wav");
		break;
	case 2:
		ParamSetting::ElementPath = _T("theme/picture/mh_element.bmp");
		ParamSetting::MaskPath = _T("theme/picture/mh_mask.bmp");
		ParamSetting::BGPath = _T("theme/picture/mh_bg.bmp");
		ParamSetting::ClickSoundPath = _T("theme/sound/mh_click.wav");
		ParamSetting::ClearSoundPath = _T("theme/sound/mh_clear.wav");
		break;
	}
}

void CSettingDlg::SetMap(int row, int col, int picNum)
{
	ParamSetting::Rows = row;
	ParamSetting::Cols = col;
	ParamSetting::PicNum = picNum;
}

void CSettingDlg::SetBGMusic(bool on)
{
	ParamSetting::BGMusicOn = on;
}

bool CSettingDlg::IsNum(CString s)
{
	int len = s.GetLength();
	if (len == 0)
	{
		return false;
	}
	// 处理正负号情况
	int startIndex = 0;
	if (s[0] == '-' || s[0] == '+')
	{
		if (len == 1)
		{
			return false;
		}
		startIndex = 1;
	}
	for (int i = startIndex; i < len; i++)
	{
		if (!_istdigit(s[i]))
		{
			return false;
		}
	}
	return true;
}

BOOL CSettingDlg::OnEraseBkgnd(CDC* pDC) {
	if (!m_bgImage.IsNull()) {
		CRect rect;
		GetClientRect(&rect);

		// 绘制背景（拉伸填充整个对话框）
		m_bgImage.Draw(pDC->GetSafeHdc(), rect);
		return TRUE;
	}
	return CDialogEx::OnEraseBkgnd(pDC);
}