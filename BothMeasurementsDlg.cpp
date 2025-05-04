// BothMeasurementsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "Globals.h"
#include "BothMeasurementsDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBothMeasurementsDlg dialog


CBothMeasurementsDlg::CBothMeasurementsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBothMeasurementsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBothMeasurementsDlg)
	//}}AFX_DATA_INIT
}


void CBothMeasurementsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBothMeasurementsDlg)
	DDX_Control(pDX, IDC_BUTTON_START_BACKGND, m_bStartBackgnd);
	DDX_Control(pDX, IDC_BUTTON_STOP_FOREGND, m_bStopForegnd);
	DDX_Control(pDX, IDC_BUTTON_STOP_BACKGND, m_bStopBackgnd);
	DDX_Control(pDX, IDC_BUTTON_START_FOREGND, m_bStartForegnd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBothMeasurementsDlg, CDialog)
	//{{AFX_MSG_MAP(CBothMeasurementsDlg)
	ON_BN_CLICKED(IDC_BUTTON_START_BACKGND, OnButtonStartBackgnd)
	ON_BN_CLICKED(IDC_BUTTON_START_FOREGND, OnButtonStartForegnd)
	ON_BN_CLICKED(IDC_BUTTON_STOP_BACKGND, OnButtonStopBackgnd)
	ON_BN_CLICKED(IDC_BUTTON_STOP_FOREGND, OnButtonStopForegnd)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBothMeasurementsDlg message handlers


