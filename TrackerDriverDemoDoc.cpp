// TrackerDriverDemoDoc.cpp : implementation of the CTrackerDriverDemoDoc class
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"

#include "TrackerDriverDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrackerDriverDemoDoc

IMPLEMENT_DYNCREATE(CTrackerDriverDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CTrackerDriverDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CTrackerDriverDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrackerDriverDemoDoc construction/destruction

CTrackerDriverDemoDoc::CTrackerDriverDemoDoc()
{
	// TODO: add one-time construction code here

}

CTrackerDriverDemoDoc::~CTrackerDriverDemoDoc()
{
}

BOOL CTrackerDriverDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTrackerDriverDemoDoc serialization

void CTrackerDriverDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTrackerDriverDemoDoc diagnostics

#ifdef _DEBUG
void CTrackerDriverDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTrackerDriverDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTrackerDriverDemoDoc commands
