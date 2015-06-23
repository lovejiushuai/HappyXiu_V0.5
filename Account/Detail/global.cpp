#include "stdafx.h"
#include "global.h"
#include "DetailDll.h"
#include "Detail.h"
#include "MainFrame.h"

CWnd * __stdcall afxGetMainWnd(void)
{
	return theApp.m_pMainWnd;
}

CWinApp * __stdcall afxGetApp(void)
{
	return &theApp;
}


// DLL CONTRUCT
int WINAPI StartDll(HWND AppHwnd,HINSTANCE &m_hAccount,CWinApp **ppDllApp)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*ppDllApp = afxGetApp();

	//_tcscpy(theApp.m_lpCmdLine,cmdLine);


	theApp.AppHwnd = AppHwnd;

	theApp.m_hAccount = m_hAccount;

	CMainFrame* pFrame = new CMainFrame;
	theApp.m_pMainWnd = pFrame;



	// create and load the frame with its resources

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);

	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	// Use message loop for DLL
	MSG msg;

	while(GetMessage(&msg,NULL,0,0))
	{

		theApp.PreTranslateMessage(&msg);
		TranslateMessage(&msg);
		DispatchMessage(&msg);


		//       if(pFrame->FromHandlePermanent(pFrame->GetSafeHwnd()) == NULL)
		if(theApp.m_bExit || ::IsWindow(pFrame->GetSafeHwnd()) == false)
		{

			//   TranslateMessage(&msg);
			//   DispatchMessage(&msg);
			return 1;
		}
	}

	return 1;
}

void getAppCurDir(TCHAR *curDir)
{
	TCHAR szPath[MAX_PATH];
	//TCHAR Path[MAX_PATH];
	TCHAR *s;

	ZeroMemory(szPath,MAX_PATH); 
	GetModuleFileName(NULL, szPath, MAX_PATH);
	//wsprintf(Path,_T("%s"),szPath);

	s = wcsrchr(szPath,'\\');
	if (s) 
		s[1]=0;
	//wsprintf(Path,_T("%s%s"),szPath,_T("log.txt"));

	wsprintf(curDir,_T("%s"),szPath);
}

int LogtoFile(const TCHAR *pszFormat, ...)
{
	return 0;

	FILE *	fileHdl;
	BOOL	ret = TRUE;
	TCHAR tempBuffer[1024];
	TCHAR logFileName[1024];
	CTime t =CTime::GetCurrentTime();
	_stprintf(tempBuffer,_T("%02d-%02d %02d:%02d:%02d "),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());

	TCHAR Path[MAX_PATH];
	TCHAR *s;
	GetModuleFileName(NULL,Path,MAX_PATH);
	s = wcsrchr(Path,'\\');
	if (s) 
		s[1]=0;
	wsprintf(logFileName,_T("%s%s"),Path,_T("log.txt"));


	va_list vaArguments;
	va_start(vaArguments, pszFormat);
	vswprintf(&(tempBuffer[_tcslen(tempBuffer)]), pszFormat, vaArguments);
	va_end(vaArguments);
	_tcscat(tempBuffer, _T("\r\n"));



	fileHdl = _tfopen(logFileName,_T("a+"));
	if(fileHdl != NULL)
	{
		fseek(fileHdl,0,SEEK_END);
		_fputts(tempBuffer,fileHdl);
		fclose(fileHdl);
	}
	return ret;
}