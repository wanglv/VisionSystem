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
	, m_strSendData(_T(""))
	, m_strRecieveData(_T(""))
{
	m_brush.CreateSolidBrush(_COLOR_BK);   //   生成刷子
	m_bConnect = FALSE;
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
	DDX_Control(pDX, IDC_COMBO_PORT, m_ComboPort);
	DDX_Control(pDX, IDC_COMBO_PAUD, m_ComboPaud);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_ComboParity);
	DDX_Control(pDX, IDC_COMBO_BITSIZE, m_ComboBitSize);
	DDX_Control(pDX, IDC_COMBO_STOPBIT, m_ComboStopBit);
	DDX_Control(pDX, IDC_MSCOMM1, m_MsComm1);
	DDX_Text(pDX, IDC_EDIT_SEND_DATA, m_strSendData);
	DDX_Text(pDX, IDC_EDIT_RECIEVE_DATA, m_strRecieveData);
}


BEGIN_MESSAGE_MAP(CCommuncationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_EXIT, &CCommuncationDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_UPDATE_232, &CCommuncationDlg::OnBnClickedBtnUpdate232)
	ON_BN_CLICKED(IDC_BTN_SEND, &CCommuncationDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_CLEAR_ALL, &CCommuncationDlg::OnBnClickedBtnClearAll)
	ON_CBN_SELCHANGE(IDC_COMBO_PORT, &CCommuncationDlg::OnCbnSelchangeComboPort)
	ON_CBN_SELCHANGE(IDC_COMBO_PAUD, &CCommuncationDlg::OnCbnSelchangeComboPaud)
	ON_CBN_SELCHANGE(IDC_COMBO_PARITY, &CCommuncationDlg::OnCbnSelchangeComboParity)
	ON_CBN_SELCHANGE(IDC_COMBO_BITSIZE, &CCommuncationDlg::OnCbnSelchangeComboBitsize)
	ON_CBN_SELCHANGE(IDC_COMBO_STOPBIT, &CCommuncationDlg::OnCbnSelchangeComboStopbit)
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

	//LoadCom232Para();

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
		pDC->SetTextColor(_COLOR_GREEN);
		return   m_brush;
	}
	case IDC_EDIT_RECIEVE_DATA:
	{
		pDC->SetBkColor(_COLOR_BLACK);
		pDC->SetTextColor(_COLOR_GREEN);
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
		m_stBtnUpdatePara.SetColor(CButtonST::BTNST_COLOR_FG_OUT, _COLOR_WHITE);
		m_stBtnUpdatePara.SetColor(CButtonST::BTNST_COLOR_FG_IN, _COLOR_WHITE);
		m_stBtnUpdatePara.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, _COLOR_WHITE);

		m_stBtnSend.SetFont(&m_stBtnFont2);
		m_stBtnSend.SetColor(CButtonST::BTNST_COLOR_BK_OUT, _COLOR_BK);
		m_stBtnSend.SetColor(CButtonST::BTNST_COLOR_BK_IN, _COLOR_BK_IN);
		m_stBtnSend.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, _COLOR_BK);
		m_stBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_OUT, _COLOR_WHITE);
		m_stBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_IN, _COLOR_WHITE);
		m_stBtnSend.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, _COLOR_WHITE);

		m_stBtnClearAll.SetFont(&m_stBtnFont2);
		m_stBtnClearAll.SetColor(CButtonST::BTNST_COLOR_BK_OUT, _COLOR_BK);
		m_stBtnClearAll.SetColor(CButtonST::BTNST_COLOR_BK_IN, _COLOR_BK_IN);
		m_stBtnClearAll.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, _COLOR_BK);
		m_stBtnClearAll.SetColor(CButtonST::BTNST_COLOR_FG_OUT, _COLOR_WHITE);
		m_stBtnClearAll.SetColor(CButtonST::BTNST_COLOR_FG_IN, _COLOR_WHITE);
		m_stBtnClearAll.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, _COLOR_WHITE);
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


void CCommuncationDlg::OnBnClickedBtnUpdate232()
{
	try
	{
		InitConnection();

		if (m_bConnect)
		{
			AfxMessageBox("串口设置成功");
			m_bConnect = FALSE;
		}
	}
	catch (...)
	{

	}
}


void CCommuncationDlg::OnBnClickedBtnSend()
{
	try
	{
		UpdateData(TRUE);

		if (m_MsComm1.get_PortOpen())
		{
			m_MsComm1.put_Output((COleVariant)m_strSendData);
		}
	}
	catch (...)
	{
		
	}
}


