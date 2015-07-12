#pragma once

#include "stdafx.h"

// CInfoDialog dialog

class CInfoDialog : public CDialog
{
	DECLARE_DYNAMIC(CInfoDialog)

public:
	CInfoDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInfoDialog();

// Dialog Data
	enum { IDD = IDD_INFODIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	/*_ConnectionPtr m_pConnection;
	_RecordsetPtr  m_pRecordset;*/

	virtual BOOL OnInitDialog();
	void OnInitADOConn();
	void ExitConnect();
	void AddToList();
	
	afx_msg void OnModuleNum();
	afx_msg void OnSlotNum();
	afx_msg void OnBoardName();
	afx_msg void OnPortNum();
	afx_msg void OnTimeSlot();
	afx_msg void OnDeviceNum();
	afx_msg void OnPortType();	
	afx_msg void OnInfo();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddData();
	afx_msg void OnModifyData();
	afx_msg void OnDeleteData();
	afx_msg void OnClearData();
	afx_msg LRESULT UpdataList(WPARAM wParam,LPARAM lParam);
	afx_msg void onSetDatabase(CString listName, CString modN, int mod, int bMod);

	void getEditText();
	void DisplayInfo();

	int idataID;
	int imoduleNum;
	int islotNum;

	/*CListCtrl m_Grid;*/
	CListCtrl m_list;
	CString dataID;	
	CString moduleNum;
	CString slotNum;
	CString boardName;
	CString portNum;
	CString timeSlot;
	CString deviceNum;
	CString portType;
	CString info;

	CString m_listName;
	CString m_inquerySQL;
	int m_containValue;
		
	CStatic dataIDText;
	CStatic moduleNumText;
	CStatic slotNumText;
	CStatic boardNameText;
	CStatic portNumText;
	CStatic timeSlotText;
	CStatic deviceNumText;
	CStatic portTypeText;
	CStatic infoText;

	/*
	CEdit m_modNum;
	CEdit m_slotNum;
	*/
	CComboBox m_cbModNum;
	CComboBox m_cbSlotNum;
	CEdit m_boardName;
	CEdit m_portNum;
	CEdit m_timeSlot;
	CEdit m_devNum;
	CEdit m_portType;
	CEdit m_info;	
	

	CButton m_addButton;
	CButton m_deleteButton;
	CButton m_modifyButton;
	CButton m_clearButton;

	virtual void OnCancel();

protected:
	void LoadControl();

};
