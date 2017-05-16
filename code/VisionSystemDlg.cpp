
// VisionSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionSystem.h"
#include "VisionSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVisionSystemDlg �Ի���




CVisionSystemDlg::CVisionSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVisionSystemDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_brush.CreateSolidBrush(RGB(20,20,22));   //   ����ˢ�� 
}

void CVisionSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VIEW, m_CtrlImageView);
}

BEGIN_MESSAGE_MAP(CVisionSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CVisionSystemDlg ��Ϣ��������

BOOL CVisionSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ����Ӷ���ĳ�ʼ������
	g_pVisionComm = CreateInterface() ;
	if (NULL == g_pVisionComm)
	{
		AfxMessageBox(_T("VisionComm Err")) ;
		EndDialog(IDOK);
		return FALSE;
	}

	InitImageView() ;

	m_cSystemMenu.LoadMenu(IDR_MENU_SYS) ;
	SetMenu ( &m_cSystemMenu );

	//button��ʼ�� m_btnCamMenu---CButtonST
	/*m_btnCamMenu.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(20,20,22));
	m_btnCamMenu.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(62,62,64));
	m_btnCamMenu.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(0,0,0));
	m_btnCamMenu.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255, 255, 255));
	m_btnCamMenu.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnCamMenu.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
	*/


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CVisionSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVisionSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVisionSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CVisionSystemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor   ==CTLCOLOR_DLG)    
		return   m_brush;

	//�����ؼ�������������ɫ����
	switch(pWnd->GetDlgCtrlID())
	{
		/*case IDC_RADIO1:
		{
		pDC->SetBkColor(RGB(0,0,0)) ;
		pDC->SetTextColor(RGB(255,255,255)) ;
		return   m_brush;
		}*/
	}

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CVisionSystemDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_ControlChange.OnSize(cx,cy);
	Invalidate();
}

//�Զ���Ӧ����仯
void CVisionSystemDlg::InitSize()
{
	/*m_ControlChange.SetOwner(this);
	m_ControlChange.SetResizeControl(IDC_BTN_CAM_MENU,PK_TOP_LEFT,PK_TOP_RIGHT,PK_BOTTOM_LEFT,PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_BTN_STATION_MENU,PK_TOP_LEFT,PK_TOP_RIGHT,PK_BOTTOM_LEFT,PK_BOTTOM_RIGHT);*/
}

void CVisionSystemDlg::InitImageView()
{
	CRect Rect;
	m_CtrlImageView.GetClientRect(Rect);
	m_nCtrlWidth =Rect.Width();
	m_nCtrlHeight=Rect.Height();
	//
	long lWindowID=0;
	lWindowID = (long)m_CtrlImageView.GetSafeHwnd();

	try
	{
		/*TCHAR chPath[MAX_PATH] ;
		GetExepath(chPath) ;
		m_strExePath = chPath ;

		CString strMdlImgPath = m_strExePath + "1.bmp" ;


		Hkey lTmp = m_hImage.Key();
		ReadImage(&m_hImage,(HTuple)strMdlImgPath) ;
		GetImageSize(m_hImage,&m_hWidth,&m_hHeight) ;*/
		m_hWidth = 1600 ;
		m_hHeight = 1200 ;

		g_pVisionComm->_V_Comm_InitCtrl(m_nCtrlWidth,m_nCtrlHeight,lWindowID,m_hWidth,m_hHeight,&m_lWindowID) ;

		if (!g_pVisionComm->_V_Comm_HObjectIsEmpty(m_hImage))
			DispObj(m_hImage,m_lWindowID) ;

	}
	catch (HException &except)
	{
	}

}