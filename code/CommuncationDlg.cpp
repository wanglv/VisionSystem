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
	DDX_Control(pDX, IDC_BTN_UPDATE_232, m_stBtnUpdatePara);
	DDX_Control(pDX, IDC_BTN_SEND, m_stBtnSend);
	DDX_Control(pDX, IDC_BTN_CLEAR_ALL, m_stBtnClearAll);
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

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_1:
	{
		pDC->SetBkColor(_COLOR_BLACK);
		pDC->SetTextColor(_COLOR_WHITE);
		return   m_brush;
	}
	case IDC_STATIC_2:
	{
		pDC->SetBkColor(_COLOR_BLACK);
		pDC->SetTextColor(_COLOR_WHITE);
		return   m_brush;
	}
	case IDC_STATIC_3:
	{
		pDC->SetBkColor(_COLOR_BLACK);
		pDC->SetTextColor(_COLOR_WHITE);
		return   m_brush;
	}
	case IDC_STATIC_4:
	{
		pDC->SetBkColor(_COLOR_BLACK);
		pDC->SetTextColor(_COLOR_WHITE);
		return   m_brush;
	}
	case IDC_STATIC_5:
	{
		pDC->SetBkColor(_COLOR_BLACK);
		pDC->SetTextColor(_COLOR_WHITE);
		return   m_brush;
	}
	case IDC_STATIC_232PARA:
	{
		pDC->SetBkColor(_COLOR_BLACK);
		pDC->SetTextColor(_COLOR_WHITE);
		return   m_brush;
	}
	case IDC_STATIC_SEND:
	{
		pDC->SetBkColor(_COLOR_BLACK);
		pDC->SetTextColor(_COLOR_WHITE);
		return   m_brush;
	}
	case IDC_STATIC_RECIEVE:
	{
		pDC->SetBkColor(_COLOR_BLACK);
		pDC->SetTextColor(_COLOR_WHITE);
		return   m_brush;
	}
	case IDC_EDIT_SEND_DATA:
	{
		pDC->SetBkColor(_COLOR_BLACK);
		pDC->SetTextColor(_COLOR_BLUE);
		return   m_brush;
	}
	case IDC_EDIT_RECIEVE_DATA:
	{
		pDC->SetBkColor(_COLOR_BLACK);
		pDC->SetTextColor(_COLOR_RED);
		return   m_brush;
	}
	default:
		break;
	}

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
		m_stBtnFont.CreatePointFont(160, "arial");
		m_stBtnExit.SetFont(&m_stBtnFont);
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_BK_OUT, _COLOR_BK);
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_BK_IN, _COLOR_BK_IN);
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, _COLOR_BK);
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_FG_OUT, _COLOR_RED);
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_FG_IN, _COLOR_RED);
		m_stBtnExit.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, _COLOR_RED);

		m_stBtnFont2.CreatePointFont(100, "arial");

		m_stBtnUpdatePara.SetFont(&m_stBtnFont2);
		m_stBtnUpdatePara.SetColor(CButtonST::BTNST_COLOR_BK_OUT, _COLOR_BK);
		m_stBtnUpdatePara.SetColor(CButtonST::BTNST_COLOR_BK_IN, _COLOR_BK_IN);
		m_stBtnUpdatePara.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, _COLOR_BK);
		m_stBtnUpdatePara.SetColor(CButtonST::BTNST_COLOR_FG_OUT, _COLOR_BLUE);
		m_stBtnUpdatePara.SetColor(CButtonST::BTNST_COLOR_FG_IN, _COLOR_BLUE);
		m_stBtnUpdatePara.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, _COLOR_BLUE);

		m_stBtnSend.SetFont(&m_stBtnFont2);
		m_stBtnSend.SetColor(CButtonST::BTNST_COLOR_BK_OUT, _COLOR_BK);
		m_stBtnSend.SetColor(CButtonST::BTNST_COLOR_BK_IN, _COLOR_BK_IN);
		m_stBtnSend.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, _COLOR_BK);
		m_stBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_OUT, _COLOR_BLUE);
		m_stBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_IN, _COLOR_BLUE);
		m_stBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, _COLOR_BLUE);

		m_stBtnClearAll.SetFont(&m_stBtnFont2);
		m_stBtnClearAll.SetColor(CButtonST::BTNST_COLOR_BK_OUT, _COLOR_BK);
		m_stBtnClearAll.SetColor(CButtonST::BTNST_COLOR_BK_IN, _COLOR_BK_IN);
		m_stBtnClearAll.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, _COLOR_BK);
		m_stBtnClearAll.SetColor(CButtonST::BTNST_COLOR_FG_OUT, _COLOR_BLUE);
		m_stBtnClearAll.SetColor(CButtonST::BTNST_COLOR_FG_IN, _COLOR_BLUE);
		m_stBtnClearAll.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, _COLOR_BLUE);
	}
	catch (...)
	{

	}
}

void CCommuncationDlg::InitSize()
{
	m_ControlChange.SetOwner(this);
	m_ControlChange.SetResizeControl(IDC_BTN_EXIT, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_BTN_UPDATE_232, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_BTN_SEND, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_BTN_CLEAR_ALL, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);

	m_ControlChange.SetResizeControl(IDC_STATIC_232PARA, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_SEND, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_RECIEVE, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);

	m_ControlChange.SetResizeControl(IDC_STATIC_1, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_2, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_3, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_4, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_5, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);

	m_ControlChange.SetResizeControl(IDC_COMBO_PORT, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_COMBO_PAUD, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_COMBO_PARITY, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_COMBO_BITSIZE, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_COMBO_STOPBIT, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);

	m_ControlChange.SetResizeControl(IDC_EDIT_SEND_DATA, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_EDIT_RECIEVE_DATA, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
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
