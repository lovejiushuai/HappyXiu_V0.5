// DLL CONTRUCT
#ifdef DLL_EXPORTS
#define DLL_API extern "C" _declspec(dllexport)
#else
#define DLL_API extern "C" _declspec(dllimport)
#endif


#include <string>

using namespace std;


// DLL CONTRUCT
CWnd * __stdcall afxGetMainWnd(void);
CWinApp * __stdcall afxGetApp(void);


int WINAPI StartDll(HWND AppHwnd,HINSTANCE &m_hAccount,CWinApp **ppDllApp);

