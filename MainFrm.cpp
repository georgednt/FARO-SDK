// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "TrackerModeDlg.h"
#include "ConnectDlg.h"
#include "Globals.h"
#include "Constants.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Tracker* gpTracker;
CBlocking gBlocking;
CWorkerThread gWorkerThread;
CListeners gListeners;
RUNMODE gRunMode;
boolean useSimulator = false;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_UPDATE_COMMAND_UI(ID_COMMAND_BOTH, &CMainFrame::OnUpdateCommandBoth)
	ON_UPDATE_COMMAND_UI(ID_COMMAND_ABORT, &CMainFrame::OnUpdateCommandAbort)
	ON_UPDATE_COMMAND_UI(ID_COMMAND_EXCEPTION, &CMainFrame::OnUpdateCommandException)
	ON_UPDATE_COMMAND_UI(ID_COMMAND_ASYNCMSGS, &CMainFrame::OnUpdateCommandAsyncmsgs)
	ON_UPDATE_COMMAND_UI_RANGE(ID_TRACKER_MODE,ID_COMMAND_CONNECT,OnUpdateCommandTrackerCommands)
	ON_UPDATE_COMMAND_UI_RANGE(ID_COMMAND_DISCONNECT,ID_COMMAND_BOTH,OnUpdateCommandTrackerCommands1)	
	ON_WM_CREATE()
	ON_COMMAND(ID_TRACKER_MODE, OnTrackerMode)
	ON_COMMAND(ID_COMMAND_CONNECT, OnCommandConnect)
	ON_COMMAND(ID_COMMAND_DISCONNECT, OnCommandDisconnect)
	ON_COMMAND(ID_COMMAND_SEQUENCE, OnCommandSequence)
	ON_COMMAND(ID_COMMAND_ASYNCMSGS, OnCommandAsyncmsgs)
	ON_COMMAND(ID_COMMAND_ABORT, OnCommandAbort)
	ON_COMMAND(ID_COMMAND_EXCEPTION, OnCommandException)	
	ON_COMMAND(ID_COMMAND_FOREGND, OnCommandForegnd)
	ON_COMMAND(ID_COMMAND_BACKGND, OnCommandBackgnd)
	ON_COMMAND(ID_COMMAND_BOTH, OnCommandBoth)	
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UWM_CONNECT_LISTENER_FIRED, OnConnectListenerFired)
	ON_MESSAGE(UWM_CONNECT_FAILED, OnConnectFailed)
	ON_MESSAGE(UWM_STATUS_CHANGED, OnStatusChanged)
	ON_MESSAGE(UWM_CHANGE_OCCURED, OnChangeOccured)
	ON_MESSAGE(UWM_SEARCH_CMD_FIRED, OnSearchCmdFired)
	ON_MESSAGE(UWM_APPLICATION_STATE_CHANGED, OnApplicationStateChanged)
	ON_MESSAGE(UWM_FOREGND_MEASUREMENT_AVAILABLE, OnForegndMeasurementAvailable)
	ON_MESSAGE(UWM_FOREGND_MEASUREMENT_STOPPED, OnForegndMeasurementStopped)
	ON_MESSAGE(UWM_BKGND_MEASUREMENT_AVAILABLE, OnBackgndMeasurementAvailable)
	ON_MESSAGE(UWM_COMMAND_FAILED, OnCommandFailed)
	ON_MESSAGE(UWM_UPDATE_CMDSEQ_STATUS, OnUpdateCmdseqStatus)
	ON_MESSAGE(UWM_ON_SMXEXCEPTION, OnSMXException)	
	ON_COMMAND(ID_DEMONSTRATIONS_COMBOSEARCH, &CMainFrame::OnDemonstrationsCombosearch)
	ON_UPDATE_COMMAND_UI(ID_DEMONSTRATIONS_COMBOSEARCH, &CMainFrame::OnUpdateDemonstrationsCombosearch)	
	ON_COMMAND(ID_DEMONSTRATIONS_RUNAUTOMATEDCOMP, OnCommandRunAutomatedComp)
	ON_UPDATE_COMMAND_UI(ID_DEMONSTRATIONS_RUNAUTOMATEDCOMP, &CMainFrame::OnUpdateRunAutomatedComp)		
	ON_UPDATE_COMMAND_UI(ID_COMMAND_RUN_APPLICATION, &CMainFrame::OnUpdateCommandRunApplication)
	ON_COMMAND(ID_COMMAND_RUN_APPLICATION, &CMainFrame::OnCommandRunApplication)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	gRunMode = UI_MODE;
	m_bConnected	=	FALSE;
	m_bCmdBusy		=	FALSE;
	m_bMeasBusy		=	FALSE;
	m_bBkndMeasBusy	=	FALSE;
	m_bCheckedSixDof =  FALSE;
}

