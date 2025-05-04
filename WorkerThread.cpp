//WorkerThread.cpp

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "CommandDone.h"
#include "Globals.h"
#include "WorkerThread.h"

UINT StartBkgndMeasurements(LPVOID pParam);

/*************************************************************************************************
* Function: CreateThread()
* Comments: 
*************************************************************************************************/
void CWorkerThread::CreateThread()
{	
	m_bCommandEventSet = FALSE;
	m_pMyMainWnd = AfxGetMainWnd();

	//After executing the command specified this event will wait untill it is set 
	//Once it is set the thread will resume and executes the next specified command
	//This event is a MANUAL event
	m_hSuspendResumeEvent = CreateEvent(NULL, TRUE, FALSE, "SuspendResumeEvent");

	//This event is used only in cases where the UI thread has to wait for the worker thread
	//to complete its operation.
	//This event is a MANUAL event
	m_hCommandDoneEvent = CreateEvent(NULL, TRUE, FALSE, "CommandCompleteEvent");
	
	//Creating the Thread which starts immediately.
	m_pWorkerThread = AfxBeginThread(StartThread, this,
									THREAD_PRIORITY_NORMAL, 0 ,CREATE_SUSPENDED);
	VERIFY(m_pWorkerThread);	
	return;
}

/*************************************************************************************************
* Function: StartThread( LPVOID pParam )
* Comments: 
*************************************************************************************************/
UINT CWorkerThread:: StartThread( LPVOID pParam )
{	
	CWorkerThread* pWorkerThread = (CWorkerThread*)pParam;	
	pWorkerThread->RunThread();
	return 0;
}

