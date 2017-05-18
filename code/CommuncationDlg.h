#pragma once
#include "resource.h"

// CCommuncationDlg �Ի���

class CCommuncationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommuncationDlg)
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
	CCommuncationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCommuncationDlg();

// �Ի�������
	enum { IDD = IDD_COMMUNICATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnExit();
};
