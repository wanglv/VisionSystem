#pragma once
#include "resource.h"
#include "afxwin.h"
#include "mscomm1.h"

// CCommuncationDlg 对话框

class CCommuncationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommuncationDlg)
public:
	CMscomm1 m_MsComm1;
	CString m_strSendData;
	CString m_strRecieveData;

	CButtonST m_stBtnExit ;

	CButtonST m_stBtnUpdatePara;
	CButtonST m_stBtnSend;
	CButtonST m_stBtnClearAll;

	CComboBox m_ComboPort;
	CComboBox m_ComboPaud;
	CComboBox m_ComboParity;
	CComboBox m_ComboBitSize;
	CComboBox m_ComboStopBit;

	BOOL m_bConnect;
protected:
	CBrush   m_brush; 
	CFont     m_stBtnFont ;
	CFont     m_stBtnFont2;
	CControlChange m_ControlChange ;

public:
	void LoadCom232Para();
	void InitConnection();
	void ReceiveFromComm();
private:
	void InitStBtn() ;
	void InitSize() ;
public:
	CCommuncationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCommuncationDlg();

// 对话框数据
	enum { IDD = IDD_COMMUNICATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnUpdate232();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnClearAll();
	afx_msg void OnCbnSelchangeComboPort();
	afx_msg void OnCbnSelchangeComboPaud();
	afx_msg void OnCbnSelchangeComboParity();
	afx_msg void OnCbnSelchangeComboBitsize();
	afx_msg void OnCbnSelchangeComboStopbit();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
};