/*************************************************************************************************
* Function: RunThread()
* Comments: 
*************************************************************************************************/
void CWorkerThread::RunThread()
{
	while(tCommand != EXIT)
	{		
		switch(tCommand)
		{			
			case CONNECT:
			{
				try
				{
					//Turn blocking on before connecting to tracker
					gpTracker->setBlocking(true);
					if (useSimulator == false)
					{
						gpTracker->connect();
					}
					else
					{
						gpTracker->connect("128.128.128.100", "user", "");
					}
				}
				catch( TrackerException* e )
				{
					char* msg = e->getText();
					LPARAM lParam = (LPARAM)msg;
					//if Tracker connection failes delete the memory of Tracker object					
					gMainWnd->PostMessage(UWM_CONNECT_FAILED, 0, lParam);
					delete e;
				}
				BOOL connected = gpTracker->connected();
				gMainWnd->PostMessage(UWM_CONNECT_LISTENER_FIRED, 0, (LPARAM)connected);
			}
			break;
			case DISCONNECT:
			{
				try
				{
					gpTracker->disconnect();
					//turn blocking off after disconnecting from tracker
					gpTracker->setBlocking(false);
				}
				catch( TrackerException* e )
				{
					char* msg = e->getText();
					LPARAM lParam = (LPARAM)msg;
					gMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
					delete e;
				}
				BOOL connected = gpTracker->connected();
				gMainWnd->PostMessage(UWM_CONNECT_LISTENER_FIRED, 0, (LPARAM)connected);
			}
			break;
			case CMD_SEQUENCE:
			{		
				try
				{
					PostMsgToUpdateStatus("Checking if Tracker is initialized");
					bool state = gpTracker->initialized();
					if(!state)
					{
						PostMsgToUpdateStatus("Tracker not initialized, Initializing");			
						gpTracker->initialize();
					}

					PostMsgToUpdateStatus("Checking motor state");
					state = gpTracker->motorsOn();
					if(!state)
					{
						PostMsgToUpdateStatus("Motors turned off, turning on");
						gpTracker->changeMotorState(true);
						PostMsgToUpdateStatus("Turned on motors");
					}

					PostMsgToUpdateStatus("Checking tracking state");
					state = gpTracker->trackingOn();
					if(!state)
					{
						PostMsgToUpdateStatus("Tracking turned off, turning on");
						gpTracker->changeTrackingState(true);
						PostMsgToUpdateStatus("Turned on tracking");
					}

					PostMsgToUpdateStatus("Checking id Distance is valid");
					state = gpTracker->targetLocationValid();
					if(!state)
					{
						PostMsgToUpdateStatus("Distance Invalid");
					}

					PostMsgToUpdateStatus("Checking if Target present");
					state = gpTracker->targetPresent();
					if(!state)
					{
						PostMsgToUpdateStatus("Target not present");
					}

					PostMsgToUpdateStatus("Homing Tracker");
					gpTracker->home(true);
					PostMsgToUpdateStatus("Home done");
				}
				catch( TrackerException* e )
				{
					char* msg = e->getText();
					LPARAM lParam = (LPARAM)msg;
					gMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
					delete e;
				}
			}
			break;
			case SEARCH:
			{
				try
				{
					gpTracker->search(3);
				}
				catch( TrackerException* e )
				{
					char* msg = e->getText();
					LPARAM lParam = (LPARAM)msg;
					gMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
					delete e;
				}
			}
			break;
			case AVAILABLE_APPS:
			{				
				TrkDrvObjectArray* pAppsArray = NULL;
				try
				{
					pAppsArray = gpTracker->availableApplications();
					if(pAppsArray)
					{
						m_Appslist.RemoveAll();
						int numApps = pAppsArray->getNumElements();
						for(int i = 0; i < numApps; i++)
						{				
							DriverStringPointer* app_name = (DriverStringPointer*)(pAppsArray->getElement(i));					
							char* name = app_name->getStringData();								
							char* temp = new char[strlen(name) + 1];
							strcpy_s(temp, strlen(name) + 1, name);
							m_Appslist.AddTail(temp);
						}
					}
				}
				catch(TrackerException* e)
				{
					char* msg = e->getText();
					LPARAM lParam = (LPARAM)msg;
					gMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
					delete e;
				}
				delete pAppsArray;				
			}
			break;
			case RUN_APP:
			{
				try
				{
					gpTracker->startApplicationFrame(m_AppName, "");		
				}
				catch(TrackerException* e)
				{
					char* msg = e->getText();
					LPARAM lParam = (LPARAM)msg;
					gMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
					delete e;
				}
			}
			break;
			case STOP_APPS:
			{
				TrkDrvObjectArray* pAppsArray = NULL;
				try
				{
					pAppsArray = gpTracker->startedApplications();

					if( pAppsArray)
					{
						int numApps = pAppsArray->getNumElements();
						for(int i = 0; i < numApps; i++)
						{		
							DriverStringPointer* app_name = (DriverStringPointer*)(pAppsArray->getElement(i));					
							char* pAppRunning = app_name->getStringData();							
							gpTracker->stopApplicationFrame(pAppRunning);					
						}
					}		
				}
				catch(TrackerException *e)
				{
					char* msg = e->getText();
					LPARAM lParam = (LPARAM)msg;
					gMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
					delete e;
				}
				delete pAppsArray;
			}
			break;
			case FOREGND_MEASURE:
			{
				TrkDrvObjectArray* pDataArray = NULL;
				MeasurePointData* pData = NULL;

				try
				{
					NullStartTrigger		startTrigger;
					IntervalTrigger			continueTrigger(2.0);
					AverageFilter			filter;
					MeasureCfg	cfg(2000, &filter,&startTrigger, &continueTrigger);				

					gpTracker->setMeasureEventRate(nEventRate);					

					gpTracker->startMeasurePoint(&cfg);
					if(nEventRate == 1 && !bMulti)
					{			
						pData = gpTracker->readMeasurePointData();
						
						ASSERT(pData);

						LPARAM lParam = (LPARAM)pData;
						gMainWnd->PostMessage(UWM_FOREGND_MEASUREMENT_AVAILABLE, 0, lParam);
					}
					else if(nEventRate == 10 && !bMulti)
					{
						pDataArray = NULL;
						pDataArray = gpTracker->readMeasurePointData(nEventRate);
						ASSERT(pDataArray);
						int numElements = pDataArray->getNumElements();
						ASSERT(numElements == nEventRate);
						for(int i = 0; i < numElements; i++)
						{
							pData = (MeasurePointData*)pDataArray->getElement(i);
							ASSERT(pData);
							LPARAM lParam = (LPARAM)pData;				
							gMainWnd->PostMessage(UWM_FOREGND_MEASUREMENT_AVAILABLE, 0, lParam);
						}
					}
					else if(nEventRate == 1 && bMulti)
					{
						while(!bStopBkgnd)
						{
							pData = gpTracker->readMeasurePointData();
						
							ASSERT(pData);

							LPARAM lParam = (LPARAM)pData;
							gMainWnd->PostMessage(UWM_FOREGND_MEASUREMENT_AVAILABLE, 0, lParam);
						}
					}					
				}
				catch( TrackerException* e )
				{
					char* msg = e->getText();
					LPARAM lParam = (LPARAM)msg;
					gMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
					delete e;
				}
				catch( SMXException* e )
				{	
					char msg[64];
					e->getMsg(msg, 64);
					LPARAM lParam = (LPARAM)lParam;
					gMainWnd->PostMessage(UWM_ON_SMXEXCEPTION, 0, lParam);
					delete e;
				}
				try
				{
					gpTracker->stopMeasurePoint();
				}
				catch( TrackerException* e )
				{
					char* msg = e->getText();
					LPARAM lParam = (LPARAM)msg;
					gMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
					delete e;
				}
			}
			break;
			case COMBO_SEARCH_1:
			{
				try
				{
					gpTracker->comboSearch();
				}
				catch( TrackerException* e )
				{
					char* msg = e->getText();
					LPARAM lParam = (LPARAM)msg;
					gMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
					delete e;
				}
			}
			break;
			case COMBO_SEARCH_2:
			{
				try
				{
					gpTracker->comboSearch(csAz, csZe, csDist, csAzTol, csZeTol, csSearchIfNeeded);
				}
				catch( TrackerException* e )
				{
					char* msg = e->getText();
					LPARAM lParam = (LPARAM)msg;
					gMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
					delete e;
				}
			}
			break;			
			default:
				break;
		}		

		ResetEvent(m_hSuspendResumeEvent);
		if(m_bCommandEventSet)
			SetEvent(m_hCommandDoneEvent);

		if(tCommand != EXIT)
		{
			VERIFY(WaitForSingleObject(m_hSuspendResumeEvent, INFINITE) == WAIT_OBJECT_0);			
		}
	}
	return;
}