void CCommuncationDlg::OnBnClickedBtnClearAll()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCommuncationDlg::OnCbnSelchangeComboPort()
{
	try
	{
		g_CommuncationIni.m_nPort = m_ComboPort.GetCurSel();
		g_CommuncationIni.WritePara();
	}
	catch (...)
	{
		
	}
}


void CCommuncationDlg::OnCbnSelchangeComboPaud()
{
	try
	{
		g_CommuncationIni.m_nBaudRate = m_ComboPaud.GetCurSel();
		g_CommuncationIni.WritePara();
	}
	catch (...)
	{

	}
}


void CCommuncationDlg::OnCbnSelchangeComboParity()
{
	try
	{
		g_CommuncationIni.m_nParity = m_ComboParity.GetCurSel();
		g_CommuncationIni.WritePara();
	}
	catch (...)
	{

	}
}


void CCommuncationDlg::OnCbnSelchangeComboBitsize()
{
	try
	{
		g_CommuncationIni.m_nBitSize = m_ComboBitSize.GetCurSel();
		g_CommuncationIni.WritePara();
	}
	catch (...)
	{

	}
}


void CCommuncationDlg::OnCbnSelchangeComboStopbit()
{
	try
	{
		g_CommuncationIni.m_nStopBit = m_ComboStopBit.GetCurSel();
		g_CommuncationIni.WritePara();
	}
	catch (...)
	{

	}
}

void CCommuncationDlg::LoadCom232Para()
{
	try
	{
		g_CommuncationIni.LoadPara();

		m_ComboPort.SetCurSel(g_CommuncationIni.m_nPort);
		m_ComboParity.SetCurSel(g_CommuncationIni.m_nParity);
		m_ComboBitSize.SetCurSel(g_CommuncationIni.m_nBitSize);
		m_ComboStopBit.SetCurSel(g_CommuncationIni.m_nStopBit);
		m_ComboPaud.SetCurSel(g_CommuncationIni.m_nBaudRate);

	}
	catch (...)
	{

	}
}

void CCommuncationDlg::InitConnection()
{
	try
	{
		g_CommuncationIni.LoadPara();

		int nPort[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		//
		int nBaudTable[11] = { 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600,
			115200, 128000
		};
		//....
		int nDataBitsTable[5] = { 4, 5, 6, 7, 8 };
		//...
		CString  strParityTable[5] = { "n", "o", "e", "m", "s" };
		//...
		int nStopBitsTable[3] = { 1, 1.5, 2 };

		CString strStatus = _T("");

		CString strComSeting;
		CString strTmp;
		CString strCommOther = _T("");
		strCommOther.Format(",%d,%d", nDataBitsTable[g_CommuncationIni.m_nBitSize], nStopBitsTable[g_CommuncationIni.m_nStopBit]);
		strTmp.Format("%d", nBaudTable[g_CommuncationIni.m_nBaudRate]);
		strComSeting += strTmp;
		strComSeting += ",";
		strComSeting += strParityTable[g_CommuncationIni.m_nParity];
		strComSeting += strCommOther;

		if (!m_MsComm1.get_PortOpen())
		{
			m_MsComm1.put_CommPort(nPort[g_CommuncationIni.m_nPort]);
			m_MsComm1.put_Settings(strComSeting);
			m_MsComm1.put_RThreshold(2);
			m_MsComm1.put_InBufferSize(2048);
			m_MsComm1.put_OutBufferSize(2048);
			m_MsComm1.put_PortOpen(TRUE);

			m_bConnect = TRUE;
		}
		else
		{
			CString strPort;
			strPort.Format("串口:%d已经打开", g_CommuncationIni.m_nPort+1);
			AfxMessageBox(strPort);
		}
	}
	catch (...)
	{
		m_bConnect = FALSE;
	}
}

BEGIN_EVENTSINK_MAP(CCommuncationDlg, CDialogEx)
ON_EVENT(CCommuncationDlg, IDC_MSCOMM1, 1, CCommuncationDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CCommuncationDlg::OnCommMscomm1()
{
	try
	{
		ReceiveFromComm();

		GetDlgItem(IDC_EDIT_RECIEVE_DATA)->SetWindowText(m_strRecieveData);
	}
	catch (...)
	{
		
	}
}

void CCommuncationDlg::ReceiveFromComm()
{
	try
	{
		m_strRecieveData = _T("");
		short iEvent = m_MsComm1.get_CommEvent();

		if (iEvent == 2)
		{
			while (1)
			{
				Sleep(10);
				::DoEvent();
				CString strTemp = _T("");
				strTemp = m_MsComm1.get_Input().bstrVal;

				if (strTemp.IsEmpty())
				{
					break;
				}

				m_strRecieveData += strTemp;

			}
		}
	}
	catch (...)
	{
		
	}
}