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

	CStatic	m_ctrlCue;
	CString	m_password;
	CString	m_username;
	afx_msg void OnBnClickedOk();
};
