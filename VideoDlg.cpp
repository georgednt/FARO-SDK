// VideoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "VideoDlg.h"
#include "Globals.h"
//#include <iostream>
#include <fstream>
using namespace std;

// VideoDlg dialog

#define  IDT_TIMER  WM_USER + 200 

IMPLEMENT_DYNAMIC(VideoDlg, CDialog)

VideoDlg::VideoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(VideoDlg::IDD, pParent)
{	
}

VideoDlg::~VideoDlg()
{
}

void VideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);	
}


BEGIN_MESSAGE_MAP(VideoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_START_VIDEO, &VideoDlg::OnBnClickedButtonStartVideo)
	ON_BN_CLICKED(IDC_BUTTON_STOP_VIDEO, &VideoDlg::OnBnClickedButtonStopVideo)	
	ON_WM_PAINT()
	ON_WM_TIMER()	
END_MESSAGE_MAP()


// VideoDlg message handlers

void VideoDlg::OnBnClickedButtonStartVideo()
{
	videoInProgress = false;
	
	//can be done in worker mode also similar to measurements
	if(gRunMode == EVENT_MODE)
	{		
		gListeners.OnStartVideo();
	}

	StartTimer(100);
}

void VideoDlg::OnBnClickedButtonStopVideo()
{
	videoInProgress = true;
	if(gRunMode == EVENT_MODE)
	{		
		gListeners.OnStopVideo();
	}
	StopTimer(IDT_TIMER);
}

void VideoDlg::SetData(int size, byte* data)
{
	if(videoInProgress)
		 return;

	m_VideoVectorSizeList.push_back(size);
	m_VideoVectorList.push_back(data);		
	
	//debug code to verify that we are getting images here
	/*ofstream myfile2;
	myfile2.open ("C:\\example.jpg",std::ios::binary);	
	myfile2.write((char*)data, size);
	myfile2.close();
	*/
}

 UINT  VideoDlg::StartTimer (UINT TimerDuration)
 {
	UINT    TimerVal;
	TimerVal = SetTimer (IDT_TIMER, TimerDuration, NULL);  // Starting the Timer
	if (TimerVal == 0)
	{
	  AfxMessageBox("Unable to obtain timer");
	}
	return TimerVal;
 }// end StartTimer


 BOOL VideoDlg::StopTimer (UINT TimerVal)
 {
      if (!KillTimer (TimerVal))
      {
		return FALSE;
      }
      //    Place clean-up code following this point.
     return TRUE;
   } // end StopTimer



 void VideoDlg::OnTimer(UINT_PTR nIDEvent)
 {
	 Invalidate();

	 CDialog::OnTimer(nIDEvent);
 }

 void VideoDlg::SetCharData(char* data)
 {
	 if(videoInProgress)
		 return;

	 this->GetDlgItem(IDC_EDIT_TARGET_DATA)->SetWindowTextA(data);
 }

 void VideoDlg::OnPaint()
 {
	 CPaintDC dc(this); // device context for painting
	 // TODO: Add your message handler code here
	 // Do not call CStatic::OnPaint() for painting messages
 }
