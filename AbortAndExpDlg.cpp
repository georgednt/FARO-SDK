// AbortAndExpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "Globals.h"
#include "AbortAndExpDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbortAndExpDlg dialog


CAbortAndExpDlg::CAbortAndExpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAbortAndExpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAbortAndExpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAbortAndExpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbortAndExpDlg)
	DDX_Control(pDX, IDCANCEL, m_bCancel);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_bStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAbortAndExpDlg, CDialog)
	//{{AFX_MSG_MAP(CAbortAndExpDlg)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbortAndExpDlg message handlers

BOOL CAbortAndExpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(m_bAbort)
		m_bCancel.ShowWindow(SW_SHOW);
	else
		m_bCancel.ShowWindow(SW_HIDE);

	m_bCancel.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAbortAndExpDlg::OnButtonSearch() 
{
	//for listeners mode we are using call back function
	if(gRunMode == WORKER_MODE)	
	{
		gWorkerThread.StartSearch();
	}	
	else if(gRunMode == UI_MODE)
	{		
		gBlocking.StartSearch();
	}
}

void CAbortAndExpDlg::OnCancel() 
{
	if(gRunMode == WORKER_MODE)	
	{
		gWorkerThread.Abort();
	}	
	else if(gRunMode == UI_MODE)
	{		
		gBlocking.AbortCommand();
	}
	CDialog::OnCancel();
}

void CAbortAndExpDlg::OnClose() 
{
	if(gMainWnd->GetCommandBusy())		
		return;
	
	EndDialog(IDOK);
	
	CDialog::OnClose();
}

LRESULT CAbortAndExpDlg::OnKickIdle(WPARAM, LPARAM)
{	
	if(gMainWnd->GetCommandBusy())
	{
		m_bStart.EnableWindow(FALSE);
		if(m_bAbort)
			m_bCancel.EnableWindow(TRUE);
	}
	else
	{
		m_bStart.EnableWindow(TRUE);
		if(m_bAbort)
			m_bCancel.EnableWindow(FALSE);
	}
	return TRUE;
}
