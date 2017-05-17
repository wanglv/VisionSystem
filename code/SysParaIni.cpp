#include "StdAfx.h"
#include "SysParaIni.h"

CSysParaIni g_SysPara ;

CSysParaIni::CSysParaIni(void)
{
}


CSysParaIni::~CSysParaIni(void)
{
}

BOOL CSysParaIni::Initialize(void *pvoid)
{
	if( !CBaseIni::Initialize(pvoid) )
		return FALSE;
	////////////
	SetInitStatus(FALSE);
	if( !pvoid ) return FALSE;
	::_tcscpy(m_szFileName,(LPCTSTR) pvoid);
	SetInitStatus(TRUE);
	////////////
	LoadPara();
	WritePara();

	return IsInitialized();
}

void CSysParaIni::LoadPara()
{
	const TCHAR szSections[][64]={
		{_T("OptionPara")},//0
	};

	m_strVersion = ReadString(szSections[0],_T("Soft_Version"),"V1.0.0") ;
	//m_lImageWidth = ReadInt(szSections[0],_T("Cam1_Width"),4608) ;
}

void CSysParaIni::WritePara()
{
	const TCHAR szSections[][64]={
		{_T("OptionPara")},//0
	};

	//WriteInt(szSections[0],_T("Cam1_Width"),m_lImageWidth) ;
}