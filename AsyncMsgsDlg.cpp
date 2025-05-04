// AsyncMsgsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "Globals.h"
#include "Constants.h"
#include "AsyncMsgsDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAsyncMsgsDlg dialog


CAsyncMsgsDlg::CAsyncMsgsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAsyncMsgsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAsyncMsgsDlg)
	//}}AFX_DATA_INIT
}


void CAsyncMsgsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAsyncMsgsDlg)
	DDX_Control(pDX, IDC_BUTTON_SIGHT, m_bSight);
	DDX_Control(pDX, IDC_BUTTON_MOTORS, m_bMotors);
	DDX_Control(pDX, IDC_BUTTON_DISTANCE, m_bDistance);
	DDX_Control(pDX, IDC_RADIO_SMM, m_rSMM);
	DDX_Control(pDX, IDC_RADIO_0_875, m_SMR0_875);
	DDX_Control(pDX, IDC_RADIO_1_5, m_rSMR1_5);
	DDX_Control(pDX, IDC_RADIO_0_5, m_rSMR0_5);
	DDX_Control(pDX, IDC_RADIO_SIXDOF, m_rSixDof);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAsyncMsgsDlg, CDialog)
	//{{AFX_MSG_MAP(CAsyncMsgsDlg)
	ON_BN_CLICKED(IDC_BUTTON_DISTANCE, OnButtonDistance)
	ON_BN_CLICKED(IDC_BUTTON_MOTORS, OnButtonMotors)
	ON_BN_CLICKED(IDC_BUTTON_SIGHT, OnButtonSight)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO_0_5, OnRadio05)
	ON_BN_CLICKED(IDC_RADIO_0_875, OnRadio0875)
	ON_BN_CLICKED(IDC_RADIO_1_5, OnRadio15)
	ON_BN_CLICKED(IDC_RADIO_SMM, OnRadioSmm)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	ON_BN_CLICKED(IDC_RADIO_SIXDOF, &CAsyncMsgsDlg::OnBnClickedRadioSixDof)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAsyncMsgsDlg message handlers
BOOL CAsyncMsgsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	m_rSixDof.ShowWindow(gMainWnd->sixDofCapable());

	const int nParts = 4;
	CRect rect;
	
	m_StatusBarCtrl.CreateStatusBar(this);

	m_StatusBarCtrl.GetClientRect(&rect);
	int pWidths[nParts] = { rect.right-275, rect.right-195, rect.right-75, -1 };	
	m_StatusBarCtrl.SetPartsOnStatusBar(nParts, pWidths);

	gListeners.StartAsyncMsgs();
	OnSetAsyncMsgStatus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAsyncMsgsDlg::OnButtonDistance() 
{
	gListeners.ExecuteAsyncCommand(DISTANCE_VALID, !m_bDistanceValid);	
}

void CAsyncMsgsDlg::OnButtonMotors() 
{
	gListeners.ExecuteAsyncCommand(TURN_MOTORS_ON, !m_bMotorState);	
}

void CAsyncMsgsDlg::OnButtonSight() 
{
	gListeners.ExecuteAsyncCommand(SIGHT_MODE, !m_bSightMode);	
}

void CAsyncMsgsDlg::OnSetAsyncMsgStatus()
{
	bool state = false;
	gListeners.GetAsyncCommandStatus(MOTORS_ON, m_bMotorState);
	if(m_bMotorState)
	{
		m_StatusBarCtrl.UpdateStatus("ON", 0, 0);
		m_bMotors.SetWindowText("Turn Motors Off");
	}
	else
	{
		m_StatusBarCtrl.UpdateStatus("OFF", 0, 0);
		m_bMotors.SetWindowText("Turn Motors On");
	}
	
	state = false;
	gListeners.GetAsyncCommandStatus(DISTANCE_VALID, m_bDistanceValid);
	if(m_bDistanceValid)
	{
		m_bDistance.SetWindowText("Set Distance InValid");
		m_StatusBarCtrl.UpdateStatus("VALID", 1, 0);
	}
	else
	{
		m_bDistance.SetWindowText("Set Distance Valid");
		m_StatusBarCtrl.UpdateStatus("INVALID", 1, 0);
	}

	state = false;
	gListeners.GetAsyncCommandStatus(SIGHT_MODE, m_bSightMode);
	if(m_bSightMode)
	{
		m_StatusBarCtrl.UpdateStatus("BACK", 3, 0);
	}
	else
	{
		m_StatusBarCtrl.UpdateStatus("FRONT", 3, 0);
	}

	char* type = gListeners.OnGetTargetAsyncStatus();	
	m_StatusBarCtrl.UpdateStatus(type, 2, 0);
	SetTargetCheck(type);
}

void CAsyncMsgsDlg::SetTargetCheck(char* type)
{
	if(strcmp(type, "SMR 1.500 in") == 0)
	{
		m_rSMR1_5.SetCheck(1);
		m_rSMR0_5.SetCheck(0);
		m_SMR0_875.SetCheck(0);
		m_rSMM.SetCheck(0);
	}
	if(strcmp(type,"SMR 0.500 in") == 0)
	{
		m_rSMR1_5.SetCheck(0);
		m_rSMR0_5.SetCheck(1);
		m_SMR0_875.SetCheck(0);
		m_rSMM.SetCheck(0);		
	}
	if(strcmp(type, "SMR 0.875 in") == 0)
	{
		m_rSMR1_5.SetCheck(0);
		m_rSMR0_5.SetCheck(0);
		m_SMR0_875.SetCheck(1);
		m_rSMM.SetCheck(0);
	}
	if(strcmp(type, "SMM") == 0)
	{
		m_rSMR1_5.SetCheck(0);
		m_rSMR0_5.SetCheck(0);
		m_SMR0_875.SetCheck(0);
		m_rSMM.SetCheck(1);
	}
}

