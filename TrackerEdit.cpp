#include "stdafx.h"
#include "TrackerEdit.h"

BEGIN_MESSAGE_MAP(CTrackerEdit, CEdit)
    ON_WM_CHAR()
END_MESSAGE_MAP()

void CTrackerEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch ( nChar )
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':			
		case VK_BACK:	
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
	}    
}
