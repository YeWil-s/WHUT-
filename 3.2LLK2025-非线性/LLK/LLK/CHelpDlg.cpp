// CHelpDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CHelpDlg.h"


// CHelpDlg 对话框

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HELP_DIALOG, pParent)
{

}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CHelpDlg 消息处理程序

BOOL CHelpDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // 从文件加载背景图片（确保路径正确）
    if (m_bgImage.Load(_T("theme\\picture\\bg.bmp")) != S_OK) {
        AfxMessageBox(_T("背景图片加载失败！"));
    }

    return TRUE;
}

BOOL CHelpDlg::OnEraseBkgnd(CDC* pDC) {
    if (!m_bgImage.IsNull()) {
        CRect rect;
        GetClientRect(&rect);

        // 绘制背景（拉伸填充整个对话框）
        m_bgImage.Draw(pDC->GetSafeHdc(), rect);
        return TRUE;
    }
    return CDialogEx::OnEraseBkgnd(pDC);
}