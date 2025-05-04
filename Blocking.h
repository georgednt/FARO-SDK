//Blocking.h
#ifndef _BLOCKING_H
#define _BLOCKING_H

#include <afxtempl.h>
class CommandDone;

class CBlocking
{
public:
	void Connect();
	void Disconnect();
	
	void ExecuteCommandSequence();
	void SetCommandDone(CommandDone* pDone);

	void StartSearch();

	void AbortCommand();

	void OnAvailableApplications(CList<char*, char*> &lstApps);
	void OnStopApplication();
	void OnRunApplication(char* appName);

	void OnStartMeasurements(CList<MeasurePointData*, MeasurePointData*> &DataList);
	void OnStartForegndMeasurements(CList<MeasurePointData*, MeasurePointData*> &DataList);
	void OnStartBackgndMeasurements(CList<MeasurePointData*, MeasurePointData*> &DataList);

	void ComboSearch1();
	void ComboSearch2(double, double, double, double, double, bool);

	BOOL sixDofCapable();

private:
	CommandDone* m_pCmdDone;
	BOOL m_bSixDofCapable;
};

#endif
