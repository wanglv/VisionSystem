#pragma once
#include "../inc/comminc/baseini.h"
class CSysParaIni :
	public CBaseIniEx
{
public:
	CString m_strVersion ; //�汾��
public:
	CSysParaIni(void);
	~CSysParaIni(void);

	void LoadPara() ;
	void WritePara() ;
	virtual BOOL Initialize(void* pvoid=NULL);
};

extern CSysParaIni g_SysPara ;