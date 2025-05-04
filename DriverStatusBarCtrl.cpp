// DriverStatusBarCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "DriverStatusBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDriverStatusBarCtrl

CDriverStatusBarCtrl::CDriverStatusBarCtrl()
{
}

CDriverStatusBarCtrl::~CDriverStatusBarCtrl()
{
}


BEGIN_MESSAGE_MAP(CDriverStatusBarCtrl, CStatusBarCtrl)
	//{{AFX_MSG_MAP(CDriverStatusBarCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDriverStatusBarCtrl message handlers

void CDriverStatusBarCtrl::CreateStatusBar(CWnd* pParentWnd)
{
	UINT IDC_STATUS_BAR = 10003;
	CRect rect(0,0,0,0);
	
	Create(WS_CHILD|WS_VISIBLE|WS_BORDER|CCS_NODIVIDER, rect, pParentWnd, IDC_STATUS_BAR);	
}


void CDriverStatusBarCtrl::UpdateStatus(char * text)
{
	SetText( text, 0, 0 );
}

void CDriverStatusBarCtrl::SetPartsOnStatusBar(int nParts, int * pWidths)
{
	VERIFY( SetParts(nParts, pWidths) );	
}

void CDriverStatusBarCtrl::UpdateStatus(char * text, int nPane, int nType)
{	
	SetText( text, nPane, nType );
}
