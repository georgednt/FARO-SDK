// ComboSearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "ComboSearchDlg.h"
#include "Globals.h"


// CComboSearchDlg dialog

IMPLEMENT_DYNAMIC(CComboSearchDlg, CDialog)

CComboSearchDlg::CComboSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComboSearchDlg::IDD, pParent)
{

}

CComboSearchDlg::~CComboSearchDlg()
{
}

void CComboSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CComboSearchDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CSEARCH_1, &CComboSearchDlg::OnBnClickedButtonCsearch1)
	ON_BN_CLICKED(IDC_BUTTON_CSEARCH_2, &CComboSearchDlg::OnBnClickedButtonCsearch2)
	ON_BN_CLICKED(IDCANCEL, &CComboSearchDlg::OnBnClickedCancel)	
END_MESSAGE_MAP()


// CComboSearchDlg message handlers

void CComboSearchDlg::OnBnClickedButtonCsearch1()
{
	// TODO: Add your control notification handler code here
	if(gRunMode == UI_MODE)
	{
		gBlocking.ComboSearch1();
	}		
	else if(gRunMode == WORKER_MODE)	
	{
		gWorkerThread.ComboSearch1();
	}	
	else if(gRunMode == EVENT_MODE)
	{		
		gListeners.ComboSearch1();
	}
}

void CComboSearchDlg::OnBnClickedButtonCsearch2()
{
	// TODO: Add your control notification handler code here
	CString azAbs;
	GetDlgItem(IDC_EDIT_AZ_ABS)->GetWindowText(azAbs);
	if(azAbs.IsEmpty())
	{
		AfxMessageBox("Specify Azimuth");
		return;
	}

	CString zeAbs;
	GetDlgItem(IDC_EDIT_ZE_ABS)->GetWindowText(zeAbs);
	if(zeAbs.IsEmpty())
	{
		AfxMessageBox("Specify Zenith");
		return;
	}

	CString dist;	
	GetDlgItem(IDC_EDIT_DIST)->GetWindowText(dist);
	if(dist.IsEmpty())
	{
		AfxMessageBox("Specify Distance");
		return;
	}

	CString azTol;
	GetDlgItem(IDC_EDIT_AZ_TOL)->GetWindowText(azTol);
	if(azTol.IsEmpty())
	{
		AfxMessageBox("Specify Azimuth Tolerance");
		return;
	}

	CString zeTol;
	GetDlgItem(IDC_EDIT_ZE_TOL)->GetWindowText(zeTol);
	if(zeTol.IsEmpty())
	{
		AfxMessageBox("Specify Zenith Tolerance");
		return;
	}
	
	 int checked = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();

	 bool search = (checked == 1) ? true : false;

	if(gRunMode == UI_MODE)
	{
		gBlocking.ComboSearch2(atof(azAbs.GetBuffer(0)),atof(zeAbs.GetBuffer(0)),atof(dist.GetBuffer(0)),atof(azTol.GetBuffer(0)),atof(zeTol.GetBuffer(0)), search);
	}		
	else if(gRunMode == WORKER_MODE)	
	{
		gWorkerThread.ComboSearch2(atof(azAbs.GetBuffer(0)),atof(zeAbs.GetBuffer(0)),atof(dist.GetBuffer(0)),atof(azTol.GetBuffer(0)),atof(zeTol.GetBuffer(0)), search);
	}	
	else if(gRunMode == EVENT_MODE)
	{		
		gListeners.ComboSearch2(atof(azAbs.GetBuffer(0)),atof(zeAbs.GetBuffer(0)),atof(dist.GetBuffer(0)),atof(azTol.GetBuffer(0)),atof(zeTol.GetBuffer(0)), search);
	}
}

void CComboSearchDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
