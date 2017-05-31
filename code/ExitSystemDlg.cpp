// ExitSystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionSystem.h"
#include "ExitSystemDlg.h"
#include "afxdialogex.h"
#include "DefineEnum.h"

// CExitSystemDlg 对话框

IMPLEMENT_DYNAMIC(CExitSystemDlg, CDialogEx)

CExitSystemDlg::CExitSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EXIT_DIALOG, pParent)
{
	m_brush.CreateSolidBrush(_COLOR_BK);   //   生成刷子
}

CExitSystemDlg::~CExitSystemDlg()
{
}

void CExitSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_stBtnOk);
	DDX_Control(pDX, IDCANCEL, m_stBtnCancel);
}


BEGIN_MESSAGE_MAP(CExitSystemDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CExitSystemDlg 消息处理程序


BOOL CExitSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMenu* pMenu = this->GetSystemMenu(FALSE);//系统菜单
	pMenu->ModifyMenu(SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);//禁用关闭按钮
	// TODO:  在此添加额外的初始化
	m_stBtnFont.CreatePointFont(150, _T("微软雅黑"));
	m_StaticFont.CreatePointFont(200, _T("微软雅黑"));

	GetDlgItem(IDC_STATIC_TIP)->SetFont(&m_StaticFont);
	GetDlgItem(IDOK)->SetFont(&m_stBtnFont);
	GetDlgItem(IDCANCEL)->SetFont(&m_stBtnFont);

	m_stBtnOk.SetColor(CButtonST::BTNST_COLOR_BK_OUT, _COLOR_BK);
	m_stBtnOk.SetColor(CButtonST::BTNST_COLOR_BK_IN, _COLOR_BK_IN);
	m_stBtnOk.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, _COLOR_BK);
	m_stBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_OUT, _COLOR_WHITE);
	m_stBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_IN, _COLOR_WHITE);
	m_stBtnOk.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, _COLOR_WHITE);

	m_stBtnCancel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, _COLOR_BK);
	m_stBtnCancel.SetColor(CButtonST::BTNST_COLOR_BK_IN, _COLOR_BK_IN);
	m_stBtnCancel.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, _COLOR_BK);
	m_stBtnCancel.SetColor(CButtonST::BTNST_COLOR_FG_OUT, _COLOR_WHITE);
	m_stBtnCancel.SetColor(CButtonST::BTNST_COLOR_FG_IN, _COLOR_WHITE);
	m_stBtnCancel.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, _COLOR_WHITE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH CExitSystemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_DLG)
		return   m_brush;

	switch (pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_TIP:
		{
			pDC->SetBkColor(_COLOR_BLACK);
			pDC->SetTextColor(_COLOR_RED);
			return   m_brush;
		}
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
