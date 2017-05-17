#pragma once
#include "afxwin.h"
#include "resource.h"
// CRunningDlg �Ի���

class CRunningDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRunningDlg)
public:
	CButtonST m_stBtnExit ;
protected:
	CBrush   m_brush; 
	CFont     m_stBtnFont ;
	CControlChange m_ControlChange ;
private:
	void InitStBtn() ;
	void InitSize() ;
public:
	CRunningDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRunningDlg();

// �Ի�������
	enum { IDD = IDD_RUNNING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
