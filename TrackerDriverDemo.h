// TrackerDriverDemo.h : main header file for the TRACKERDRIVERDEMO application
//

#if !defined(AFX_TRACKERDRIVERDEMO_H__520CDF27_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
#define AFX_TRACKERDRIVERDEMO_H__520CDF27_4D62_11D6_8BCD_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTrackerDriverDemoApp:
// See TrackerDriverDemo.cpp for the implementation of this class
//

class CTrackerDriverDemoApp : public CWinApp
{
public:
	CTrackerDriverDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackerDriverDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTrackerDriverDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACKERDRIVERDEMO_H__520CDF27_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
