
// VisionSystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionSystem.h"
#include "VisionSystemDlg.h"
#include "afxdialogex.h"
#include "ExitSystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// CVisionSystemDlg 对话框




CVisionSystemDlg::CVisionSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVisionSystemDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_brush.CreateSolidBrush(_COLOR_BK);   //   生成刷子 
}

void CVisionSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VIEW, m_CtrlImageView);
	DDX_Control(pDX, IDC_RICHEDIT_SYSTIPS, m_ctlSysTipsDisplay);
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
	ON_MESSAGE(WM_STATICMOUSE, OnStaticMouseMove)
END_MESSAGE_MAP()


// CVisionSystemDlg 消息处理程序

BOOL CVisionSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitDll() ;

	InitChildWindow() ;

	InitImageView() ;

	m_cSystemMenu.LoadMenu(IDR_MENU_SYS) ;
	SetMenu ( &m_cSystemMenu );

	//适应窗口
	InitSize() ;

	//加载参数
	LoadPara()  ;
	//button初始化 m_btnCamMenu---CButtonST
	/*m_btnCamMenu.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(20,20,22));
	m_btnCamMenu.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(62,62,64));
	m_btnCamMenu.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(0,0,0));
	m_btnCamMenu.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255, 255, 255));
	m_btnCamMenu.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnCamMenu.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
	*/
	m_ctlSysTipsDisplay.SetBackgroundColor(FALSE, _COLOR_BK);
	SetSysTipsInfo(LoadStringTable(IDS_INIT_OK), _COLOR_GREEN);

	//return FALSE;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVisionSystemDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CExitSystemDlg exitDlg;
	if (exitDlg.DoModal() != IDOK)
		return;

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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVisionSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVisionSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CVisionSystemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor   ==CTLCOLOR_DLG)    
		return   m_brush;

	//其他控件背景、字体颜色设置
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_CHILD_PAGE:
		{
			pDC->SetBkColor(_COLOR_BLACK) ;
			pDC->SetTextColor(_COLOR_WHITE) ;
			return   m_brush;
		}
	case IDC_STATIC_ROW:
		{
			pDC->SetBkColor(_COLOR_BLACK);
			pDC->SetTextColor(_COLOR_WHITE);
			return   m_brush;
		}
	case IDC_STATIC_COL:
		{
			pDC->SetBkColor(_COLOR_BLACK);
			pDC->SetTextColor(_COLOR_WHITE);
			return   m_brush;
		}
	case IDC_STATIC_GRAY:
		{
			pDC->SetBkColor(_COLOR_BLACK);
			pDC->SetTextColor(_COLOR_WHITE);
			return   m_brush;
		}
	case IDC_STATIC_CAM_RATE:
		{
			pDC->SetBkColor(_COLOR_BLACK);
			pDC->SetTextColor(_COLOR_WHITE);
			return   m_brush;
		}
	default:
		break;
	}

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
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

//自动适应窗体变化
void CVisionSystemDlg::InitSize()
{
	m_ControlChange.SetOwner(this);
	m_ControlChange.SetResizeControl(IDC_RICHEDIT_SYSTIPS, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_CHILD_PAGE,PK_TOP_LEFT,PK_TOP_RIGHT,PK_BOTTOM_LEFT,PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_VIEW,PK_TOP_LEFT,PK_TOP_RIGHT,PK_BOTTOM_LEFT,PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_ROW, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_COL, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_GRAY, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
	m_ControlChange.SetResizeControl(IDC_STATIC_CAM_RATE, PK_TOP_LEFT, PK_TOP_RIGHT, PK_BOTTOM_LEFT, PK_BOTTOM_RIGHT);
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
		SetSysTipsInfo(LoadStringTable(IDS_INIT_VIEW_ERR), _COLOR_RED);
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
		SetSysTipsInfo(LoadStringTable(IDS_INIT_RUNNING_DLG_OK), _COLOR_GREEN);

		m_pCom232 = NULL ;
		m_pCom232 = new CCommuncationDlg ;
		m_pCom232->Create(IDD_COMMUNICATION_DIALOG,this) ;
		SetSysTipsInfo(LoadStringTable(IDS_INIT_232DLG_SUCCESS), _COLOR_GREEN);

	}
	catch (...)
	{
		SetSysTipsInfo(LoadStringTable(IDS_INIT_CHILD_DLG_ERR), _COLOR_RED);
	}
}

