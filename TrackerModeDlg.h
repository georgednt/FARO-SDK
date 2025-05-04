#if !defined(AFX_TRACKERMODEDLG_H__520CDF39_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
#define AFX_TRACKERMODEDLG_H__520CDF39_4D62_11D6_8BCD_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TrackerModeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTrackerModeDlg dialog

class CTrackerModeDlg : public CDialog
{
// Construction
public:
	CTrackerModeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTrackerModeDlg)
	enum { IDD = IDD_DIALOG_MODE };
	CButton	m_rWorkerMode;
	CButton	m_rUIMode;
	CButton	m_rListenersMode;
	int		m_RunMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackerModeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTrackerModeDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACKERMODEDLG_H__520CDF39_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
