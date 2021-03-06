
// Account.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Account.h"
#include "AccountDlg.h"
#include "Global.h"
#include "LoginDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAccountApp

BEGIN_MESSAGE_MAP(CAccountApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAccountApp construction

// 程序主线程  初始化参数
CAccountApp::CAccountApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_hApptDllInstance = NULL;
	adminLevel = 0;
}

//定义全局变量 theApp  整个工程只要包含 App头文件都可以访问
// The one and only CAccountApp object

CAccountApp theApp;


// CAccountApp initialization

BOOL CAccountApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	HANDLE hEvent;
	UINT   cTries = 0;
	// 创建一个名字事件   避免启动多个程序 
	// Create a named event
	hEvent = CreateEvent(NULL, TRUE, FALSE, _T("兰新高铁网管台帐"));
	if (hEvent != NULL)
	{ 
		// If the event already existed, that means there's another copy of our app
		// already running
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			do
			{
				// Just in case the other window needs to finish initialization
				Sleep(cTries ? 250 : 0);

				// Try to find the other application window
				CWnd* pwnd = CWnd::FindWindow(NULL,_T("兰新高铁网管台帐"));
				if(pwnd)
				{
					CWnd* pwndLast = pwnd->GetLastActivePopup();
					if(!pwndLast)
					{
						exit(1);
						return FALSE;
					}

					pwndLast->SetForegroundWindow();
					exit(1);
					return FALSE;
				}
			}
			while (++cTries < 2);  // only try twice

			// If we didn't find the window, the other application was probably
			// shutting down, so we'll just continue
		}
	}

	// 获取当前exe运行路径，先不用管他  目前没用
	getAppCurDir(m_exeFullPath);

	// 登录对话框  若不想验证  可直接屏蔽掉
	CLoginDialog loginDlg;
	if(IDOK==loginDlg.DoModal()) // 登录对话框
	{
		theApp.adminLevel = 1;
	}
	else
	{
		if (loginDlg.m_bIsUser)
		{
		}
		else
		{
			return FALSE;
		}
		theApp.adminLevel = 0;
	}


	// 各站点对话框 
	CAccountDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

