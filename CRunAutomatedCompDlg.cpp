// CRunAutomatedCompDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "CRunAutomatedCompDlg.h"
#include "Globals.h"
#include "afxdialogex.h"


// CRunAutomatedCompDlg dialog

IMPLEMENT_DYNAMIC(CRunAutomatedCompDlg, CDialog)

CRunAutomatedCompDlg::CRunAutomatedCompDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_RUN_AUTOMATED_COMP_DIALOG, pParent)
{

}

CRunAutomatedCompDlg::~CRunAutomatedCompDlg()
{
}

void CRunAutomatedCompDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRunAutomatedCompDlg, CDialog)
	ON_BN_CLICKED(IDC_RUN_AUTOMATED_COMP_BUTTON, &CRunAutomatedCompDlg::OnBnClickedRunAutomatedCompButton)
	ON_BN_CLICKED(IDOK, &CRunAutomatedCompDlg::OnBnClickedOk)
	ON_MESSAGE(UWM_RUN_AUTO_COMP_CHANGE_EVENT_FIRED, &CRunAutomatedCompDlg::OnChangeEventFired)
END_MESSAGE_MAP()


// CRunAutomatedCompDlg message handlers


BOOL CRunAutomatedCompDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	changeListener = new MyChangelistener(this->m_hWnd);
	gpTracker->addChangeListener(changeListener);	
	gpTracker->startAsync();	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CRunAutomatedCompDlg::OnBnClickedRunAutomatedCompButton()
{
	// TODO: Add your control notification handler code here
	RunAutomatedComp();
}


void CRunAutomatedCompDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if(changeListener)
		gpTracker->removeChangeListener(changeListener);
	
	gpTracker->stopAsync();	
	CDialog::OnOK();
}

void MyChangelistener::changeOccurred(ChangeEvent* event)
{
	Change* change = event->getChange();

	::PostMessage(hWnd, UWM_RUN_AUTO_COMP_CHANGE_EVENT_FIRED, 0, (LPARAM)change);
}

MyChangelistener::MyChangelistener(HWND hWndArg)
{
	hWnd = hWndArg;
}

LRESULT CRunAutomatedCompDlg::OnChangeEventFired(WPARAM wParam, LPARAM lParam)
{
	Change* change = (Change*)lParam;

	int changeCode = change->getCode();
	if (changeCode == change->RUN_AUTO_COMP)
	{
		bool run = ((Boolean*)change->getRelatedData())->booleanValue();
		//if run is true, it is recommended to prompt the user if it is ok to launch the compensation. If ok, then launch the compensation.
		//If run is false, it means autocomp completed the run.
		if (run)
		{
			int sel = AfxMessageBox("Tracker needs to be compensated. Would you like to run the compensation?", MB_YESNO);
			if (sel == IDYES)
			{
				RunAutomatedComp();
			}			
		}
		else
		{
			//if run is false, autocomp completed the run.
		}
	}

	delete change;

	return 0;
}

void CRunAutomatedCompDlg::RunAutomatedComp()
{
	if (!gpTracker)
		return;

	try
	{
		//This method should be called within blocking mode to get the return value.
		//If run in non blocking mode, the cmd will return -1.
		//store the blocking state
		boolean block = gpTracker->getBlocking();
		//turn blocking on
		gpTracker->setBlocking(true);
		int ret = gpTracker->runAutomatedComp();
		//restore the blocking state
		gpTracker->setBlocking(block);
		
		
		if (ret == AutomatedCompResult::FAILED_TO_FIND_TARGET_1 || AutomatedCompResult::FAILED_TO_FIND_TARGET_2 || AutomatedCompResult::LEARN_TARGETS_PROCEDURE_NOT_RUN)
		{
			gpTracker->startApplicationFrame("CompIT", "-a AUTOMATED_COMP");
		}
		else if (ret == AutomatedCompResult::NO_TARGET_AT_HOME)
		{
			AfxMessageBox("Place target at home location");
		}
		else if (ret == AutomatedCompResult::OUT_OF_SPEC)
		{
			AfxMessageBox("Auto Comp failed");
		}
		else if (ret == AutomatedCompResult::PASS)
		{
			AfxMessageBox("Auto Comp passed");
		}
	}
	catch (TrackerException* e)
	{
		char* msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}
}
