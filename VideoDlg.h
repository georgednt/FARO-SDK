#include <vector>

#pragma once


// VideoDlg dialog

class VideoDlg : public CDialog
{
	DECLARE_DYNAMIC(VideoDlg)

public:
	VideoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~VideoDlg();
	void SetData(int size, byte* data);
	void SetCharData(char* data);	
	std::vector<byte*> m_VideoVectorList;
	std::vector<int> m_VideoVectorSizeList;	
	bool videoInProgress;

// Dialog Data
	enum { IDD = IDD_DIALOG_VIDEO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStartVideo();
	afx_msg void OnBnClickedButtonStopVideo();	
	void CreateBitmapFromBytes(byte pixelValues[], int width, int height);	
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg UINT  StartTimer (UINT TimerDuration);  // Start the Timer 
	afx_msg BOOL StopTimer (UINT TimerVal);           // Stop the Timer 
};
