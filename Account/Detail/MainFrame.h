#pragma once

#include "LeftCtrl.h"
#include "RightView.h"
#include "TabSplitterWnd.h"

// CMainFrame frame

//#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

class CMainFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CMainFrame)

public:
	CMainFrame();           // protected constructor used by dynamic creation
protected:
	
	virtual ~CMainFrame();

public:
	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

protected:
	CLeftCtrl *m_pLeft;
	CRightView *m_pRight;
	CTabSplitterWnd m_wndSplitter;
	CTreeCtrl m_wndTree;
		
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg void OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult);

	void LoadControl();

public:
	/*_ConnectionPtr m_pConnection;
	_RecordsetPtr  m_pRecordset;*/

	afx_msg void OnDestroy();
};