/*************************************************************************************************
* Function: OnConnect(char* ip)
* Comments: 
*************************************************************************************************/
void CWorkerThread::OnConnect()
{	
	tCommand = CONNECT;
	m_pWorkerThread->ResumeThread();
	//SetEvent(m_hSuspendResumeEvent);
}

/*************************************************************************************************
* Function: OnDisconnect()
* Comments: 
*************************************************************************************************/
void CWorkerThread::OnDisconnect()
{
	tCommand = DISCONNECT;
	m_bCommandEventSet = TRUE;
	SetEvent(m_hSuspendResumeEvent);

	//Here the UI thread will wait untill the worker thread completely Disconnects
	ResetEvent(m_hCommandDoneEvent);	
	VERIFY(WaitForSingleObject(m_hCommandDoneEvent, INFINITE) == WAIT_OBJECT_0);
	m_bCommandEventSet = FALSE;

	//After disconnecting the thread is asked to kill itself.
	tCommand = EXIT;
	SetEvent(m_hSuspendResumeEvent);

	DWORD dwExitCode;
	//After asking the thread to kill itself we will wait untill the worker thread kills itself
	if (m_pWorkerThread)
	{
		if(GetExitCodeThread(m_pWorkerThread->m_hThread, &dwExitCode) && dwExitCode == STILL_ACTIVE)
		{			
			VERIFY(WaitForSingleObject(m_pWorkerThread->m_hThread, INFINITE) == WAIT_OBJECT_0);
		}			
	}
	if(m_pIpAdd)
		delete m_pIpAdd;
	if(m_AppName)
		delete m_AppName;
}

/*************************************************************************************************
* Function: ExecuteCommandSequence()
* Comments: 
*************************************************************************************************/
void CWorkerThread::ExecuteCommandSequence()
{
	tCommand = CMD_SEQUENCE;
	SetEvent(m_hSuspendResumeEvent);
}

/*************************************************************************************************
* Function: PostMsgToUpdateStatus(char* txt)
* Comments: 
*************************************************************************************************/
void CWorkerThread::PostMsgToUpdateStatus(char* txt)
{
	LPARAM lParam = (LPARAM)txt;
	gMainWnd->PostMessage(UWM_UPDATE_CMDSEQ_STATUS, 0, lParam);
}

/*************************************************************************************************
* Function: StartSearch()
* Comments: 
*************************************************************************************************/
void CWorkerThread::StartSearch()
{
	tCommand = SEARCH;
	SetEvent(m_hSuspendResumeEvent);
}

/*************************************************************************************************
* Function: Abort()
* Comments: 
*************************************************************************************************/
void CWorkerThread::Abort()
{
	//Since worker thread is busy executing the Search command, Tracker command
	//is aborted from the UI thread.	
	try
	{
	//	gpTracker->setBlocking(true);
		gpTracker->abort();
	//	gpTracker->setBlocking(false)
	}	
	catch( TrackerException* e )
	{	
		char* msg = e->getText();		
		LPARAM lParam = (LPARAM)msg;
		gMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
		delete e;
	}
}

