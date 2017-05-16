
// VisionSystemDlg.h : 头文件
//

#pragma once


// CVisionSystemDlg 对话框
class CVisionSystemDlg : public CDialogEx
{
public:
	CMenu m_cSystemMenu ;
	CControlChange m_ControlChange ;
	CStatic m_CtrlImageView;

	int m_nCtrlWidth ;
	int m_nCtrlHeight ;

	HTuple m_lWindowID ;

	HObject m_hImage ;

	HTuple  m_hWidth ;
	HTuple  m_hHeight ;
public:
	void InitSize() ;
	void InitImageView() ;

protected:
	CBrush   m_brush; 
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
};
