#pragma once

// CLoginDialog dialog

class CLoginDialog : public CDialog
{
	DECLARE_DYNAMIC(CLoginDialog)

public:
	CLoginDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginDialog();

// Dialog Data
	enum { IDD = IDD_LOGINDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CStatic	m_alertM;
	CString	m_passWord;
	CString	m_userName;
	int m_userID;
	bool m_bIsUser;

	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedNomal();
};
