
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
	ON_COMMAND(ID_OTHER_RUNNING, &CVisionSystemDlg::OnOtherRunning)
	ON_WM_CLOSE()
	ON_COMMAND(ID_COMMUNICATION_COM232, &CVisionSystemDlg::OnCommunicationCom232)
END_MESSAGE_MAP()


// CVisionSystemDlg ��Ϣ�������

BOOL CVisionSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitDll() ;

	InitChildWindow() ;

	InitImageView() ;

	m_cSystemMenu.LoadMenu(IDR_MENU_SYS) ;
	SetMenu ( &m_cSystemMenu );

	//��Ӧ����
	InitSize() ;

	//���ز���
	LoadPara()  ;
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

void CVisionSystemDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_pRunDlg != NULL)
	{
		m_pRunDlg->DestroyWindow() ;
		delete m_pRunDlg ;
		m_pRunDlg = NULL ;
	}

	if (m_pCom232 != NULL)
	{
		m_pCom232->DestroyWindow() ;
		delete m_pCom232 ;
		m_pCom232 = NULL ;
	}

	CDialogEx::OnClose();
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

// �����Ի��������С����ť������Ҫ����Ĵ���
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
	case IDC_STATIC_CHILD_PAGE:
		{
			pDC->SetBkColor(RGB(0,0,0)) ;
			pDC->SetTextColor(RGB(255,255,255)) ;
			return   m_brush;
		}
	}

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CVisionSystemDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	static bool bFirst = TRUE ;
	if (bFirst)
	{
		bFirst = !bFirst ;
		return ;
	}
	m_ControlChange.OnSize(cx,cy);
	Invalidate();

	HalconCpp::CloseWindow(m_lWindowID) ;
	InitImageView() ;
}

//�Զ���Ӧ����仯
void CVisionSystemDlg::InitSize()
{
	m_ControlChange.SetOwner(this);
	m_ControlChange.SetResizeControl(IDC_STATIC_CHILD_PAGE,PK_TOP_LEFT,PK_TOP_RIGHT,PK_BOTTOM_LEFT,PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_VIEW,PK_TOP_LEFT,PK_TOP_RIGHT,PK_BOTTOM_LEFT,PK_BOTTOM_RIGHT);
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

	

	m_lWindowID = HTuple() ;
	GenEmptyObj(&m_hImage) ;
	try
	{
		TCHAR chPath[MAX_PATH] ;
		GetExepath(chPath) ;
		m_strExePath = chPath ;

		CString strMdlImgPath = m_strExePath + "Model.bmp" ;

		ReadImage(&m_hImage,(HTuple)strMdlImgPath) ;
		GetImageSize(m_hImage,&m_hWidth,&m_hHeight) ;

		
		
		
		
		
		g_pVisionComm->_V_Comm_InitCtrl(m_nCtrlWidth,m_nCtrlHeight,lWindowID,m_hWidth,m_hHeight,&m_lWindowID) ;

		
		if (!g_pVisionComm->_V_Comm_HObjectIsEmpty(m_hImage))
			DispObj(m_hImage,m_lWindowID) ;
	}
	catch (HException &except)
	{
	}

}

void CVisionSystemDlg::InitChildWindow()
{
	try
	{
		//Init Running Dialog
		m_pRunDlg = NULL ;
		m_pRunDlg = new CRunningDlg ;
		m_pRunDlg->Create(IDD_RUNNING_DIALOG,this) ;

		m_pCom232 = NULL ;
		m_pCom232 = new CCommuncationDlg ;
		m_pCom232->Create(IDD_COMMUNICATION_DIALOG,this) ;

	}
	catch (...)
	{
		
	}
}

void CVisionSystemDlg::InitDll()
{
	try
	{
		g_pVisionComm = CreateInterface() ;
		if (NULL == g_pVisionComm)
		{
			AfxMessageBox(_T("VisionComm Err")) ;
			EndDialog(IDOK);
			return ;
		}
	}
	catch (...)
	{
		
	}
}

void CVisionSystemDlg::DispChildWindow(int nWindowID)
{
	try
	{
		switch(nWindowID)
		{
		case _MAIN_DLG:
			{
				this->ShowWindow(SW_SHOW) ;
				m_pRunDlg->ShowWindow(SW_HIDE) ;
				m_pCom232->ShowWindow(SW_HIDE) ;

				this->CenterWindow() ;

				break ;
			}
		case _RUNNING_DLG:
			{
				this->ShowWindow(SW_HIDE) ;
				m_pRunDlg->ShowWindow(SW_SHOW) ;
				m_pCom232->ShowWindow(SW_HIDE) ;

				m_pRunDlg->CenterWindow() ;

				break;
			}
		case _COM232_DLG:
			{
				this->ShowWindow(SW_SHOW) ;
				m_pRunDlg->ShowWindow(SW_HIDE) ;
				m_pCom232->ShowWindow(SW_SHOW) ;

				
				LocateChildDlg(_COM232_DLG) ;
				break;
			}
		default:
			return ;
		}
	}
	catch (...)
	{
		
	}
	
}

void CVisionSystemDlg::OnOtherRunning()
{
	try
	{
		DispChildWindow(_RUNNING_DLG) ;
	}
	catch (...)
	{
		
	}
}

void CVisionSystemDlg::LoadPara() 
{
	try
	{
		LoadIniFile()  ;
	}
	catch (...)
	{
		
	}
}

void CVisionSystemDlg::LoadIniFile() 
{
	try
	{
		
		CString strSysParaFile("") ;

		//Load SysParaFileIni
		strSysParaFile = m_strExePath + "Config\\IniFile\\SysPara.ini" ;
		TCHAR szBuffer[MAX_PATH] ;
		_tcscpy ( szBuffer, strSysParaFile ) ;
		g_SysPara.Initialize ( szBuffer ) ;

		g_SysPara.LoadPara() ;
		this->SetWindowText(g_SysPara.m_strVersion) ;
	}
	catch (...)
	{

	}
}

void CVisionSystemDlg::LocateChildDlg(int nWindowID)
{
	try
	{
		CRect lpRec ;
		int nDlgLeft,nDlgTop ;
		GetDlgItem(IDC_STATIC_CHILD_PAGE)->GetWindowRect(&lpRec) ;
		nDlgLeft = lpRec.left ;
		nDlgTop = lpRec.top ;

		switch(nWindowID)
		{
		case _COM232_DLG:
			{
				m_pCom232->SetWindowPos(NULL,nDlgLeft,nDlgTop,0,0,SWP_NOZORDER | SWP_NOSIZE ) ;
				break;
			}
		default:
			return ;
		}
	}
	catch (...)
	{
		
	}
}


void CVisionSystemDlg::OnCommunicationCom232()
{
	try
	{
		DispChildWindow(_COM232_DLG) ;
	}
	catch (...)
	{
		
	}
}
