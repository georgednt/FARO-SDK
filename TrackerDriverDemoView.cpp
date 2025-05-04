// TrackerDriverDemoView.cpp : implementation of the CTrackerDriverDemoView class
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"

#include "TrackerDriverDemoDoc.h"
#include "TrackerDriverDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrackerDriverDemoView

IMPLEMENT_DYNCREATE(CTrackerDriverDemoView, CView)

BEGIN_MESSAGE_MAP(CTrackerDriverDemoView, CView)
	//{{AFX_MSG_MAP(CTrackerDriverDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrackerDriverDemoView construction/destruction

CTrackerDriverDemoView::CTrackerDriverDemoView()
{
	// TODO: add construction code here

}

CTrackerDriverDemoView::~CTrackerDriverDemoView()
{
}

BOOL CTrackerDriverDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTrackerDriverDemoView drawing

void CTrackerDriverDemoView::OnDraw(CDC* pDC)
{
	CTrackerDriverDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTrackerDriverDemoView diagnostics

#ifdef _DEBUG
void CTrackerDriverDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CTrackerDriverDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTrackerDriverDemoDoc* CTrackerDriverDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTrackerDriverDemoDoc)));
	return (CTrackerDriverDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTrackerDriverDemoView message handlers
