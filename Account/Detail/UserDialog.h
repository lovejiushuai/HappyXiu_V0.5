#pragma once

// CUserDialog dialog

class CUserDialog : public CDialog
{
	DECLARE_DYNAMIC(CUserDialog)

public:
	CUserDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserDialog();

// Dialog Data
	enum { IDD = IDD_USERDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CStatic	m_alertM;
	CString	m_passWord;
	CString	m_passWordConfirm;
	CString	m_userName;
	int m_userID;
	CRect m_rcPanel;
	CFont m_Font;

	CEdit m_editPW;
	CEdit m_editPWConfirm;
	CButton m_buttonSubmit;
	CButton m_buttonCancel;

	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	BOOL LoadControl();	
};
