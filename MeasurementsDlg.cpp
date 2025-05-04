// MeasurementsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "Globals.h"
#include "MeasurementsDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeasurementsDlg dialog


CMeasurementsDlg::CMeasurementsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMeasurementsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMeasurementsDlg)
	//}}AFX_DATA_INIT
}


void CMeasurementsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeasurementsDlg)
	DDX_Control(pDX, IDC_RADIO_TEN_MEASUREMENTS, m_rTen);
	DDX_Control(pDX, IDC_RADIO_SINGLE_MEASUREMENTS, m_rSingle);
	DDX_Control(pDX, IDC_BUTTON_START, m_bStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMeasurementsDlg, CDialog)
	//{{AFX_MSG_MAP(CMeasurementsDlg)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeasurementsDlg message handlers

BOOL CMeasurementsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(gMainWnd->GetMeasurementType())	
		SetWindowText("Foreground Measurements");
	else
		SetWindowText("Background Measurements");	

	m_rSingle.SetCheck(1);
	
	int nCols = 4;	

	RECT rect;
	rect.left = 20;
	rect.top = 50;
	rect.right = 450;
	rect.bottom = 330;
	UINT nID = 10001;

	if(gMainWnd->sixDofCapable())
	{		
		rect.right = 820;

		nCols = 8;
	}
	ctrl.CreateListCtrl(1, nCols, rect, this, nID, gMainWnd->sixDofCapable());	
	
	//if not six dof capable, resize the dialog as there is no probe data
	if(gMainWnd->sixDofCapable() == false)
	{
		CRect dlgRect;
		this->GetWindowRect(dlgRect);	

		this->SetWindowPos(NULL, 0, 0, 490, dlgRect.Height(), SWP_NOZORDER | SWP_NOMOVE);

		CRect buttonRect;
		GetDlgItem(IDC_BUTTON_START)->GetWindowRect(buttonRect);
		//convert to client coords
		ScreenToClient(buttonRect);	

		GetDlgItem(IDC_BUTTON_START)->MoveWindow(375, 345, buttonRect.Width(), buttonRect.Height());
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMeasurementsDlg::OnButtonStart() 
{
	if(m_rSingle.GetCheck())
	{
		gMainWnd->SetEventRate(1);
	}
	else if(m_rTen.GetCheck())
	{
		gMainWnd->SetEventRate(10);
	}

	gMainWnd->StartMeasurements();
}

void CMeasurementsDlg::InsertMeasurementToList(double az, double ze, double d, int status)
{
	LPTSTR str = getStatusString(status);	

	ctrl.InsertMeasurement(az, ze, d, str);
}

void CMeasurementsDlg::InsertMeasurementToList(double az, double ze, double d, double A, double B, double C, int status, bool sixDofData)
{
	LPTSTR str = getStatusString(status);

	ctrl.InsertMeasurement(az, ze, d, A, B, C, str, sixDofData);
}

LRESULT CMeasurementsDlg::OnKickIdle(WPARAM, LPARAM)
{
	//If measurement is busy we would like to disable the start button.
	CMainFrame* pMainFrm = STATIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if(gMainWnd->GetMeasureBusy() || gMainWnd->GetBkndMeasureBusy())
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	return 0;
}

void CMeasurementsDlg::OnClose() 
{
	CMainFrame* pMainFrm = STATIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if(gMainWnd->GetMeasureBusy() || gMainWnd->GetBkndMeasureBusy())
		return;

	CDialog::OnClose();
}

LPTSTR CMeasurementsDlg::getStatusString(int status) 
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
