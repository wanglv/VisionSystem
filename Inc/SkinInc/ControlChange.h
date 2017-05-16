// ControlChange.h: interface for the CControlChange class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLCHANGE_H__F3DA714D_C1FB_4FA0_88E5_78512173F6FB__INCLUDED_)
#define AFX_CONTROLCHANGE_H__F3DA714D_C1FB_4FA0_88E5_78512173F6FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"

typedef struct _tagControlChange
{
	UINT ID;
	CRect rt;
	int type1;
	int type2;
	int type3;
	int type4;
}tagControlChange;
enum{PK_TOP_LEFT,PK_TOP_RIGHT,PK_BOTTOM_LEFT,PK_BOTTOM_RIGHT};

class CControlChange  
{
public:
	CControlChange();
	virtual ~CControlChange();
	void SetResizeControl(UINT ID,int type1,int type2,int type3,int type4);
	void SetOwner(CWnd *pWnd);
	void OnSize(int cx,int cy);

private:
	CWnd *m_pWnd;
    CArray <tagControlChange,tagControlChange>m_arrControlChange;
	CRect m_rtParent;
};

#endif // !defined(AFX_CONTROLCHANGE_H__F3DA714D_C1FB_4FA0_88E5_78512173F6FB__INCLUDED_)
