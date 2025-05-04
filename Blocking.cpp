//Blocking.cpp
#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "CommandDone.h"
#include "Globals.h"
#include "Constants.h"
#include "Blocking.h"

/*************************************************************************************************
* Function: Connect(char* ip)
* Comments: Establishes a connection to the tracker. To connect to the Tracker ipAddress,
*			Username and Password must be supplied. Also the Tracker object must be intialized
*			before connecting to the tracker.
/*************************************************************************************************/
void CBlocking::Connect()
{
	if(!gpTracker)
		return;

	try
	{
		gpTracker->setBlocking(true);
		if (useSimulator == false)
		{
			gpTracker->connect();	
		} 
		else
		{
			gpTracker->connect("128.128.128.100", "user", "");
		}

		gpTracker->setBlocking(false);
		gMainWnd->SetConnected(TRUE);
	}
	catch(TrackerException* e)
	{
		//Messsages are not modified in this demo. If you would like messages can be modified
		//if an exception is thrown
		char* msg;
		msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		//if Tracker connection failes delete the memory of Tracker object
		gMainWnd->OnConnectFailed(0,0);
		delete e;
	}
}

/*************************************************************************************************
* Function: Disconnect()
* Comments: Disconnects from the Tracker
*************************************************************************************************/
void CBlocking::Disconnect()
{
	if(!gpTracker)
		return;

	try
	{
		gpTracker->setBlocking(true);
		gpTracker->disconnect();
		gpTracker->setBlocking(false);
		gMainWnd->SetConnected(FALSE);
	}
	catch(TrackerException* e)
	{
		char* msg;
		msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}
}

/*************************************************************************************************
* Function: ExecuteCommandSequence()
* Comments: This method shows how Tracker commands can be executed one after another in blocking
*			mode.To execute the Tracker commands in Blocking mode is one of the easiest 
*			way. But, if there are too many commands then there is a chance for UI to get blocked
*************************************************************************************************/
void CBlocking::ExecuteCommandSequence()
{
	if(!gpTracker)
		return;	
	
	try
	{
		gpTracker->setBlocking(true);		

		m_pCmdDone->TrackerCommandDone("Checking if Tracker is initialized");		
		bool state = gpTracker->initialized();
		if(!state)
		{
			m_pCmdDone->TrackerCommandDone("Tracker not initialized, Initializing");
			gpTracker->initialize();
		}

		m_pCmdDone->TrackerCommandDone("Checking motor state");
		state = gpTracker->motorsOn();
		if(!state)
		{
			m_pCmdDone->TrackerCommandDone("Motors turned off, turning on");
			gpTracker->changeMotorState(true);
			m_pCmdDone->TrackerCommandDone("Turned on motors");
		}

		m_pCmdDone->TrackerCommandDone("Checking tracking state");
		state = gpTracker->trackingOn();
		if(!state)
		{
			m_pCmdDone->TrackerCommandDone("Tracking turned off, turning on");
			gpTracker->changeTrackingState(true);
			m_pCmdDone->TrackerCommandDone("Turned on tracking");
		}

		m_pCmdDone->TrackerCommandDone("Checking if Distance is valid");
		state = gpTracker->targetLocationValid();
		if(!state)
		{
			m_pCmdDone->TrackerCommandDone("Distance Invalid");
		}

		m_pCmdDone->TrackerCommandDone("Checking if Target present");
		state = gpTracker->targetPresent();
		if(!state)
		{
			m_pCmdDone->TrackerCommandDone("Target not present");
		}

		m_pCmdDone->TrackerCommandDone("Homing Tracker");
		gpTracker->home(true);
		m_pCmdDone->TrackerCommandDone("Home done");
		
		gpTracker->setBlocking(false);		
	}
	catch(TrackerException* e)
	{
		char* msg;
		msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}
}

/*************************************************************************************************
* Function: SetCommandDone(CommandDone* pDone)
* Comments: 
*************************************************************************************************/
void CBlocking::SetCommandDone(CommandDone* pDone)
{
	m_pCmdDone = pDone;
}

/*************************************************************************************************
* Function: StartSearch()
* Comments: Searches for the Target at the specified radius.
*************************************************************************************************/
void CBlocking::StartSearch()
{
	if(!gpTracker)
	return;

	try
	{
		gpTracker->setBlocking(true);
		gpTracker->search(3);
		gpTracker->setBlocking(false);	
	}
	catch(TrackerException* e)
	{
		char* msg;
		msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}
}

