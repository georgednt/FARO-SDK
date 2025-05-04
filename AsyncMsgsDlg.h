#if !defined(AFX_ASYNCMSGSDLG_H__520CDF3B_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
#define AFX_ASYNCMSGSDLG_H__520CDF3B_4D62_11D6_8BCD_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AsyncMsgsDlg.h : header file
//
#include "Tracker.h"
#include "DriverStatusBarCtrl.h"
#include "CommandDone.h"
/////////////////////////////////////////////////////////////////////////////
// CAsyncMsgsDlg dialog

class CAsyncMsgsDlg : public CDialog, CommandDone
{
// Construction
public:	
	CAsyncMsgsDlg(CWnd* pParent = NULL);   // standard constructor
	void SetChangeOccured(Change * change);
	void SetStatusChange(Status * status);
	void SetTargetCheck(char* type);
	void OnSetAsyncMsgStatus();
	virtual void TrackerCommandDone(void* pResult);

// Dialog Data
	//{{AFX_DATA(CAsyncMsgsDlg)
	enum { IDD = IDD_DIALOG_ASYNC_MSGS };
	CButton	m_bSight;
	CButton	m_bMotors;
	CButton	m_bDistance;
	CButton	m_rSMM;
	CButton	m_SMR0_875;
	CButton	m_rSMR1_5;
	CButton	m_rSMR0_5;
	CButton m_rSixDof;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAsyncMsgsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAsyncMsgsDlg)
	afx_msg void OnButtonDistance();
	afx_msg void OnButtonMotors();
	afx_msg void OnButtonSight();
	afx_msg void OnButtonTarget();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnRadio05();
	afx_msg void OnRadio0875();
	afx_msg void OnRadio15();
	afx_msg void OnRadioSmm();
	afx_msg void OnRadioSixDOf();
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	CDriverStatusBarCtrl m_StatusBarCtrl;
	bool m_bMotorState;
	bool m_bDistanceValid;
	bool m_bSightMode;
	void EnableTargetButtons(BOOL);
public:
	afx_msg void OnBnClickedRadioSixDof();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASYNCMSGSDLG_H__520CDF3B_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
