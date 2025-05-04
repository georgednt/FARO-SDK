#pragma once


// CComboSearchDlg dialog

class CComboSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CComboSearchDlg)

public:
	CComboSearchDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CComboSearchDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_COMBO_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCsearch1();
	afx_msg void OnBnClickedButtonCsearch2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDemonstrationsCombosearch();
};
