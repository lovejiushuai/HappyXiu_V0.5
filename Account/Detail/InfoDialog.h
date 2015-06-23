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
	/*CListCtrl m_Grid;*/
	CListCtrl m_list;
	CString dataID, boardName, deviceNum, info, moduleNum, portNum, portType, slotNum, timeSlot;
	CEdit m_boardName;
	CEdit m_devNum;
	CEdit m_info;
	CEdit m_modNum;
	CEdit m_portNum;
	CEdit m_portType;
	CEdit m_slotNum;
	CEdit m_timeSlot;
	virtual void OnCancel();
};
