// CmdSeqDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "Globals.h"
#include "CmdSeqDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCmdSeqDlg dialog


CCmdSeqDlg::CCmdSeqDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCmdSeqDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCmdSeqDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCmdSeqDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCmdSeqDlg)
	DDX_Control(pDX, IDC_BUTTON_START, m_bStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCmdSeqDlg, CDialog)
	//{{AFX_MSG_MAP(CCmdSeqDlg)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmdSeqDlg message handlers

BOOL CCmdSeqDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_StatusBarCtrl.CreateStatusBar(this);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCmdSeqDlg::OnButtonStart() 
{
	
	if(gRunMode == WORKER_MODE)
	{
		gWorkerThread.ExecuteCommandSequence();
	}
	else if(gRunMode == UI_MODE)
	{
		gBlocking.SetCommandDone(this);
		gBlocking.ExecuteCommandSequence();
	}
	else if(gRunMode == EVENT_MODE)	
	{
		gListeners.SetCommandDone(this);
		gListeners.ExecuteCommandSequence();	
	}	
}

void CCmdSeqDlg::TrackerCommandDone(void* pResult)
{
	char* text = (char*)pResult;
	UpdateCmdseqStatus(text);
}

void CCmdSeqDlg::UpdateCmdseqStatus(char* msg)
{
	m_StatusBarCtrl.UpdateStatus(msg);
}

LRESULT CCmdSeqDlg::OnKickIdle(WPARAM, LPARAM)
{
	if(gMainWnd->GetCommandBusy())
		m_bStart.EnableWindow(FALSE);
	else
		m_bStart.EnableWindow(TRUE);

	return TRUE;
}

void CCmdSeqDlg::OnClose() 
{
	if(gMainWnd->GetCommandBusy())
		return;
	
	CDialog::OnClose();
}
