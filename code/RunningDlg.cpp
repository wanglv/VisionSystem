// RunningDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionSystem.h"
#include "RunningDlg.h"
#include "afxdialogex.h"
#include "VisionSystemDlg.h"

// CRunningDlg 对话框

IMPLEMENT_DYNAMIC(CRunningDlg, CDialogEx)

CRunningDlg::CRunningDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRunningDlg::IDD, pParent)
{
	m_brush.CreateSolidBrush(RGB(20,20,22));   //   生成刷子
}

CRunningDlg::~CRunningDlg()
{
}

void CRunningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_EXIT, m_stBtnExit);
}


BEGIN_MESSAGE_MAP(CRunningDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_EXIT, &CRunningDlg::OnBnClickedBtnExit)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRunningDlg 消息处理程序


BOOL CRunningDlg::OnInitDialog()
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


void CRunningDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


HBRUSH CRunningDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor   ==CTLCOLOR_DLG)    
		return   m_brush;
	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CRunningDlg::InitStBtn()
{
	try
	{
		m_stBtnFont.CreatePointFont(160,"arial") ;

		m_stBtnExit.SetFont(&m_stBtnFont) ;
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(20,20,22));
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(62,62,64));
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(0,0,0));
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255, 0, 0));
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 0, 0));
	}
	catch (...)
	{
		
	}
}

void CRunningDlg::OnBnClickedBtnExit()
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


void CRunningDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_ControlChange.OnSize(cx,cy);
	Invalidate();
}

void CRunningDlg::InitSize()
{
	m_ControlChange.SetOwner(this);
	m_ControlChange.SetResizeControl(IDC_BTN_EXIT,PK_TOP_LEFT,PK_TOP_RIGHT,PK_BOTTOM_LEFT,PK_BOTTOM_RIGHT);
}