void CVisionSystemDlg::InitDll()
{
	try
	{
		g_pVisionComm = CreateInterface() ;
		if (NULL == g_pVisionComm)
		{
			AfxMessageBox(_T("VisionComm Err"));
			EndDialog(IDOK);
			return;
		}
		else
			SetSysTipsInfo(LoadStringTable(IDS_LOAD_DLL_OK),_COLOR_GREEN);
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
		//Load system Ini file
		SetSysTipsInfo(LoadStringTable(IDS_LOAD_SYS_INI), _COLOR_YELLOW);
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

		//Load Comm232ParaFileIni
		strSysParaFile = m_strExePath + "Config\\IniFile\\Comm232.ini";
		_tcscpy(szBuffer, strSysParaFile);
		g_CommuncationIni.Initialize(szBuffer);

		m_pCom232->LoadCom232Para();
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

void CVisionSystemDlg::SetSysTipsInfo(CString strInfo, COLORREF crColor)
{
	try
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(CHARFORMAT));

		m_ctlSysTipsDisplay.GetSelectionCharFormat(cf);
		cf.dwMask = CFM_COLOR | CFM_SIZE;
		cf.yHeight = 218;
		cf.cbSize = 1000;
		cf.crTextColor = crColor;
		cf.dwEffects = 0;
		m_ctlSysTipsDisplay.SetSelectionCharFormat(cf);

		CString strLine = _T(""), strEdit = _T("");

		m_ctlSysTipsDisplay.GetWindowText(strEdit);
		m_ctlSysTipsDisplay.SetSel(-1, -1);
		strLine.Format("%s\r\n", strInfo);
		m_ctlSysTipsDisplay.ReplaceSel(strLine);
		

		HWND  hWnd = (HWND)m_ctlSysTipsDisplay;
		int line = ::SendMessage(hWnd, EM_GETFIRSTVISIBLELINE, 0, 0);
		int linecount = ::SendMessage(hWnd, EM_GETLINECOUNT, 0, 0);

		::SendMessage(hWnd, EM_LINESCROLL, 0, (linecount - line - 2));

		//Cancel select all text in richedit control
		m_ctlSysTipsDisplay.SetOptions(ECOOP_OR, ECO_SAVESEL);
	}
	catch (...)
	{

	}
	
}

CString CVisionSystemDlg::LoadStringTable(int nID)
{
	
	CString strTable("");
	strTable.LoadString(nID);

	return strTable;
	
}

LRESULT  CVisionSystemDlg::OnStaticMouseMove(WPARAM wParam, LPARAM lParam)
{
	try
	{
		HTuple hRow, hCol,hGray;
		CString strRow(""), strCol(""), strGray("");
		hRow = hCol = hGray = HTuple();

		SetCheck("~give_error");
		GetMposition(m_lWindowID, &hRow, &hCol, NULL);
		if (hRow.TupleNumber() < 1)
			return 0L;
		GetGrayval(m_hImage, hRow, hCol, &hGray);

		strRow.Format("Row:%.0f", hRow[0].D());
		strCol.Format("Col:%.0f", hCol[0].D());
		strGray.Format("Gray:%.0f", hGray[0].D());

		GetDlgItem(IDC_STATIC_ROW)->SetWindowText(strRow);
		GetDlgItem(IDC_STATIC_COL)->SetWindowText(strCol);
		GetDlgItem(IDC_STATIC_GRAY)->SetWindowText(strGray);
	}
	catch (HException& except)
	{
		
	}

	return 1L;
}