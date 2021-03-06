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

//启动 dll入口
// DLL CONTRUCT
int WINAPI StartDll(HWND AppHwnd,HINSTANCE &m_hAccount,CWinApp **ppDllApp)
{
	// 获取当前 App    和 句柄 
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*ppDllApp = afxGetApp();

	//_tcscpy(theApp.m_lpCmdLine,cmdLine);


	theApp.AppHwnd = AppHwnd;

	theApp.m_hAccount = m_hAccount;

	// 创建 框架 并 保存
	CMainFrame* pFrame = new CMainFrame;
	theApp.m_pMainWnd = pFrame;


	// 加载 框架  设置显示
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

		//屏蔽掉以后  不再出现  CEdit 框内按下一个字符出现四个字符现象  20150625
		/*theApp.PreTranslateMessage(&msg);*/


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

//设置 管理模式 函数
int WINAPI SetAdmin(int userID)
{
	int tempAdmin;
	tempAdmin = userID;
	if(tempAdmin)
	{
		theApp.m_bIsAdmin = true;
		theApp.m_userID = tempAdmin;
	}
	else
	{
		theApp.m_bIsAdmin = false;
		theApp.m_userID = 0;
	}
	return 1;
}

// 获取当前路径
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

// 打印 日志 函数  用来调试  现在未使用未开放
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