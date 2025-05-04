#pragma once

#include "Tracker.h"

class MyChangelistener : public ChangeListener
{
public:
	HWND hWnd = NULL;
	MyChangelistener(HWND hwnd);
	void changeOccurred(ChangeEvent* event);
};

// CRunAutomatedCompDlg dialog

class CRunAutomatedCompDlg : public CDialog
{
	DECLARE_DYNAMIC(CRunAutomatedCompDlg)

public:
	CRunAutomatedCompDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CRunAutomatedCompDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RUN_AUTOMATED_COMP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRunAutomatedCompButton();
	afx_msg void OnBnClickedOk();
	LRESULT OnChangeEventFired(WPARAM wParam, LPARAM lParam);
	void RunAutomatedComp();
	MyChangelistener* changeListener;
};
