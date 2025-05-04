// TrackerModeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "Globals.h"
#include "TrackerModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrackerModeDlg dialog


CTrackerModeDlg::CTrackerModeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrackerModeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrackerModeDlg)
	m_RunMode = 0;
	//}}AFX_DATA_INIT
}


void CTrackerModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrackerModeDlg)
	DDX_Control(pDX, IDC_RADIO_WORKER, m_rWorkerMode);
	DDX_Control(pDX, IDC_RADIO_UI, m_rUIMode);
	DDX_Control(pDX, IDC_RADIO_LISTENER, m_rListenersMode);
	DDX_Radio(pDX, IDC_RADIO_UI, m_RunMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrackerModeDlg, CDialog)
	//{{AFX_MSG_MAP(CTrackerModeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrackerModeDlg message handlers

void CTrackerModeDlg::OnOK() 
{
	if(m_rUIMode.GetCheck())
		gRunMode = UI_MODE;
	else if(m_rListenersMode.GetCheck())	
		gRunMode =  EVENT_MODE;
	else if(m_rWorkerMode.GetCheck())
		gRunMode = WORKER_MODE;
	
	CDialog::OnOK();
}
