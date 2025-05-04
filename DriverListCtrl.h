#if !defined(AFX_DRIVERLISTCTRL_H__B84814B7_4647_11D6_8BC9_0001031CC11D__INCLUDED_)
#define AFX_DRIVERLISTCTRL_H__B84814B7_4647_11D6_8BC9_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DriverListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDriverListCtrl window

class CDriverListCtrl : public CListCtrl
{
// Construction
public:
	CDriverListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDriverListCtrl)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	void InsertMeasurement(double az, double ze, double d, LPTSTR status);
	void InsertMeasurement(double az, double ze, double d, double A, double B, double C, LPTSTR status, bool sixDofData);
	void CreateListCtrl(int nRows, int nCols, RECT rect, CWnd* pParentWnd, UINT nID, BOOL sixDofCapable);
	virtual ~CDriverListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDriverListCtrl)
	afx_msg void OnPaint();
	afx_msg void OnCustomdraw( NMHDR* pNMHDR, LRESULT* pResult );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRIVERLISTCTRL_H__B84814B7_4647_11D6_8BC9_0001031CC11D__INCLUDED_)
