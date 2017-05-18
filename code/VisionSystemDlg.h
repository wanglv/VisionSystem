
// VisionSystemDlg.h : 头文件
//

#pragma once
#include "DefineEnum.h"
#include "RunningDlg.h"
#include "CommuncationDlg.h"

// CVisionSystemDlg 对话框
class CVisionSystemDlg : public CDialogEx
{
public:
	CRunningDlg *m_pRunDlg ;
	CCommuncationDlg *m_pCom232 ;

	CStatic m_CtrlImageView;

	int m_nCtrlWidth ;
	int m_nCtrlHeight ;

	HTuple m_lWindowID ;

	HObject m_hImage ;

	HTuple  m_hWidth ;
	HTuple  m_hHeight ;

	CString  m_strExePath ;
public:
	void LoadPara() ;
	void LoadIniFile() ;
	void DispChildWindow(int nWindowID) ;
private:
	void InitSize() ;
	void InitImageView() ;
	void InitChildWindow() ;
	void InitDll() ;
	void LocateChildDlg(int nWindowID) ;

protected:
	CBrush   m_brush; 
	CControlChange m_ControlChange ;
	CMenu m_cSystemMenu ;
// 构造
public:
	CVisionSystemDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VISIONSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOtherRunning();
	afx_msg void OnClose();
	afx_msg void OnCommunicationCom232();
};

