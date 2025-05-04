// TrackerDriverDemoDoc.h : interface of the CTrackerDriverDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACKERDRIVERDEMODOC_H__520CDF2F_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
#define AFX_TRACKERDRIVERDEMODOC_H__520CDF2F_4D62_11D6_8BCD_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTrackerDriverDemoDoc : public CDocument
{
protected: // create from serialization only
	CTrackerDriverDemoDoc();
	DECLARE_DYNCREATE(CTrackerDriverDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackerDriverDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTrackerDriverDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTrackerDriverDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACKERDRIVERDEMODOC_H__520CDF2F_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