/*************************************************************************************************
* Function: OnAvailableApplications(CList<char*, char*> &AppsList)
* Comments: 
*************************************************************************************************/
void CWorkerThread::OnAvailableApplications(CList<char*, char*> &AppsList)
{
	tCommand = AVAILABLE_APPS;

	m_bCommandEventSet = TRUE;
	ResetEvent(m_hCommandDoneEvent);
	//Here also the UI thread waits for the worker thread to complete its operation
	//so that the UI thread can then access the data in m_AppsList filled by the worker thread	
	SetEvent(m_hSuspendResumeEvent);
	VERIFY(WaitForSingleObject(m_hCommandDoneEvent, INFINITE) == WAIT_OBJECT_0);
	m_bCommandEventSet = FALSE;

	for( POSITION pos = m_Appslist.GetHeadPosition(); pos; m_Appslist.GetNext(pos))
	{
		char* pAppName =  m_Appslist.GetAt(pos);
		AppsList.AddTail(pAppName);		
	}	
}

/*************************************************************************************************
* Function: OnRunApplication(char* appName)
* Comments: 
*************************************************************************************************/
void CWorkerThread::OnRunApplication(char* appName)
{
	tCommand = RUN_APP;
	m_AppName = new char[strlen(appName)+1];
	strcpy_s(m_AppName, strlen(appName) + 1, appName);
	SetEvent(m_hSuspendResumeEvent);
}

/*************************************************************************************************
* Function: OnStopApplication()
* Comments: 
*************************************************************************************************/
void CWorkerThread::OnStopApplication()
{
	tCommand = STOP_APPS;
	SetEvent(m_hSuspendResumeEvent);
}

/*************************************************************************************************
* Function: OnStartMeasurements()
* Comments: 
*************************************************************************************************/
void CWorkerThread::OnStartMeasurements()
{
	if(gMainWnd->GetMeasurementType())	
		OnStartForegndMeasurements();
	else
		OnStartBackgndMeasurements();
}

/*************************************************************************************************
* Function: OnStopMeasurements()
* Comments: 
*************************************************************************************************/
void CWorkerThread::OnStopMeasurements()
{
	if(gMainWnd->GetMeasurementType())	
		OnStopForegndMeasurements();
	else
		OnStopBackgndMeasurements();
}

/*************************************************************************************************
* Function: OnStartForegndMeasurements()
* Comments: 
*************************************************************************************************/
void CWorkerThread::OnStartForegndMeasurements()
{
	//Before the foregnd measurements are started we would like to supply the information
	//whether the measurements have to run untill user selects stop and even rate.
	tCommand = FOREGND_MEASURE;
	bMulti = gMainWnd->GetIfMultiMeasurements();
	bStopBkgnd = FALSE;
	nEventRate = gMainWnd->GetEventRate();
	SetEvent(m_hSuspendResumeEvent);
}

/*************************************************************************************************
* Function: OnStopForegndMeasurements()
* Comments: 
*************************************************************************************************/
void CWorkerThread::OnStopForegndMeasurements()
{
	bStopBkgnd = TRUE;
}

/*************************************************************************************************
* Function: OnStartBackgndMeasurements()
* Comments: 
*************************************************************************************************/
void CWorkerThread::OnStartBackgndMeasurements()
{
	//For backgnd measurements we are creating a new worker thread
	//For forgnd measurements the worker thread that is already existing is used.
	backGndInfo.bMulti = gMainWnd->GetIfMultiMeasurements();
	backGndInfo.pMainWnd = AfxGetMainWnd();
	backGndInfo.bStopBkgnd = FALSE;
	backGndInfo.nEventRate = gMainWnd->GetEventRate();
	
	m_pBkgndThread = AfxBeginThread(StartBkgndMeasurements, (LPVOID)&backGndInfo,
									THREAD_PRIORITY_NORMAL, 0 ,0);
}

