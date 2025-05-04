// MainFrm.h : interface of the CMainFrame class
//
#include "MeasurementsDlg.h"
#include "BothMeasurementsDlg.h"
#include "AsyncMsgsDlg.h"
#include "AppDlg.h"
#include "AbortAndExpDlg.h"
#include "CmdSeqDlg.h"
#include "ComboSearchDlg.h"
#include "CRunAutomatedCompDlg.h"
#include <afxmt.h>

/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__520CDF2B_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
#define AFX_MAINFRM_H__520CDF2B_4D62_11D6_8BCD_0001031CC11D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class TrackerBusyListener : public BusyListener
{
	public:		
		void stateChanged(BusyEvent* event);
};

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	LRESULT OnConnectFailed(WPARAM wParam, LPARAM lParam);
	LRESULT OnSMXException(WPARAM wParam, LPARAM lParam);
	BOOL GetIfMultiMeasurements()const {return m_bMultiMeasurements;}	
	int GetEventRate()const { return m_nEventRate;}
	void SetEventRate(int num){m_nEventRate = num;}
	afx_msg LRESULT OnUpdateCmdseqStatus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCommandFailed(WPARAM wParam, LPARAM lParam);
	inline BOOL GetMeasurementType()const {return m_bMeasurement;}	
	inline void SetMeasurementType(BOOL type){m_bMeasurement = type;}
	afx_msg LRESULT OnBackgndMeasurementAvailable(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnForegndMeasurementStopped(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnForegndMeasurementAvailable(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnApplicationStateChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSearchCmdFired(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChangeOccured(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStatusChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnConnectListenerFired(WPARAM wParam, LPARAM lParam);
	
	inline void SetConnected(BOOL bConnected){ m_bConnected = bConnected;}
	
	inline void SetCommandBusy(bool busy){m_bCmdBusy = busy;}
	inline void SetMeasureBusy(bool busy){m_bMeasBusy = busy;}
	inline void SetBkndMeasureBusy(bool busy){m_bBkndMeasBusy = busy;}	
	inline bool GetCommandBusy()const {return m_bCmdBusy;}	
	inline bool GetMeasureBusy()const {return m_bMeasBusy;}
	inline bool GetBkndMeasureBusy()const {return m_bBkndMeasBusy;}

	void SetDisconnectEvent();

	BOOL sixDofCapable();

	void StartMeasurements();	
	void StopMeasurements();

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	void OnUpdateCommandTrackerCommands1(CCmdUI * pCmdUI);
	void OnUpdateCommandTrackerCommands(CCmdUI* pCmdUI);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTrackerMode();
	afx_msg void OnCommandConnect();
	afx_msg void OnCommandDisconnect();
	afx_msg void OnCommandSequence();
	afx_msg void OnCommandAsyncmsgs();
	afx_msg void OnCommandAbort();
	afx_msg void OnCommandException();
	afx_msg void OnCommandRunApplication();
	afx_msg void OnCommandForegnd();
	afx_msg void OnCommandBackgnd();
	afx_msg void OnCommandBoth();
	afx_msg void OnCommandRunAutomatedComp();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bConnected;
	int m_TrackerType;
	char m_IPAddress[80];
	BOOL m_bMeasurement;
	int m_nEventRate;
	BOOL m_bMultiMeasurements;

	CMeasurementsDlg m_MeasureDlg;
	CBothMeasurementsDlg m_BothDlg;	
	CAppDlg m_AppDlg;
	CAsyncMsgsDlg m_AyncMsgDlg;
	CAbortAndExpDlg m_AbortAndExpdlg;
	CCmdSeqDlg m_CmdseqDlg;	
	CComboSearchDlg m_ComboSearchDlg;

	TrackerBusyListener* m_pTrackerBusyListener;

	bool m_bCmdBusy;
	bool m_bMeasBusy;
	bool m_bBkndMeasBusy;	

	HANDLE m_hDisconnectEvent;
	
	BOOL m_bSixDofCapable;
	void checkIfTrkSixDofCapable();
	bool m_bCheckedSixDof;

	CRunAutomatedCompDlg runAutomatedCompDlg;

public:
	afx_msg void OnUpdateCommandAsyncmsgs(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCommandBoth(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCommandAbort(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCommandException(CCmdUI *pCmdUI);
	
	afx_msg void OnDemonstrationsCombosearch();
	afx_msg void OnUpdateDemonstrationsCombosearch(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRunAutomatedComp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCommandRunApplication(CCmdUI *pCmdUI);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__520CDF2B_4D62_11D6_8BCD_0001031CC11D__INCLUDED_)