BOOL CBothMeasurementsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	
	int nCols = 4;
	RECT rect;
	rect.left = 35;
	rect.top = 45;
	rect.right = 455;
	rect.bottom = 260;
	UINT nID = 10001;	

	if(gMainWnd->sixDofCapable())
	{
		rect.right = 840;

		nCols = 8;
	}
	m_ForegndList.CreateListCtrl(1, nCols, rect, this, nID, gMainWnd->sixDofCapable());
	
	rect.top = 340;		
	rect.bottom = 550;
	nID = 10002;
	
	m_BackgndList.CreateListCtrl(1, nCols, rect, this, nID, gMainWnd->sixDofCapable());

	//If not six dof capable, resize the dialog as there is no probe data
	if(gMainWnd->sixDofCapable() == false)
	{
		CRect dlgRect;
		this->GetWindowRect(dlgRect);	

		this->SetWindowPos(NULL, 0, 0, 500, dlgRect.Height(), SWP_NOZORDER | SWP_NOMOVE);

		CRect buttonRect;
		GetDlgItem(IDC_BUTTON_START_BACKGND)->GetWindowRect(buttonRect);
		//convert to client coords
		ScreenToClient(buttonRect);	

		GetDlgItem(IDC_BUTTON_START_FOREGND)->MoveWindow(310, 270, buttonRect.Width(), buttonRect.Height());
		GetDlgItem(IDC_BUTTON_STOP_FOREGND)->MoveWindow(390, 270, buttonRect.Width(), buttonRect.Height());

		GetDlgItem(IDC_BUTTON_START_BACKGND)->MoveWindow(310, 565, buttonRect.Width(), buttonRect.Height());
		GetDlgItem(IDC_BUTTON_STOP_BACKGND)->MoveWindow(390, 565, buttonRect.Width(), buttonRect.Height());

		CRect groupBoxRect;
		GetDlgItem(IDC_FOREGND_STATIC)->GetWindowRect(groupBoxRect);

		GetDlgItem(IDC_FOREGND_STATIC)->SetWindowPos(NULL, 0, 0, 460, groupBoxRect.Height(), SWP_NOZORDER | SWP_NOMOVE);
		GetDlgItem(IDC_BACKGND_STATIC)->SetWindowPos(NULL, 0, 0, 460, groupBoxRect.Height(), SWP_NOZORDER | SWP_NOMOVE);
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBothMeasurementsDlg::OnButtonStartForegnd() 
{	
	gMainWnd->SetMeasurementType(TRUE);

	gMainWnd->SetEventRate(1);	

	//In the setblocking mode both the foregnd and backgnd measuremnts cannot be run since
	//if we start either one of the measurement the UI is already busy.
	//To run both of them simultaneously either Listeners or separate worker thread has
	//to be used as shown.
	gMainWnd->StartMeasurements();
}

void CBothMeasurementsDlg::OnButtonStopForegnd() 
{
	gMainWnd->SetMeasurementType(TRUE);	

	gMainWnd->StopMeasurements();
}

void CBothMeasurementsDlg::OnButtonStartBackgnd() 
{
	gMainWnd->SetMeasurementType(FALSE);

	gMainWnd->SetEventRate(1);	

	gMainWnd->StartMeasurements();
}

void CBothMeasurementsDlg::OnButtonStopBackgnd() 
{
	gMainWnd->SetMeasurementType(FALSE);
	
	gMainWnd->StopMeasurements();
}

void CBothMeasurementsDlg::InsertForegndMeasurementToList(double az, double ze, double d, int status)
{
	InsertMeasurementToList(&m_ForegndList,az, ze, d, status);
}

void CBothMeasurementsDlg::InsertBackgndMeasurementToList(double az, double ze, double d, int status)
{
	InsertMeasurementToList(&m_BackgndList,az, ze, d, status);
}

void CBothMeasurementsDlg::InsertMeasurementToList(CDriverListCtrl* list, double az, double ze, double d, int status)
{
	LPTSTR str = getStatusString(status);
	
	list->InsertMeasurement(az, ze, d, str);
}

void CBothMeasurementsDlg::InsertForegndMeasurementToList(double az, double ze, double d, double A, double B, double C, int status, bool sixDofData)
{
	LPTSTR str = getStatusString(status);
	
	InsertMeasurementToList(&m_ForegndList, az, ze, d, A, B, C, status, sixDofData);
}

void CBothMeasurementsDlg::InsertBackgndMeasurementToList(double az, double ze, double d, double A, double B, double C, int status, bool sixDofData)
{	
	InsertMeasurementToList(&m_BackgndList, az, ze, d, A, B, C, status, sixDofData);
}

void CBothMeasurementsDlg::InsertMeasurementToList(CDriverListCtrl* list, double az, double ze, double d, double A, double B, double C, int status, bool sixDofData)
{
	LPTSTR str = getStatusString(status);

	list->InsertMeasurement(az, ze, d, A, B, C, str, sixDofData);
}

LRESULT CBothMeasurementsDlg::OnKickIdle(WPARAM, LPARAM)
{	
	/*Here is something about Foregnd and Backgnd measurements
	->To run both the Foregnd and Backgnd measurements simultaneously Backgnd 
	  measurements must be started before Foregnd measurements are started.
	->Also foregnd measurements must be stopped before Backgnd measurements
	  are stopped.
	->To start and stop the Backgnd measurements Tracker must not be busy. If Tracker
	  is busy it will throw an Interface busy exception.
	->To start or stop Foregnd measurements, Backgnd measurements can be running.
	  Also any command can be executed while Backgnd measurements are in progress.
	*/	

	/*Start and Stop buttons of Foregnd and Backgnd are enabled and disabled in the follwing way
	->Intially the Start buttons of both the Foregnd and Backgnd measurements are enabled
	  and Stop buttons disabled.
	->If Foregnd measurements are started prior to starting Backgnd then the Start and Stop
	  buttons of Backgnd are disabled since Backgnd measurements cannot be started with the
	  Tracker busy.
	->If Foregnd measurements are stopped then the Start and Stop buttons of Backgnd
	  are enabled since Tracker is no more busy.
	->If Backgnd measurements are started prior to starting Foregnd measurements, the Start
	  button of Foregnd is still left enabled since Foregnd measurements can be started with
	  Backgnd measurements running.
	->Once the Foregnd measurements are started then the Stop button of Backgnd is disabled.
	->If Foregnd measurements are stopped then again the Stop button of Backgnd is enabled.
	*/
	//All this is achieved using Busy listener which provides here a good example how UI
	//can be made available to the user depending upon Tracker busy.
	
	CMainFrame* pMainFrm = STATIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	bool bMeasbusy = gMainWnd->GetMeasureBusy();
	bool bBkndbusy = gMainWnd->GetBkndMeasureBusy();

	if(bMeasbusy)
	{	
		m_bStartForegnd.EnableWindow(false);
		m_bStopForegnd.EnableWindow(true);
	}
	else
	{
		m_bStartForegnd.EnableWindow(true);
		m_bStopForegnd.EnableWindow(false);
	
	}
	
	if(bBkndbusy)
	{
		if(bMeasbusy)
		{
			m_bStartBackgnd.EnableWindow(false);
			m_bStopBackgnd.EnableWindow(false);
		}
		else
		{
			m_bStartBackgnd.EnableWindow(false);
			m_bStopBackgnd.EnableWindow(true);
		}
	
	}
	else
	{
		if(bMeasbusy)
		{	
			m_bStartBackgnd.EnableWindow(false);
			m_bStopBackgnd.EnableWindow(false);
		}
		else
		{
			m_bStartBackgnd.EnableWindow(true);
			m_bStopBackgnd.EnableWindow(false);
		}
	}
	return TRUE;
}

void CBothMeasurementsDlg::OnClose() 
{
	CMainFrame* pMainFrm = STATIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if(gMainWnd->GetMeasureBusy() || gMainWnd->GetBkndMeasureBusy())
		return;

	CDialog::OnClose();
}

LPTSTR CBothMeasurementsDlg::getStatusString(int status) 
{
	LPTSTR str = "";
	if(status == MeasurePointData::DATA_ACCURATE)
		str = "Accurate";
	else if(status == MeasurePointData::DATA_INACCURATE)
		str = "InAccurate";
	else if(status == MeasurePointData::DATA_ERROR)
		str = "Error";

	return str;
}
