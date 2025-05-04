// AppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "Globals.h"
#include "AppDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppDlg dialog


CAppDlg::CAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppDlg)
	DDX_Control(pDX, IDC_LIST_STARTED_APPS, m_lStartedAppList);
	DDX_Control(pDX, IDC_LIST_AVAILABLE_APPS, m_lAvailableList);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_bStopApps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppDlg, CDialog)
	//{{AFX_MSG_MAP(CAppDlg)
	ON_LBN_DBLCLK(IDC_LIST_AVAILABLE_APPS, OnDblclkListAvailableApps)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppDlg message handlers

BOOL CAppDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CList<char*, char*>lstApps;	

	if(gRunMode == WORKER_MODE)
	{
		gWorkerThread.OnAvailableApplications(lstApps);
	}
	else if(gRunMode == UI_MODE)
	{
		gBlocking.OnAvailableApplications(lstApps);
	}
	else if(gRunMode == EVENT_MODE)
	{
		gListeners.OnAvailableApplications(lstApps);
	}
	
	for ( POSITION pos = lstApps.GetHeadPosition(); pos; lstApps.GetNext(pos) )
	{
		char* pAppName =  lstApps.GetAt(pos);		
		m_lAvailableList.AddString( pAppName );		
		delete [] pAppName;
	}

	gListeners.AddListenersforApps();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAppDlg::OnDblclkListAvailableApps() 
{
	char appName[36];
	int nIndex = m_lAvailableList.GetCurSel();
	m_lAvailableList.GetText( nIndex, appName );

	if(gRunMode == WORKER_MODE)
	{
		gWorkerThread.OnRunApplication(appName);
	}
	else if(gRunMode == UI_MODE)
	{	
		gBlocking.OnRunApplication(appName);
	}
	else if(gRunMode == EVENT_MODE)
	{
		gListeners.OnRunApplication(appName);
	}	
}

void CAppDlg::OnButtonStop() 
{
	if(gRunMode == WORKER_MODE)
	{
		gWorkerThread.OnStopApplication();
	}
	else if(gRunMode == UI_MODE)
	{	
		gBlocking.OnStopApplication();
	}
	else if(gRunMode == EVENT_MODE)
	{
		gListeners.OnStopApplication();
	}	

	m_lStartedAppList.ResetContent();	
}

LRESULT CAppDlg::OnKickIdle(WPARAM, LPARAM)
{
	//Enabling and Disabling the  ability to start the applications depending upon 
	//whether the Tracker command is busy or not.
	//If the tracker is busy we do not want to allow the users to start any application
	//since the Tracker would throw Interface busy exception.
	bool run = gListeners.GetAppRunning();
	bool busy = gMainWnd->GetCommandBusy();
	if(busy)
	{
		m_lAvailableList.EnableWindow(FALSE);
		m_bStopApps.EnableWindow(FALSE);
	}
	else
	{
		m_lAvailableList.EnableWindow(TRUE);
		if(run)
			m_bStopApps.EnableWindow(TRUE);
		else
			m_bStopApps.EnableWindow(FALSE);
	}
	return 0;
}

void CAppDlg::FillStartedAppList(BOOL run, char * name)
{
	if(run)
		m_lStartedAppList.AddString(name);
	else
	{
		int index = m_lStartedAppList.FindStringExact( -1, name) ;
		m_lStartedAppList.DeleteString(index);
	}
}

void CAppDlg::OnClose() 
{
	if(gMainWnd->GetCommandBusy())
		return;

	OnButtonStop();

	gListeners.RemoveListenersofApps();
	
	CDialog::OnClose();
}
