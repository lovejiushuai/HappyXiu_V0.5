
// AccountDlg.h : header file
//

#pragma once


// DLL CONTRUCT
//typedef int (WINAPI* LaunchDllEntryFuncAPI)(HWND,HINSTANCE &,CWinApp** ,CString);
// Don't pass CString, It's ok for CString &
typedef int (WINAPI* LaunchDllFuncAPI)(HWND,HINSTANCE &,CWinApp**);
typedef int (WINAPI* SetAdminFuncAPI)(int);

// CAccountDlg dialog
class CAccountDlg : public CDialogEx
{
// Construction
public:
	CAccountDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ACCOUNT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void LoadControl();	

	int m_buttonCount;
	CRect m_rcPanel;

	CButton m_hMainButton;
	CButton m_hLanZhouXiButton;
	CButton m_hLanXiDButton;
	CButton m_hChenButton;
	CButton m_hMinButton;
	CButton m_hSpareButton;
	int widthRect,heightRectL,heightRectS,topRect;
	int lineY_1,lineY_2;

	LaunchDllFuncAPI LaunchDllFunc;
	SetAdminFuncAPI SetAdminFunc;
	LRESULT ExitDLLMessage(WPARAM wParam,LPARAM lParam);


public:
	afx_msg void OnButtonClickedLZX();
	afx_msg void OnButtonClickedLXD();
	afx_msg void OnButtonClickedC();
	afx_msg void OnButtonClickedM();
	afx_msg void OnButtonClickedMain();
	afx_msg void OnButtonClickedSpare();
	afx_msg LRESULT  LaunchDll(WPARAM wParam, LPARAM lParam);
	CWinApp  *pDllEntryWinApp;

};
