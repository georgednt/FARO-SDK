#if !defined(AFX_APPDLG_H__520CDF40_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
#define AFX_APPDLG_H__520CDF40_4D62_11D6_8BCD_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AppDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppDlg dialog

class CAppDlg : public CDialog
{
// Construction
public:
	void FillStartedAppList(BOOL run, char* name);
	CAppDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAppDlg)
	enum { IDD = IDD_DIALOG_APPLICATION };
	CListBox	m_lStartedAppList;
	CListBox	m_lAvailableList;
	CButton	m_bStopApps;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListAvailableApps();
	afx_msg void OnButtonStop();
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPDLG_H__520CDF40_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