/*************************************************************************************************
* Function: StartBkgndMeasurements(LPVOID pParam)
* Comments: 
*************************************************************************************************/
UINT StartBkgndMeasurements(LPVOID pParam)
{
	if(!gpTracker)
	return 0;

	BACKGNDINFO* tBackGndInfo = (BACKGNDINFO*)pParam;
		
	MeasurePointData* pData = NULL;	
	TrkDrvObjectArray* pDataArray = NULL;

	try
	{
		NullStartTrigger		startTrigger;
		IntervalTrigger			continueTrigger(0.25);
		AverageFilter			filter;
		MeasureCfg	cfg(20, &filter,&startTrigger, &continueTrigger);

		gpTracker->setBkndMeasureEventRate(tBackGndInfo->nEventRate);

		gpTracker->setBkndMeasureBlocking(true);
			
		gpTracker->startBkndMeasurePoint(&cfg);		

		if(tBackGndInfo->nEventRate == 1 && !tBackGndInfo->bMulti)
		{			
			pData = gpTracker->readBkndMeasurePointData();
			
			ASSERT(pData);

			LPARAM lParam = (LPARAM)pData;
			tBackGndInfo->pMainWnd->PostMessage(UWM_BKGND_MEASUREMENT_AVAILABLE, 0, lParam);	
		}
		else if(tBackGndInfo->nEventRate == 10 && !tBackGndInfo->bMulti)
		{
			pDataArray = NULL;
			pDataArray = gpTracker->readBkndMeasurePointData(tBackGndInfo->nEventRate);
			int numElements = pDataArray->getNumElements();
			for(int i = 0; i < numElements; i++)
			{
				pData = (MeasurePointData*)pDataArray->getElement(i);
				ASSERT(pData);
				LPARAM lParam = (LPARAM)pData;
				tBackGndInfo->pMainWnd->PostMessage(UWM_BKGND_MEASUREMENT_AVAILABLE, 0, lParam);
			}
		}
		else if(tBackGndInfo->nEventRate == 1 && tBackGndInfo->bMulti)
		{
			while(!tBackGndInfo->bStopBkgnd)
			{
				pData = gpTracker->readBkndMeasurePointData();
			
				ASSERT(pData);

				LPARAM lParam = (LPARAM)pData;
				tBackGndInfo->pMainWnd->PostMessage(UWM_BKGND_MEASUREMENT_AVAILABLE, 0, lParam);
			}
		}		
	}
	catch( TrackerException* e )
	{
		char* msg = e->getText();
		LPARAM lParam = (LPARAM)msg;
		tBackGndInfo->pMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
		delete e;	
	}
	catch( SMXException* e )
	{	
		char msg[64];
		e->getMsg(msg, 64);
		LPARAM lParam = (LPARAM)msg;
		tBackGndInfo->pMainWnd->PostMessage(UWM_ON_SMXEXCEPTION, 0, lParam);
		delete e;
	}
	try
	{
		gpTracker->stopBkndMeasurePoint();
		gpTracker->setBkndMeasureBlocking(false);		
	}
	catch( TrackerException* e )
	{
		char* msg = e->getText();
		LPARAM lParam = (LPARAM)msg;
		tBackGndInfo->pMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
		delete e;	
	}
	return 0;
}

/*************************************************************************************************
* Function: OnStopBackgndMeasurements()
* Comments: 
*************************************************************************************************/
void CWorkerThread::OnStopBackgndMeasurements()
{
	backGndInfo.bStopBkgnd = TRUE;
}

/*************************************************************************************************
* Function: sixDOFCapable
* Comments: 
*************************************************************************************************/
BOOL CWorkerThread::sixDofCapable()
{
	try
	{		
		m_bSixDofCapable = gpTracker->sixDofCapable();
	}
	catch( TrackerException* e )
	{
		char* msg = e->getText();
		LPARAM lParam = (LPARAM)msg;
		gMainWnd->PostMessage(UWM_COMMAND_FAILED, 0, lParam);
		delete e;
	}
	return m_bSixDofCapable;
}

/*************************************************************************************************
* Function: comboSearch1()
* Comments: 
*************************************************************************************************/
void CWorkerThread::ComboSearch1()
{
	tCommand = COMBO_SEARCH_1;
	SetEvent(m_hSuspendResumeEvent);
}

/*************************************************************************************************
* Function: comboSearch2()
* Comments: 
*************************************************************************************************/
void CWorkerThread::ComboSearch2(double az, double ze, double dist, double azTol, double zeTol, bool searchIfNeeded)
{
	csAz = az;
	csZe = ze;
	csDist = dist;
	csAzTol = azTol;
	csZeTol = zeTol;
	csSearchIfNeeded = searchIfNeeded;
	tCommand = COMBO_SEARCH_2;
	SetEvent(m_hSuspendResumeEvent);
}
