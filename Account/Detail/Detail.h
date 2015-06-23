// Detail.h : main header file for the Detail DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDetailApp
// See Detail.cpp for the implementation of this class
//

class CDetailApp : public CWinApp
{
public:
	CDetailApp();
	HWND    AppHwnd;
	HINSTANCE m_hAccount;
	bool m_bExit;
	TCHAR m_strCurDir[MAX_PATH];
	TCHAR m_exeFullPath[MAX_PATH];
	CString m_status;
// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CDetailApp theApp;