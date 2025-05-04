// TrackerDriverDemoView.h : interface of the CTrackerDriverDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACKERDRIVERDEMOVIEW_H__520CDF31_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
#define AFX_TRACKERDRIVERDEMOVIEW_H__520CDF31_4D62_11D6_8BCD_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTrackerDriverDemoView : public CView
{
protected: // create from serialization only
	CTrackerDriverDemoView();
	DECLARE_DYNCREATE(CTrackerDriverDemoView)

// Attributes
public:
	CTrackerDriverDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackerDriverDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTrackerDriverDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTrackerDriverDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TrackerDriverDemoView.cpp
inline CTrackerDriverDemoDoc* CTrackerDriverDemoView::GetDocument()
   { return (CTrackerDriverDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACKERDRIVERDEMOVIEW_H__520CDF31_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
