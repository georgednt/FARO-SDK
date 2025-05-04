// ConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "Globals.h"
#include "ConnectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg dialog


CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectDlg)	
	//}}AFX_DATA_INIT
}


void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectDlg)	
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT_SERIAL_NUMBER, m_SerialNumber);
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectDlg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CConnectDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg message handlers

void CConnectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString srNum;
	m_SerialNumber.GetWindowTextA(srNum);	

	//Calling UpdateData so tha the member variable m_TrackerType has the current state of the radio button selection.
	UpdateData(TRUE);

		
	if(srNum.IsEmpty())
	{
		AfxMessageBox("Please specify the serial number.", MB_ICONSTOP);
		return;
	}

	if (srNum.CompareNoCase("Simulator") == 0)
	{
		useSimulator = true;
	}
	else
	{
		CString errMsg = "If specifying ip address, format is xxx.xxx.xxx.xxx and each xxx must be within [0-255].";

		if (srNum.Find('.') >= 0)
		{
			if (isValidIpAddress(srNum) == false)
			{
				AfxMessageBox(errMsg, MB_ICONSTOP);
				return;
			}
		}		
		m_srNum = srNum;
	}
	
	OnOK();
}

BOOL CConnectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CConnectDlg::isValidIpAddress(CString ipaddr)
{	
	int num, i, len;
    char *ch;
	char* context = NULL;

	char sz[100];
	sprintf_s(sz, "%s", ipaddr.GetString());
	
	LPTSTR p = ipaddr.GetBuffer();

	//When you call ReleaseBuffer, the actual length of the string is recomputed and stored in the CString. 
	//Within the scope of a GetBuffer/ReleaseBuffer sequene, You Must Not, Ever, Use Any Method Of CString 
	//on the CString whose buffer you have!The reason for this is that the integrity of the CString object 
	//is not guaranteed until the ReleaseBuffer is called.
	ipaddr.ReleaseBuffer();

	len = ipaddr.GetLength();	
	//  Check if the string is valid
    if(len < 7 || len > 15)
	{
        return false;
	}

    //counting number of quads present in a given IP address
    int quadsCnt = 0;

	ch = strtok_s(p, ".", &context);

    while (ch != NULL) 
    {
        quadsCnt++;        

        num = 0;
        i = 0;

        //  Get the current token and convert to an integer value
		int num = atoi(ch);

        if(num < 0 || num > 255)
        {            
            return false;
        }

        if( (quadsCnt == 1 && num == 0) || (quadsCnt == 4 && num == 0))
        {            
            return false;
        }

        ch = strtok_s(NULL, ".", &context);
    }

    //  Check the address string, should be n.n.n.n format
    if(quadsCnt!= 4)
    {
        return false;
    }

    //  Looks like a valid IP address
    return true;
}
CString CConnectDlg::getSerialNumber()
{
	return m_srNum;
}
