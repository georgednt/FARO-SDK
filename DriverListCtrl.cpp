// DriverListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerDriverDemo.h"
#include "DriverListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDriverListCtrl

CDriverListCtrl::CDriverListCtrl()
{
}

CDriverListCtrl::~CDriverListCtrl()
{
}


BEGIN_MESSAGE_MAP(CDriverListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CDriverListCtrl)
	ON_WM_PAINT()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDriverListCtrl message handlers
char* TempColumnNames1[] =
{
	"Azimuth(rad)",
	"Zenith(rad)",
	"Distance(m)",
	"Status",	
};

char* TempColumnNames2[] =
{
	"Azimuth(rad)",
	"Zenith(rad)",
	"Distance(m)",	
	"A",
	"B",
	"C",
	"Status",
	"SixDof Data"
};

void CDriverListCtrl::CreateListCtrl(int nRows, int nCols, RECT rect,CWnd* pParentWnd, UINT nID, BOOL sixDofCapable)
{	
	LV_ITEM			lvi;
	LV_COLUMN		lvcolumn;

	DWORD dwStyle = LVS_NOSORTHEADER|LVS_REPORT|WS_CHILD|WS_VISIBLE|WS_BORDER;
	Create(dwStyle,rect,pParentWnd, nID);

	// add the columns to the list control
 	for (int i = 0; i < nCols; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_CENTER;		
		if(sixDofCapable)
		{
			lvcolumn.pszText = TempColumnNames2[i];
			lvcolumn.cchTextMax = strlen(TempColumnNames2[i]);
		}
		else
		{
			lvcolumn.pszText = TempColumnNames1[i];
			lvcolumn.cchTextMax = strlen(TempColumnNames1[i]);
		}
		lvcolumn.cx = 100;	
		lvcolumn.iSubItem = i;		
		InsertColumn(i, &lvcolumn);  // assumes return value is OK.
	}
	
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			lvi.iItem = i;

			// Set subitem 0
			lvi.mask = LVIF_TEXT;
			lvi.iSubItem = j;		
			lvi.pszText = "";
			InsertItem(&lvi);
		}
	}
}

void CDriverListCtrl::InsertMeasurement(double az, double ze, double d, LPTSTR status)
{
	LV_ITEM	lvi;
	char  buffer[50];
	
	//adding always to the top
	lvi.iItem = 0;

	// Set subitem 0
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 0;
	sprintf_s( buffer, "%f", az );
	lvi.pszText = buffer;
	InsertItem(&lvi);

	// Set subitem 1
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 1;
	sprintf_s( buffer, "%f", ze );
	lvi.pszText = buffer;
	SetItem(&lvi);

	// Set subitem 2
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 2;
	sprintf_s( buffer, "%f", d );
	lvi.pszText = buffer;
	SetItem(&lvi);

	// Set subitem 3
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 3;	
	lvi.pszText = status;
	SetItem(&lvi);	
}

void CDriverListCtrl::InsertMeasurement(double az, double ze, double d, double A, double B, double C, LPTSTR status, bool sixDofData)
{
	LV_ITEM	lvi;
	char  buffer[50];
	
	//adding always to the top
	lvi.iItem = 0;

	// Set subitem 0
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 0;
	sprintf_s( buffer, "%f", az );
	lvi.pszText = buffer;
	InsertItem(&lvi);

	// Set subitem 1
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 1;
	sprintf_s( buffer, "%f", ze );
	lvi.pszText = buffer;
	SetItem(&lvi);

	// Set subitem 2
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 2;
	sprintf_s( buffer, "%f", d );
	lvi.pszText = buffer;
	SetItem(&lvi);

	// Set subitem 3
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 3;	
	sprintf_s( buffer, "%f", A );
	lvi.pszText = buffer;
	SetItem(&lvi);

	// Set subitem 4
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 4;
	sprintf_s( buffer, "%f", B );
	lvi.pszText = buffer;	
	SetItem(&lvi);

	// Set subitem 5
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 5;
	sprintf_s( buffer, "%f", C);
	lvi.pszText = buffer;
	SetItem(&lvi);

	// Set subitem 6
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 6;	
	lvi.pszText = status;
	SetItem(&lvi);
	
	// Set subitem 7
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 7;
	if(sixDofData)
		lvi.pszText = "yes";
	else
		lvi.pszText = "no";
	SetItem(&lvi);
}

void CDriverListCtrl::OnPaint() 
{
	const MSG *msg = GetCurrentMessage();
	DefWindowProc(msg->message,msg->wParam,msg->lParam);

	if ((GetStyle() & LVS_TYPEMASK) == LVS_REPORT)
	{
		// Get the number of columns		
		CClientDC dc(this );
		CPen graypen(PS_SOLID,0,RGB(200,200,200));
		//CPen graypen(PS_SOLID,0,RGB(255,255,255));
		CPen *oldpen = dc.SelectObject(&graypen);

		CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
		int nColumnCount = pHeader->GetItemCount();
		
		// The bottom of the header corresponds to the top of the line		
		RECT rect;
		pHeader->GetClientRect( &rect ); 	
		int top = rect.bottom;
		int	headerheight = rect.bottom - rect.top;
		// Now get the client rect so we know the line length and		
		// when to stop

		GetClientRect( &rect );

		// adjust rect.bottom to avoid drawing column for empty rows:
		int firstrow  = GetTopIndex();
		int	perpage   = GetCountPerPage();
		int realrows  = min(perpage,GetItemCount()-firstrow);
		int	rowheight = (rect.bottom - rect.top - headerheight) / perpage;

		// adjustment for incomplete rows:
		if (realrows * rowheight < rect.bottom - rect.top - headerheight &&
			GetItemCount() > GetTopIndex() + realrows) {
			//rect.bottom	= realrows * rowheight + headerheight;
			;
		}
		else {
			rect.bottom   = realrows * rowheight + headerheight;
		}

		// The border of the column is offset by the horz scroll		
			int borderx = 0 - GetScrollPos( SB_HORZ );
			for( int i = 0; i < nColumnCount; i++ )	{
				// Get the next border
				borderx += GetColumnWidth( i );
				// if next border is outside client area, break out
				if( borderx >= rect.right ) 
					break;			
				// Draw the line.
				dc.MoveTo( borderx-1, top);			
				dc.LineTo( borderx-1, rect.bottom );
			}		

		// Draw the horizontal grid lines		
		// First get the height
		if( !GetItemRect( 0, &rect, LVIR_BOUNDS ))			
			return;
		int height = rect.bottom - rect.top;		
		GetClientRect( &rect );

		int width = rect.right; 	
		for( int i = 1; i <= realrows; i++ ) {
			dc.MoveTo( 0, top + height*i);
			dc.LineTo( width, top + height*i );
		}

		dc.SelectObject(oldpen);
	}	
	
	
	// Do not call CListCtrl::OnPaint() for painting messages
}

BOOL CDriverListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	switch (((NMHDR*)lParam)->code)
		{
				case HDN_BEGINTRACKW:
				case HDN_BEGINTRACKA:
						*pResult = TRUE;                // disable tracking
						return TRUE;                    // Processed message
		}

        
	return CListCtrl::OnNotify(wParam, lParam, pResult);
}

void CDriverListCtrl::OnCustomdraw(NMHDR * pNMHDR, LRESULT * pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	// Take the default processing unless we set this to something else below.
	*pResult = 0;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the prepaint stage for an item. Here's where we set the
		// item's text color. Our return value will tell Windows to draw the
		// item itself, but it will use the new color we set here.
		// We'll cycle the colors through gray and white.		
			COLORREF crBkgnd;
			if ( (pLVCD->nmcd.dwItemSpec % 2) == 0 )
 				crBkgnd= RGB(255,255,255);
			else if ( (pLVCD->nmcd.dwItemSpec % 2) == 1 )
				crBkgnd= RGB(223,223,223);
			// Store the color back in the NMLVCUSTOMDRAW struct.        
			pLVCD->clrTextBk = crBkgnd;		

		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}
	return;
}
