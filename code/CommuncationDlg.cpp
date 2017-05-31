// CommuncationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionSystem.h"
#include "CommuncationDlg.h"
#include "afxdialogex.h"
#include "VisionSystemDlg.h"

// CCommuncationDlg 对话框

IMPLEMENT_DYNAMIC(CCommuncationDlg, CDialogEx)

CCommuncationDlg::CCommuncationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommuncationDlg::IDD, pParent)
{
	m_brush.CreateSolidBrush(_COLOR_BK);   //   生成刷子
}

CCommuncationDlg::~CCommuncationDlg()
{
}

void CCommuncationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_EXIT, m_stBtnExit);
}


BEGIN_MESSAGE_MAP(CCommuncationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_EXIT, &CCommuncationDlg::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CCommuncationDlg 消息处理程序


BOOL CCommuncationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMenu* pMenu = this->GetSystemMenu(FALSE);//系统菜单
	pMenu->ModifyMenu(SC_CLOSE,MF_BYCOMMAND | MF_GRAYED );//禁用关闭按钮
	// TODO:  在此添加额外的初始化
	InitStBtn() ;

	InitSize() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CCommuncationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


HBRUSH CCommuncationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if(nCtlColor   ==CTLCOLOR_DLG)    
		return   m_brush;


	return hbr;
}


void CCommuncationDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_ControlChange.OnSize(cx,cy);
	Invalidate();
}

void CCommuncationDlg::InitStBtn() 
{
	try
	{
		m_stBtnFont.CreatePointFont(160,"arial") ;

		m_stBtnExit.SetFont(&m_stBtnFont) ;
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_BK_OUT, _COLOR_BK);
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_BK_IN, _COLOR_BK_IN);
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, _COLOR_BK);
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_FG_OUT, _COLOR_RED);
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_FG_IN, _COLOR_RED);
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, _COLOR_RED);
	}
	catch (...)
	{

	}
}

void CCommuncationDlg::InitSize()
{
	m_ControlChange.SetOwner(this);
	m_ControlChange.SetResizeControl(IDC_BTN_EXIT,PK_TOP_LEFT,PK_TOP_RIGHT,PK_BOTTOM_LEFT,PK_BOTTOM_RIGHT);
}

void CCommuncationDlg::OnBnClickedBtnExit()
{
	try
	{
		CVisionSystemDlg *pDlg = ( CVisionSystemDlg * ) AfxGetMainWnd();

		pDlg->DispChildWindow(_MAIN_DLG) ;
	}
	catch (...)
	{

	}
}