void CAsyncMsgsDlg::SetStatusChange(Status* status)
{
	int code = status->getCode();
	//if motors are OFF it returns true else false
	if(code == Status::MOTORS_OFF)
	{
		m_bMotorState = status->getState();

		m_bMotorState = !m_bMotorState;
		if(m_bMotorState)
		{
			m_StatusBarCtrl.UpdateStatus("ON", 0, 0);
			m_bMotors.SetWindowText("Turn Motors Off");
		}
		else
		{
			m_StatusBarCtrl.UpdateStatus("OFF", 0, 0);
			m_bMotors.SetWindowText("Turn Motors On");
		}
	}
	//if distance reset is required it returns true else false
	else if(code == Status::NEED_DISTANCE_RESET)
	{
		m_bDistanceValid = status->getState();
		m_bDistanceValid = !m_bDistanceValid;
		if(m_bDistanceValid)
		{
			m_bDistance.SetWindowText("Set Distance Invalid");
			m_StatusBarCtrl.UpdateStatus("VALID", 1, 0);
		}
		else
		{
			m_bDistance.SetWindowText("Set Distance Valid");
			m_StatusBarCtrl.UpdateStatus("INVALID", 1, 0);
		}
	}	
}

void CAsyncMsgsDlg::SetChangeOccured(Change* change)
{
	int changeCode = change->getCode();	
	if(changeCode == Change::SIGHT_ORIENTATION )
	{		
		m_bSightMode = ((Boolean*)change->getRelatedData())->booleanValue();
		//if m_bSightMode is true then tracker is in backsight else in frontsight.
		if(m_bSightMode)
		{
			m_StatusBarCtrl.UpdateStatus("BACK", 3, 0);
		}
		else
		{
			m_StatusBarCtrl.UpdateStatus("FRONT", 3, 0);
		}
	}
	else if(changeCode == Change::TARGET_TYPE  )
	{		
		TargetType* target= ((TargetType*)change->getRelatedData());
		if(target)
		{	
			SMRTargetType* SMRTarget = dynamic_cast<SMRTargetType*>(target);
			if(SMRTarget)
			{
				double diameter = SMRTarget->getDiameter();
				for (int i = 0; i < sizeof(targets)/sizeof(TARGET_INFO); i++)
				{
					if (targets[i].diameter == diameter)
					{
						char* type = (char*)targets[i].keyword;
						m_StatusBarCtrl.UpdateStatus(type, 2, 0);
						break;
					}
				}
				delete SMRTarget;
			}
			else
			{
				MirrorTargetType* mirrorTarget = dynamic_cast<MirrorTargetType*>(target);				
				m_StatusBarCtrl.UpdateStatus("SMM", 2, 0);
			}			
		}		
	}
}

void CAsyncMsgsDlg::TrackerCommandDone(void* pResult)
{
	char* text = (char*)pResult;
	m_StatusBarCtrl.UpdateStatus(text);
}

void CAsyncMsgsDlg::OnClose() 
{
	gListeners.StopAsyncMsgs();	
	CDialog::OnClose();
}

LRESULT CAsyncMsgsDlg::OnKickIdle(WPARAM, LPARAM)
{	
	if(gMainWnd->GetCommandBusy())
	{
		m_bMotors.EnableWindow(FALSE);
		m_bDistance.EnableWindow(FALSE);
		m_bSight.EnableWindow(FALSE);
		EnableTargetButtons(FALSE);
	}
	else
	{
		m_bMotors.EnableWindow(TRUE);
		m_bDistance.EnableWindow(TRUE);
		m_bSight.EnableWindow(TRUE);
		EnableTargetButtons(TRUE);
	}
	return TRUE;
}

void CAsyncMsgsDlg::OnRadio05() 
{	
	gListeners.ChangeTarget(targets[0].keyword);
}

void CAsyncMsgsDlg::OnRadio0875() 
{
	gListeners.ChangeTarget(targets[1].keyword);
}

void CAsyncMsgsDlg::OnRadio15() 
{
	gListeners.ChangeTarget(targets[2].keyword);
}

void CAsyncMsgsDlg::OnRadioSmm() 
{
	gListeners.ChangeTarget("SMM");	
}

void CAsyncMsgsDlg::EnableTargetButtons(BOOL bEnable)
{
	m_rSMR0_5.EnableWindow(bEnable);
	m_SMR0_875.EnableWindow(bEnable);
	m_rSMR1_5.EnableWindow(bEnable);
	m_rSMM.EnableWindow(bEnable);
	m_rSixDof.EnableWindow(bEnable);
}

void CAsyncMsgsDlg::OnBnClickedRadioSixDof()
{
	gListeners.ChangeTarget("SixDof");	
}
