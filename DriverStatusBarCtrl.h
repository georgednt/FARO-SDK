#if !defined(AFX_DRIVERSTATUSBARCTRL_H__756350C5_4742_11D6_8BCA_0001031CC11D__INCLUDED_)
#define AFX_DRIVERSTATUSBARCTRL_H__756350C5_4742_11D6_8BCA_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DriverStatusBarCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDriverStatusBarCtrl window

class CDriverStatusBarCtrl : public CStatusBarCtrl
{
// Construction
public:
	CDriverStatusBarCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDriverStatusBarCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateStatus(char* text, int, int);
	void SetPartsOnStatusBar(int nParts, int* nWidths);
	void UpdateStatus(char* text);
	void CreateStatusBar(CWnd* pParentWnd);
	virtual ~CDriverStatusBarCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDriverStatusBarCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRIVERSTATUSBARCTRL_H__756350C5_4742_11D6_8BCA_0001031CC11D__INCLUDED_)