/*************************************************************************************************
* Function: AbortCommand()
* Comments: Aborts the currently executing Tracker command.
*************************************************************************************************/
void CBlocking::AbortCommand()
{
	if(!gpTracker)
	return;

	try
	{
		gpTracker->setBlocking(true);
		gpTracker->abort();
		gpTracker->setBlocking(false);	
	}
	catch(TrackerException* e)
	{
		char* msg;
		msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}
}

/*************************************************************************************************
* Function: OnAvailableApplications(CList<char*, char*> &lstApps)
* Comments: Returns all the available java applications.
*************************************************************************************************/
void CBlocking::OnAvailableApplications(CList<char*, char*> &lstApps)
{
	if(!gpTracker)
	return;

	TrkDrvObjectArray* pAppsArray = NULL;
	try
	{
		gpTracker->setBlocking(true);

		pAppsArray = gpTracker->availableApplications();
		if(pAppsArray)
		{
			int numApps = pAppsArray->getNumElements();
			for(int i = 0; i < numApps; i++)
			{					
				DriverStringPointer* app_name = (DriverStringPointer*)(pAppsArray->getElement(i));					
				char* name = app_name->getStringData();
				char* temp = new char[strlen(name) + 1];
				strcpy_s(temp, strlen(name) + 1, name);
				lstApps.AddTail(temp);
			}
		}	
		gpTracker->setBlocking(false);	
	}
	catch(TrackerException* e)
	{
		char* msg;
		msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}
	delete pAppsArray;
}

/*************************************************************************************************
* Function: OnStopApplication()
* Comments: Stops any java application that is currently running.
*************************************************************************************************/
void CBlocking::OnStopApplication()
{
	if(!gpTracker)
	return;

	TrkDrvObjectArray* pAppsArray = NULL;
	try
	{		
		//This method returns the aplications that are currently running.
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
		gpTracker->setBlocking(false);
	}
	catch(TrackerException* e)
	{
		char* msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}
	delete pAppsArray;
}

/*************************************************************************************************
* Function: OnRunApplication(char* appName)
* Comments: Start an application
*************************************************************************************************/
void CBlocking::OnRunApplication(char* appName)
{
	try
	{
		gpTracker->setBlocking(true);
		gpTracker->startApplicationFrame(appName, "");
		//turning blocking off when application is stopped.
	}
	catch(TrackerException* e)
	{
		char* msg;
		msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}
}

/*************************************************************************************************
* Function: OnStartMeasurements(CList<MEASUREDDATA, MEASUREDDATA> &DataList)
* Comments: 
*************************************************************************************************/
void CBlocking::OnStartMeasurements(CList<MeasurePointData*, MeasurePointData*> &DataList)
{
	if(gMainWnd->GetMeasurementType())	
		OnStartForegndMeasurements(DataList);
	else
		OnStartBackgndMeasurements(DataList);
}

/*************************************************************************************************
* Function: OnForegndMeasurements(CList<MEASUREDDATA, MEASUREDDATA> &DataList)
* Comments: Here measurement is started, data is read and measurement is stopped.
*************************************************************************************************/
void CBlocking::OnStartForegndMeasurements(CList<MeasurePointData*, MeasurePointData*> &DataList)
{
	if(!gpTracker)
	return;	
	
	//With the UI thread in blocking mode both the foreground and background measurements 
	//cannot be run at the same time. So that option is ignored here.

	TrkDrvObjectArray* pDataArray = NULL;
	MeasurePointData* pData = NULL;

	try
	{
		//Before starting the measurement a measurement configuration must be specified
		//for the Tracker to take observations.
		//In the measurement configuration no of samples per observation, type of filter,
		//type of start trigger, type of continue trigger has to be specified.
		//In the measurement configuration we can also specify time trigger,
		//distance trigger, digital trigger etc. By default here we are using
		//null and continue trigger. Refer to the documentation how they can be specified.

		NullStartTrigger		startTrigger;
		IntervalTrigger			continueTrigger(2.0);
		AverageFilter			filter;
		MeasureCfg	cfg(2000, &filter,&startTrigger, &continueTrigger);

		gpTracker->setBlocking(true);

		//Tells the Tracker how many records to be read.
		int nEventRate = gMainWnd->GetEventRate();
		gpTracker->setMeasureEventRate(nEventRate);

		gpTracker->startMeasurePoint(&cfg);
		
		if(nEventRate == 1)
		{			
			//if the user selects only to read a single data then we can read
			//the data as below.
			pData = gpTracker->readMeasurePointData();			
			ASSERT(pData);
			DataList.AddTail(pData);
		}
		else if(nEventRate == 10)
		{
			//if the user selects to read data of 10 points then we can use an SMXObjectArray
			//to read the data.
			//All the data from SMXObjectArray must be copied into a local buffer because
			//if it is deleted all the data also gets deleted.
			pDataArray = NULL;
			pDataArray = gpTracker->readMeasurePointData(nEventRate);
			ASSERT(pDataArray);
			int numElements = pDataArray->getNumElements();
			ASSERT(nEventRate == numElements);
			for(int i = 0; i < numElements; i++)
			{
				pData = (MeasurePointData*)pDataArray->getElement(i);
				ASSERT(pData);
				DataList.AddTail(pData);				
			}
		}
		gpTracker->stopMeasurePoint();

		gpTracker->setBlocking(false);
	}
		
	catch( TrackerException* e )
	{
		char* msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}
	catch( SMXException* e )
	{	
		char msg[50];
		e->getMsg(msg, 50);
		AfxMessageBox(msg);
		delete e;
	}
}

