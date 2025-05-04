#if !defined(AFX_MEASUREMENTSDLG_H__520CDF3E_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
#define AFX_MEASUREMENTSDLG_H__520CDF3E_4D62_11D6_8BCD_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MeasurementsDlg.h : header file
//
#include "DriverListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CMeasurementsDlg dialog

class CMeasurementsDlg : public CDialog
{
// Construction
public:
	CMeasurementsDlg(CWnd* pParent = NULL);   // standard constructor
	void InsertMeasurementToList(double, double, double, BOOL);
	void InsertMeasurementToList(double, double, double, double, double, double, BOOL, bool);

// Dialog Data
	//{{AFX_DATA(CMeasurementsDlg)
	enum { IDD = IDD_DIALOG_MEASURE };
	CButton	m_rTen;
	CButton	m_rSingle;
	CButton	m_bStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeasurementsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeasurementsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonStart();
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	CDriverListCtrl ctrl;
	double m_nAzimuth;
	double m_nZenith;
	double m_nDistance;
	BOOL m_bStatus;
	LPTSTR getStatusString(int);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEASUREMENTSDLG_H__520CDF3E_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
