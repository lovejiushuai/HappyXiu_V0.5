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
	void AddToGrid();

	
	afx_msg void OnModuleNum();
	afx_msg void OnSlotNum();
	afx_msg void OnBoardName();
	afx_msg void OnPortNum();
	afx_msg void OnTimeSlot();
	afx_msg void OnDeviceNum();
	afx_msg void OnPortType();	
	afx_msg void OnInfo();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);

	/*CListCtrl m_Grid;*/
	CListCtrl m_list;
	CString dataID;
	CString boardName;
	CString deviceNum;
	CString info;
	CString moduleNum;
	CString portNum;
	CString portType;
	CString slotNum;
	CString timeSlot;

	CEdit m_boardName;
	CEdit m_devNum;
	CEdit m_info;
	CEdit m_modNum;
	CEdit m_portNum;
	CEdit m_portType;
	CEdit m_slotNum;
	CEdit m_timeSlot;

	CButton m_addButton;
	CButton m_deleteButton;
	CButton m_modifyButton;
	CButton m_clearButton;

	virtual void OnCancel();

protected:
	void LoadControl();
};
