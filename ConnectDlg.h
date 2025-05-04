#include "afxcmn.h"
#include "afxwin.h"
#if !defined(AFX_CONNECTDLG_H__520CDF3A_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
#define AFX_CONNECTDLG_H__520CDF3A_4D62_11D6_8BCD_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConnectDlg.h : header file
//
#include "TrackerEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CConnectDlg dialog

class CConnectDlg : public CDialog
{
// Construction
public:
	CConnectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConnectDlg)
	enum { IDD = IDD_DIALOG_CONNECT };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_SerialNumber;
	virtual BOOL OnInitDialog();	
	BOOL isValidIpAddress(CString ipaddr);
	CString m_srNum;
	CString getSerialNumber();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTDLG_H__520CDF3A_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
