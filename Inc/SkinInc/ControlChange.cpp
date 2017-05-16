// ControlChange.cpp: implementation of the CControlChange class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ControlChange.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CControlChange::CControlChange()
{

}

CControlChange::~CControlChange()
{

}

void CControlChange::SetOwner(CWnd *pWnd)
{
    m_pWnd=pWnd;
	pWnd->GetClientRect(&m_rtParent);
}

void CControlChange::OnSize(int cx,int cy)
{
	CRect rt;
	for (int i=0;i<m_arrControlChange.GetSize();i++)
	{
		rt=m_arrControlChange.GetAt(i).rt;
		rt.left=rt.left*cx/m_rtParent.Width();
		rt.right=rt.right*cx/m_rtParent.Width();
		rt.top=rt.top*cy/m_rtParent.Height();
		rt.bottom=rt.bottom*cy/m_rtParent.Height();

		if(m_pWnd->GetDlgItem(m_arrControlChange.GetAt(i).ID)->m_hWnd)
			m_pWnd->GetDlgItem(m_arrControlChange.GetAt(i).ID)->MoveWindow(rt);
	}
}

void CControlChange::SetResizeControl(UINT ID,int type1,int type2,int type3,int type4)
{
	tagControlChange iCon;
	CRect rt;
	iCon.ID=ID;
	m_pWnd->GetDlgItem(ID)->GetWindowRect(&rt);
	m_pWnd->ScreenToClient(rt);
	iCon.rt=rt;
	iCon.type1=type1;
	iCon.type2=type2;
	iCon.type3=type3;
	iCon.type4=type4;
	m_arrControlChange.Add(iCon);
}