CMainFrame::~CMainFrame()
{	
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnTrackerMode() 
{
	//Just because here in this demo we are showing modes in blocking and listeners
	//it does not mean one cannot use a combination of both. A combination of blocking
	//and listeners can very well be used. Examples of this are provided in case of
	//stopping the applications and stopping background measurements.
	CTrackerModeDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnCommandConnect() 
{
	CConnectDlg dlg;
	if(dlg.DoModal() != IDOK)
		return;
	
	BeginWaitCursor();
	//Before intializing Tracker object make sure that all the jar files(Tracker.jar,
	//Apps4xx.jar, AppsKeystoneSim.jar(if you want to use simulator), Utility.jar, Ftp. jar)
	//Tracker.dll and the JRE(Java Runtime Environment) folder is present in the debug or release directory.
	//Make sure that Tracker.h and Tracker.lib files are present in the working directory.
	//If these files are missing and if you are trying to intialize Tracker object it
	//would cause a crash.

	//Also, Its very important to select the "Enable Run-Time Type Information(RTTI)" in the
	//project settings to support the throwing of exceptions and casting. This has to be done
	//in the projects where Tracker Driver is being used.
	CString srNum = dlg.getSerialNumber();
	try
	{	
		//If you would like to use Simulator, please specify "Simulator" instead of serial number or ip address in the Connect dlg and select ok.
		if(useSimulator == false)
		{
			gpTracker = new Tracker(srNum.GetBuffer());	
		}
		else
		{
			gpTracker = new Tracker("TrackerKeystoneSim");
		}		
	}
	catch(TrackerException* e)
	{
		char* msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
		return;
	}
	catch(SMXException* e)
	{
		char msg[1024];
		e->getMsg(msg, 1024);
		CString text = "\nPlease check that the JRE folder and the jar files are in\nthe current working directory and restart the application.";
		strcat_s(msg, text.GetBuffer(0));
		AfxMessageBox(msg, MB_ICONSTOP);
		delete e;
		return;
	}

	//This listener is used to enable and disable the UI items whenever the Tracker
	//is busy since if any Tracker command is executed while Tracker is busy it would
	//throw an UserInterfacebusy exception.
	m_pTrackerBusyListener = new TrackerBusyListener();		
	gpTracker->addBusyListener(m_pTrackerBusyListener);

	//Make sure that Tracker object is intialized before executing any Tracker command.
	//To connect to the Tracker IpAddress, Username and Password has to be supplied
	//depending upon whether you are user or factory or admin etc..
	if(gRunMode == WORKER_MODE)
	{
		gWorkerThread.CreateThread();
		gWorkerThread.OnConnect();
	}
	else if(gRunMode == UI_MODE)
	{
		gBlocking.Connect();
	}
	else if(gRunMode == EVENT_MODE)
	{
		//The listeners that are being added here are used specifically when the user
		//selects Listeners mode
		gListeners.AddListeners();
		gListeners.Connect();	
	}	
	
	EndWaitCursor();
}

void CMainFrame::OnCommandDisconnect()
{
	if(!m_bConnected)
		return;

	BeginWaitCursor();	

	if(gRunMode == WORKER_MODE)
	{
		gWorkerThread.OnDisconnect();
	}
	else if(gRunMode == UI_MODE)
	{
		gBlocking.Disconnect();
	}
	else if(gRunMode == EVENT_MODE)
	{
		m_hDisconnectEvent = CreateEvent(NULL, TRUE, FALSE, "DisconnectEvent");
		ResetEvent(m_hDisconnectEvent);
		gListeners.Disconnect();
		VERIFY(WaitForSingleObject(m_hDisconnectEvent, INFINITE) == WAIT_OBJECT_0);
		gListeners.RemoveListeners();
	}

	if(m_pTrackerBusyListener)
	{
		gpTracker->removeBusyListener(m_pTrackerBusyListener);
		delete m_pTrackerBusyListener;
		m_pTrackerBusyListener = NULL;
	}
	m_bCheckedSixDof = false;
	if(gpTracker)
	{
		delete gpTracker;
		gpTracker = NULL;
	}
	useSimulator = false;
	EndWaitCursor();
}

LRESULT CMainFrame::OnConnectListenerFired(WPARAM wParam, LPARAM lParam)
{	
	m_bConnected = (BOOL)lParam;
	return 0;
}

void CMainFrame::OnCommandSequence() 
{	
	//This demonstration shows how Tracker commands can be executed in sequence.
	//The best option would be to use listeners or in separate Worker Thread execute
	//the commands in blocking. Both of these options would not block the User Interface.
	//If User Interface is of no concern then they can be done in Blocking mode in the main
	//UI thread itself.
	m_CmdseqDlg.DoModal();
}

LRESULT CMainFrame::OnUpdateCmdseqStatus(WPARAM wParam, LPARAM lParam)
{
	char* msg = (char*)lParam;
	m_CmdseqDlg.UpdateCmdseqStatus(msg);
	return 0;
}

void CMainFrame::OnCommandAsyncmsgs() 
{
	checkIfTrkSixDofCapable();
	//Shows how asynchronous messages fire.
	//For the msgs to fire asynchronous messages should be started and the status listener
	//and change listener should be added.
	//Whenever there is a change in the status like motors are turned OFF or ON etc the listener
	//fires. Whenever there is a change in Target type etc. change listener fires.
	//Once the listeners are added they would fire whenever a Tracker command is executed.
	//irrespective of any mode.
	m_AyncMsgDlg.DoModal();
}

LRESULT CMainFrame::OnStatusChanged(WPARAM wParam, LPARAM lParam)
{
	Status* status = (Status*)lParam;	
	m_AyncMsgDlg.SetStatusChange(status);
	delete status;
	return 0;
}

LRESULT CMainFrame::OnChangeOccured(WPARAM wParam, LPARAM lParam)
{
	Change* change = (Change*)lParam;	
	m_AyncMsgDlg.SetChangeOccured(change);	
	delete change;
	return 0;
}

void CMainFrame::OnCommandAbort() 
{
	//This shows how a Tracker Command can be aborted.
	//Here when the Abort command demo is selected we are just pointing the laser beam
	//to a postion where there may not be a target so that search takes place for
	//a little bit of long time and it would give some time to abort the command.	
	try
	{
		//get the current blocking state and reset state after the command is executed
		bool block = gpTracker->getBlocking();

		gpTracker->setBlocking(true);
		gpTracker->move(90,90,3, false);
		gpTracker->setBlocking(block);
	}
	catch(TrackerException* e)
	{
		char* msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}

	m_AbortAndExpdlg.m_bAbort = TRUE;
	
	if(gRunMode == EVENT_MODE)
	{
		LPARAM lParam = (LPARAM)m_AbortAndExpdlg.m_bAbort;
		DialogBoxParam(AfxGetResourceHandle(), (LPCSTR)IDD_DIALOG_SEARCH , m_hWnd, SEARCHDlgProc, lParam);
	}
	else
	{
		m_AbortAndExpdlg.DoModal();	
	}	
}

void CMainFrame::OnCommandException() 
{
	//Shows how a Tracker Exception is generated.
	//Again here also we are using Search. We are searching for the Target at a location
	//by pointing the laser beam to that location. The Tracker will throw an exception after
	//completing the search.
	//Also we used exceptions all over the place which must provide as examples.
	//While using this demo to see how the Tracker driver works there might be some exceptions
	//thrown by the Tracker.
	try
	{
		//turn blocking on and execute move command.
		bool block = gpTracker->getBlocking();		
		gpTracker->setBlocking(true);
		gpTracker->move(90,90,3, false);		
		//reset blocking to its original state.		
		gpTracker->setBlocking(block);		
	}
	catch(TrackerException* e)
	{
		char* msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}

	m_AbortAndExpdlg.m_bAbort = FALSE;
	
	if(gRunMode == EVENT_MODE)
	{
		LPARAM lParam = (LPARAM)m_AbortAndExpdlg.m_bAbort;
		DialogBoxParam(AfxGetResourceHandle(), (LPCSTR)IDD_DIALOG_SEARCH , m_hWnd, SEARCHDlgProc, lParam);
	}
	else
	{
		m_AbortAndExpdlg.DoModal();	
	}	
}

LRESULT CMainFrame::OnSearchCmdFired(WPARAM wParam, LPARAM lParam)
{
	char* msg = (char*)lParam;
	AfxMessageBox(msg);	
	trackerDeleteString(msg);
	return 0;
}

void CMainFrame::OnCommandRunApplication() 
{
	//This demo shows how Tracker applications are started and stopped.
	//Also tells how to get the available applications and started applications
	m_AppDlg.DoModal();	
}

LRESULT CMainFrame::OnApplicationStateChanged(WPARAM wParam, LPARAM lParam)
{
	BOOL run = (BOOL)lParam;
	char* name = (char*)wParam;
	m_AppDlg.FillStartedAppList(run, name);
	trackerDeleteString(name);
	return 0;
}

void CMainFrame::OnCommandForegnd() 
{
	//How Foregnd measurements can be done.
	m_bMeasurement = TRUE;
	m_bMultiMeasurements = FALSE;
	checkIfTrkSixDofCapable();
	m_MeasureDlg.DoModal();
}

LRESULT CMainFrame::OnForegndMeasurementAvailable(WPARAM wParam, LPARAM lParam)
{
	if(lParam)
	{
		MeasurePointData* pData = (MeasurePointData*)lParam;
		if(pData)
		{	
			if(m_bMultiMeasurements)
			{
				if(m_bSixDofCapable)
					m_BothDlg.InsertForegndMeasurementToList(pData->azimuth(), pData->zenith(), pData->distance(), pData->rotationA(), pData->rotationB(), pData->rotationC(), pData->status(), pData->sixDofData());
				else
					m_BothDlg.InsertForegndMeasurementToList(pData->azimuth(), pData->zenith(), pData->distance(), pData->status());
			}
			else
			{
				if(gRunMode == EVENT_MODE)
					gListeners.OnStopMeasurements();

				if(m_bSixDofCapable)
					m_MeasureDlg.InsertMeasurementToList(pData->azimuth(), pData->zenith(), pData->distance(), pData->rotationA(), pData->rotationB(), pData->rotationC(), pData->status(), pData->sixDofData());
				else
					m_MeasureDlg.InsertMeasurementToList(pData->azimuth(), pData->zenith(), pData->distance(), pData->status());
			}
		}
	}
	return 0;
}

LRESULT CMainFrame::OnForegndMeasurementStopped(WPARAM wParam, LPARAM lParam)
{
	gListeners.OnRemoveForegndCmdCompleteListener();		
	return 0;
}

void CMainFrame::OnCommandBackgnd() 
{
	//How backgnd measurements can be done
	m_bMeasurement = FALSE;	
	m_bMultiMeasurements = FALSE;
	checkIfTrkSixDofCapable();
	m_MeasureDlg.DoModal();	
}

LRESULT CMainFrame::OnBackgndMeasurementAvailable(WPARAM wParam, LPARAM lParam)
{	
	if(lParam)
	{
		MeasurePointData* pData = (MeasurePointData*)lParam;
		if(pData)
		{	
			if(m_bMultiMeasurements)
			{
				if(m_bSixDofCapable)
					m_BothDlg.InsertBackgndMeasurementToList(pData->azimuth(), pData->zenith(), pData->distance(), pData->rotationA(), pData->rotationB(), pData->rotationC(), pData->status(), pData->sixDofData());
				else
					m_BothDlg.InsertBackgndMeasurementToList(pData->azimuth(), pData->zenith(), pData->distance(), pData->status());
			}
			else
			{
				if(gRunMode == EVENT_MODE)
					gListeners.OnStopMeasurements();

				if(m_bSixDofCapable)
					m_MeasureDlg.InsertMeasurementToList(pData->azimuth(), pData->zenith(), pData->distance(), pData->rotationA(), pData->rotationB(), pData->rotationC(), pData->status(), pData->sixDofData());
				else
					m_MeasureDlg.InsertMeasurementToList(pData->azimuth(), pData->zenith(), pData->distance(), pData->status());
			}
		}			
	}
	return 0;
}

void CMainFrame::OnCommandBoth() 
{
	//In blocking mode of the UI we cannot run both the Foregnd and Backgnd measurements
	//simultaneously. For this to work either listeners or separate worker thread has
	//to be used.
	if(gRunMode == UI_MODE)
		return;	
	m_bMultiMeasurements = TRUE;
	checkIfTrkSixDofCapable();
	m_BothDlg.DoModal();	
}

void CMainFrame::OnUpdateCommandTrackerCommands(CCmdUI * pCmdUI)
{
	if((!m_bConnected && m_bCmdBusy) || (m_bConnected && !m_bCmdBusy))
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateCommandTrackerCommands1(CCmdUI * pCmdUI)
{
	if(m_bConnected && !m_bCmdBusy)		
		pCmdUI->Enable(TRUE);
	else		
		pCmdUI->Enable(FALSE);
}

void CMainFrame::OnClose() 
{
	OnCommandDisconnect();
	
	CMDIFrameWnd::OnClose();
}

LRESULT CMainFrame::OnCommandFailed(WPARAM wParam, LPARAM lParam)
{
	char* msg = (char*)lParam;
	AfxMessageBox(msg);
	trackerDeleteString(msg);
	return 0;
}

LRESULT CMainFrame::OnSMXException(WPARAM wParam, LPARAM lParam)
{
	char* msg = (char*)lParam;
	AfxMessageBox(msg);
	return 0;
}

/*************************************************************************************************
* Function: stateChanged(BusyEvent* event)
* Fires: This listener fires whenever the tracker is busy executing tracker command.
* Event: The event tells whether the Tracker command is busy or the measurements or
*		 the background measurements
* Comments: Busy listener can be added immediately after establishing a connection to the Tracker
*			This listener comes in handy for many purposes like if we want to disable
*			UI or any UI item when Tracker command is busy or measurements are busy.
*			The listener is being used here to disable all the items in the listbox 
*			whenever the listener fires saying that Tracker command is busy so that the
*			user will not start another application. If the user starts another application
*			or starts any other Tracker command while the Tracker is busy it throws
*			InterfaceBusy exception.
*************************************************************************************************/
void TrackerBusyListener::stateChanged(BusyEvent* event)
{
	bool busy = event->getCommandState();
	gMainWnd->SetCommandBusy(busy);

	bool mbusy = event->getMeasureState();
	gMainWnd->SetMeasureBusy(mbusy);
	
	bool bkndbusy = event->getBkndMeasureState();	
	gMainWnd->SetBkndMeasureBusy(bkndbusy);
}


void CMainFrame::SetDisconnectEvent()
{
	SetEvent(m_hDisconnectEvent);
}

LRESULT CMainFrame::OnConnectFailed(WPARAM wParam, LPARAM lParam)
{
	if(lParam)
	{
		char* msg = (char*)lParam;
		AfxMessageBox(msg);
		trackerDeleteString(msg);
	}

	if(gRunMode == EVENT_MODE)
		gListeners.RemoveListeners();
	
	if(m_pTrackerBusyListener)
	{
		gpTracker->removeBusyListener(m_pTrackerBusyListener);
		delete m_pTrackerBusyListener;
		m_pTrackerBusyListener = NULL;
	}	
	if(gpTracker)
	{
		delete gpTracker;
		gpTracker = NULL;
	}
	return 0;
}


void CMainFrame::OnUpdateCommandAsyncmsgs(CCmdUI *pCmdUI)
{
	if(!m_bConnected || useSimulator)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	if(gRunMode == EVENT_MODE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}	
}

void CMainFrame::OnUpdateCommandBoth(CCmdUI *pCmdUI)
{
	if(!m_bConnected)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	if(gRunMode == EVENT_MODE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}	
}

void CMainFrame::OnUpdateCommandAbort(CCmdUI *pCmdUI)
{
	if(!m_bConnected)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	if(gRunMode == WORKER_MODE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}	
}

void CMainFrame::OnUpdateCommandException(CCmdUI *pCmdUI)
{
	if(!m_bConnected)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	if(gRunMode == EVENT_MODE)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}	
}

void CMainFrame::OnDemonstrationsCombosearch()
{
	// TODO: Add your command handler code here
	m_ComboSearchDlg.DoModal();
}

void CMainFrame::OnUpdateDemonstrationsCombosearch(CCmdUI *pCmdUI)
{
	if(!m_bConnected )
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	pCmdUI->Enable(TRUE);	
}

BOOL CMainFrame::sixDofCapable()
{
	return m_bSixDofCapable;
}

void CMainFrame::StartMeasurements()
{	
	
    if(gRunMode == UI_MODE && m_bMultiMeasurements == false)
    {
		CList<MeasurePointData*, MeasurePointData*> MeasurementList;
		gBlocking.OnStartMeasurements(MeasurementList);
		
		for ( POSITION pos = MeasurementList.GetHeadPosition(); pos; MeasurementList.GetNext(pos) )
		{
			MeasurePointData* pData = (MeasurePointData*)MeasurementList.GetAt(pos);
			
			if(gMainWnd->sixDofCapable())
				m_MeasureDlg.InsertMeasurementToList(pData->azimuth(), pData->zenith(), pData->distance(), pData->rotationA(), pData->rotationB(), pData->rotationC(), pData->status(), pData->sixDofData());
			else
				m_MeasureDlg.InsertMeasurementToList(pData->azimuth(), pData->zenith(), pData->distance(), pData->status());
		}            
    }
    else if(gRunMode == WORKER_MODE)
    {
        gWorkerThread.OnStartMeasurements();
    }
    else if(gRunMode == EVENT_MODE)
    {
        gListeners.OnStartMeasurements();
    }
}

void CMainFrame::StopMeasurements()
{
    if (gRunMode == WORKER_MODE)
    {
        gWorkerThread.OnStopMeasurements();
    }
    else if (gRunMode == EVENT_MODE)
    {
        gListeners.OnStopMeasurements();
    }
}

void CMainFrame::checkIfTrkSixDofCapable()
{
	if(m_bCheckedSixDof == false)
	{
		m_bCheckedSixDof = true;
		if(gRunMode == UI_MODE)
		{			
			m_bSixDofCapable = gBlocking.sixDofCapable();
		}
		else if(gRunMode == WORKER_MODE)
		{
			m_bSixDofCapable = gWorkerThread.sixDofCapable();
		}
		else if(gRunMode == EVENT_MODE)
		{
			m_bSixDofCapable = gListeners.sixDofCapable();
		}
	}
}

void CMainFrame::OnCommandRunAutomatedComp()
{
	runAutomatedCompDlg.DoModal();
}

void CMainFrame::OnUpdateRunAutomatedComp(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (!m_bConnected)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateCommandRunApplication(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (!m_bConnected || useSimulator )
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	pCmdUI->Enable(TRUE);
}