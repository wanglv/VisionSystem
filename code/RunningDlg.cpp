// RunningDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionSystem.h"
#include "RunningDlg.h"
#include "afxdialogex.h"
#include "VisionSystemDlg.h"

// CRunningDlg �Ի���

IMPLEMENT_DYNAMIC(CRunningDlg, CDialogEx)

CRunningDlg::CRunningDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRunningDlg::IDD, pParent)
{
	m_brush.CreateSolidBrush(RGB(20,20,22));   //   ����ˢ��
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


// CRunningDlg ��Ϣ�������


BOOL CRunningDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMenu* pMenu = this->GetSystemMenu(FALSE);//ϵͳ�˵�
	pMenu->ModifyMenu(SC_CLOSE,MF_BYCOMMAND | MF_GRAYED );//���ùرհ�ť
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitStBtn() ;

	InitSize() ;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CRunningDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


HBRUSH CRunningDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor   ==CTLCOLOR_DLG)    
		return   m_brush;
	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
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