/*************************************************************************************************
* Function: OnBackgndMeasurements(CList<MEASUREDDATA, MEASUREDDATA> &DataList)
* Comments: Similiar to foreground measurements
*************************************************************************************************/
void CBlocking::OnStartBackgndMeasurements(CList<MeasurePointData*, MeasurePointData*> &DataList)
{
	if(!gpTracker)
	return;	

	//With the UI thread in blocking mode both the foreground and background measuremnts 
	//cannot be run at the same time. So that option is ignored here.
	TrkDrvObjectArray* pDataArray = NULL;
	MeasurePointData* pData = NULL;

	try
	{
		//Specifying measurement configuration.
		NullStartTrigger		startTrigger;
		IntervalTrigger			continueTrigger(0.25);
		AverageFilter			filter;
		MeasureCfg	cfg(20, &filter,&startTrigger, &continueTrigger);		

		gpTracker->setBlocking(true);

		//This blocking is just for readBkndmeasurePointData
		gpTracker->setBkndMeasureBlocking(true);

		int nEventRate = gMainWnd->GetEventRate();
		gpTracker->setBkndMeasureEventRate(nEventRate);	

		gpTracker->startBkndMeasurePoint(&cfg);		

		if(nEventRate == 1)
		{			
			pData = gpTracker->readBkndMeasurePointData();
			ASSERT(pData);
			DataList.AddTail(pData);
		}
		else if(nEventRate == 10)
		{
			pDataArray = NULL;
			pDataArray = gpTracker->readBkndMeasurePointData(nEventRate);
			ASSERT(pDataArray);
			int numElements = pDataArray->getNumElements();			
			ASSERT(nEventRate == numElements);
			for(int i = 0; i < numElements; i++)
			{
				pData = (MeasurePointData*)pDataArray->getElement(i);
				ASSERT(pData);
				DataList.AddTail(pData);				
			}
		}		
	}
	catch( TrackerException* e )
	{
		char* msg;
		msg = e->getText();
		AfxMessageBox(msg );
		trackerDeleteString(msg);
		delete e;
	}
	catch( SMXException* e )
	{	
		char msg[50];
		e->getMsg(msg, 50);
		AfxMessageBox(msg);
		delete e;
	}
	try
	{
		gpTracker->stopBkndMeasurePoint();
		gpTracker->setBkndMeasureBlocking(false);
		gpTracker->setBlocking(false);
	}
	catch( TrackerException* e )
	{
		char* msg;
		msg = e->getText();
		AfxMessageBox(msg );
		trackerDeleteString(msg);
		delete e;
	}
}

/*************************************************************************************************
* Function: sixDOFCapable
* Comments: 
*************************************************************************************************/
BOOL CBlocking::sixDofCapable()
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
void CBlocking::ComboSearch1()
{	
	if(!gpTracker)
		return;
		
	try
	{
		gpTracker->setBlocking(true);
		gpTracker->comboSearch();		
	}
	catch( TrackerException* e )
	{
		char* msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}

	gpTracker->setBlocking(false);
}

/*************************************************************************************************
* Function: comboSearch2()
* Comments: 
*************************************************************************************************/
void CBlocking::ComboSearch2(double az, double ze, double dist, double azTol, double zeTol, bool searchIfNeeded)
{	
	if(!gpTracker)
		return;
		
	try
	{
		gpTracker->setBlocking(true);
		gpTracker->comboSearch(az, ze, dist, azTol, zeTol, searchIfNeeded);		
	}
	catch( TrackerException* e )
	{
		char* msg = e->getText();
		AfxMessageBox(msg);
		trackerDeleteString(msg);
		delete e;
	}
	gpTracker->setBlocking(false);
}
