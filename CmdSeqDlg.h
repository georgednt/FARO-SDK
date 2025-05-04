#if !defined(AFX_CMDSEQDLG_H__520CDF3C_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
#define AFX_CMDSEQDLG_H__520CDF3C_4D62_11D6_8BCD_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CmdSeqDlg.h : header file
//
#include "DriverStatusBarCtrl.h"
#include "CommandDone.h"
/////////////////////////////////////////////////////////////////////////////
// CCmdSeqDlg dialog

class CCmdSeqDlg : public CDialog, CommandDone
{
// Construction
public:
	void UpdateCmdseqStatus(char* msg);
	CCmdSeqDlg(CWnd* pParent = NULL);   // standard constructor	
	virtual void TrackerCommandDone(void* pResult);

// Dialog Data
	//{{AFX_DATA(CCmdSeqDlg)
	enum { IDD = IDD_DIALOG_COMMAND_SEQUENCE };
	CButton	m_bStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmdSeqDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCmdSeqDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonStart();
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	CDriverStatusBarCtrl m_StatusBarCtrl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMDSEQDLG_H__520CDF3C_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
