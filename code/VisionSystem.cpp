
// VisionSystem.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "VisionSystem.h"
#include "VisionSystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVisionSystemApp

BEGIN_MESSAGE_MAP(CVisionSystemApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CVisionSystemApp ����

CVisionSystemApp::CVisionSystemApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CVisionSystemApp ����

CVisionSystemApp theApp;


// CVisionSystemApp ��ʼ��

BOOL CVisionSystemApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	m_myMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "VisionSystem Mutex");

	if (m_myMutex == NULL)
	{   //��ʾû������ʵ������
		m_myMutex = ::CreateMutexA(NULL, TRUE, "VisionSystem Mutex");
	}
	else
	{   //��ʾ��ǰ������ʵ������
		AfxMessageBox("Software running, please don't repeat to open!");

		if (m_myMutex != NULL)
		{
			ReleaseMutex(m_myMutex);

			m_myMutex = NULL;
		}

		return FALSE;
	}

	//AfxInitRichEdit();
	AfxInitRichEdit2();

	CVisionSystemDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CVisionSystemApp::ExitInstance()
{
	if (m_myMutex != NULL)
	{
		ReleaseMutex(m_myMutex);

		m_myMutex = NULL;
	}

	return CWinApp::ExitInstance();
}
