#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "Tracker.h"
#include "WorkerThread.h"
#include "Blocking.h"
#include "Listeners.h"
#include "Mainfrm.h"

extern Tracker* gpTracker;
extern CBlocking gBlocking;
extern CWorkerThread gWorkerThread;
extern CListeners gListeners;
extern CMainFrame* gMainWnd;

enum RUNMODE
{
	WORKER_MODE,
	UI_MODE,
	EVENT_MODE
};

extern RUNMODE gRunMode;

enum TRACKER_TYPE
{
	TRACKER_4XXX,
	TRACKER_FARO,
	TRACKER_VANTAGE
};

extern boolean useSimulator;

#endif // _GLOBALS_H
