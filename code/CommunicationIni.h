#pragma once
#include "DefineEnum.h"
#include "..\Inc\CommInc\BaseIni.h"
class CCommunicationIni :
	public CBaseIniEx
{
public:
	int m_nConnectType;
	int m_nBaudRate;
	int m_nBitSize;
	int m_nPort;
	int m_nParity;
	int m_nStopBit;
public:
	CCommunicationIni();
	~CCommunicationIni();
	virtual BOOL Initialize(void* pvoid = NULL);

	void LoadPara();
	void WritePara();
};
extern CCommunicationIni g_CommuncationIni;

