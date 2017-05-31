// ExitSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionSystem.h"
#include "ExitSystemDlg.h"
#include "afxdialogex.h"
#include "DefineEnum.h"

// CExitSystemDlg �Ի���

IMPLEMENT_DYNAMIC(CExitSystemDlg, CDialogEx)

CExitSystemDlg::CExitSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EXIT_DIALOG, pParent)
{
	m_brush.CreateSolidBrush(_COLOR_BK);   //   ����ˢ��
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


// CExitSystemDlg ��Ϣ�������


BOOL CExitSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMenu* pMenu = this->GetSystemMenu(FALSE);//ϵͳ�˵�
	pMenu->ModifyMenu(SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);//���ùرհ�ť
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_stBtnFont.CreatePointFont(150, _T("΢���ź�"));
	m_StaticFont.CreatePointFont(200, _T("΢���ź�"));

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
				  // �쳣: OCX ����ҳӦ���� FALSE
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

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
