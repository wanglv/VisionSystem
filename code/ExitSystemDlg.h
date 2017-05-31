#pragma once
#include "resource.h"


// CExitSystemDlg �Ի���

class CExitSystemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExitSystemDlg)
public:
	CButtonST m_stBtnOk;
	CButtonST m_stBtnCancel;

protected:
	CBrush    m_brush;
	CFont     m_stBtnFont;
	CFont     m_StaticFont;
public:
	CExitSystemDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExitSystemDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXIT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
