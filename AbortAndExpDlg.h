#if !defined(AFX_ABORTANDEXPDLG_H__520CDF3D_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
#define AFX_ABORTANDEXPDLG_H__520CDF3D_4D62_11D6_8BCD_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AbortAndExpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAbortAndExpDlg dialog

class CAbortAndExpDlg : public CDialog
{
// Construction
public:
	CAbortAndExpDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bAbort;

// Dialog Data
	//{{AFX_DATA(CAbortAndExpDlg)
	enum { IDD = IDD_DIALOG_SEARCH };
	CButton	m_bCancel;
	CButton	m_bStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAbortAndExpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAbortAndExpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSearch();
	virtual void OnCancel();
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABORTANDEXPDLG_H__520CDF3D_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
