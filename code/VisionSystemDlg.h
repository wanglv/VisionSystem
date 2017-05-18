
// VisionSystemDlg.h : ͷ�ļ�
//

#pragma once
#include "DefineEnum.h"
#include "RunningDlg.h"
#include "CommuncationDlg.h"

// CVisionSystemDlg �Ի���
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
// ����
public:
	CVisionSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VISIONSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

