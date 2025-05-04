#if !defined(AFX_BOTHMEASUREMENTSDLG_H__520CDF3F_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
#define AFX_BOTHMEASUREMENTSDLG_H__520CDF3F_4D62_11D6_8BCD_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BothMeasurementsDlg.h : header file
//
#include "DriverListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CBothMeasurementsDlg dialog

class CBothMeasurementsDlg : public CDialog
{
// Construction
public:
	CBothMeasurementsDlg(CWnd* pParent = NULL);   // standard constructor
	void InsertBackgndMeasurementToList(double, double, double, BOOL);
	void InsertForegndMeasurementToList(double, double, double, BOOL);
	void InsertBackgndMeasurementToList(double, double, double, double, double, double, BOOL, bool);
	void InsertForegndMeasurementToList(double, double, double, double, double, double, BOOL, bool);
	void InsertMeasurementToList(CDriverListCtrl* c, double, double, double, BOOL);
	void InsertMeasurementToList(CDriverListCtrl* c, double, double, double, double, double, double, BOOL, bool);

// Dialog Data
	//{{AFX_DATA(CBothMeasurementsDlg)
	enum { IDD = IDD_DIALOG_BOTH_MEASUREMENTS };
	CButton	m_bStartBackgnd;
	CButton	m_bStopForegnd;
	CButton	m_bStopBackgnd;
	CButton	m_bStartForegnd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBothMeasurementsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBothMeasurementsDlg)
	afx_msg void OnButtonStartBackgnd();
	afx_msg void OnButtonStartForegnd();
	afx_msg void OnButtonStopBackgnd();
	afx_msg void OnButtonStopForegnd();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	CDriverListCtrl m_ForegndList;
	CDriverListCtrl m_BackgndList;
	double m_nAzimuth;
	double m_nZenith;
	double m_nDistance;
	BOOL m_bStatus;
	LPTSTR getStatusString(int);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOTHMEASUREMENTSDLG_H__520CDF3F_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
