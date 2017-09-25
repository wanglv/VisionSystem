#include "stdafx.h"
#include "CommunicationIni.h"

CCommunicationIni g_CommuncationIni;

CCommunicationIni::CCommunicationIni()
{
}


CCommunicationIni::~CCommunicationIni()
{
}

BOOL CCommunicationIni::Initialize(void *pvoid)
{
	if (!CBaseIni::Initialize(pvoid))
		return FALSE;
	////////////
	SetInitStatus(FALSE);
	if (!pvoid) return FALSE;
	::_tcscpy(m_szFileName, (LPCTSTR)pvoid);
	SetInitStatus(TRUE);
	////////////
	LoadPara();
	WritePara();

	return IsInitialized();
}

void CCommunicationIni::LoadPara()
{
	const TCHAR szSections[][64] = {
		{ _T("Comm232Para") },//0
	};

	m_nConnectType = ReadInt(szSections[0], "Connect_Type", _232_COMM);
	m_nBitSize = ReadInt(szSections[0], "Bits_Size", 4);
	m_nPort = ReadInt(szSections[0], _T("Port"), 2);
	m_nParity = ReadInt(szSections[0], _T("Parity"), 0);
	m_nStopBit = ReadInt(szSections[0], _T("Stop_Bits"), 0);
	m_nBaudRate = ReadInt(szSections[0], _T("Baud_Rate"), 3);

}

void CCommunicationIni::WritePara()
{
	const TCHAR szSections[][64] = {
		{ _T("OptionPara") },//0
	};

	WriteInt(szSections[0], "Connect_Type", m_nConnectType);
	WriteInt(szSections[0], "Bits_Size", m_nBitSize);
	WriteInt(szSections[0], "Port", m_nPort);
	WriteInt(szSections[0], "Parity", m_nParity);
	WriteInt(szSections[0], "Stop_Bits", m_nStopBit);
	WriteInt(szSections[0], "Baud_Rate", m_nBaudRate);
}

