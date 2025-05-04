//WorkerThread.h
#ifndef _WORKERTHREAD_H
#define _WORKERTHREAD_H

#include <afxtempl.h>
#include "Constants.h"

struct BACKGNDINFO
{	
	BOOL bMulti;
	CWnd* pMainWnd;
	BOOL bStopBkgnd;
	int nEventRate;
};

class CWorkerThread
{
public:		
	void CreateThread();
	static UINT StartThread(LPVOID pParam);
	void RunThread();

	void OnConnect();
	void OnDisconnect();

	void ExecuteCommandSequence();

	void StartSearch();

	void Abort();

	void OnAvailableApplications(CList<char*, char*> &lstApps);
	void OnRunApplication(char* appName);
	void OnStopApplication();	
	
	void OnStartMeasurements();
	void OnStopMeasurements();
	void OnStartForegndMeasurements();
	void OnStopForegndMeasurements();
	void OnStartBackgndMeasurements();	
	void OnStopBackgndMeasurements();
	
	BOOL sixDofCapable();

	void ComboSearch1();
	void ComboSearch2(double, double, double, double, double, bool);

private:
	void PostMsgToUpdateStatus(char* txt);

	CWinThread* m_pWorkerThread;
	CWinThread* m_pBkgndThread;
	TRACKERCOMMANDS tCommand;
	HANDLE m_hSuspendResumeEvent;
	HANDLE m_hCommandDoneEvent;
	CWnd* m_pMyMainWnd;
	char* m_pIpAdd;
	CList<char*, char*>m_Appslist;
	char* m_AppName;
	BOOL bMulti;	
	BOOL bStopBkgnd;
	int nEventRate;
	BACKGNDINFO backGndInfo;
	BOOL m_bSixDofCapable;
	BOOL m_bCommandEventSet;

	double csAz;
	double csZe;
	double csDist;
	double csAzTol;
	double csZeTol;
	bool csSearchIfNeeded;
};
#endif
